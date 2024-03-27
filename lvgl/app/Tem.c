/*******************************************************************************
 * Size: 36 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef TEM
#define TEM 1
#endif

#if TEM

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E71C "" */
    0xf, 0x0, 0x3, 0xc0, 0x3e, 0x80, 0x5, 0xe0,
    0x5f, 0xc0, 0xb, 0xf0, 0x3f, 0xc0, 0xf, 0xf0,
    0x3f, 0xc0, 0xf, 0xf0, 0x3f, 0xc0, 0xf, 0xf0,
    0x3f, 0xc0, 0xf, 0xf0, 0x3f, 0xc0, 0xf, 0xf0,
    0x3f, 0xc0, 0xf, 0xf0, 0x3f, 0xc0, 0xf, 0xf0,
    0x3f, 0xdc, 0xf, 0xf0, 0x3f, 0xc0, 0xf, 0xf0,
    0x3f, 0xdc, 0xf, 0xf0, 0x3f, 0xc0, 0xf, 0xf0,
    0x3f, 0xdc, 0xf, 0xf0, 0x3f, 0xc0, 0xf, 0xf0,
    0x3f, 0xdc, 0xf, 0xf7, 0x3f, 0xdc, 0xf, 0xf7,
    0x3f, 0xc0, 0xf, 0xf0, 0x3f, 0xdc, 0xf, 0xf7,
    0x3f, 0xc0, 0xf, 0xf0, 0x3f, 0xdc, 0xf, 0xf7,
    0x3f, 0xc0, 0xf, 0xf0, 0x3f, 0xc0, 0xf, 0xf0,
    0xff, 0xa0, 0x17, 0xf8, 0xff, 0xd0, 0x2f, 0xf4,
    0xff, 0xe8, 0x3f, 0xfc, 0xff, 0xe8, 0x5f, 0xfc,
    0xbf, 0xf8, 0x5f, 0xfc, 0xff, 0xe8, 0x5f, 0xfc,
    0xff, 0xe8, 0x7f, 0xfc, 0xbf, 0xd0, 0x2f, 0xfc,
    0x7f, 0xd0, 0x1f, 0xf8, 0x3f, 0x20, 0x13, 0xf0,
    0x1f, 0xc0, 0xf, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 576, .box_w = 32, .box_h = 35, .ofs_x = 2, .ofs_y = -4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 59164, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t Tem = {
#else
lv_font_t Tem = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 35,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if TEM*/

