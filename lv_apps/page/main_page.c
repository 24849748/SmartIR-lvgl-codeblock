#include "main_page.h"
#include "fan_page.h"
// #include "setting_page.h"
#include "ac_page.h"
#include "info_page.h"
#include "ctrl_page.h"
#include "../anim/anim.h"
#include "../common/lv_common.h"

#include <stdio.h>


// #define FAN_X
#define FAN_Y   
#define AC_Y    
#define INFO_Y  
#define CTRL_Y  


LV_IMG_DECLARE(logo_setting);
LV_IMG_DECLARE(logo_fan);
LV_IMG_DECLARE(logo_ac);
LV_IMG_DECLARE(astronaut1);
LV_IMG_DECLARE(astronaut2);
LV_IMG_DECLARE(astronaut3);
LV_IMG_DECLARE(astronaut4);
LV_IMG_DECLARE(astronaut5);
LV_IMG_DECLARE(astronaut6);
LV_IMG_DECLARE(astronaut7);
LV_IMG_DECLARE(astronaut8);
LV_IMG_DECLARE(astronaut9);
LV_IMG_DECLARE(astronaut10);
LV_IMG_DECLARE(astronaut11);
LV_IMG_DECLARE(astronaut12);
LV_IMG_DECLARE(astronaut13);
LV_IMG_DECLARE(astronaut14);


// static lv_obj_t * astronaut;        //太空人动图 obj
static lv_obj_t * btn_fan;          //风扇界面按钮 obj
static lv_obj_t * btn_ac;           //空调界面按钮 obj
static lv_obj_t * btn_info;         //信息界面按钮
static lv_obj_t * btn_ctrl;         //控制界面按钮
static lv_obj_t * time_bg;          //时间、太空人背景


/* 太空人动图集 */
const lv_img_dsc_t *astronaut_imgs[14] = {
    &astronaut1,
    &astronaut2,
    &astronaut3,
    &astronaut4,
    &astronaut5,
    &astronaut6,
    &astronaut7,
    &astronaut8,
    &astronaut9,
    &astronaut10,
    &astronaut11,
    &astronaut12,
    &astronaut13,
    &astronaut14,
};


/* 按钮回调事件 */
static void btn_fan_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        // anim_mainpage_out(0);
        printf("enter fan page\n");
        // remove_main_page_obj();
        // remove_group_obj();
        main_page_anim_out(0);
        // show_fan_page();
        fan_page_anim_in(200);
    }
}
static void btn_ac_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        //led_blink(PIN_LED);
        // anim_mainpage_out(0);
        // remove_main_page_obj();
        printf("enter ac page\n");
        // remove_group_obj();
        main_page_anim_out(0);
        ac_page_anim_in(200);
        // show_ac_page();
    }
}
static void btn_info_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        //led_blink(PIN_LED);
        // anim_mainpage_out(0);
        printf("enter info page\n");
        // remove_main_page_obj();
        // remove_group_obj();
        main_page_anim_out(200);
        info_page_anim_in(200);
        // show_info_page();
    }
}
static void btn_ctrl_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        printf("enter control page\n");
        // remove_group_obj();
        main_page_anim_out(200);
        ctrl_page_anim_in(200);
        // show_ctrl_page();
    }
}


/*************************
 *      绘制主页内容
 *************************/

