idf_component_register(SRCS "nokia_font.cpp" "nokia_ui.cpp" "main.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES u8g2 u8g2-hal-esp-idf driver esp_wifi esp_event nvs_flash)