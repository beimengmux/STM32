/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
//#include "custom.h"


void setup_scr_screen_1(lv_ui *ui){

	//Write codes screen_1
	ui->screen_1 = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for screen_1
	static lv_style_t style_screen_1_main;
	lv_style_reset(&style_screen_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_main
	lv_style_set_bg_color(&style_screen_1_main, LV_STATE_DEFAULT, lv_color_make(0xa4, 0xdb, 0xd0));
	lv_style_set_bg_opa(&style_screen_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1, LV_OBJ_PART_MAIN, &style_screen_1_main);

	//Write codes screen_1_cont_1
	ui->screen_1_cont_1 = lv_cont_create(ui->screen_1, NULL);

	//Write style LV_CONT_PART_MAIN for screen_1_cont_1
	static lv_style_t style_screen_1_cont_1_main;
	lv_style_reset(&style_screen_1_cont_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_cont_1_main
	lv_style_set_radius(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0x5c, 0x85, 0xb7));
	lv_style_set_bg_grad_color(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0xac, 0xb1, 0xc8));
	lv_style_set_bg_grad_dir(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, lv_color_make(0x38, 0x6b, 0x68));
	lv_style_set_border_width(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_cont_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_cont_1, LV_CONT_PART_MAIN, &style_screen_1_cont_1_main);
	lv_obj_set_pos(ui->screen_1_cont_1, 197, 42);
	lv_obj_set_size(ui->screen_1_cont_1, 123, 56);
	lv_obj_set_click(ui->screen_1_cont_1, false);

	//Write codes screen_1_label_18
	ui->screen_1_label_18 = lv_label_create(ui->screen_1_cont_1, NULL);
	lv_label_set_text(ui->screen_1_label_18, "23");
	lv_label_set_long_mode(ui->screen_1_label_18, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_18, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_18
	static lv_style_t style_screen_1_label_18_main;
	lv_style_reset(&style_screen_1_label_18_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_18_main
	lv_style_set_radius(&style_screen_1_label_18_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_18_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_18_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_18_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_18_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_18_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_18_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_18_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_18_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_18_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_18_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_18_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_18, LV_LABEL_PART_MAIN, &style_screen_1_label_18_main);
	lv_obj_set_pos(ui->screen_1_label_18, 59, 21);
	lv_obj_set_size(ui->screen_1_label_18, 38, 0);

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
	lv_obj_set_pos(ui->screen_1_img_3, 94, 20);
	lv_obj_set_size(ui->screen_1_img_3, 17, 17);
	lv_obj_set_click(ui->screen_1_img_3, true);
	lv_img_set_src(ui->screen_1_img_3,&_pictur3_alpha_17x17);
	lv_img_set_pivot(ui->screen_1_img_3, 0,0);
	lv_img_set_angle(ui->screen_1_img_3, 0);

	//Write codes screen_1_label_5
	ui->screen_1_label_5 = lv_label_create(ui->screen_1_cont_1, NULL);
	lv_label_set_text(ui->screen_1_label_5, "温度:");
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
	lv_style_set_text_color(&style_screen_1_label_5_main, LV_STATE_DEFAULT, lv_color_make(0x0f, 0x10, 0x10));
	lv_style_set_text_font(&style_screen_1_label_5_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_5_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_5_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_5, LV_LABEL_PART_MAIN, &style_screen_1_label_5_main);
	lv_obj_set_pos(ui->screen_1_label_5, 29, 21);
	lv_obj_set_size(ui->screen_1_label_5, 36, 0);

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
	lv_obj_set_pos(ui->screen_1_img_1, 2, 12);
	lv_obj_set_size(ui->screen_1_img_1, 30, 30);
	lv_obj_set_click(ui->screen_1_img_1, true);
	lv_img_set_src(ui->screen_1_img_1,&_1_alpha_30x30);
	lv_img_set_pivot(ui->screen_1_img_1, 0,0);
	lv_img_set_angle(ui->screen_1_img_1, 0);
	lv_cont_set_layout(ui->screen_1_cont_1, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->screen_1_cont_1, LV_FIT_NONE);

	//Write codes screen_1_cont_2
	ui->screen_1_cont_2 = lv_cont_create(ui->screen_1, NULL);

	//Write style LV_CONT_PART_MAIN for screen_1_cont_2
	static lv_style_t style_screen_1_cont_2_main;
	lv_style_reset(&style_screen_1_cont_2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_cont_2_main
	lv_style_set_radius(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, lv_color_make(0x12, 0xba, 0xba));
	lv_style_set_bg_grad_color(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, lv_color_make(0xda, 0x2f, 0x93));
	lv_style_set_bg_grad_dir(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_cont_2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_cont_2, LV_CONT_PART_MAIN, &style_screen_1_cont_2_main);
	lv_obj_set_pos(ui->screen_1_cont_2, 197, 105);
	lv_obj_set_size(ui->screen_1_cont_2, 123, 56);
	lv_obj_set_click(ui->screen_1_cont_2, false);

	//Write codes screen_1_label_17
	ui->screen_1_label_17 = lv_label_create(ui->screen_1_cont_2, NULL);
	lv_label_set_text(ui->screen_1_label_17, "%RH");
	lv_label_set_long_mode(ui->screen_1_label_17, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_17, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_17
	static lv_style_t style_screen_1_label_17_main;
	lv_style_reset(&style_screen_1_label_17_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_17_main
	lv_style_set_radius(&style_screen_1_label_17_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_17_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_17_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_17_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_17_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_17_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_17_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_17_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_17_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_17_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_17_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_17_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_17, LV_LABEL_PART_MAIN, &style_screen_1_label_17_main);
	lv_obj_set_pos(ui->screen_1_label_17, 80, 20);
	lv_obj_set_size(ui->screen_1_label_17, 28, 0);

	//Write codes screen_1_label_16
	ui->screen_1_label_16 = lv_label_create(ui->screen_1_cont_2, NULL);
	lv_label_set_text(ui->screen_1_label_16, "70");
	lv_label_set_long_mode(ui->screen_1_label_16, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_16, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_16
	static lv_style_t style_screen_1_label_16_main;
	lv_style_reset(&style_screen_1_label_16_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_16_main
	lv_style_set_radius(&style_screen_1_label_16_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_16_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_16_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_16_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_16_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_16_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_16_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_16_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_16_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_16_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_16_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_16_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_16, LV_LABEL_PART_MAIN, &style_screen_1_label_16_main);
	lv_obj_set_pos(ui->screen_1_label_16, 65, 20);
	lv_obj_set_size(ui->screen_1_label_16, 17, 0);

	//Write codes screen_1_label_6
	ui->screen_1_label_6 = lv_label_create(ui->screen_1_cont_2, NULL);
	lv_label_set_text(ui->screen_1_label_6, "湿度:");
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
	lv_style_set_text_color(&style_screen_1_label_6_main, LV_STATE_DEFAULT, lv_color_make(0x07, 0x08, 0x08));
	lv_style_set_text_font(&style_screen_1_label_6_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_6_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_6_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_6_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_6, LV_LABEL_PART_MAIN, &style_screen_1_label_6_main);
	lv_obj_set_pos(ui->screen_1_label_6, 30, 20);
	lv_obj_set_size(ui->screen_1_label_6, 37, 0);

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
	lv_obj_set_pos(ui->screen_1_img_2, 2, 11);
	lv_obj_set_size(ui->screen_1_img_2, 30, 30);
	lv_obj_set_click(ui->screen_1_img_2, true);
	lv_img_set_src(ui->screen_1_img_2,&_2_alpha_30x30);
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
	lv_style_set_text_color(&style_screen_1_label_7_main, LV_STATE_DEFAULT, lv_color_make(0x0c, 0x03, 0x03));
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
	lv_style_set_radius(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 65);
	lv_style_set_bg_color(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, lv_color_make(0x6f, 0xce, 0xb6));
	lv_style_set_bg_grad_color(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, lv_color_make(0xd9, 0xa1, 0x6d));
	lv_style_set_bg_grad_dir(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_cont_3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_cont_3, LV_CONT_PART_MAIN, &style_screen_1_cont_3_main);
	lv_obj_set_pos(ui->screen_1_cont_3, 0, 83);
	lv_obj_set_size(ui->screen_1_cont_3, 123, 56);
	lv_obj_set_click(ui->screen_1_cont_3, false);

	//Write codes screen_1_label_20
	ui->screen_1_label_20 = lv_label_create(ui->screen_1_cont_3, NULL);
	lv_label_set_text(ui->screen_1_label_20, "PPM");
	lv_label_set_long_mode(ui->screen_1_label_20, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_20, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_20
	static lv_style_t style_screen_1_label_20_main;
	lv_style_reset(&style_screen_1_label_20_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_20_main
	lv_style_set_radius(&style_screen_1_label_20_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_20_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_20_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_20_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_20_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_20_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_20_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_20_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_20_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_20_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_20_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_20_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_20, LV_LABEL_PART_MAIN, &style_screen_1_label_20_main);
	lv_obj_set_pos(ui->screen_1_label_20, 85, 27);
	lv_obj_set_size(ui->screen_1_label_20, 26, 0);

	//Write codes screen_1_label_19
	ui->screen_1_label_19 = lv_label_create(ui->screen_1_cont_3, NULL);
	lv_label_set_text(ui->screen_1_label_19, "300");
	lv_label_set_long_mode(ui->screen_1_label_19, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_19, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_19
	static lv_style_t style_screen_1_label_19_main;
	lv_style_reset(&style_screen_1_label_19_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_19_main
	lv_style_set_radius(&style_screen_1_label_19_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_19_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_19_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_19_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_19_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_19_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_19_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_19_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_19_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_19_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_19_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_19_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_19, LV_LABEL_PART_MAIN, &style_screen_1_label_19_main);
	lv_obj_set_pos(ui->screen_1_label_19, 49, 28);
	lv_obj_set_size(ui->screen_1_label_19, 33, 0);

	//Write codes screen_1_label_9
	ui->screen_1_label_9 = lv_label_create(ui->screen_1_cont_3, NULL);
	lv_label_set_text(ui->screen_1_label_9, "二氧化碳");
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
	lv_style_set_bg_opa(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_9_main, LV_STATE_DEFAULT, lv_color_make(0x0f, 0x10, 0x10));
	lv_style_set_text_font(&style_screen_1_label_9_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_9_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_9, LV_LABEL_PART_MAIN, &style_screen_1_label_9_main);
	lv_obj_set_pos(ui->screen_1_label_9, 1, 3);
	lv_obj_set_size(ui->screen_1_label_9, 126, 0);

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
	lv_obj_set_pos(ui->screen_1_img_5, 13, 13);
	lv_obj_set_size(ui->screen_1_img_5, 30, 30);
	lv_obj_set_click(ui->screen_1_img_5, true);
	lv_img_set_src(ui->screen_1_img_5,&_5_alpha_30x30);
	lv_img_set_pivot(ui->screen_1_img_5, 0,0);
	lv_img_set_angle(ui->screen_1_img_5, 0);
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

	//Write codes screen_1_cont_4
	ui->screen_1_cont_4 = lv_cont_create(ui->screen_1, NULL);

	//Write style LV_CONT_PART_MAIN for screen_1_cont_4
	static lv_style_t style_screen_1_cont_4_main;
	lv_style_reset(&style_screen_1_cont_4_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_cont_4_main
	lv_style_set_radius(&style_screen_1_cont_4_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_1_cont_4_main, LV_STATE_DEFAULT, lv_color_make(0x5b, 0xe6, 0x77));
	lv_style_set_bg_grad_color(&style_screen_1_cont_4_main, LV_STATE_DEFAULT, lv_color_make(0x89, 0xe1, 0xc8));
	lv_style_set_bg_grad_dir(&style_screen_1_cont_4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_screen_1_cont_4_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_1_cont_4_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_screen_1_cont_4_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_1_cont_4_main, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_screen_1_cont_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_cont_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_cont_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_cont_4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_cont_4, LV_CONT_PART_MAIN, &style_screen_1_cont_4_main);
	lv_obj_set_pos(ui->screen_1_cont_4, 197, 168);
	lv_obj_set_size(ui->screen_1_cont_4, 123, 56);
	lv_obj_set_click(ui->screen_1_cont_4, false);

	//Write codes screen_1_label_15
	ui->screen_1_label_15 = lv_label_create(ui->screen_1_cont_4, NULL);
	lv_label_set_text(ui->screen_1_label_15, "21:41:45");
	lv_label_set_long_mode(ui->screen_1_label_15, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_15, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_15
	static lv_style_t style_screen_1_label_15_main;
	lv_style_reset(&style_screen_1_label_15_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_15_main
	lv_style_set_radius(&style_screen_1_label_15_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_15_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_15_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_15_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_15_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_15_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_15_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_15_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_15_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_15_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_15_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_15_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_15, LV_LABEL_PART_MAIN, &style_screen_1_label_15_main);
	lv_obj_set_pos(ui->screen_1_label_15, 20, 30);
	lv_obj_set_size(ui->screen_1_label_15, 100, 0);

	//Write codes screen_1_label_14
	ui->screen_1_label_14 = lv_label_create(ui->screen_1_cont_4, NULL);
	lv_label_set_text(ui->screen_1_label_14, "2023/8/18");
	lv_label_set_long_mode(ui->screen_1_label_14, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_14, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_14
	static lv_style_t style_screen_1_label_14_main;
	lv_style_reset(&style_screen_1_label_14_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_14_main
	lv_style_set_radius(&style_screen_1_label_14_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_14_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_14_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_14_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_14_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_14_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_14_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_14_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_14_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_14_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_14_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_14_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_14, LV_LABEL_PART_MAIN, &style_screen_1_label_14_main);
	lv_obj_set_pos(ui->screen_1_label_14, 20, 11);
	lv_obj_set_size(ui->screen_1_label_14, 100, 0);

	//Write codes screen_1_img_9
	ui->screen_1_img_9 = lv_img_create(ui->screen_1_cont_4, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_9
	static lv_style_t style_screen_1_img_9_main;
	lv_style_reset(&style_screen_1_img_9_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_9_main
	lv_style_set_image_recolor(&style_screen_1_img_9_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_9_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_9_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_9, LV_IMG_PART_MAIN, &style_screen_1_img_9_main);
	lv_obj_set_pos(ui->screen_1_img_9, 3, 12);
	lv_obj_set_size(ui->screen_1_img_9, 30, 30);
	lv_obj_set_click(ui->screen_1_img_9, true);
	lv_img_set_src(ui->screen_1_img_9,&_3_alpha_30x30);
	lv_img_set_pivot(ui->screen_1_img_9, 0,0);
	lv_img_set_angle(ui->screen_1_img_9, 0);
	lv_cont_set_layout(ui->screen_1_cont_4, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->screen_1_cont_4, LV_FIT_NONE);

	//Write codes screen_1_cont_5
	ui->screen_1_cont_5 = lv_cont_create(ui->screen_1, NULL);

	//Write style LV_CONT_PART_MAIN for screen_1_cont_5
	static lv_style_t style_screen_1_cont_5_main;
	lv_style_reset(&style_screen_1_cont_5_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_cont_5_main
	lv_style_set_radius(&style_screen_1_cont_5_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_1_cont_5_main, LV_STATE_DEFAULT, lv_color_make(0x14, 0x77, 0x90));
	lv_style_set_bg_grad_color(&style_screen_1_cont_5_main, LV_STATE_DEFAULT, lv_color_make(0x8b, 0xca, 0xdf));
	lv_style_set_bg_grad_dir(&style_screen_1_cont_5_main, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_screen_1_cont_5_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_1_cont_5_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_screen_1_cont_5_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_1_cont_5_main, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_screen_1_cont_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_cont_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_cont_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_cont_5_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_cont_5, LV_CONT_PART_MAIN, &style_screen_1_cont_5_main);
	lv_obj_set_pos(ui->screen_1_cont_5, 0, 155);
	lv_obj_set_size(ui->screen_1_cont_5, 123, 56);
	lv_obj_set_click(ui->screen_1_cont_5, false);

	//Write codes screen_1_label_23
	ui->screen_1_label_23 = lv_label_create(ui->screen_1_cont_5, NULL);
	lv_label_set_text(ui->screen_1_label_23, "甲醛");
	lv_label_set_long_mode(ui->screen_1_label_23, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_23, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_23
	static lv_style_t style_screen_1_label_23_main;
	lv_style_reset(&style_screen_1_label_23_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_23_main
	lv_style_set_radius(&style_screen_1_label_23_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_23_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_23_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_23_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_23_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_23_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_23_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_23_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_23_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_23_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_23_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_23_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_23, LV_LABEL_PART_MAIN, &style_screen_1_label_23_main);
	lv_obj_set_pos(ui->screen_1_label_23, 9, 4);
	lv_obj_set_size(ui->screen_1_label_23, 100, 0);

	//Write codes screen_1_img_10
	ui->screen_1_img_10 = lv_img_create(ui->screen_1_cont_5, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_10
	static lv_style_t style_screen_1_img_10_main;
	lv_style_reset(&style_screen_1_img_10_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_10_main
	lv_style_set_image_recolor(&style_screen_1_img_10_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_10_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_10_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_10, LV_IMG_PART_MAIN, &style_screen_1_img_10_main);
	lv_obj_set_pos(ui->screen_1_img_10, 12, 20);
	lv_obj_set_size(ui->screen_1_img_10, 20, 20);
	lv_obj_set_click(ui->screen_1_img_10, true);
	lv_img_set_src(ui->screen_1_img_10,&_6_alpha_20x20);
	lv_img_set_pivot(ui->screen_1_img_10, 0,0);
	lv_img_set_angle(ui->screen_1_img_10, 0);

	//Write codes screen_1_label_22
	ui->screen_1_label_22 = lv_label_create(ui->screen_1_cont_5, NULL);
	lv_label_set_text(ui->screen_1_label_22, "mg/m3");
	lv_label_set_long_mode(ui->screen_1_label_22, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_22, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_22
	static lv_style_t style_screen_1_label_22_main;
	lv_style_reset(&style_screen_1_label_22_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_22_main
	lv_style_set_radius(&style_screen_1_label_22_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_22_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_22_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_22_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_22_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_22_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_22_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_22_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_22_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_22_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_22_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_22_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_22, LV_LABEL_PART_MAIN, &style_screen_1_label_22_main);
	lv_obj_set_pos(ui->screen_1_label_22, 74, 23);
	lv_obj_set_size(ui->screen_1_label_22, 41, 0);

	//Write codes screen_1_label_21
	ui->screen_1_label_21 = lv_label_create(ui->screen_1_cont_5, NULL);
	lv_label_set_text(ui->screen_1_label_21, "0.01");
	lv_label_set_long_mode(ui->screen_1_label_21, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_21, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_21
	static lv_style_t style_screen_1_label_21_main;
	lv_style_reset(&style_screen_1_label_21_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_21_main
	lv_style_set_radius(&style_screen_1_label_21_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_21_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_21_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_21_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_21_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_21_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_21_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_21_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_21_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_21_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_21_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_21_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_21, LV_LABEL_PART_MAIN, &style_screen_1_label_21_main);
	lv_obj_set_pos(ui->screen_1_label_21, 43, 24);
	lv_obj_set_size(ui->screen_1_label_21, 34, 0);
	lv_cont_set_layout(ui->screen_1_cont_5, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->screen_1_cont_5, LV_FIT_NONE);

	//Write codes screen_1_label_24
	ui->screen_1_label_24 = lv_label_create(ui->screen_1, NULL);
	lv_label_set_text(ui->screen_1_label_24, "3500");
	lv_label_set_long_mode(ui->screen_1_label_24, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_24, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_24
	static lv_style_t style_screen_1_label_24_main;
	lv_style_reset(&style_screen_1_label_24_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_24_main
	lv_style_set_radius(&style_screen_1_label_24_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_24_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_24_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_24_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_24_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_24_main, LV_STATE_DEFAULT, lv_color_make(0xb8, 0x92, 0x0a));
	lv_style_set_text_font(&style_screen_1_label_24_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_24_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_24_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_24_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_24_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_24_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_24, LV_LABEL_PART_MAIN, &style_screen_1_label_24_main);
	lv_obj_set_pos(ui->screen_1_label_24, 23, 37);
	lv_obj_set_size(ui->screen_1_label_24, 100, 0);

	//Write codes screen_1_img_11
	ui->screen_1_img_11 = lv_img_create(ui->screen_1, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_11
	static lv_style_t style_screen_1_img_11_main;
	lv_style_reset(&style_screen_1_img_11_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_11_main
	lv_style_set_image_recolor(&style_screen_1_img_11_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_11_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_11_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_11, LV_IMG_PART_MAIN, &style_screen_1_img_11_main);
	lv_obj_set_pos(ui->screen_1_img_11, 10.5, 22.5);
	lv_obj_set_size(ui->screen_1_img_11, 35, 35);
	lv_obj_set_click(ui->screen_1_img_11, true);
	lv_img_set_src(ui->screen_1_img_11,&_pic_alpha_35x35);
	lv_img_set_pivot(ui->screen_1_img_11, 0,0);
	lv_img_set_angle(ui->screen_1_img_11, 0);

	//Write codes screen_1_img_12
	ui->screen_1_img_12 = lv_img_create(ui->screen_1, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_12
	static lv_style_t style_screen_1_img_12_main;
	lv_style_reset(&style_screen_1_img_12_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_12_main
	lv_style_set_image_recolor(&style_screen_1_img_12_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_12_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_12_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_12, LV_IMG_PART_MAIN, &style_screen_1_img_12_main);
	lv_obj_set_pos(ui->screen_1_img_12, 111, 140);
	lv_obj_set_size(ui->screen_1_img_12, 95, 100);
	lv_obj_set_click(ui->screen_1_img_12, true);
	lv_img_set_src(ui->screen_1_img_12,&_5_alpha_95x100);
	lv_img_set_pivot(ui->screen_1_img_12, 0,0);
	lv_img_set_angle(ui->screen_1_img_12, 0);

	//Write codes screen_1_img_13
	ui->screen_1_img_13 = lv_img_create(ui->screen_1, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_13
	static lv_style_t style_screen_1_img_13_main;
	lv_style_reset(&style_screen_1_img_13_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_13_main
	lv_style_set_image_recolor(&style_screen_1_img_13_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_13_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_13_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_13, LV_IMG_PART_MAIN, &style_screen_1_img_13_main);
	lv_obj_set_pos(ui->screen_1_img_13, 128, 99);
	lv_obj_set_size(ui->screen_1_img_13, 35, 35);
	lv_obj_set_click(ui->screen_1_img_13, true);
	lv_img_set_src(ui->screen_1_img_13,&_6_alpha_35x35);
	lv_img_set_pivot(ui->screen_1_img_13, 0,0);
	lv_img_set_angle(ui->screen_1_img_13, 0);
}
