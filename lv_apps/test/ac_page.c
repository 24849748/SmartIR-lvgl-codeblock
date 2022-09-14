#include "ac_page.h"
// #include "bg_page.h"
#include "main_page.h"
#include "../common/lv_common.h"
#include <stdio.h>

LV_FONT_DECLARE(font_LMYY);
LV_IMG_DECLARE(logo_kaiguan);

//user data
bool acswitch = false;     //后面需要给其他任务extern
int16_t acTemperature = 26;

static lv_obj_t * ac_title;     //标题
static lv_obj_t * ac_return;    //返回键
static lv_obj_t * ac_switch;    //开关键
static lv_obj_t * ac_arc;       //圆弧条
static lv_obj_t * ac_add;       //+
static lv_obj_t * ac_cut;       //+
static lv_obj_t * text_temp;      //温度显示
static lv_obj_t * ac_speed;     //风速按钮
static lv_obj_t * ac_timing;    //定时按钮


static void remove_ac_page_obj(void){
    lv_obj_del(ac_title);
    lv_obj_del(ac_return);
    lv_obj_del(ac_switch);
    lv_obj_del(ac_arc);
    lv_obj_del(ac_speed);
    lv_obj_del(ac_add);
    lv_obj_del(ac_cut);
    lv_obj_del(ac_timing);
}

/* 按钮回调函数 */
static void return_mainpage_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        printf("return main page\n");
        remove_ac_page_obj();
        show_main_page();
    }
}
static void ac_switch_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        if(acswitch){
            printf("ac: open\n");
        }else{
            printf("ac: close\n");
        }
        acswitch = !acswitch;
    }
}
static void ac_arc_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_VALUE_CHANGED){
        // lv_obj_del(ac_temp);
        // draw_temp_cb();
        acTemperature = lv_arc_get_value(ac_arc);
        lv_label_set_text_fmt(text_temp, "#88B2FB %d°", acTemperature);
        printf("ac: %d\n",lv_arc_get_value(ac_arc));
    }
}
static void ac_add_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED){
        acTemperature = lv_arc_get_value(ac_arc) + 1;
        if(acTemperature >32){
            acTemperature = 32;
        }
        lv_arc_set_value(ac_arc, acTemperature);
        lv_label_set_text_fmt(text_temp, "#88B2FB %d°", acTemperature);
        printf("ac temp add: %d\n",lv_arc_get_value(ac_arc));
    }
}
static void ac_cut_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED){
        acTemperature = lv_arc_get_value(ac_arc) - 1;
        if(acTemperature < 16){
            acTemperature = 16;
        }
        lv_arc_set_value(ac_arc, acTemperature);
        lv_label_set_text_fmt(text_temp, "#88B2FB %d°", acTemperature);
        printf("ac temp cut: %d\n",lv_arc_get_value(ac_arc));
    }
}

/* 显示风扇文字标题 */
void show_title_ac(void){
    ac_title = lv_label_create(bg_screen);
    lv_label_set_recolor(ac_title, true);
    lv_label_set_text(ac_title, "#88B2FB 空调");
    lv_obj_set_style_text_font(ac_title, &font_LMYY,0);
    lv_obj_align(ac_title, LV_ALIGN_TOP_MID, 0, 10);  //位置
}


/* 温度圆弧 */
void create_ac_arc(void){
    ac_arc = lv_arc_create(bg_screen);
    lv_obj_set_size(ac_arc, 150, 150);
    lv_obj_align(ac_arc, LV_ALIGN_CENTER, 0, -30);
    // lv_obj_align_to(ac_arc, ac_switch, LV_ALIGN_CENTER, 0, 20);


    lv_obj_remove_style(ac_arc, NULL, LV_PART_KNOB);
    lv_obj_set_style_arc_color(ac_arc, lv_color_hex(0x88B2FB), LV_PART_INDICATOR);   //圆弧前景颜色
    lv_obj_set_style_arc_color(ac_arc, lv_color_hex(0xf34c44), LV_PART_MAIN);        //圆弧背景颜色

    lv_arc_set_rotation(ac_arc, 160);       //到0°的偏移量
    lv_arc_set_bg_angles(ac_arc, 0, 220);
    // lv_arc_set_angles();
    lv_arc_set_value(ac_arc, acTemperature);       //得到空调值 保存到nvs
    lv_arc_set_range(ac_arc, 16, 32);
    // lv_obj_remove_style(ac_arc, NULL, LV_PART_KNOB);
    lv_obj_add_event_cb(ac_arc, ac_arc_cb, LV_EVENT_VALUE_CHANGED, NULL);

    //圆弧温度
    text_temp = lv_label_create(ac_arc);
    lv_label_set_recolor(text_temp, true);
    // lv_label_set_text(ac_temp, "#88B2FB 26°");
    lv_label_set_text_fmt(text_temp, "#88B2FB %d°", acTemperature);
    lv_obj_set_style_text_font(text_temp, &font_LMYY, 0);
    lv_obj_align_to(text_temp, ac_arc, LV_ALIGN_BOTTOM_MID, 10, 0);
    // lv_obj_align(ac_temp,LV_ALIGN_BOTTOM_MID,0,70);

}




