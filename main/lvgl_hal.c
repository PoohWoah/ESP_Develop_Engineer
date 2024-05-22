// #include "lvgl_hal.h"
#include <stdio.h>
#include "sdkconfig.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_psram.h"
#include "esp_psram.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "lv_demos.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "GT911.h"
#include "pinout.h"
#include "esp_lcd_touch_gt911.h"

#define SW_PRINT_LCD 1

#if SW_PRINT_LCD
#include "esp_log.h"
static const char *TAG = "LCD:";
#define PRINT_LCD(fmt, args...) ESP_LOGW(TAG, fmt, ##args)
#else
#define PRINT_UTILS(...)
#endif

// #define CONFIG_EXAMPLE_AVOID_TEAR_EFFECT_WITH_SEM 1
// #define CONFIG_EXAMPLE_DOUBLE_FB 1
#if CONFIG_EXAMPLE_DOUBLE_FB
#define EXAMPLE_LCD_NUM_FB 2
#else
#define EXAMPLE_LCD_NUM_FB 1
#endif

// we use two semaphores to sync the VSYNC event and the LVGL task, to avoid potential tearing effect
#if CONFIG_EXAMPLE_AVOID_TEAR_EFFECT_WITH_SEM
SemaphoreHandle_t sem_vsync_end;
SemaphoreHandle_t sem_gui_ready;
#endif

static bool example_on_vsync_event(esp_lcd_panel_handle_t panel, const esp_lcd_rgb_panel_event_data_t *event_data, void *user_data)
{
    BaseType_t high_task_awoken = pdFALSE;
#if CONFIG_EXAMPLE_AVOID_TEAR_EFFECT_WITH_SEM
    if (xSemaphoreTakeFromISR(sem_gui_ready, &high_task_awoken) == pdTRUE)
    {
        xSemaphoreGiveFromISR(sem_vsync_end, &high_task_awoken);
    }
#endif
    return high_task_awoken == pdTRUE;
}

static void usr_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)disp->user_data;
#if CONFIG_EXAMPLE_AVOID_TEAR_EFFECT_WITH_SEM
    xSemaphoreGive(sem_gui_ready);
    xSemaphoreTake(sem_vsync_end, portMAX_DELAY);
#endif
    esp_lcd_panel_draw_bitmap(panel_handle, area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_p);
    lv_disp_flush_ready(disp);
}

void usr_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

esp_lcd_panel_handle_t rgb_panel_initialization(void)
{
    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_rgb_panel_config_t panel_config = {
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .timings = {
            .pclk_hz = LCD_PCLK_HZ,
            .h_res = LCD_H_RES,
            .v_res = LCD_V_RES,
            .hsync_pulse_width = LCD_HSYNC_PULSE_WIDTH,
            .hsync_back_porch = LCD_HSYNC_BACK_PORCH,
            .hsync_front_porch = LCD_HSYNC_FRONT_PORCH,
            .vsync_pulse_width = LCD_VSYNC_PULSE_WIDTH,
            .vsync_back_porch = LCD_VSYNC_BACK_PORCH,
            .vsync_front_porch = LCD_VSYNC_FRONT_PORCH,
            .flags = {
                .pclk_active_neg = true, // 用来控制 LCD 面板的像素时钟(PCLK)极性的。根据 LCD 面板的数据手册来查看 PCLK 的极性要求
            },
        },
        .data_width = 16,
        .num_fbs = EXAMPLE_LCD_NUM_FB,
#define CONFIG_EXAMPLE_USE_BOUNCE_BUFFER 1
#if CONFIG_EXAMPLE_USE_BOUNCE_BUFFER
        .bounce_buffer_size_px = 10 * LCD_H_RES,
#endif
        .psram_trans_align = 64,
        .bits_per_pixel = 16,
        .hsync_gpio_num = LCD_HSYNC_PIN,
        .vsync_gpio_num = LCD_VSYNC_PIN,
        .de_gpio_num = LCD_DE_PIN,
        .pclk_gpio_num = LCD_PCLK_PIN,
        .disp_gpio_num = LCD_DISP_PIN,
        .data_gpio_nums = {
            LCD_B3_PIN,
            LCD_B4_PIN,
            LCD_B5_PIN,
            LCD_B6_PIN,
            LCD_B7_PIN,
            LCD_G2_PIN,
            LCD_G3_PIN,
            LCD_G4_PIN,
            LCD_G5_PIN,
            LCD_G6_PIN,
            LCD_G7_PIN,
            LCD_R3_PIN,
            LCD_R4_PIN,
            LCD_R5_PIN,
            LCD_R6_PIN,
            LCD_R7_PIN,
        },
        .flags.fb_in_psram = 1,
        // .double_fb = 1,
        // .refresh_on_demand = 1,
        // allocate frame buffer in PSRAM
        // .flags.refresh_on_demand = refresh_on_demand,
    };
    esp_lcd_new_rgb_panel(&panel_config, &panel_handle);
    esp_lcd_panel_reset(panel_handle);
    esp_lcd_panel_init(panel_handle);

    return panel_handle;
}

