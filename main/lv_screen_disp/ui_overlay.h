#ifndef UI_OVERLAY_H
#define UI_OVERLAY_H

#include <stdio.h>
#include "lvgl.h"








typedef enum 
{
    UI_TYPE_ERROR = 0,

    UI_TYPE_PANEL_LEFT,
    UI_TYPE_BTN_LEFT_HOME,
    UI_TYPE_BTN_LEFT_CTRL,
    UI_TYPE_BTN_LEFT_PRINT,
    UI_TYPE_BTN_LEFT_SETTING,
    UI_TYPE_BTN_LEFT_PRINTERS,

    UI_TYPE_PANEL_TOP,

    UI_TYPE_BTN_TOP_CTRL_AXIS,
    UI_TYPE_BTN_TOP_CTRL_FILAMENT,

    UI_TYPE_BTN_TOP_PRINT_MICROSDCARD,
    UI_TYPE_BTN_TOP_PRINT_USB_FLASH_DRIVER,

    UI_TYPE_BTN_TOP_SETTING_GENERAL,
    UI_TYPE_BTN_TOP_SETTING_NETWORK,

    UI_TYPE_DELETE_DEVICE,
    UI_TYPE_PRESERVE_DEVICE,
    UI_TYPE_KEYBOARD_LABEL_TITLE,
    UI_TYPE_KEYBOARD_TEXTAREA_TXT,
    UI_TYPE_KEYBOARD_BTN_PWD_MODE,
    UI_TYPE_KEYBOARD_BTN_OK,
    UI_TYPE_KEYBOARD_BTN_CANCEL,
    UI_TYPE_KEYBOARD_BTN_MOVING_ADD,
    UI_TYPE_KEYBOARD_BTN_MOVING_REDUCE,
    UI_TYPE_RESET,
    UI_TYPE_SCREEN_HOME = (1 << 31) | (UI_TYPE_BTN_LEFT_HOME << 16),
    UI_TYPE_SCREEN_CTRL = (1 << 31) | (UI_TYPE_BTN_LEFT_CTRL << 16),
    UI_TYPE_SCREEN_PRINT = (1 << 31) | (UI_TYPE_BTN_LEFT_PRINT << 16),
    UI_TYPE_SCREEN_SETTING = (1 << 31) | (UI_TYPE_BTN_LEFT_SETTING << 16),
    UI_TYPE_SCREEN_PRINTERS = (1 << 31) | (UI_TYPE_BTN_LEFT_PRINTERS << 16),

    UI_TYPE_SCREEN_CTRL_AXIS = UI_TYPE_SCREEN_CTRL | (UI_TYPE_BTN_TOP_CTRL_AXIS << 0),
    UI_TYPE_SCREEN_CTRL_FILAMENT = UI_TYPE_SCREEN_CTRL | (UI_TYPE_BTN_TOP_CTRL_FILAMENT << 0),
    UI_TYPE_SCREEN_PRINT_MICROSDCARD = UI_TYPE_SCREEN_PRINT | (UI_TYPE_BTN_TOP_PRINT_MICROSDCARD << 0),
    UI_TYPE_SCREEN_PRINT_USB_FLASH_DRIVER = UI_TYPE_SCREEN_PRINT | (UI_TYPE_BTN_TOP_PRINT_USB_FLASH_DRIVER << 0),
    UI_TYPE_SCREEN_SETTING_GENERAL = UI_TYPE_SCREEN_SETTING | (UI_TYPE_BTN_TOP_SETTING_GENERAL << 0),
    UI_TYPE_SCREEN_SETTING_NETWORK = UI_TYPE_SCREEN_SETTING | (UI_TYPE_BTN_TOP_SETTING_NETWORK << 0),

} ui_type_t;



/* 封装API */
lv_obj_t *ui_obj_get(lv_obj_t *parent, ui_type_t type);
lv_obj_t *ui_obj_get(lv_obj_t *parent, ui_type_t type);
void ui_del_myself_clicked(lv_event_t *e);
void ui_obj_set_type(lv_obj_t *obj, ui_type_t type);

lv_obj_t *ui_PanelXY_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y, lv_coord_t radius, lv_color_t bg_c);
lv_obj_t *ui_btn_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y, lv_coord_t radius, lv_color_t bg_c);
lv_obj_t *ui_image_create(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, const void *image);
lv_obj_t *ui_btn_image_create(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, const char * txt, int seconds, const void *image,const void *image1);
lv_obj_t *ui_label_create(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, const char *text, const lv_font_t *fonts);
lv_obj_t *ui_List_create(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, lv_color_t bg_c, lv_coord_t hor, lv_coord_t row, lv_coord_t top);
lv_obj_t *ui_ListBtn_create(lv_obj_t *parent, lv_coord_t h, lv_color_t bg_c, lv_coord_t hor, lv_coord_t row, lv_coord_t top, const char *text, lv_coord_t text_x, lv_coord_t text_y,
                            const char *text1, lv_coord_t text1_x, lv_coord_t text1_y, const void *img, lv_coord_t img_x);
lv_obj_t *ui_btnmatrix_create(lv_obj_t *parent, const char **btnm_text, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y,
                              lv_coord_t x1, lv_coord_t y1, uint16_t btn_id, lv_color_t btn_bg, lv_color_t btn_border_bg, lv_color_t bg_c);
lv_obj_t *ui_TextArea_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t x, lv_coord_t y, lv_coord_t radius);
lv_obj_t *ui_btn_img_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y, lv_coord_t radius, lv_color_t bg_c, const void *bg_img_src);
lv_obj_t *ui_Arc_create(lv_obj_t *parent);
lv_obj_t *ui_Arc_Print_create(lv_obj_t *parent);
lv_obj_t *ui_slider_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h,lv_coord_t x, lv_coord_t y, lv_coord_t radius);
lv_obj_t *ui_key_textarea_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h,lv_coord_t x, lv_coord_t y);
lv_obj_t *ui_keyboard_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y);
lv_obj_t *ui_bar_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y);
lv_obj_t *ui_line_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_color_t bg_c);
lv_obj_t *ui_btn_img_createe(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t radius, lv_color_t bg_c, const void *bg_img_src);
lv_obj_t *ui_btn_label_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t radius, lv_color_t bg_c, const char *text);
lv_obj_t *ui_line_createe(lv_obj_t *parent, const lv_point_t *points, uint16_t num, lv_coord_t w, lv_color_t color);
lv_obj_t *ui_panel_create(lv_obj_t *parent, lv_coord_t radius, lv_color_t bg_c);
lv_obj_t *lv_Spinner_create(lv_obj_t *parent);











#endif