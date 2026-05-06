#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "esp_sntp.h"
#include "esp_log.h"
#include "lwip/ip4_addr.h"
#include "driver/gpio.h"

extern "C" {
    #include "u8g2.h"
    #include "u8g2_esp32_hal.h"
}

#include "nokia_font.h"
#include "nokia_ui.h"

#define WIFI_SSID      "Valentin-Netz"
#define WIFI_PASS      "nordpfeil"

// Pin Definitionen für I2C
#define PIN_SDA 19
#define PIN_SCL 18

// Button-Pin: Taster zwischen GPIO und GND, interner Pull-up aktiv
#define PIN_BUTTON 27

// WiFi status cached by event handler
static bool s_wifi_connected = false;
static esp_ip4_addr_t s_wifi_ip = {0};

enum class ScreenPage {
    Main,
    Secondary,
};

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    if (event_base == WIFI_EVENT) {
        if (event_id == WIFI_EVENT_STA_START) {
            esp_wifi_connect();
        } else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
            s_wifi_connected = false;
            s_wifi_ip.addr = 0;
            esp_wifi_connect();
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        s_wifi_connected = true;
        s_wifi_ip = event->ip_info.ip;
    }
}

void wifi_init() {
    esp_err_t nvs_ret = nvs_flash_init();
    if (nvs_ret == ESP_ERR_NVS_NO_FREE_PAGES || nvs_ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        nvs_ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(nvs_ret);

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL));

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {};
    strncpy((char *)wifi_config.sta.ssid, WIFI_SSID, sizeof(wifi_config.sta.ssid) - 1);
    strncpy((char *)wifi_config.sta.password, WIFI_PASS, sizeof(wifi_config.sta.password) - 1);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void time_init() {
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");
    esp_sntp_init();
    setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
    tzset();
}

void button_init() {
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = 1ULL << PIN_BUTTON;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    ESP_ERROR_CHECK(gpio_config(&io_conf));
}

// Liest die bekannte IPv4-Adresse des WLAN-STA und schreibt sie in out_buffer.
void get_wifi_ip_text(char *out_buffer, size_t out_buffer_size) {
    if (out_buffer == NULL || out_buffer_size == 0) return;
    if (!s_wifi_connected || s_wifi_ip.addr == 0) {
        snprintf(out_buffer, out_buffer_size, "verbinde...");
        return;
    }
    snprintf(
        out_buffer,
        out_buffer_size,
        "%u.%u.%u.%u",
        esp_ip4_addr1(&s_wifi_ip),
        esp_ip4_addr2(&s_wifi_ip),
        esp_ip4_addr3(&s_wifi_ip),
        esp_ip4_addr4(&s_wifi_ip)
    );
}

// --- 3. HAUPTPROGRAMM ---

extern "C" void app_main(void)
{
    // Initialisierungen
    init_nokia_font();
    wifi_init();
    time_init();
    button_init();

    u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
    u8g2_esp32_hal.bus.i2c.scl = (gpio_num_t)PIN_SCL;
    u8g2_esp32_hal.bus.i2c.sda = (gpio_num_t)PIN_SDA;
    u8g2_esp32_hal_init(u8g2_esp32_hal);

    u8g2_t u8g2;
    u8g2_Setup_sh1106_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8g2_esp32_i2c_byte_cb, u8g2_esp32_gpio_and_delay_cb);
    u8x8_SetI2CAddress(&u8g2.u8x8, 0x3C << 1); 
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    NokiaUi ui(&u8g2);

    char time_str[6];
    char ip_str[16];
    ScreenPage current_page = ScreenPage::Main;
    int last_button_level = 1;
    TickType_t last_toggle_tick = 0;

    while (1) {
        time_t now;
        struct tm timeinfo;
        time(&now);
        localtime_r(&now, &timeinfo);
        strftime(time_str, sizeof(time_str), "%H:%M", &timeinfo);
        get_wifi_ip_text(ip_str, sizeof(ip_str));

        int button_level = gpio_get_level((gpio_num_t)PIN_BUTTON);
        TickType_t now_ticks = xTaskGetTickCount();
        if (last_button_level == 1 && button_level == 0 && (now_ticks - last_toggle_tick) > pdMS_TO_TICKS(200)) {
            current_page = (current_page == ScreenPage::Main) ? ScreenPage::Secondary : ScreenPage::Main;
            last_toggle_tick = now_ticks;
        }
        last_button_level = button_level;

        if (current_page == ScreenPage::Main) {
            ui.render_main_page(time_str, WIFI_SSID);
        } else {
            ui.render_secondary_page();
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