/* 宇航员动图 */
void gif_astronaut(void){
    // astronaut = lv_obj_create(time_bg);
    // lv_obj_remove_style_all(astronaut);
    // lv_obj_set_style_radius(astronaut,75,0);
    // lv_obj_set_style_bg_color(astronaut,lv_color_black(),0);
    // lv_obj_set_style_bg_opa(astronaut,LV_OPA_0,0);//opa 透明度
    // // lv_obj_align(astronaut,LV_ALIGN_TOP_MID,0,20);
    // lv_obj_align(astronaut,LV_ALIGN_RIGHT_MID, -10, 0);
    // lv_obj_clear_flag(astronaut, LV_OBJ_FLAG_SCROLLABLE);
    
    // astronaut_anim();
    lv_obj_t *animing_astronaut = lv_animimg_create(time_bg);
    // lv_obj_center(animing_astronaut);
    lv_obj_align(animing_astronaut, LV_ALIGN_RIGHT_MID, -2, 0);
    lv_animimg_set_src(animing_astronaut,  (lv_img_dsc_t**)astronaut_imgs, 14);
    lv_animimg_set_duration(animing_astronaut, 400);
    lv_animimg_set_repeat_count(animing_astronaut, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(animing_astronaut);

    // lv_obj_t *animing_astronaut = lv_animimg_create(astronaut);
    // lv_obj_center(animing_astronaut);
}

void create_time_bg(){
    time_bg = lv_obj_create(bg_screen);
    lv_obj_remove_style_all(time_bg);
    lv_obj_add_flag(time_bg, LV_OBJ_FLAG_CHECKABLE);

    lv_obj_add_style(time_bg, &style_btn, LV_STATE_DEFAULT);
    lv_obj_add_style(time_bg, &style_btn_pr, LV_STATE_CHECKED);

    lv_obj_set_size(time_bg, 200, 80);
    lv_obj_align(time_bg, LV_ALIGN_TOP_MID, 0, 30);


    /* 数字时间 */
    LV_FONT_DECLARE(HmOS_45pxnum);
    lv_obj_t *time = lv_label_create(time_bg);
    int hour = 13, min = 35;
    lv_obj_align(time, LV_ALIGN_LEFT_MID, 2, 0);
    lv_label_set_recolor(time, true);
    lv_obj_set_style_text_font(time, &HmOS_45pxnum, 0);
    lv_label_set_text_fmt(time, "#ffffff %d:%d", hour, min);

}

void create_buttons(void){
    /* info button */
    btn_info = lv_btn_create(bg_screen);
    lv_obj_remove_style_all(btn_info);

    lv_obj_add_style(btn_info, &style_btn, LV_STATE_DEFAULT);
    lv_obj_add_style(btn_info, &style_btn_pr, LV_STATE_PRESSED);

    lv_obj_set_size(btn_info, 90, 60);
    lv_obj_align(btn_info, LV_ALIGN_LEFT_MID, 20, 10);

    lv_obj_add_event_cb(btn_info, btn_info_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t * info_label = lv_label_create(btn_info);
    lv_label_set_recolor(info_label, true);
    lv_label_set_text(info_label, "#ffffff Info");
    lv_obj_align(info_label, LV_ALIGN_TOP_LEFT, 5, 5);

    

    /* control button */
    btn_ctrl = lv_btn_create(bg_screen);
    lv_obj_remove_style_all(btn_ctrl);
    // lv_obj_add_flag(btn_info, LV_OBJ_FLAG_CLICKABLE);
    
    lv_obj_add_style(btn_ctrl, &style_btn, LV_STATE_DEFAULT);
    lv_obj_add_style(btn_ctrl, &style_btn_pr, LV_STATE_PRESSED);

    lv_obj_set_size(btn_ctrl, 90, 60);
    lv_obj_align(btn_ctrl, LV_ALIGN_LEFT_MID, 20, 90);

    lv_obj_add_event_cb(btn_ctrl, btn_ctrl_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t * ctrl_label = lv_label_create(btn_ctrl);
    lv_label_set_recolor(ctrl_label, true);
    lv_label_set_text(ctrl_label, "#ffffff Control");
    lv_obj_align(ctrl_label, LV_ALIGN_TOP_LEFT, 5, 5);


    /* ac button */
    btn_ac = lv_obj_create(bg_screen);
    lv_obj_remove_style_all(btn_ac);
    
    lv_obj_add_style(btn_ac, &style_btn, LV_STATE_DEFAULT);
    lv_obj_add_style(btn_ac, &style_btn_pr, LV_STATE_PRESSED);

    lv_obj_set_size(btn_ac, 90, 60);
    lv_obj_align(btn_ac, LV_ALIGN_RIGHT_MID, -20, 10);
    lv_obj_add_event_cb(btn_ac, btn_ac_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t * ac_label = lv_label_create(btn_ac);
    lv_label_set_recolor(ac_label, true);
    lv_label_set_text(ac_label, "#ffffff Ac");
    lv_obj_align(ac_label, LV_ALIGN_TOP_LEFT, 5, 5);

    // lv_obj_t *ac_logo = lv_img_create(btn_ac);
    // lv_img_set_src(ac_logo, &logo_ac);
    // lv_obj_align(ac_logo, LV_ALIGN_CENTER, 0, 0);
    


    /* fan button */
    btn_fan = lv_obj_create(bg_screen);
    lv_obj_remove_style_all(btn_fan);
    
    lv_obj_add_style(btn_fan, &style_btn, LV_STATE_DEFAULT);
    lv_obj_add_style(btn_fan, &style_btn_pr, LV_STATE_PRESSED);

    lv_obj_set_size(btn_fan, 90, 60);
    lv_obj_align(btn_fan, LV_ALIGN_RIGHT_MID, -20, 90);

    lv_obj_add_event_cb(btn_fan, btn_fan_cb, LV_EVENT_CLICKED, NULL);
    // lv_obj_t *fan_logo = lv_img_create(btn_fan);
    // lv_img_set_src(fan_logo, &logo_fan);
    // lv_obj_align(fan_logo, LV_ALIGN_CENTER, 0, 0);
    lv_obj_t * fan_label = lv_label_create(btn_fan);
    lv_label_set_recolor(fan_label, true);
    lv_label_set_text(fan_label, "#ffffff Fan");
    lv_obj_align(fan_label, LV_ALIGN_TOP_LEFT, 5, 5);
}

// void create_main_page_btn(void){

//     /* 空调按键 */
//     btn_ac = lv_img_create(bg_screen);
//     lv_obj_add_style(btn_ac, &style_btn_pressed, LV_STATE_PRESSED);
//     lv_obj_add_style(btn_ac, &style_outline_focused, LV_STATE_FOCUSED);
//     // lv_obj_set_style_transform_zoom(btn_ac, 230, 0);
//     lv_obj_add_flag(btn_ac, LV_OBJ_FLAG_CLICKABLE);
//     lv_obj_add_event_cb(btn_ac, btn_ac_cb, LV_EVENT_CLICKED, NULL);
//     lv_img_set_src(btn_ac, &logo_ac);
//     lv_obj_align(btn_ac, LV_ALIGN_BOTTOM_MID, 0,-70);
//     // lv_obj_align_to(btn_ac, btn_setting, LV_ALIGN_CENTER, -70, 0);
//     // lv_obj_align(btn_ac, LV_ALIGN_BOTTOM_MID, -50,-70);

//     /* 设置按键 */
//     btn_setting = lv_img_create(bg_screen);
//     lv_obj_add_style(btn_setting, &style_btn_pressed, LV_STATE_PRESSED);
//     lv_obj_add_style(btn_setting, &style_outline_focused, LV_STATE_FOCUSED);
//     // lv_obj_set_style_transform_zoom(btn_setting, 220, 0);
//     lv_obj_add_flag(btn_setting, LV_OBJ_FLAG_CLICKABLE);
//     lv_obj_add_event_cb(btn_setting, btn_setting_cb, LV_EVENT_CLICKED, NULL);
//     lv_img_set_src(btn_setting, &logo_setting);
//     // lv_obj_align(btn_setting, LV_ALIGN_BOTTOM_MID, 0,-70);
//     // lv_obj_align_to(btn_setting, btn_ac, LV_ALIGN_CENTER, -70, 0);
//     lv_obj_align(btn_setting, LV_ALIGN_BOTTOM_MID, -70, -70);

//     /* 风扇按键 */
//     btn_fan = lv_img_create(bg_screen);
//     lv_obj_add_style(btn_fan, &style_btn_pressed, LV_STATE_PRESSED);
//     lv_obj_add_style(btn_fan, &style_outline_focused, LV_STATE_FOCUSED);
//     lv_obj_set_style_transform_zoom(btn_fan, 220, 0);
//     lv_obj_add_flag(btn_fan, LV_OBJ_FLAG_CLICKABLE);
//     lv_obj_add_event_cb(btn_fan, btn_fan_cb, LV_EVENT_CLICKED, NULL);
//     lv_img_set_src(btn_fan, &logo_fan);
//     // lv_obj_align_to(btn_fan, btn_ac, LV_ALIGN_CENTER, 70, 0);
//     lv_obj_align(btn_fan, LV_ALIGN_BOTTOM_MID, 70,-70);
//     // lv_obj_align(btn_fan, LV_ALIGN_BOTTOM_MID, 50, -70);



// }


/*************************
 *        页面动画
 *************************/

void main_page_anim_in(uint32_t delay){
    anim_y_fade_in(time_bg, -100, 30, delay);
    anim_y_fade_in(btn_ac, 190, 10, delay);
    anim_y_fade_in(btn_fan, 190, 90, delay);
    anim_y_fade_in(btn_info, 190, 10, delay);
    anim_y_fade_in(btn_ctrl, 190, 90, delay);
}

void main_page_anim_out(uint32_t delay){
    anim_y_fade_out(time_bg, 30,-100, delay);
    anim_y_fade_out(btn_ac, 10, 190, delay);
    anim_y_fade_out(btn_fan, 90, 190, delay);
    anim_y_fade_out(btn_info, 10, 190, delay);
    anim_y_fade_out(btn_ctrl, 90, 190, delay);
}

/*************************
 *        页面API
 *************************/

/* 隐藏主页obj */
void main_page_hide_obj(void){
    lv_obj_add_flag(time_bg, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_info, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_ctrl, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_ac, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_fan, LV_OBJ_FLAG_HIDDEN);
}

/* 创建主页obj */
void main_page_create_obj(void){
    create_time_bg();
    gif_astronaut();
    create_buttons();

    main_page_hide_obj();
}


void show_main_page(void){
    if(time_bg != NULL){
        main_page_anim_in(200);
    }else{
        create_time_bg();
        create_buttons();
        gif_astronaut();    //太空人动图
        main_page_anim_in(200);
    }
}


/* 
    改3D外壳
    改用 LV_OBJ_FLAG_HIDDEN 而不是lv_obj_del_anim_ready_cb 
    移植新版ui
 */