void create_ac_btn(void){
    /* 返回键 */
    ac_return = lv_label_create(bg_screen);
    lv_obj_add_style(ac_return, &style_btn_pressed, LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ac_return,lv_color_hex(0x21252b),LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ac_return,LV_OPA_COVER,LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ac_return, 5, LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ac_return,lv_color_hex(0x202020),LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ac_return,LV_OPA_COVER,LV_STATE_PRESSED);
    lv_obj_set_style_radius(ac_return, 5, LV_STATE_PRESSED);

    lv_obj_align(ac_return, LV_ALIGN_TOP_LEFT,5,5);
    lv_obj_set_size(ac_return, 36,30);
    lv_obj_add_flag(ac_return, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ac_return, return_mainpage_cb, LV_EVENT_CLICKED, NULL);
    lv_label_set_recolor(ac_return,true);
    lv_label_set_text(ac_return,"#88B2FB   < ");
    lv_obj_set_style_text_font(ac_return, &font_LMYY, 0);


    /* 风扇开关 */
    // ac_switch = create_click_imgbtn(bg_screen, ac_switch_cb, LV_ALIGN_CENTER, 0, 60);
    ac_switch = lv_img_create(bg_screen);
    lv_obj_add_style(ac_switch, &style_btn_pressed, LV_STATE_PRESSED);
    lv_obj_add_flag(ac_switch, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ac_switch, ac_switch_cb, LV_EVENT_CLICKED, NULL);
    // lv_obj_align_to(ac_switch, ac_arc, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(ac_switch, LV_ALIGN_CENTER, 0, -30);

    lv_img_set_src(ac_switch, &logo_kaiguan);


    /* 风速按钮 */
    ac_speed = lv_btn_create(bg_screen);
    lv_obj_remove_style(ac_speed, NULL, LV_PART_MAIN);
    lv_obj_add_style(ac_speed, &style_btn_pressed, LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ac_speed, lv_color_hex(0x21252b), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ac_speed, LV_OPA_COVER, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ac_speed, 5, LV_STATE_DEFAULT);
    lv_obj_set_size(ac_speed, 60, 40);
    lv_obj_align(ac_speed, LV_ALIGN_BOTTOM_MID, 50, -40);
    // lv_obj_add_event_cb(ac_speed, return_mainpage_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t * text_speed = lv_label_create(ac_speed);
    lv_label_set_recolor(text_speed, true);
    lv_label_set_text(text_speed, "#88B2FB 风速");
    lv_obj_set_style_text_font(text_speed, &font_LMYY, 0);
    lv_obj_center(text_speed);


    /* 定时按钮 */
    ac_timing = lv_btn_create(bg_screen);
    lv_obj_remove_style(ac_timing, NULL, LV_PART_MAIN);
    lv_obj_add_style(ac_timing, &style_btn_pressed, LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ac_timing, lv_color_hex(0x21252b), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ac_timing, LV_OPA_COVER, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ac_timing, 5, LV_STATE_DEFAULT);
    lv_obj_set_size(ac_timing, 60, 40);
    lv_obj_align(ac_timing, LV_ALIGN_BOTTOM_MID, -50, -40);
    // lv_obj_add_event_cb(ac_speed, return_mainpage_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t * text_timing = lv_label_create(ac_timing);
    lv_label_set_recolor(text_timing, true);
    lv_label_set_text(text_timing, "#88B2FB 定时");
    lv_obj_set_style_text_font(text_timing, &font_LMYY, 0);
    lv_obj_center(text_timing);
    

    /* + button */
    ac_add = create_text_btn(bg_screen);
    lv_obj_align(ac_add, LV_ALIGN_CENTER, 80, 35);
    lv_obj_add_event_cb(ac_add, ac_add_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_size(ac_add, 30, 30);
    lv_obj_t * text_add = lv_label_create(ac_add);
    lv_label_set_recolor(text_add, true);
    lv_label_set_text(text_add, "#88B2FB +");
    lv_obj_set_style_text_font(text_add, &font_LMYY, 0);
    lv_obj_center(text_add);
    

    /* - button */
    ac_cut = create_text_btn(bg_screen);
    lv_obj_align(ac_cut, LV_ALIGN_CENTER, -80, 35);
    lv_obj_add_event_cb(ac_cut, ac_cut_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_size(ac_cut, 30, 30);
    lv_obj_t * text_cut = lv_label_create(ac_cut);
    lv_label_set_recolor(text_cut, true);
    lv_label_set_text(text_cut, "#88B2FB -");
    lv_obj_set_style_text_font(text_cut, &font_LMYY, 0);
    lv_obj_center(text_cut);
}


void show_ac_page(void){
    show_title_ac();
    create_ac_arc();
    create_ac_btn();
}

/**
 * @todo
 *      - 绘制ac page
 *            摆风（上下/左右）
 *      - 整理fan_page代码
 */
