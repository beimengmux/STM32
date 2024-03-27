/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_screen_1(lv_ui *ui){

	//Write codes screen_1
	ui->screen_1 = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for screen_1
	static lv_style_t style_screen_1_main;
	lv_style_reset(&style_screen_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_main
	lv_style_set_bg_color(&style_screen_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_screen_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1, LV_OBJ_PART_MAIN, &style_screen_1_main);

	//Write codes screen_1_label_3
	ui->screen_1_label_3 = lv_label_create(ui->screen_1, NULL);
	lv_label_set_text(ui->screen_1_label_3, "2023-08-18");
	lv_label_set_long_mode(ui->screen_1_label_3, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_3, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_3
	static lv_style_t style_screen_1_label_3_main;
	lv_style_reset(&style_screen_1_label_3_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_3_main
	lv_style_set_radius(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_3_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0xe1));
	lv_style_set_text_font(&style_screen_1_label_3_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_3, LV_LABEL_PART_MAIN, &style_screen_1_label_3_main);
	lv_obj_set_pos(ui->screen_1_label_3, 207, 159);
	lv_obj_set_size(ui->screen_1_label_3, 100, 0);

	//Write codes screen_1_cont_1
	ui->screen_1_cont_1 = lv_cont_create(ui->screen_1, NULL);

	//Write style LV_CONT_PART_MAIN for screen_1_cont_1
	static lv_style_t style_screen_1_cont_1_main;
	lv_style_reset(&style_screen_1_cont_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_cont_1_main
	lv_style_set_radius(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0xec, 0xdf, 0xda));
	lv_style_set_bg_grad_color(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0xd8, 0x41, 0x41));
	lv_style_set_bg_grad_dir(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0x38, 0x6b, 0x68));
	lv_style_set_border_width(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_cont_1, LV_CONT_PART_MAIN, &style_screen_1_cont_1_main);
	lv_obj_set_pos(ui->screen_1_cont_1, 195, 58);
	lv_obj_set_size(ui->screen_1_cont_1, 123, 56);
	lv_obj_set_click(ui->screen_1_cont_1, false);

	//Write codes screen_1_img_3
	ui->screen_1_img_3 = lv_img_create(ui->screen_1_cont_1, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_3
	static lv_style_t style_screen_1_img_3_main;
	lv_style_reset(&style_screen_1_img_3_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_3_main
	lv_style_set_image_recolor(&style_screen_1_img_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_3_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_3, LV_IMG_PART_MAIN, &style_screen_1_img_3_main);
	lv_obj_set_pos(ui->screen_1_img_3, 90.5, 17.5);
	lv_obj_set_size(ui->screen_1_img_3, 17, 17);
	lv_obj_set_click(ui->screen_1_img_3, true);
	lv_img_set_src(ui->screen_1_img_3,&_pictur3_alpha_17x17);
	lv_img_set_pivot(ui->screen_1_img_3, 0,0);
	lv_img_set_angle(ui->screen_1_img_3, 0);

	//Write codes screen_1_label_5
	ui->screen_1_label_5 = lv_label_create(ui->screen_1_cont_1, NULL);
	lv_label_set_text(ui->screen_1_label_5, "温度:30");
	lv_label_set_long_mode(ui->screen_1_label_5, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_5, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_5
	static lv_style_t style_screen_1_label_5_main;
	lv_style_reset(&style_screen_1_label_5_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_5_main
	lv_style_set_radius(&style_screen_1_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_5_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_5_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xf5, 0xd8));
	lv_style_set_text_font(&style_screen_1_label_5_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_5_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_5_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_5, LV_LABEL_PART_MAIN, &style_screen_1_label_5_main);
	lv_obj_set_pos(ui->screen_1_label_5, 9, 20);
	lv_obj_set_size(ui->screen_1_label_5, 100, 0);

	//Write codes screen_1_img_1
	ui->screen_1_img_1 = lv_img_create(ui->screen_1_cont_1, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_1
	static lv_style_t style_screen_1_img_1_main;
	lv_style_reset(&style_screen_1_img_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_1_main
	lv_style_set_image_recolor(&style_screen_1_img_1_main, LV_STATE_DEFAULT, lv_color_make(0x82, 0x25, 0xc1));
	lv_style_set_image_recolor_opa(&style_screen_1_img_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_1, LV_IMG_PART_MAIN, &style_screen_1_img_1_main);
	lv_obj_set_pos(ui->screen_1_img_1, 0, 11);
	lv_obj_set_size(ui->screen_1_img_1, 30, 30);
	lv_obj_set_click(ui->screen_1_img_1, true);
	lv_img_set_src(ui->screen_1_img_1,&_picture_alpha_30x30);
	lv_img_set_pivot(ui->screen_1_img_1, 0,0);
	lv_img_set_angle(ui->screen_1_img_1, 0);
	lv_cont_set_layout(ui->screen_1_cont_1, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->screen_1_cont_1, LV_FIT_NONE);

	//Write codes screen_1_label_4
	ui->screen_1_label_4 = lv_label_create(ui->screen_1, NULL);
	lv_label_set_text(ui->screen_1_label_4, "10:00:00");
	lv_label_set_long_mode(ui->screen_1_label_4, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_4, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_4
	static lv_style_t style_screen_1_label_4_main;
	lv_style_reset(&style_screen_1_label_4_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_4_main
	lv_style_set_radius(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_4_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xfa, 0xe9));
	lv_style_set_text_font(&style_screen_1_label_4_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_4, LV_LABEL_PART_MAIN, &style_screen_1_label_4_main);
	lv_obj_set_pos(ui->screen_1_label_4, 209, 175);
	lv_obj_set_size(ui->screen_1_label_4, 100, 0);

	//Write codes screen_1_cont_2
	ui->screen_1_cont_2 = lv_cont_create(ui->screen_1, NULL);

	//Write style LV_CONT_PART_MAIN for screen_1_cont_2
	static lv_style_t style_screen_1_cont_2_main;
	lv_style_reset(&style_screen_1_cont_2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_cont_2_main
	lv_style_set_radius(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, lv_color_make(0xd5, 0xe6, 0xe6));
	lv_style_set_bg_grad_color(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, lv_color_make(0x5b, 0xc8, 0xb6));
	lv_style_set_bg_grad_dir(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_cont_2, LV_CONT_PART_MAIN, &style_screen_1_cont_2_main);
	lv_obj_set_pos(ui->screen_1_cont_2, 197, 104);
	lv_obj_set_size(ui->screen_1_cont_2, 123, 56);
	lv_obj_set_click(ui->screen_1_cont_2, false);

	//Write codes screen_1_label_6
	ui->screen_1_label_6 = lv_label_create(ui->screen_1_cont_2, NULL);
	lv_label_set_text(ui->screen_1_label_6, "湿度:70%HR");
	lv_label_set_long_mode(ui->screen_1_label_6, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_6, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_6
	static lv_style_t style_screen_1_label_6_main;
	lv_style_reset(&style_screen_1_label_6_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_6_main
	lv_style_set_radius(&style_screen_1_label_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_6_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_6_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0xee));
	lv_style_set_text_font(&style_screen_1_label_6_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_6_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_6_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_6, LV_LABEL_PART_MAIN, &style_screen_1_label_6_main);
	lv_obj_set_pos(ui->screen_1_label_6, 19, 20);
	lv_obj_set_size(ui->screen_1_label_6, 100, 0);

	//Write codes screen_1_img_2
	ui->screen_1_img_2 = lv_img_create(ui->screen_1_cont_2, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_2
	static lv_style_t style_screen_1_img_2_main;
	lv_style_reset(&style_screen_1_img_2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_2_main
	lv_style_set_image_recolor(&style_screen_1_img_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_2_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_2, LV_IMG_PART_MAIN, &style_screen_1_img_2_main);
	lv_obj_set_pos(ui->screen_1_img_2, 0, 10);
	lv_obj_set_size(ui->screen_1_img_2, 30, 30);
	lv_obj_set_click(ui->screen_1_img_2, true);
	lv_img_set_src(ui->screen_1_img_2,&_picture2_alpha_30x30);
	lv_img_set_pivot(ui->screen_1_img_2, 0,0);
	lv_img_set_angle(ui->screen_1_img_2, 0);
	lv_cont_set_layout(ui->screen_1_cont_2, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->screen_1_cont_2, LV_FIT_NONE);

	//Write codes screen_1_label_7
	ui->screen_1_label_7 = lv_label_create(ui->screen_1, NULL);
	lv_label_set_text(ui->screen_1_label_7, "空气质量检测仪");
	lv_label_set_long_mode(ui->screen_1_label_7, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_7, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_7
	static lv_style_t style_screen_1_label_7_main;
	lv_style_reset(&style_screen_1_label_7_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_7_main
	lv_style_set_radius(&style_screen_1_label_7_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_7_main, LV_STATE_DEFAULT, lv_color_make(0xe0, 0xe4, 0xd3));
	lv_style_set_bg_grad_color(&style_screen_1_label_7_main, LV_STATE_DEFAULT, lv_color_make(0xbb, 0xc6, 0x24));
	lv_style_set_bg_grad_dir(&style_screen_1_label_7_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_7_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_7_main, LV_STATE_DEFAULT, lv_color_make(0xf3, 0xf2, 0xf2));
	lv_style_set_text_font(&style_screen_1_label_7_main, LV_STATE_DEFAULT, &lv_font_simsun_15);
	lv_style_set_text_letter_space(&style_screen_1_label_7_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_7_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_7_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_7_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_7_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_7, LV_LABEL_PART_MAIN, &style_screen_1_label_7_main);
	lv_obj_set_pos(ui->screen_1_label_7, 83.5, 17);
	lv_obj_set_size(ui->screen_1_label_7, 153, 0);

	//Write codes screen_1_cont_3
	ui->screen_1_cont_3 = lv_cont_create(ui->screen_1, NULL);

	//Write style LV_CONT_PART_MAIN for screen_1_cont_3
	static lv_style_t style_screen_1_cont_3_main;
	lv_style_reset(&style_screen_1_cont_3_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_cont_3_main
	lv_style_set_radius(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_color(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_cont_3, LV_CONT_PART_MAIN, &style_screen_1_cont_3_main);
	lv_obj_set_pos(ui->screen_1_cont_3, 0, 54);
	lv_obj_set_size(ui->screen_1_cont_3, 200, 137);
	lv_obj_set_click(ui->screen_1_cont_3, false);

	//Write codes screen_1_label_11
	ui->screen_1_label_11 = lv_label_create(ui->screen_1_cont_3, NULL);
	lv_label_set_text(ui->screen_1_label_11, "甲醛:0.01mg/m3");
	lv_label_set_long_mode(ui->screen_1_label_11, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_11, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_11
	static lv_style_t style_screen_1_label_11_main;
	lv_style_reset(&style_screen_1_label_11_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_11_main
	lv_style_set_radius(&style_screen_1_label_11_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_11_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_11_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_11_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_11_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_11_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xee, 0xff));
	lv_style_set_text_font(&style_screen_1_label_11_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_11_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_11_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_11_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_11_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_11_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_11, LV_LABEL_PART_MAIN, &style_screen_1_label_11_main);
	lv_obj_set_pos(ui->screen_1_label_11, 62, 108);
	lv_obj_set_size(ui->screen_1_label_11, 126, 0);

	//Write codes screen_1_label_10
	ui->screen_1_label_10 = lv_label_create(ui->screen_1_cont_3, NULL);
	lv_label_set_text(ui->screen_1_label_10, "烟雾:100");
	lv_label_set_long_mode(ui->screen_1_label_10, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_10, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_10
	static lv_style_t style_screen_1_label_10_main;
	lv_style_reset(&style_screen_1_label_10_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_10_main
	lv_style_set_radius(&style_screen_1_label_10_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_10_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_10_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_10_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_10_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_10_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xee, 0xff));
	lv_style_set_text_font(&style_screen_1_label_10_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_10_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_10_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_10_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_10_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_10_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_10, LV_LABEL_PART_MAIN, &style_screen_1_label_10_main);
	lv_obj_set_pos(ui->screen_1_label_10, 68, 23);
	lv_obj_set_size(ui->screen_1_label_10, 100, 0);

	//Write codes screen_1_label_9
	ui->screen_1_label_9 = lv_label_create(ui->screen_1_cont_3, NULL);
	lv_label_set_text(ui->screen_1_label_9, "二氧化碳:100PPM");
	lv_label_set_long_mode(ui->screen_1_label_9, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_9, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_9
	static lv_style_t style_screen_1_label_9_main;
	lv_style_reset(&style_screen_1_label_9_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_9_main
	lv_style_set_radius(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_9_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_9_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_9_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 20);
	lv_style_set_text_color(&style_screen_1_label_9_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xf5, 0xf9));
	lv_style_set_text_font(&style_screen_1_label_9_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_9, LV_LABEL_PART_MAIN, &style_screen_1_label_9_main);
	lv_obj_set_pos(ui->screen_1_label_9, 62, 66);
	lv_obj_set_size(ui->screen_1_label_9, 125, 0);

	//Write codes screen_1_img_6
	ui->screen_1_img_6 = lv_img_create(ui->screen_1_cont_3, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_6
	static lv_style_t style_screen_1_img_6_main;
	lv_style_reset(&style_screen_1_img_6_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_6_main
	lv_style_set_image_recolor(&style_screen_1_img_6_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_6_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_6, LV_IMG_PART_MAIN, &style_screen_1_img_6_main);
	lv_obj_set_pos(ui->screen_1_img_6, 26, 96);
	lv_obj_set_size(ui->screen_1_img_6, 30, 30);
	lv_obj_set_click(ui->screen_1_img_6, true);
	lv_img_set_src(ui->screen_1_img_6,&_6_alpha_30x30);
	lv_img_set_pivot(ui->screen_1_img_6, 0,0);
	lv_img_set_angle(ui->screen_1_img_6, 0);

	//Write codes screen_1_img_5
	ui->screen_1_img_5 = lv_img_create(ui->screen_1_cont_3, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_5
	static lv_style_t style_screen_1_img_5_main;
	lv_style_reset(&style_screen_1_img_5_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_5_main
	lv_style_set_image_recolor(&style_screen_1_img_5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_5_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_5, LV_IMG_PART_MAIN, &style_screen_1_img_5_main);
	lv_obj_set_pos(ui->screen_1_img_5, 26, 57);
	lv_obj_set_size(ui->screen_1_img_5, 30, 30);
	lv_obj_set_click(ui->screen_1_img_5, true);
	lv_img_set_src(ui->screen_1_img_5,&_5_alpha_30x30);
	lv_img_set_pivot(ui->screen_1_img_5, 0,0);
	lv_img_set_angle(ui->screen_1_img_5, 0);

	//Write codes screen_1_img_4
	ui->screen_1_img_4 = lv_img_create(ui->screen_1_cont_3, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_4
	static lv_style_t style_screen_1_img_4_main;
	lv_style_reset(&style_screen_1_img_4_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_4_main
	lv_style_set_image_recolor(&style_screen_1_img_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_4_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_4, LV_IMG_PART_MAIN, &style_screen_1_img_4_main);
	lv_obj_set_pos(ui->screen_1_img_4, 26, 15);
	lv_obj_set_size(ui->screen_1_img_4, 30, 30);
	lv_obj_set_click(ui->screen_1_img_4, true);
	lv_img_set_src(ui->screen_1_img_4,&_3_alpha_30x30);
	lv_img_set_pivot(ui->screen_1_img_4, 0,0);
	lv_img_set_angle(ui->screen_1_img_4, 0);
	lv_cont_set_layout(ui->screen_1_cont_3, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->screen_1_cont_3, LV_FIT_NONE);

	//Write codes screen_1_img_7
	ui->screen_1_img_7 = lv_img_create(ui->screen_1, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_7
	static lv_style_t style_screen_1_img_7_main;
	lv_style_reset(&style_screen_1_img_7_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_7_main
	lv_style_set_image_recolor(&style_screen_1_img_7_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_7_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_7_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_7, LV_IMG_PART_MAIN, &style_screen_1_img_7_main);
	lv_obj_set_pos(ui->screen_1_img_7, 287, 3);
	lv_obj_set_size(ui->screen_1_img_7, 30, 15);
	lv_obj_set_click(ui->screen_1_img_7, true);
	lv_img_set_src(ui->screen_1_img_7,&_7_alpha_30x15);
	lv_img_set_pivot(ui->screen_1_img_7, 0,0);
	lv_img_set_angle(ui->screen_1_img_7, 0);

	//Write codes screen_1_line_1
	ui->screen_1_line_1 = lv_line_create(ui->screen_1, NULL);

	//Write style LV_LINE_PART_MAIN for screen_1_line_1
	static lv_style_t style_screen_1_line_1_main;
	lv_style_reset(&style_screen_1_line_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_line_1_main
	lv_style_set_line_color(&style_screen_1_line_1_main, LV_STATE_DEFAULT, lv_color_make(0x04, 0xe7, 0xfb));
	lv_style_set_line_width(&style_screen_1_line_1_main, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->screen_1_line_1, LV_LINE_PART_MAIN, &style_screen_1_line_1_main);
	lv_obj_set_pos(ui->screen_1_line_1, 193, 54);
	lv_obj_set_size(ui->screen_1_line_1, 60, 160);
	static lv_point_t screen_1_line_1[] ={{0,0},{0,150}};
	lv_line_set_points(ui->screen_1_line_1,screen_1_line_1,2);

	//Write codes screen_1_img_8
	ui->screen_1_img_8 = lv_img_create(ui->screen_1, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_8
	static lv_style_t style_screen_1_img_8_main;
	lv_style_reset(&style_screen_1_img_8_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_8_main
	lv_style_set_image_recolor(&style_screen_1_img_8_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_8_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_8_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_8, LV_IMG_PART_MAIN, &style_screen_1_img_8_main);
	lv_obj_set_pos(ui->screen_1_img_8, 266, 5);
	lv_obj_set_size(ui->screen_1_img_8, 15, 12);
	lv_obj_set_click(ui->screen_1_img_8, true);
	lv_img_set_src(ui->screen_1_img_8,&_wifi_alpha_15x12);
	lv_img_set_pivot(ui->screen_1_img_8, 0,0);
	lv_img_set_angle(ui->screen_1_img_8, 0);
}