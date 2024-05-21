idf_component_register(
    SRCS 
    "main.c"
    "lvgl_hal.c" 
    "esp_psram.c"
    "ui/fonts/opensansb12.c"
    "ui/fonts/opensansb16.c"
    "ui/fonts/opensansb20.c"
    "ui/fonts/opensansb24.c"         
    INCLUDE_DIRS 
    "."
    "ui"

    )
