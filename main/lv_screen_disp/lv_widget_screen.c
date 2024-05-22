#include "ui_overlay.h"
#include "lvgl.h"
#include "ui/ui.h"
lv_obj_t *ui_obj_get(lv_obj_t *parent, ui_type_t type)
{
    if (parent == NULL)
        return NULL;
    for (uint32_t i = 0; i < lv_obj_get_child_cnt(parent); i++)
    {
        lv_obj_t *obj = lv_obj_get_child(parent, i);
        if ((uint32_t)obj->user_data == type)
        {
            return obj;
        }
    }
    return NULL;
}

lv_obj_t *ui_obj_get_type(lv_obj_t *parent, ui_type_t type)
{
    if (parent == NULL)
        return NULL;
    lv_obj_t *obj = lv_obj_get_child(parent, 0);
    lv_obj_t *panel = lv_obj_get_child(obj, 0);
    lv_obj_t *list = lv_obj_get_child(panel, 1);

    for (uint32_t i = 0; i < lv_obj_get_child_cnt(list); i++)
    {

        lv_obj_t *obj = lv_obj_get_child(list, i);
        if ((uint32_t)obj->user_data == type)
        {
            return obj;
        }
    }

    return NULL;
}
// 创建一个面板
lv_obj_t *ui_PanelXY_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y, lv_coord_t radius, lv_color_t bg_c)
{
    lv_obj_t *panel = lv_obj_create(parent);
    lv_obj_set_size(panel, w, h);
    lv_obj_set_pos(panel, x, y);
    lv_obj_set_align(panel, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(panel, radius, LV_PART_MAIN);
    lv_obj_set_style_bg_color(panel, bg_c, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(panel, 255, LV_PART_MAIN);
    lv_obj_set_style_border_width(panel, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(panel, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_opa(panel, 255, LV_PART_MAIN);
    lv_obj_set_style_text_font(panel, &opensansb16, LV_PART_MAIN);

    return panel;
}
// 创建一个按钮
lv_obj_t *ui_btn_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y, lv_coord_t radius, lv_color_t bg_c)
{
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, w, h);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_align(btn, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(btn, radius, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, bg_c, LV_PART_MAIN);
    // lv_obj_set_style_bg_opa(btn, 255, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(btn, lv_color_hex(0xF0F0F0), LV_PART_MAIN);
    lv_obj_set_style_text_opa(btn, 255, LV_PART_MAIN);

    return btn;
}
// 创建图片
lv_obj_t *ui_image_create(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, const void *image)
{
    lv_obj_t *img = lv_img_create(parent);
    lv_img_set_src(img, image);
    lv_obj_set_width(img, LV_SIZE_CONTENT);
    lv_obj_set_height(img, LV_SIZE_CONTENT);
    lv_obj_set_pos(img, x, y);
    lv_obj_set_align(img, LV_ALIGN_CENTER);
    return img;
}

lv_obj_t *ui_btn_image_create(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, const char *txt, int seconds, const void *image, const void *image1)
{
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, 147.5, 174);
    lv_obj_align(btn, LV_ALIGN_CENTER, x, y);
    lv_obj_set_style_radius(btn, 8, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x363636), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(btn, 255, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(btn, lv_color_hex(0xF0F0F0), LV_PART_MAIN);
    lv_obj_set_style_text_opa(btn, 255, LV_PART_MAIN);
    lv_obj_set_style_clip_corner(btn, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *label_panel = ui_PanelXY_create(btn, 147.5, 50, 0, 0, 0, lv_color_hex(0x808080));
    lv_obj_set_align(label_panel, LV_ALIGN_BOTTOM_MID);

    // 去除后缀 ".gode"
    // char new_string[strlen(path.c_str()) - 6];
    // strncpy(new_string, path.c_str(), strlen(path.c_str()) - 5);
    // new_string[strlen(path.c_str()) - 6] = '\0';

    int hours, minutes, secs;
    char time_str[20];
    hours = seconds / 3600;
    minutes = (seconds % 3600) / 60;
    secs = seconds % 60;
    sprintf(time_str, "%dh%02dm%02ds", hours, minutes, secs);

    lv_obj_t *label_name = ui_label_create(label_panel, 0, 0, txt, &opensansb16);
    lv_obj_set_width(label_name, 147.5);
    lv_coord_t width = lv_txt_get_width(txt, strlen(txt), &opensansb16, 0, LV_TEXT_FLAG_NONE);
    if (width >= 147.5)
        lv_label_set_long_mode(label_name, LV_LABEL_LONG_SCROLL_CIRCULAR);
    else
        lv_obj_set_width(label_name, LV_SIZE_CONTENT);
    lv_obj_align(label_name, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_t *label_name1 = ui_label_create(label_panel, 0, 0, time_str, &opensansb16);
    lv_obj_align(label_name1, LV_ALIGN_CENTER, 0, 9);

    if (image)
    {
        lv_obj_t *img = ui_image_create(label_panel, 0, 0, image);
        lv_obj_align(img, LV_ALIGN_LEFT_MID, 3.5, 9);
    }
    if (image1)
    {
        lv_obj_t *img1 = ui_image_create(btn, 0, 0, image1);
        lv_obj_align(img1, LV_ALIGN_TOP_MID, 0, 0);
        lv_obj_add_flag(img1, LV_OBJ_FLAG_CHECKABLE);
    }

    return btn;
}
// 创建label
lv_obj_t *ui_label_create(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, const char *text, const lv_font_t *fonts)
{
    lv_obj_t *Label = lv_label_create(parent);
    lv_obj_set_width(Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_pos(Label, x, y);
    lv_obj_set_align(Label, LV_ALIGN_CENTER);
    lv_label_set_text(Label, text);
    lv_obj_set_style_text_font(Label, fonts, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(Label, lv_color_hex(0xF0F0F0), LV_PART_MAIN | LV_STATE_DEFAULT);

    return Label;
}
// 创建List
lv_obj_t *ui_List_create(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, lv_color_t bg_c, lv_coord_t hor, lv_coord_t row, lv_coord_t top)
{

    lv_obj_t *obj = lv_list_create(parent);
    lv_obj_set_width(obj, x);
    lv_obj_set_height(obj, y);
    lv_obj_set_align(obj, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(obj, bg_c, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN);
    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(obj, hor, LV_PART_MAIN);
    lv_obj_set_style_pad_row(obj, row, LV_PART_MAIN);
    lv_obj_set_style_pad_top(obj, top, LV_STATE_DEFAULT); // 将列表的内边距设置为20像素

    return obj;
}
// 为列表添加按钮（图片 label）
lv_obj_t *ui_ListBtn_create(lv_obj_t *parent, lv_coord_t h, lv_color_t bg_c, lv_coord_t hor, lv_coord_t row, lv_coord_t top, const char *text, lv_coord_t text_x, lv_coord_t text_y,
                            const char *text1, lv_coord_t text1_x, lv_coord_t text1_y, const void *img, lv_coord_t img_x)
{

    lv_obj_t *btn = lv_list_add_btn(parent, NULL, NULL);
    lv_obj_set_style_radius(btn, 8, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, bg_c, LV_PART_MAIN);
    lv_obj_set_style_border_width(btn, 1, LV_PART_MAIN);
    lv_obj_set_style_border_side(btn, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(btn, lv_color_hex(0x999999), LV_PART_MAIN);
    lv_obj_set_style_layout(btn, 0, LV_PART_MAIN); // clear flex
    lv_obj_set_style_text_color(btn, lv_color_hex(0xF0F0F0), LV_PART_MAIN);
    lv_obj_set_style_pad_hor(btn, hor, LV_PART_MAIN);
    lv_obj_set_style_pad_gap(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(btn, row, LV_PART_MAIN);
    lv_obj_set_style_pad_top(btn, top, LV_PART_MAIN);
    lv_obj_set_height(btn, h);
    if (text)
    {
        lv_obj_t *label_name = ui_label_create(btn, 0, 0, text, &opensansb16);
        lv_obj_align(label_name, LV_ALIGN_LEFT_MID, text_x, text_y); // 文本相对于图片右对齐
    }
    if (text1)
    {
        lv_obj_t *label_name1 = ui_label_create(btn, 0, 0, text1, &opensansb16);
        lv_obj_align(label_name1, LV_ALIGN_RIGHT_MID, text1_x, text1_y); // 文本相对于图片右对齐
    }
    if (img)
    {
        ui_image_create(btn, img_x, 5, img);
    }

    return btn;
}

/* 创建一个矩阵按钮 */
lv_obj_t *ui_btnmatrix_create(lv_obj_t *parent, const char **btnm_text, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y,
                              lv_coord_t x1, lv_coord_t y1, uint16_t btn_id, lv_color_t btn_bg, lv_color_t btn_border_bg, lv_color_t bg_c)
{
    static lv_style_t style_bg;
    lv_style_init(&style_bg);
    lv_style_set_pad_all(&style_bg, 0);
    lv_style_set_pad_gap(&style_bg, 0);
    lv_style_set_clip_corner(&style_bg, true);
    lv_style_set_radius(&style_bg, 0); // LV_RADIUS_CIRCLE
    lv_style_set_border_width(&style_bg, 0);
    lv_style_set_border_color(&style_bg, lv_color_hex(0x505050));
    lv_style_set_bg_color(&style_bg, bg_c);

    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, 0);
    lv_style_set_border_width(&style_btn, 1);
    lv_style_set_border_opa(&style_btn, LV_OPA_50);
    lv_style_set_border_color(&style_btn, btn_border_bg);
    lv_style_set_bg_color(&style_btn, btn_bg);
    lv_style_set_border_side(&style_btn, LV_BORDER_SIDE_INTERNAL);

    lv_obj_t *btnmatrix_panel = ui_PanelXY_create(parent, w, h, 0, 0, 8, lv_color_hex(0x363636));
    lv_obj_align(btnmatrix_panel, LV_ALIGN_CENTER, x, y);
    lv_obj_set_style_clip_corner(btnmatrix_panel, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *Movingdis_but = lv_btnmatrix_create(btnmatrix_panel);
    lv_btnmatrix_set_map(Movingdis_but, btnm_text);
    int num_elements = 0;
    while (btnm_text[num_elements] != NULL)
    {
        lv_btnmatrix_set_btn_ctrl(Movingdis_but, num_elements, LV_BTNMATRIX_CTRL_CHECKABLE);
        num_elements++;
    }
    lv_btnmatrix_set_one_checked(Movingdis_but, true);
    lv_btnmatrix_set_btn_ctrl(Movingdis_but, btn_id, LV_BTNMATRIX_CTRL_CHECKED);
    lv_obj_add_style(Movingdis_but, &style_bg, 0);
    lv_obj_add_style(Movingdis_but, &style_btn, LV_PART_ITEMS);
    lv_obj_set_size(Movingdis_but, x1, y1);
    lv_obj_align(Movingdis_but, LV_ALIGN_CENTER, 0, 0);
    return Movingdis_but;
}

// 创建TextArea
lv_obj_t *ui_TextArea_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t x, lv_coord_t y, lv_coord_t radius)
{
    lv_obj_t *TextArea = lv_textarea_create(parent);
    lv_obj_set_size(TextArea, 213, LV_SIZE_CONTENT);
    lv_obj_set_pos(TextArea, x, y);
    lv_obj_set_align(TextArea, LV_ALIGN_CENTER);
    lv_textarea_set_one_line(TextArea, true);
    lv_obj_set_style_text_color(TextArea, lv_color_hex(0xF0F0F0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(TextArea, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(TextArea, &opensansb16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(TextArea, radius, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(TextArea, lv_color_hex(0x505050), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(TextArea, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(TextArea, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    return TextArea;
}

// 创建一个带有背景图片label的按钮对象，设置了按钮大小、圆角、背景颜色等样式。
lv_obj_t *ui_btn_img_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y, lv_coord_t radius, lv_color_t bg_c, const void *bg_img_src)
{
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, w, h);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_align(btn, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(btn, radius, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, bg_c, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(btn, 255, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(btn, lv_color_hex(0xF0F0F0), LV_PART_MAIN);
    lv_obj_set_style_text_opa(btn, 255, LV_PART_MAIN);
    if (bg_img_src)
    {
        lv_obj_set_style_bg_img_src(btn, bg_img_src, LV_PART_MAIN);
    }
    return btn;
}
// 创建个圆环
lv_obj_t *ui_Arc_create(lv_obj_t *parent)
{
    lv_obj_t *Arc = lv_arc_create(parent);
    lv_obj_set_size(Arc, 22, 22);
    lv_obj_set_pos(Arc, -273, 18);
    lv_obj_set_align(Arc, LV_ALIGN_CENTER);
    lv_arc_set_value(Arc, 366);
    lv_arc_set_bg_angles(Arc, 0, 360);
    lv_obj_set_style_arc_color(Arc, lv_color_hex(0x505050), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(Arc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(Arc, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Arc, LV_OBJ_FLAG_CLICKABLE); /// Flags
    lv_obj_set_style_arc_color(Arc, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(Arc, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(Arc, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Arc, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Arc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    return Arc;
}
lv_obj_t *ui_Arc_Print_create(lv_obj_t *parent)
{
    lv_obj_t *Arc = lv_arc_create(parent);
    lv_obj_set_width(Arc, 116);
    lv_obj_set_height(Arc, 124);
    lv_obj_set_x(Arc, 80);
    lv_obj_set_y(Arc, 75);
    lv_obj_set_align(Arc, LV_ALIGN_TOP_MID);
    lv_arc_set_bg_angles(Arc, 0, 360);
    lv_arc_set_rotation(Arc, 270);
    lv_obj_set_style_arc_color(Arc, lv_color_hex(0x4B4B4B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(Arc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(Arc, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(Arc, lv_color_hex(0x5CFD6B), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(Arc, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(Arc, 15, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(Arc, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Arc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Arc, LV_OBJ_FLAG_CLICKABLE);

    return Arc;
}

/* 创建个条形进度条 */
lv_obj_t *ui_slider_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h,
                           lv_coord_t x, lv_coord_t y, lv_coord_t radius)
{
    lv_obj_t *Slider = lv_slider_create(parent);
    lv_obj_set_width(Slider, w);
    lv_obj_set_height(Slider, h);
    lv_obj_set_x(Slider, x);
    lv_obj_set_y(Slider, y);
    lv_obj_set_align(Slider, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(Slider, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Slider, lv_color_hex(0x424242), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Slider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(Slider, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Slider, lv_color_hex(0x50D4FA), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Slider, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Slider, lv_color_hex(0xF0F0F0), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Slider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    return Slider;
}
lv_obj_t *ui_key_textarea_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h,
                                 lv_coord_t x, lv_coord_t y)
{
    lv_obj_t *tx = lv_textarea_create(parent);
    lv_obj_set_size(tx, w, h);
    lv_obj_set_pos(tx, x, y);
    lv_obj_set_style_radius(tx, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(tx, lv_color_hex(0x505050), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_clear_flag(tx, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(tx, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_textarea_set_align(tx, LV_TEXT_ALIGN_LEFT);
    lv_textarea_set_max_length(tx, 3);
    return tx;
}

lv_obj_t *ui_keyboard_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y)
{
    lv_obj_t *panel_kayboard = ui_PanelXY_create(parent, w, h, x, y, 8, lv_color_hex(0xF0F0F0));
    lv_obj_set_style_clip_corner(panel_kayboard, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *kb = lv_keyboard_create(panel_kayboard);
    lv_obj_set_size(kb, w, h);
    lv_obj_set_pos(kb, 0, 0);
    lv_obj_set_align(kb, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(kb, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(kb, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(kb, 1, 0);
    lv_obj_set_style_pad_top(kb, 0, 0);
    lv_obj_set_style_pad_left(kb, 0, 0);
    lv_obj_set_style_pad_right(kb, 0, 0);
    lv_obj_set_style_pad_column(kb, 1, 0);
    lv_obj_set_style_pad_bottom(kb, 0, 0);
    lv_obj_set_style_bg_color(kb, lv_color_hex(0x363636), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(kb, lv_color_hex(0x505050), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(kb, &lv_font_montserrat_16, LV_PART_ITEMS | LV_STATE_DEFAULT);
    return kb;
}
/* 进度条样式 */
lv_obj_t *ui_bar_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y)
{
    static lv_style_t style_bg;
    static lv_style_t style_indic;
    lv_style_init(&style_bg);
    lv_style_set_border_width(&style_bg, 0);
    lv_style_set_pad_all(&style_bg, 0); /*To make the indicator smaller*/
    lv_style_set_radius(&style_bg, 6);
    lv_style_set_anim_time(&style_bg, 1000);

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_radius(&style_indic, 3);

    lv_obj_t *Bar = lv_bar_create(parent);
    lv_obj_remove_style_all(Bar); /*To have a clean start*/
    lv_obj_add_style(Bar, &style_bg, 0);
    lv_obj_add_style(Bar, &style_indic, LV_PART_INDICATOR);

    lv_obj_set_size(Bar, w, h);
    lv_obj_set_pos(Bar, x, y);
    lv_obj_set_align(Bar, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(Bar, lv_color_hex(0xFD3636), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Bar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(Bar, lv_color_hex(0x505050), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Bar, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_bar_set_value(Bar, 100, LV_ANIM_OFF); // 设置初始值为0，关闭动画

    return Bar;
}
/* 创建线条 */

lv_obj_t *ui_line_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_color_t bg_c)
{
    lv_obj_t *obj = ui_PanelXY_create(parent, 18, 18, 0, 0, 18, bg_c);
    lv_obj_t *obj1 = ui_PanelXY_create(obj, w, h, 0, 0, 18, bg_c);
    lv_obj_set_style_clip_corner(obj1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    /*
        设置一组点，用来提供给line组件画线
        这个数组应该是静态、全局或动态分配的，不能是函数中的局部变量
        因为lv_line_set_points保存的只是该数组的指针
    */
    lv_coord_t local_w = w;
    lv_coord_t local_h = h;
    lv_point_t line_points[2];
    line_points[0].x = local_w;
    line_points[0].y = 0;
    line_points[1].x = local_w;
    line_points[1].y = local_h;

    lv_point_t line_points1[2];
    line_points1[0].x = local_w;
    line_points1[0].y = 0;
    line_points1[1].x = 0;
    line_points1[1].y = local_h;
    /*创建一个共享样式*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    // 下面3个样式是 line 的专有样式接口，类似于arc
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_color_hex(0xF0F0F0));
    // 使用这个样式能让画出来的线条看起来更平滑
    lv_style_set_line_rounded(&style_line, true);
    lv_obj_t *line = lv_line_create(obj1);
    lv_line_set_y_invert(line, true); // 反转y轴，LCD坐标系->平面直角坐标系第一象限
    lv_obj_align(line, LV_ALIGN_CENTER, -1, 0);

    lv_line_set_points(line, line_points, 2); // 设置点数组。line将连接这些点，按顺序画出直线
    lv_obj_add_style(line, &style_line, 0);
    lv_obj_t *line1 = lv_line_create(obj1);
    lv_line_set_y_invert(line1, true); // 反转y轴，LCD坐标系->平面直角坐标系第一象限
    lv_obj_align(line1, LV_ALIGN_CENTER, 2, 0);
    lv_line_set_points(line1, line_points1, 2); // 设置点数组。line将连接这些点，按顺序画出直线
    lv_obj_add_style(line1, &style_line, 0);

    return obj;
}
void ui_del_myself_clicked(lv_event_t *e)
{
    lv_obj_t *myself = lv_event_get_target(e);
    lv_obj_del_async(myself);
}
void ui_obj_set_type(lv_obj_t *obj, ui_type_t type)
{
    uint32_t user_data = type;
    lv_obj_set_user_data(obj, (void *)user_data);
}

lv_obj_t *ui_btn_img_createe(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t radius, lv_color_t bg_c, const void *bg_img_src)
{
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, w, h);
    lv_obj_set_style_radius(btn, radius, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, bg_c, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(btn, 255, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(btn, lv_color_hex(0x505050), LV_PART_MAIN);
    lv_obj_set_style_text_opa(btn, 255, LV_PART_MAIN);
    if (bg_img_src)
    {
        lv_obj_set_style_bg_img_src(btn, bg_img_src, LV_PART_MAIN);
        // lv_obj_set_style_bg_img_recolor(btn, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_PRESSED);
        // lv_obj_set_style_bg_img_recolor_opa(btn, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    }

    return btn;
}
lv_obj_t *ui_btn_label_create(lv_obj_t *parent, lv_coord_t w, lv_coord_t h, lv_coord_t radius, lv_color_t bg_c, const char *text)
{
    lv_obj_t *btn = ui_btn_img_createe(parent, w, h, radius, bg_c, NULL);
    lv_obj_set_style_text_color(btn, lv_color_hex(0xF0F0F0), LV_PART_MAIN);
    lv_obj_t *label = lv_label_create(btn);
    lv_obj_set_align(label, LV_ALIGN_CENTER);
    lv_label_set_text(label, text);
    lv_obj_set_width(label, w);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    return btn;
}
lv_obj_t *ui_line_createe(lv_obj_t *parent, const lv_point_t *points, uint16_t num, lv_coord_t w, lv_color_t color)
{
    lv_obj_t *line = lv_line_create(parent);
    lv_line_set_points(line, points, num);
    lv_obj_set_style_line_width(line, w, LV_PART_MAIN);
    lv_obj_set_style_line_color(line, color, LV_PART_MAIN);
    lv_obj_set_style_line_opa(line, 255, LV_PART_MAIN);
    lv_obj_set_style_line_rounded(line, false, LV_PART_MAIN);
    return line;
}
// 创建一个面板对象，设置背景颜色、边框等样式。
lv_obj_t *ui_panel_create(lv_obj_t *parent, lv_coord_t radius, lv_color_t bg_c)
{
    lv_obj_t *panel = lv_obj_create(parent);
    // lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_set_style_radius(panel, radius, LV_PART_MAIN);
    lv_obj_set_style_bg_color(panel, bg_c, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(panel, 255, LV_PART_MAIN);
    lv_obj_set_style_border_width(panel, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(panel, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_opa(panel, 255, LV_PART_MAIN);
    lv_obj_set_style_text_font(panel, &opensansb16, LV_PART_MAIN);

    return panel;
}
/* 旋转器渐变 */
lv_obj_t *lv_Spinner_create(lv_obj_t *parent)
{
    lv_obj_t *ui_Spinner2 = lv_spinner_create(parent, 1000, 90);
    lv_obj_set_width(ui_Spinner2, 18);
    lv_obj_set_height(ui_Spinner2, 18);
    lv_obj_set_x(ui_Spinner2, 49);
    lv_obj_set_y(ui_Spinner2, -11);
    lv_obj_set_align(ui_Spinner2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Spinner2, LV_OBJ_FLAG_CLICKABLE); /// Flags
    lv_obj_set_style_radius(ui_Spinner2, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Spinner2, lv_color_hex(0x717171), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Spinner2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_Spinner2, lv_color_hex(0x999999), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Spinner2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_Spinner2, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_Spinner2, lv_color_hex(0xF0F0F0), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Spinner2, 200, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_Spinner2, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    return ui_Spinner2;
}
