/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *screen;
	lv_obj_t *screen_img_1;
	lv_obj_t *screen_label_1;
	lv_obj_t *screen_bar_1;
	lv_obj_t *screen_1;
	lv_obj_t *screen_1_label_3;
	lv_obj_t *screen_1_cont_1;
	lv_obj_t *screen_1_img_3;
	lv_obj_t *screen_1_label_5;
	lv_obj_t *screen_1_img_1;
	lv_obj_t *screen_1_label_4;
	lv_obj_t *screen_1_cont_2;
	lv_obj_t *screen_1_label_6;
	lv_obj_t *screen_1_img_2;
	lv_obj_t *screen_1_label_7;
	lv_obj_t *screen_1_cont_3;
	lv_obj_t *screen_1_label_11;
	lv_obj_t *screen_1_label_10;
	lv_obj_t *screen_1_label_9;
	lv_obj_t *screen_1_img_6;
	lv_obj_t *screen_1_img_5;
	lv_obj_t *screen_1_img_4;
	lv_obj_t *screen_1_img_7;
	lv_obj_t *screen_1_line_1;
	lv_obj_t *screen_1_img_8;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen(lv_ui *ui);
void setup_scr_screen_1(lv_ui *ui);
LV_IMG_DECLARE(_6_alpha_30x30);
LV_IMG_DECLARE(_picture_alpha_30x30);
LV_IMG_DECLARE(_wifi_alpha_15x12);
LV_IMG_DECLARE(_5_alpha_30x30);
LV_IMG_DECLARE(_1_alpha_320x240);
LV_IMG_DECLARE(_7_alpha_30x15);
LV_IMG_DECLARE(_pictur3_alpha_17x17);
LV_IMG_DECLARE(_picture2_alpha_30x30);
LV_IMG_DECLARE(_3_alpha_30x30);

#ifdef __cplusplus
}
#endif
#endif