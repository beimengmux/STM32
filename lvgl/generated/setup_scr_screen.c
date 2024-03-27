/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
//#include "custom.h"


void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for screen
	static lv_style_t style_screen_main;
	lv_style_reset(&style_screen_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_main
	lv_style_set_bg_color(&style_screen_main, LV_STATE_DEFAULT, lv_color_make(0x3a, 0x97, 0xdf));
	lv_style_set_bg_opa(&style_screen_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen, LV_OBJ_PART_MAIN, &style_screen_main);

	//Write codes screen_img_1
	ui->screen_img_1 = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_img_1
	static lv_style_t style_screen_img_1_main;
	lv_style_reset(&style_screen_img_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_1_main
	lv_style_set_image_recolor(&style_screen_img_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_img_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_img_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_img_1, LV_IMG_PART_MAIN, &style_screen_img_1_main);
	lv_obj_set_pos(ui->screen_img_1, 0, 0);
	lv_obj_set_size(ui->screen_img_1, 320, 240);
	lv_obj_set_click(ui->screen_img_1, true);
	lv_img_set_src(ui->screen_img_1,&_1_alpha_320x240);
	lv_img_set_pivot(ui->screen_img_1, 0,0);
	lv_img_set_angle(ui->screen_img_1, 0);

	//Write codes screen_label_1
	ui->screen_label_1 = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_label_1, "Loading......");
	lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_label_1, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_label_1
	static lv_style_t style_screen_label_1_main;
	lv_style_reset(&style_screen_label_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_label_1_main
	lv_style_set_radius(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_label_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xe7, 0xe7, 0xde));
	lv_style_set_text_font(&style_screen_label_1_main, LV_STATE_DEFAULT, &lv_font_simsun_20);           //×Ö¿âµÄÀ´Ô´
	lv_style_set_text_letter_space(&style_screen_label_1_main, LV_STATE_DEFAULT, 3);
	lv_style_set_pad_left(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_label_1, LV_LABEL_PART_MAIN, &style_screen_label_1_main);
	lv_obj_set_pos(ui->screen_label_1, 58.5, 186);
	lv_obj_set_size(ui->screen_label_1, 203, 0);

	//Write codes screen_bar_1
	ui->screen_bar_1 = lv_bar_create(ui->screen, NULL);

	//Write style LV_BAR_PART_BG for screen_bar_1
	static lv_style_t style_screen_bar_1_bg;
	lv_style_reset(&style_screen_bar_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen_bar_1_bg
	lv_style_set_radius(&style_screen_bar_1_bg, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_screen_bar_1_bg, LV_STATE_DEFAULT, lv_color_make(0x31, 0x95, 0xd8));
	lv_style_set_bg_grad_color(&style_screen_bar_1_bg, LV_STATE_DEFAULT, lv_color_make(0xec, 0xed, 0xef));
	lv_style_set_bg_grad_dir(&style_screen_bar_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_screen_bar_1_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_screen_bar_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_bar_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_bar_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_bar_1_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_bar_1, LV_BAR_PART_BG, &style_screen_bar_1_bg);

	//Write style LV_BAR_PART_INDIC for screen_bar_1
	static lv_style_t style_screen_bar_1_indic;
	lv_style_reset(&style_screen_bar_1_indic);
	
	//Write style state: LV_STATE_DEFAULT for style_screen_bar_1_indic
	lv_style_set_radius(&style_screen_bar_1_indic, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_screen_bar_1_indic, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_bg_grad_color(&style_screen_bar_1_indic, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_bg_grad_dir(&style_screen_bar_1_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_bar_1_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_bar_1, LV_BAR_PART_INDIC, &style_screen_bar_1_indic);
	lv_obj_set_pos(ui->screen_bar_1, 60, 154);
	lv_obj_set_size(ui->screen_bar_1, 200, 20);
	lv_bar_set_anim_time(ui->screen_bar_1,1000);
	lv_bar_set_value(ui->screen_bar_1,0,LV_ANIM_OFF);
	lv_bar_set_range(ui->screen_bar_1,0,100);
}
