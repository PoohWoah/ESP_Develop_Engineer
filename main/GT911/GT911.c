#include <stdio.h>

#include "driver/i2c.h"
#include "esp_lcd_touch_gt911.h"
#include "lvgl.h"
#include "pinout.h"
#define TOUCH_SWAP_XY false
#define TOUCH_MIRROR_X false
#define TOUCH_MIRROR_Y false

#define SW_PRINT_UTILS 1

#if SW_PRINT_UTILS
#include "esp_log.h"
static const char *TAG = "LCD_TOUCH:";
#define PRINT_UTILS(fmt, args...) ESP_LOGW(TAG, fmt, ##args)
#else
#define PRINT_UTILS(...)
#endif
void i2c_init(void)
{
    // 初始化一组i2c，如果使用已经注册的则可以不要这个步骤
    const i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C0_SDA_PIN,
        .scl_io_num = I2C0_SCL_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C0_SPEED,
    };
    ESP_ERROR_CHECK(i2c_param_config(GT911_I2C, &i2c_config));
    ESP_ERROR_CHECK(i2c_driver_install(GT911_I2C, i2c_config.mode, 0, 0, 0));
}

static void lvgl_touch_cb(lv_indev_drv_t * drv, lv_indev_data_t * data)
{
    uint16_t touchpad_x[1] = {0};
    uint16_t touchpad_y[1] = {0};
    uint8_t touchpad_cnt = 0;

    /* Read touch controller data */
    esp_lcd_touch_read_data(drv->user_data);

    /* Get coordinates */
    bool touchpad_pressed = esp_lcd_touch_get_coordinates(drv->user_data, touchpad_x, touchpad_y, NULL, &touchpad_cnt, 1);

    if (touchpad_pressed && touchpad_cnt > 0) {
        data->point.x = touchpad_x[0];
        data->point.y = touchpad_y[0];
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}
void GT911_init(void)
{
    i2c_init();
    esp_lcd_touch_handle_t tp = NULL;
    esp_lcd_panel_io_handle_t tp_io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();
    int i = 0;
    PRINT_UTILS("Initialize touch IC IO (I2C)%d", i);
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c((esp_lcd_i2c_bus_handle_t)GT911_I2C, &tp_io_config, &tp_io_handle));
    // 初始化gt911
    const esp_lcd_touch_config_t tp_cfg = {
        .x_max = LCD_H_RES,
        .y_max = LCD_V_RES,
        .levels = {
            .reset = GT911_RST_PIN,
            .interrupt = GT911_IRQ_PIN,
        },
        .flags = {
            .swap_xy = TOUCH_SWAP_XY,
            .mirror_x = TOUCH_MIRROR_X,
            .mirror_y = TOUCH_MIRROR_Y,
        },
    };
    /* Initialize touch */
    PRINT_UTILS( "Initialize touch controller GT911%d",i);
    esp_lcd_touch_new_i2c_gt911(tp_io_handle, &tp_cfg, &tp);
    PRINT_UTILS( "Init touch ic GT911 OK.%d.",i);

    static lv_indev_drv_t indev_drv; // Input device driver (Touch)
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    // indev_drv.disp = disp;
    indev_drv.read_cb = lvgl_touch_cb;
    indev_drv.user_data = tp;

    lv_indev_drv_register(&indev_drv);

    PRINT_UTILS( "LVGL TCP register OK%d",i);
}
