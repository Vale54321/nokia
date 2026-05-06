#include "nokia_font.h"

NokiaChar nokiaFont[256];

void init_nokia_font() {
    nokiaFont['0'] = {5, 8, {0x3E, 0x7F, 0x41, 0x7F, 0x3E}};
    nokiaFont['1'] = {5, 8, {0x00, 0x02, 0x7F, 0x7F, 0x00}};
    nokiaFont['2'] = {5, 8, {0x71, 0x79, 0x49, 0x4F, 0x46}};
    nokiaFont['3'] = {5, 8, {0x41, 0x49, 0x49, 0x7F, 0x36}};
    nokiaFont['4'] = {5, 8, {0x18, 0x14, 0x12, 0x7F, 0x7F}};
    nokiaFont['5'] = {5, 8, {0x47, 0x45, 0x45, 0x7D, 0x38}};
    nokiaFont['6'] = {5, 8, {0x3E, 0x7F, 0x45, 0x7D, 0x38}};
    nokiaFont['7'] = {5, 8, {0x01, 0x71, 0x7D, 0x0F, 0x03}};
    nokiaFont['8'] = {5, 8, {0x36, 0x7F, 0x49, 0x7F, 0x36}};
    nokiaFont['9'] = {5, 8, {0x0E, 0x5F, 0x51, 0x7F, 0x3E}};

    // big letters
    nokiaFont['A'] = {5, 8, {0x7E, 0x7F, 0x11, 0x7F, 0x7E}};
    nokiaFont['H'] = {5, 8, {0x7F, 0x7F, 0x04, 0x7F, 0x7F}};
    nokiaFont['K'] = {6, 8, {0x7F, 0x7F, 0x1C, 0x36, 0x63, 0x41}};
    nokiaFont['M'] = {7, 8, {0x7F, 0x7E, 0x0C, 0x18, 0x0C, 0x7E, 0x7F}};
    nokiaFont['N'] = {6, 8, {0x7F, 0x7E, 0x0C, 0x18, 0x3F, 0x7F}};
    nokiaFont['R'] = {5, 8, {0x7F, 0x7F, 0x31, 0x7F, 0x4E}};
    nokiaFont['S'] = {4, 8, {0x46, 0x4F, 0x79, 0x31}};
    nokiaFont['T'] = {6, 8, {0x01, 0x01, 0x7F, 0x7F, 0x01, 0x01}};
    nokiaFont['V'] = {6, 8, {0x07, 0x1F, 0x78, 0x78, 0x1F, 0x07}};

    // small letters
    nokiaFont['a'] = {5, 8, {0x20, 0x74, 0x54, 0x7C, 0x78}};
    nokiaFont['b'] = {5, 8, {0x7F, 0x7F, 0x44, 0x7C, 0x38}};
    nokiaFont['c'] = {4, 8, {0x38, 0x7C, 0x44, 0x44}};
    nokiaFont['d'] = {5, 8, {0x38, 0x7C, 0x44, 0x7F, 0x7F}};
    nokiaFont['e'] = {5, 8, {0x38, 0x7C, 0x54, 0x5C, 0x58}};
    nokiaFont['f'] = {3, 8, {0x7E, 0x7F, 0x05}};
    nokiaFont['g'] = {5, 8, {0x18, 0xBC, 0xA4, 0xFC, 0x7C}};
    nokiaFont['h'] = {5, 8, {0x7F, 0x7F, 0x04, 0x7C, 0x78}};
    nokiaFont['i'] = {2, 8, {0x7D, 0x7D}};
    nokiaFont['j'] = {3, 8, {0x80, 0xFD, 0x7D}};
    nokiaFont['k'] = {5, 8, {0x7F, 0x7F, 0x38, 0x6C, 0x44}};
    nokiaFont['l'] = {2, 8, {0x7F, 0x7F}};
    nokiaFont['m'] = {8, 8, {0x7C, 0x7C, 0x04, 0x7C, 0x7C, 0x04, 0x7C, 0x78}};
    nokiaFont['n'] = {5, 8, {0x7C, 0x7C, 0x04, 0x7C, 0x78}};
    nokiaFont['o'] = {5, 8, {0x38, 0x7C, 0x44, 0x7C, 0x38}};
    nokiaFont['p'] = {5, 8, {0xFC, 0xFC, 0x24, 0x3C, 0x18}};
    nokiaFont['q'] = {5, 8, {0x18, 0x3C, 0x24, 0xFC, 0xFC}};
    nokiaFont['r'] = {4, 8, {0x7C, 0x7C, 0x08, 0x0C}};
    nokiaFont['s'] = {4, 8, {0x58, 0x5C, 0x74, 0x34}};
    nokiaFont['t'] = {3, 8, {0x3F, 0x7F, 0x44}};
    nokiaFont['u'] = {5, 8, {0x3C, 0x7C, 0x40, 0x7C, 0x7C}};
    nokiaFont['v'] = {5, 8, {0x0C, 0x3C, 0x70, 0x3C, 0x0C}};
    nokiaFont['w'] = {7, 8, {0x1C, 0x7C, 0x60, 0x38, 0x60, 0x7C, 0x1C}};
    nokiaFont['x'] = {5, 8, {0x6C, 0x7C, 0x10, 0x7C, 0x6C}};
    nokiaFont['y'] = {5, 8, {0x1C, 0xBC, 0xA0, 0xFC, 0x7C}};
    nokiaFont['z'] = {5, 8, {0x64, 0x74, 0x5C, 0x4C, 0x44}};

    // umlaute
    nokiaFont['\xE4'] = {5, 8, {0x20, 0x75, 0x54, 0x7D, 0x78}};
    nokiaFont['\xF6'] = {5, 8, {0x38, 0x7D, 0x44, 0x7D, 0x38}};
    nokiaFont['\xFC'] = {5, 8, {0x3C, 0x7D, 0x40, 0x7D, 0x7C}};

    // symbols
    nokiaFont['.'] = {2, 8, {0x60, 0x60}};
    nokiaFont[':'] = {2, 8, {0x6C, 0x6C}};
    nokiaFont['+'] = {5, 8, {0x08, 0x08, 0x3E, 0x08, 0x08}};
    nokiaFont['-'] = {4, 8, {0x10, 0x10, 0x10, 0x10}};
}