static esp_lcd_panel_handle_t esp_panel;

void lvgl_hal_init(void)
{

#if CONFIG_EXAMPLE_AVOID_TEAR_EFFECT_WITH_SEM
    sem_vsync_end = xSemaphoreCreateBinary();
    assert(sem_vsync_end);
    sem_gui_ready = xSemaphoreCreateBinary();
    assert(sem_gui_ready);
#endif
    // must static
    esp_panel = rgb_panel_initialization();

    void *buf1 = NULL;
    void *buf2 = NULL;
#if CONFIG_EXAMPLE_DOUBLE_FB
    ESP_ERROR_CHECK(esp_lcd_rgb_panel_get_frame_buffer(panel_handle, 2, &buf1, &buf2));
#else
    buf1 = esp_psram_malloc(LCD_H_RES * LCD_V_RES * sizeof(lv_color_t));
    buf2 = esp_psram_malloc(LCD_H_RES * LCD_V_RES * sizeof(lv_color_t));
    memset(buf1, 0x00, LCD_H_RES * LCD_V_RES * sizeof(lv_color_t));
#endif
    gpio_set_direction(LCD_BL_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LCD_BL_PIN, 0);
    gpio_set_direction(LCD_RESET_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LCD_RESET_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(100));
    gpio_set_level(LCD_RESET_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(LCD_BL_PIN, 1);

    lv_init();

    // must static
    static lv_disp_draw_buf_t draw_buf;
    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, LCD_H_RES * LCD_V_RES);

    /*Initialize the display*/
    // must static
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LCD_H_RES;
    disp_drv.ver_res = LCD_V_RES;
    disp_drv.flush_cb = usr_disp_flush;
    // disp_drv.sw_rotate = 1;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.user_data = esp_panel; // esp_lcd_rgb_panel_get_frame_buffer(esp_panel);
    lv_disp_drv_register(&disp_drv);
    //  lv_disp_set_rotation(NULL, LV_DISP_ROT_180);
#if CONFIG_EXAMPLE_DOUBLE_FB
    disp_drv.full_refresh = true; // the full_refresh mode can maintain the synchronization between the two frame buffers
#endif
    lv_disp_drv_register(&disp_drv);
    esp_lcd_rgb_panel_event_callbacks_t cbs = {
        .on_vsync = example_on_vsync_event,
    };
    esp_lcd_rgb_panel_register_event_callbacks(esp_panel, &cbs, &disp_drv);

    GT911_init();
    /* set background color to black (default white) */
    // lv_obj_set_style_bg_color(lv_scr_act(), LV_COLOR_MAKE(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
}

uint16_t *rgb_ldc_get_fb(void)
{
    void *p_buf;
    esp_lcd_rgb_panel_get_frame_buffer(esp_panel, 1, &p_buf);
    return (uint16_t *)p_buf;
}
