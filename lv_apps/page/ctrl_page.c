#include "ctrl_page.h"
#include "main_page.h"
#include "../anim/anim.h"
#include "../common/lv_common.h"
#include <stdio.h>

#define CTRL_RETURN_Y 15

static lv_obj_t * ctrl_return;
static lv_obj_t * btn_led;
static lv_obj_t * btn_motor;

bool LEDstatus = false;
bool MOTORstatus = false;


/* 按钮回调函数 */
static void return_mainpage_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        printf("return main page\n");
        ctrl_page_anim_out(200);
        // show_main_page();
        main_page_anim_in(200);
    }
}
static void btn_led_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        LEDstatus = !LEDstatus;
        printf("LED:%s\n",LEDstatus?"open":"close");
    }
}
static void btn_motor_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        MOTORstatus = !MOTORstatus;
        printf("Motor:%s\n", MOTORstatus?"open":"close");
    }
}


/*************************
 *      绘制页面内容
 *************************/


/* info 页面返回按键 */
void create_ctrl_return_btn(void){
    /* 返回键 */
    ctrl_return = lv_img_create(bg_screen);
    lv_obj_set_style_translate_y(ctrl_return, 5, LV_STATE_PRESSED);
    lv_obj_align(ctrl_return, LV_ALIGN_TOP_LEFT, 10, CTRL_RETURN_Y);
    lv_obj_add_flag(ctrl_return, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ctrl_return, return_mainpage_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_ext_click_area(ctrl_return, 15);
    LV_IMG_DECLARE(logo_return);        //使用返回图片
    lv_img_set_src(ctrl_return, &logo_return); 
}

void create_ctrl_page_btn(void){
    
    // btn_led = lv_obj_create(bg_screen);
    // lv_obj_remove_style_all(btn_led);
    
    // lv_obj_add_style(btn_led, &style_btn, LV_STATE_DEFAULT);
    // lv_obj_add_style(btn_led, &style_btn_pr, LV_STATE_PRESSED);

    // lv_obj_set_size(btn_led, 90, 60);
    // lv_obj_align(btn_led, LV_ALIGN_RIGHT_MID, -20, 10);
    // lv_obj_add_event_cb(btn_led, btn_led, LV_EVENT_CLICKED, NULL);

    // lv_obj_t * ac_label = lv_label_create(btn_led);
    // lv_label_set_recolor(ac_label, true);
    // lv_label_set_text(ac_label, "#ffffff Led");
    // lv_obj_align(ac_label, LV_ALIGN_TOP_LEFT, 5, 5);

    btn_led = lv_create_button_c(bg_screen, 90, 60, LV_ALIGN_LEFT_MID, 20, 10, btn_led_cb, "#ffffff Led");
    lv_obj_remove_style(btn_led, &style_btn_pr, LV_STATE_PRESSED);
    lv_obj_add_flag(btn_led, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_style(btn_led, &style_btn_pr, LV_STATE_CHECKED);
    btn_motor = lv_create_button_c(bg_screen, 90, 60, LV_ALIGN_RIGHT_MID, -20, 10, btn_motor_cb, "#ffffff Motor");
    lv_obj_remove_style(btn_motor, &style_btn_pr, LV_STATE_PRESSED);
    lv_obj_add_flag(btn_motor, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_style(btn_motor, &style_btn_pr, LV_STATE_CHECKED);
}


/*************************
 *        页面动画
 *************************/

void ctrl_page_anim_in(uint32_t delay){
    anim_y_fade_in(ctrl_return, -50, CTRL_RETURN_Y, delay);
    anim_x_fade_in(btn_led, -100, 20, delay);
    anim_x_fade_in(btn_motor, 100, -20, delay);
}

void ctrl_page_anim_out(uint32_t delay){
    anim_y_fade_out(ctrl_return, CTRL_RETURN_Y, -50, delay);
    anim_x_fade_out(btn_led, 20, -100, delay);
    anim_x_fade_out(btn_motor, -20, 100, delay);
}



/*************************
 *        页面API
 *************************/


void ctrl_page_hide_obj(void){
    lv_obj_add_flag(ctrl_return, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_led, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_motor, LV_OBJ_FLAG_HIDDEN);
}

void ctrl_page_create_obj(void){
    create_ctrl_return_btn();
    create_ctrl_page_btn();

    ctrl_page_hide_obj();
}


void show_ctrl_page(void){
    create_ctrl_return_btn();
    create_ctrl_page_btn();

    ctrl_page_anim_in(200);
}