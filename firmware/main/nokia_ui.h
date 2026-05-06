#ifndef NOKIA_UI_H
#define NOKIA_UI_H

#include "u8g2.h"

class NokiaUi {
public:
    explicit NokiaUi(u8g2_t *display);

    void render_main_page(const char *time_text, const char *network_name);
    void render_secondary_page();

    void draw_footer_menu();
    void draw_signal_bars();
    void draw_battery_bars();

private:
    void begin_frame();
    void draw_secondary_icon();

    u8g2_t *display_;
};

#endif // NOKIA_UI_H
