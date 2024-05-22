#ifndef _LV_SCREENPRINT_H
#define _LV_SCREENPRINT_H

#include "lvgl.h"
#include "K_Touch.h"
extern lv_obj_t* navigationscreen;
void ui_homescreen_guide_init(void);
typedef struct
{
    int32_t scan_state;
    lv_obj_t *get_obj;
} lv_temp_state_t;
extern bool Set_Fanspeed;
extern lv_obj_t *label_Slider;
extern lv_obj_t *File_Printing_Panel;
void ui_event_Debugbut(lv_event_t *e);
void ui_event_Tempbut(lv_event_t *e);
void ui_event_Setbut(lv_event_t *e);
void ui_event_Printbut(lv_event_t *e);
void ui_event_Fliebut(lv_event_t *e);

lv_obj_t *lv_temp_scan_create(lv_obj_t *parent, int32_t state);
int32_t lv_temp_get_scan_state(lv_obj_t *panel);
void lv_loop_guide_home_state(int32_t scan_state, int32_t printing_state);
int32_t printing_get_scan_status(void);
#endif