
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "lvgl/lvgl.h"
// #include "lv_examples/src/lv_demo_widgets/lv_demo_widgets.h"
#include "lv_drivers/win32drv/win32drv.h"

#include "lv_apps/page/main_page.h"
#include "lv_apps/page/fan_page.h"
#include "lv_apps/page/ac_page.h"
#include "lv_apps/page/ctrl_page.h"
#include "lv_apps/page/info_page.h"
#include "lv_apps/anim/anim.h"
#include "lv_apps/common/lv_common.h"

#include <windows.h>


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);
static int tick_thread(void *data);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    /*Initialize LittlevGL*/
    lv_init();



    /*Initialize the HAL for LittlevGL*/
    lv_win32_init(hInstance, SW_SHOWNORMAL, 240, 320, NULL);
    printf("init over\n");

    /*Run the demo*/
    /* do in first */
    bg_page();
    lv_init_btn_style();
    init_custom_btn_style();

    main_page_create_obj();
    info_page_create_obj();
    ac_page_create_obj();
    fan_page_create_obj();
    ctrl_page_create_obj();

    main_page_anim_in(200);

    // show_main_page();

    while(!lv_win32_quit_signal) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(10000);       /*Just to let the system breath*/
    }
    return 0;
}
