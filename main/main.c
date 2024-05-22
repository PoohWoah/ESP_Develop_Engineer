/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "lvgl_hal.h"
#include "lv_screen_disp/lv_screen_home.h"
#include "ui.h"
#include "esp_lcd_touch_gt911.h"
extern esp_lcd_touch_handle_t tp;
void app_main(void)
{
   lvgl_hal_init();
   lv_obj_t *screen = lv_obj_create(lv_scr_act());
   lv_obj_set_width(screen, 800);
   lv_obj_set_height(screen, 480);
   lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
   lv_obj_set_style_bg_color(screen, lv_color_hex(0xFD3636), LV_PART_MAIN | LV_STATE_DEFAULT);
   lv_obj_set_style_bg_opa(screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
   lv_obj_clear_flag(screen, LV_OBJ_FLAG_CLICKABLE);
   lv_obj_align(screen, LV_ALIGN_CENTER, 0, 0);
   ui_homescreen_guide_init();
   lv_disp_load_scr(navigationscreen);

   lv_obj_t *img;

   img = lv_img_create(lv_scr_act());
   lv_img_set_src(img, &wink_png);
   lv_obj_align(img, LV_ALIGN_LEFT_MID, 20, 0);

   while (1)
   { 
      lv_timer_handler();
      vTaskDelay(500);
   }
}
