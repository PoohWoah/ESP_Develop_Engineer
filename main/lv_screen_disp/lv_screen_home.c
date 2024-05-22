#include "lvgl.h"
#include "ui/ui.h"
#include "lv_screen_home.h"
#include "ui_overlay.h"
static lv_temp_state_t lv_guide_temp_state;
// static lv_printing_state_t lv_guide_printing_state;
static lv_obj_t *ui_panel_guide_temp_list;
lv_obj_t *File_Printing_Panel;
static lv_obj_t *ui_Fliebut;
static void ui_event_Fanbtn(lv_event_t *e)
{
    // switch_screen(ui_AxisMOVE);
}
static void ui_create_tempscan_list(lv_obj_t *parent)
{
    lv_obj_set_style_clip_corner(parent, true, LV_PART_MAIN);
    /* 修改尺寸 */
    lv_obj_t *obj = ui_List_create(parent, 300, 205, lv_color_hex(0x363636), 0, 8, 0);

    const char *sensor_names[5] = {"喷头温度", "热床温度", "CB1",
                                   "MCU", "风扇"};
    const lv_img_dsc_t *icons[5] = {&ui_img_exturder, &ui_img_hotbed, &ui_img_CB1, &ui_img_MCU, &ui_img_fan};
    for (int i = 0; i < 5; i++)
    {
        lv_obj_t *btn = ui_ListBtn_create(obj, 33, lv_color_hex(0x505050), 0, 0, 0, sensor_names[i], 45, 8, NULL, 0, 0, NULL, NULL);
        lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
        lv_obj_t *img_icon = ui_image_create(btn, 8, 0, icons[i]);
        if (i == 2 || i == 3)
            lv_obj_align(img_icon, LV_ALIGN_LEFT_MID, 13, 8);
        else
            lv_obj_align(img_icon, LV_ALIGN_LEFT_MID, 8, 8);
        lv_obj_add_event_cb(btn, ui_event_Fanbtn, LV_EVENT_CLICKED, NULL);
        lv_obj_move_to_index(img_icon, 1);
    }
}
void ui_panel_create_guide_temp(lv_obj_t *parent)
{
    // File_Printing_Panel = ui_PanelXY_create(parent, 330, 233, -120, 140, 0, lv_color_hex(0x363636));
    // lv_memset_00(&lv_guide_printing_state, sizeof(lv_guide_printing_state));
    // lv_obj_set_user_data(File_Printing_Panel, &lv_guide_printing_state);
    // lv_obj_move_to_index(File_Printing_Panel, 0);

    ui_panel_guide_temp_list = lv_obj_create(parent);
    lv_obj_set_size(ui_panel_guide_temp_list, 350, 210);
    lv_obj_set_pos(ui_panel_guide_temp_list, 85, 50);
    lv_obj_set_style_radius(ui_panel_guide_temp_list, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_panel_guide_temp_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_panel_guide_temp_list, 0, LV_PART_MAIN);

    ui_create_tempscan_list(ui_panel_guide_temp_list);
    lv_memset_00(&lv_guide_temp_state, sizeof(lv_guide_temp_state));
    lv_obj_set_user_data(ui_panel_guide_temp_list, &lv_guide_temp_state);
}
static lv_style_t style_btn_pr;
void ui_Homeright_create(lv_obj_t *parent)
{
    // 打印机选择
    lv_obj_t *ui_Printbut = ui_btn_create(parent, 156, 146, 136, -115, 8, lv_color_hex(0x505050));
    lv_obj_t *Print_image = ui_image_create(ui_Printbut, 0, 0, &ui_img_HomePrint);
    lv_obj_t *Print_Label = ui_label_create(ui_Printbut, 0, 45, "打印机选择",&opensansb16 );
    // lv_obj_t *Print_Label = ui_label_create(ui_Printbut, 0, 45, RS_TRANSLATE(K_HOME_PRINT),&opensansb16 );
    // lv_obj_add_flag(Print_Label, LV_OBJ_FLAG_MULTI_LANG);
    // rs_add_translate_cb(Print_Label, RS_TRANSLATE_DEFAULT_CB, (void *)K_HOME_PRINT, KEY_NUMBER);
    lv_obj_add_event_cb(ui_Printbut, ui_event_Printbut, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_flag(Print_image, LV_OBJ_FLAG_MULTI_COLOR);
    // 轴移动/温度
    lv_obj_t *ui_Tempbut = ui_btn_create(parent, 156, 146, 302, -115, 8, lv_color_hex(0x505050));
    lv_obj_t *Temp_image = ui_image_create(ui_Tempbut, 0, 0, &ui_img_HomeAxis);
    lv_obj_t *Temp_Label = ui_label_create(ui_Tempbut, 0, 45, "轴移动/温度", &opensansb16);
    // lv_obj_add_flag(Temp_Label, LV_OBJ_FLAG_MULTI_LANG);
    // rs_add_translate_cb(Temp_Label, RS_TRANSLATE_DEFAULT_CB, (void *)K_HOME_AXIS, KEY_NUMBER);
    lv_obj_add_event_cb(ui_Tempbut, ui_event_Tempbut, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_flag(Temp_image, LV_OBJ_FLAG_MULTI_COLOR);
    // 辅助调试
    lv_obj_t *ui_Debugbut = ui_btn_create(parent, 156, 146, 136, 41, 8, lv_color_hex(0x505050));
    lv_obj_t *Debug_image = ui_image_create(ui_Debugbut, 0, 0, &ui_img_HomeDebug);
    lv_obj_t *Debug_Label = ui_label_create(ui_Debugbut, 0, 45, "辅助调试", &opensansb16);
    // lv_obj_add_flag(Debug_Label, LV_OBJ_FLAG_MULTI_LANG);
    // rs_add_translate_cb(Debug_Label, RS_TRANSLATE_DEFAULT_CB, (void *)K_HOME_CAIL, KEY_NUMBER);
    lv_obj_add_event_cb(ui_Debugbut, ui_event_Debugbut, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_flag(Debug_image, LV_OBJ_FLAG_MULTI_COLOR);

    // 系统设置
    lv_obj_t *ui_Setbut = ui_btn_create(parent, 156, 146, 302, 41, 8, lv_color_hex(0x505050));
    lv_obj_t *Set_image = ui_image_create(ui_Setbut, 0, 0, &ui_img_HomeSet);
    lv_obj_t *Set_Label = ui_label_create(ui_Setbut, 0, 45, "系统设置", &opensansb16);
    // lv_obj_add_flag(Set_Label, LV_OBJ_FLAG_MULTI_LANG);
    // rs_add_translate_cb(Set_Label, RS_TRANSLATE_DEFAULT_CB, (void *)K_HOME_SETTING, KEY_NUMBER);
    // lv_obj_add_event_cb(ui_Setbut, ui_event_Setbut, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_flag(Set_image, LV_OBJ_FLAG_MULTI_COLOR);

    // 系统设置
    ui_Fliebut = ui_btn_create(parent, 327, 91, 219, 171, 8, lv_color_hex(0x505050));
    lv_obj_move_to_index(ui_Fliebut, 1);
    lv_obj_t *Flie_image = ui_image_create(ui_Fliebut, -30, 0, &ui_img_HomeFile);
    lv_obj_t *Flie_Label = ui_label_create(ui_Fliebut, 40, 4, "打印文件", &opensansb16);
    // lv_obj_add_flag(Flie_Label, LV_OBJ_FLAG_MULTI_LANG);
    // rs_add_translate_cb(Flie_Label, RS_TRANSLATE_DEFAULT_CB, (void *)K_HOME_FILE, KEY_NUMBER);
    lv_obj_add_event_cb(ui_Fliebut, ui_event_Fliebut, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_clip_corner(ui_Fliebut, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Flieresumebut = ui_btn_create(ui_Fliebut, 109, 90, -106, 0, 8, lv_color_hex(0x505050));
    lv_obj_set_style_border_color(ui_Flieresumebut, lv_color_hex(0x999999), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Flieresumebut, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Flieresumebut, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Flieresumebut, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Flieresumebut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Flieresumebut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Fliestopbut = ui_btn_create(ui_Fliebut, 109, 90, -106, 0, 8, lv_color_hex(0x505050));
    lv_obj_set_style_border_color(ui_Fliestopbut, lv_color_hex(0x999999), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Fliestopbut, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Fliestopbut, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Fliestopbut, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Fliestopbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Fliestopbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Flieruducebut = ui_btn_create(ui_Fliebut, 109, 90, 3, 0, 8, lv_color_hex(0x505050));
    lv_obj_set_style_border_color(ui_Flieruducebut, lv_color_hex(0x999999), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Flieruducebut, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Flieruducebut, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Flieruducebut, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Flieruducebut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Flieruducebut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_FileINGbut = ui_btn_create(ui_Fliebut, 109, 90, 112, 0, 8, lv_color_hex(0x505050));
    lv_obj_set_style_bg_color(ui_FileINGbut, lv_color_hex(0x505050), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_FileINGbut, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_FileINGbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_FileINGbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_flag(ui_Flieresumebut, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Fliestopbut, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_Flieruducebut, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_FileINGbut, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_bg_img_src(ui_Fliestopbut, &ui_img_down, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(ui_Flieresumebut, &ui_img_resume, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(ui_Flieruducebut, &ui_img_stoprint, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(ui_FileINGbut, &ui_img_homefile1, LV_PART_MAIN);

    // lv_obj_add_event_cb(ui_Flieresumebut, ui_event_Flieresumebut, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_event_cb(ui_Fliestopbut, ui_event_Fliestopbut, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_event_cb(ui_Flieruducebut, ui_event_Flieruducebut, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_FileINGbut, ui_event_Fliebut, LV_EVENT_CLICKED, NULL);
}
lv_obj_t* navigationscreen;
void ui_homescreen_guide_init(void)
{
    // 创建温度引导面板
    navigationscreen = lv_obj_create(NULL); // ui_panel_create(ui_WIFIScreen_main, 0, lv_color_hex(0x444444));
    lv_obj_set_width(navigationscreen, 800);
    lv_obj_set_height(navigationscreen, 480);
    lv_obj_set_align(navigationscreen, LV_ALIGN_CENTER);
    lv_obj_clear_flag(navigationscreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(navigationscreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(navigationscreen, lv_color_hex(0x363636), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(navigationscreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(navigationscreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 创建Home传感器刷新面板的UI元素
    ui_panel_create_guide_temp(navigationscreen);
    // 创建Home左侧导航元素
    ui_Homeright_create(navigationscreen);
    // 导航键
    // screen_basis_init(navigationscreen);


}
void lv_loop_guide_home_state(int32_t scan_state, int32_t printing_state)
{
    // if (navigationscreen == NULL)
    //     return;
    // // 如果Wi-Fi列表面板存在
    // if (ui_panel_guide_temp_list)
    // {
    //     // 获取UI中的扫描状态
    //     int32_t ui_temp_scan_state = lv_temp_get_scan_state(ui_panel_guide_temp_list);
    //     // 如果UI中的扫描状态与传入的状态不同，则创建新的扫描UI
    //     if (ui_temp_scan_state != scan_state)
    //     {
    //         lv_temp_scan_create(ui_panel_guide_temp_list, scan_state);
    //     }
    // }
    // if (File_Printing_Panel)
    // {
    //     // 获取UI中的扫描状态
    //     int32_t ui_Printing_state = lv_get_printing_state(File_Printing_Panel);
    //     // 如果UI中的扫描状态与传入的状态不同，则创建新的扫描UI
    //     if (ui_Printing_state != printing_state)
    //     {
    //         lv_printing_create(File_Printing_Panel, printing_state);
    //     }
    // }
}