// Zeichnet einen einzelnen Nokia-Buchstaben
void draw_nokia(u8g2_t *u8g2, int x, int y, NokiaChar nChar) {
    if (nChar.width == 0) return;
    for (int col = 0; col < nChar.width; col++) {
        for (int row = 0; row < nChar.height; row++) {
            if (nChar.data[col] & (1 << row)) {
                u8g2_DrawPixel(u8g2, N_X(x + col), N_Y(y + row));
            }
        }
    }
}

// Zeichnet eine ganze Zeichenkette
void draw_nokia_text(u8g2_t *u8g2, int x, int y, const char *text) {
    int current_x = x;
    while (*text) {
        uint8_t c = (uint8_t)*text;
        if (c == ' ') {
            current_x += 4; 
        } else if (nokiaFont[c].width > 0) {
            draw_nokia(u8g2, current_x, y, nokiaFont[c]);
            current_x += nokiaFont[c].width + 1; // 1px Abstand zwischen Buchstaben
        }
        text++;
    }
}

// Berechnet die Breite eines Textes in Pixeln
int calculate_text_width(const char *text) {
    int width = 0;
    while (*text) {
        uint8_t c = (uint8_t)*text;
        if (c == ' ') {
            width += 4;
        } else if (nokiaFont[c].width > 0) {
            width += nokiaFont[c].width + 1; // Charakter + 1px Abstand
        }
        text++;
    }
    // Entferne den letzten 1px Abstand (wird nicht benötigt)
    return width > 0 ? width - 1 : 0;
}

// Zeichnet zentrierten Text (horizontal zentriert auf 84px Nokia-Bereich)
void draw_nokia_text_centered(u8g2_t *u8g2, int y, const char *text) {
    int text_width = calculate_text_width(text);
    int x = (84 - text_width) / 2; // 84px ist die Nokia-Breite
    draw_nokia_text(u8g2, x, y, text);
}

// Zeichnet rechtsbündig ausgerichteten Text
void draw_nokia_text_right_aligned(u8g2_t *u8g2, int right_offset, int y, const char *text) {
    int text_width = calculate_text_width(text);
    int x = 84 - text_width - right_offset; // 84px ist die Nokia-Breite
    draw_nokia_text(u8g2, x, y, text);
}
