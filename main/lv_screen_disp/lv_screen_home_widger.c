#include "ui_overlay.h"
#include "lvgl.h"
#include "ui/ui.h"
#include "K_Touch.h"
#include "lv_screen_home.h"
#define SW_PRINT_UTILS 1

#if SW_PRINT_UTILS 
#include "esp_log.h"
static const char * TAG = "LCD_TOUCH:"; 
#define PRINT_UTILS(fmt,args...) ESP_LOGW(TAG,fmt,##args)  
#else
#define PRINT_UTILS(...)
#endif

int32_t lv_temp_get_scan_state(lv_obj_t *panel)
{
    lv_temp_state_t *p_state = (lv_temp_state_t *)panel->user_data;
    if (p_state == NULL)
        return 0;
    return p_state->scan_state;
}
static void ui_create_temp_home(lv_obj_t *parent)
{
    // lv_obj_t *obj = lv_obj_get_child(parent, 0);
    // double temperatures[4] = {moonraker.temp_data.temp_extruder, moonraker.temp_data.temp_heater_bed, moonraker.temp_data.temp_sensor_CB1, moonraker.temp_data.temp_sensor_MCU};
    // double values[5] = {moonraker.temp_data.target_extruder, moonraker.temp_data.target_heater_bed, NULL, NULL, Klipper_Data.fan_value};
    // for (int i = 0; i < lv_obj_get_child_cnt(obj); i++)
    // {
    //     lv_obj_t *btn = lv_obj_get_child(obj, i);
    //     char str[20] = {0}; // 假设字符串的最大长度为20
    //     sprintf(str, "%.1f", temperatures[i]);
    //     String STR = "℃";
    //     if (values[i] != 0 && i < 2)
    //     {
    //         char SStr[20] = {0};
    //         sprintf(SStr, "%.0f", values[i]);
    //         STR = "/" + String(SStr) + "℃";
    //     }
    //     if (i == 4)
    //     {
    //         char SStr[20] = {0};
    //         sprintf(SStr, "%.0f", values[i]);
    //         STR = String(SStr) + "%";
    //         strcpy(str, "");
    //     }
    //     String Str = String(str) + STR;
    //     lv_obj_t *label_temp = ui_label_create(btn, 0, 0, Str.c_str(), &opensansb16);
    //     lv_obj_align(label_temp, LV_ALIGN_RIGHT_MID, -12, 4);
    // }
}
lv_obj_t *lv_temp_scan_create(lv_obj_t *parent, int32_t state)
{
    lv_temp_state_t *p_state = (lv_temp_state_t *)parent->user_data;
    if (p_state == NULL)
        return NULL;
    // if spinner or list exists, delete it first
    lv_obj_t *obj = lv_obj_get_child(parent, 0);
    for (int i = 0; i < lv_obj_get_child_cnt(obj); i++)
    {
        lv_obj_t *btn = lv_obj_get_child(obj, i);
        lv_obj_t *label = lv_obj_get_child(btn, 2);
        if (label)
        {
            lv_obj_del_async(label);
            label = NULL;
        }
    }
    // obj = NULL;
    switch (state)
    {
    case SENSORS_SCAN_ING:
        ui_create_temp_home(parent);
        break;
    case SENSORS_SCAN_COMPLETED:
        // 温度、目标温度
        ui_create_temp_home(parent);

        break;
    }
    p_state->scan_state = state;
    p_state->get_obj = NULL;

    return obj;
}
/* Flie显示 */
extern int32_t file_status;
void ui_event_Fliebut(lv_event_t *e)
{
    // switch_screen(FileScreen);
    // File_symbol = true;
    // file_status = FILE_SCAN_ING;
}
/* 进入打印机 */
void ui_event_Printbut(lv_event_t *e)
{
    // if (Klipper_Data.Print_screensymbol == false)
    // {
    //     screen_basis_init(ui_PrintConScreen);
    //     Klipper_Data.Print_screensymbol = true;
    //     lv_obj_clear_flag(ui_Printretrunbut, LV_OBJ_FLAG_CLICKABLE);
    //     lv_obj_clear_flag(ui_NextPrint, LV_OBJ_FLAG_CLICKABLE);
    //     lv_obj_set_style_text_opa(ui_Printretrunbut, 0, LV_PART_MAIN);
    //     lv_obj_set_style_text_opa(ui_NextPrint, 0, LV_PART_MAIN);
    //     uint8_t get_color = rs_get_color_type();
    //     /*刚开始不重置颜色为蓝色*/
    //     rs_set_local_color_guide(COLORS_1);
    // }
    // switch_screen(ui_PrintConScreen);
    // lv_obj_t*panel =lv_obj_create(lv_scr_act());
    // lv_obj_set_size(panel, 350, 210);
    // lv_obj_set_pos(panel, 0, 0);
    // lv_obj_set_style_radius(panel, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_width(panel, 0, LV_PART_MAIN);
    // lv_obj_set_style_bg_color(navigationscreen, lv_color_hex(0x505050), LV_PART_MAIN | LV_STATE_DEFAULT);
    PRINT_UTILS("Received touch event\n");
}

/* 进入轴/温度设置 */
void ui_event_Tempbut(lv_event_t *e)
{
    // switch_screen(ui_AxisMOVE);
}
/* 进入Debug */
void ui_event_Debugbut(lv_event_t *e)
{

    // switch_screen(ui_Debugscreen);
}
