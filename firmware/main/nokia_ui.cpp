#include "nokia_ui.h"

#include "nokia_font.h"

namespace {
// 16x6 icon, one bit per pixel, row-major.
// Bit value 1 means draw black, 0 means leave white.
static const uint16_t kSecondaryIconRows[] = {
    0x0FFF, // wwwwssssssssssss
    0x1086, // wwwswwwwswwwwssw
    0x210C, // wwswwwwswwwwssww
    0x4218, // wswwwwswwwwsswww
    0xFFF0, // sssssssssssswwww
    0x7FE0  // wsssssssssswwwww
};
} // namespace

NokiaUi::NokiaUi(u8g2_t *display) : display_(display) {
}

void NokiaUi::begin_frame() {
    u8g2_ClearBuffer(display_);

    // Weißer Nokia-Bereich auf dem OLED
    u8g2_SetDrawColor(display_, 1);
    u8g2_DrawBox(display_, 20, 6, 88, 52);

    // Schwarze Tinte für die UI-Elemente
    u8g2_SetDrawColor(display_, 0);
}

void NokiaUi::draw_signal_bars() {
    u8g2_DrawBox(display_, N_X(0), N_Y(0), 4, 7);
    u8g2_DrawBox(display_, N_X(0), N_Y(8), 3, 7);
    u8g2_DrawBox(display_, N_X(0), N_Y(16), 2, 7);
    u8g2_DrawBox(display_, N_X(0), N_Y(24), 2, 7);

    u8g2_DrawHLine(display_, N_X(0), N_Y(32), 5);
    u8g2_DrawPixel(display_, N_X(0), N_Y(33));
    u8g2_DrawPixel(display_, N_X(2), N_Y(33));
    u8g2_DrawPixel(display_, N_X(4), N_Y(33));
    u8g2_DrawHLine(display_, N_X(1), N_Y(34), 3);
    u8g2_DrawPixel(display_, N_X(2), N_Y(35));
    u8g2_DrawPixel(display_, N_X(2), N_Y(36));
    u8g2_DrawPixel(display_, N_X(2), N_Y(37));
}

void NokiaUi::draw_battery_bars() {
    u8g2_DrawBox(display_, N_X(80), N_Y(0), 4, 7);
    u8g2_DrawBox(display_, N_X(81), N_Y(8), 3, 7);
    u8g2_DrawBox(display_, N_X(82), N_Y(16), 2, 7);
    u8g2_DrawBox(display_, N_X(82), N_Y(24), 2, 7);

    u8g2_DrawPixel(display_, N_X(81), N_Y(32));
    u8g2_DrawPixel(display_, N_X(82), N_Y(32));
    u8g2_DrawHLine(display_, N_X(80), N_Y(33), 4);
    u8g2_DrawPixel(display_, N_X(80), N_Y(34));
    u8g2_DrawPixel(display_, N_X(83), N_Y(34));
    u8g2_DrawPixel(display_, N_X(80), N_Y(35));
    u8g2_DrawPixel(display_, N_X(83), N_Y(35));
    u8g2_DrawPixel(display_, N_X(80), N_Y(36));
    u8g2_DrawPixel(display_, N_X(83), N_Y(36));
    u8g2_DrawHLine(display_, N_X(80), N_Y(37), 4);
}

void NokiaUi::draw_footer_menu() {
    draw_nokia_text_centered(display_, 39, "Men\xFC");
}

void NokiaUi::draw_secondary_icon() {
    for (uint8_t row = 0; row < sizeof(kSecondaryIconRows) / sizeof(kSecondaryIconRows[0]); ++row) {
        uint16_t mask = kSecondaryIconRows[row];
        for (uint8_t col = 0; col < 16; ++col) {
            if (mask & (1U << (15 - col))) {
                u8g2_DrawPixel(display_, N_X(col + 1), N_Y(row));
            }
        }
    }
}

void NokiaUi::render_main_page(const char *time_text, const char *network_name) {
    begin_frame();
    draw_signal_bars();
    draw_battery_bars();
    draw_nokia_text_right_aligned(display_, 7, 0, time_text);
    draw_nokia_text_centered(display_, 9, network_name);
    draw_footer_menu();
    u8g2_SendBuffer(display_);
}

void NokiaUi::render_secondary_page() {
    begin_frame();
    draw_secondary_icon();
    draw_nokia_text(display_, 0, 7, "Andrea");
    draw_nokia_text_right_aligned(display_, 1, 26, "+4915165915063");
    draw_nokia_text_centered(display_, 39, "Anrufen");
    u8g2_SendBuffer(display_);
}
