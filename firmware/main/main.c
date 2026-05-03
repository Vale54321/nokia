#include <stdio.h>
#include "esp_partition.h"

#include "u8g2_esp32_hal.h"
#include "u8g2.h"

#define PIN_SDA 19
#define PIN_SCL 18

void app_main(void)
{
    printf("Nokia 3210 OS - Partition Check\n");
    
    // Suche nach der Speicher-Partition
    const esp_partition_t *storage_part = esp_partition_find_first(
        ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_SPIFFS, "storage");

    if (storage_part != NULL) {
        printf("Partition 'storage' gefunden! Groesse: %ld Bytes\n", storage_part->size);
    } else {
        printf("FEHLER: Partition 'storage' nicht gefunden!\n");
    }

    // HAL konfigurieren
    u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
    u8g2_esp32_hal.sda = (gpio_num_t)PIN_SDA;
    u8g2_esp32_hal.scl = (gpio_num_t)PIN_SCL;
    u8g2_esp32_hal_init(u8g2_esp32_hal);

    u8g2_t u8g2;
    // WICHTIG: Nutze SH1106 für das 1.3" Modell
    u8g2_Setup_sh1106_i2c_128x64_noname_f(
        &u8g2, 
        U8G2_R0, 
        u8g2_esp32_i2c_byte_cb, 
        u8g2_esp32_gpio_and_delay_cb
    );

    u8x8_SetI2CAddress(&u8g2.u8x8, 0x3C << 1); 
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);
    u8g2_ClearBuffer(&u8g2);

    // Nokia "Splash Screen"
    u8g2_SetFont(&u8g2, u8g2_font_unifont_t_symbols);
    u8g2_DrawStr(&u8g2, 35, 35, "NOKIA"); 
    u8g2_SendBuffer(&u8g2);
}