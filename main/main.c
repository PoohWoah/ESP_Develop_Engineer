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
void app_main(void)
{
   lvgl_hal_init();
   lv_obj_t *screen = lv_obj_create(lv_scr_act());
   lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
   lv_obj_set_style_bg_color(screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
   lv_obj_set_style_bg_opa(screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
   lv_obj_clear_flag(screen, LV_OBJ_FLAG_CLICKABLE);
   while (1)
   {
      lv_timer_handler();
      vTaskDelay(50);
   }
}
