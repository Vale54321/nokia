#ifndef NOKIA_FONT_H
#define NOKIA_FONT_H

#include <stdint.h>
#include "u8g2.h"

// Makros zur Positionierung des 84x48 Nokia-Fensters auf dem 128x64 OLED
#define N_X(x) (x + 22)
#define N_Y(y) (y + 8)

typedef struct {
    uint8_t width;
    uint8_t height;
    uint8_t data[8];
} NokiaChar;

extern NokiaChar nokiaFont[256];

void init_nokia_font();
void draw_nokia(u8g2_t *u8g2, int x, int y, NokiaChar nChar);
void draw_nokia_text(u8g2_t *u8g2, int x, int y, const char *text);
int calculate_text_width(const char *text);
void draw_nokia_text_centered(u8g2_t *u8g2, int y, const char *text);
void draw_nokia_text_right_aligned(u8g2_t *u8g2, int right_offset, int y, const char *text);

#endif // NOKIA_FONT_H
