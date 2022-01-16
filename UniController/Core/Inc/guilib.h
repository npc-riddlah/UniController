#include "stm32f1xx_hal.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "pins.h"
#include "l10n.h"
#include "theme.h"

#ifndef __GUILIB_H__
#define __GUILIB_H__

void screen_draw_page(int id_page, int id_item);
void screen_draw_helper(char txt_b1, char txt_b2, char txt_b3, char txt_b4, char txt_b5, char txt_b6);
void screen_draw_statusbar(char str_text[50]);
void screen_draw_menu(char txt_items[10][25], uint16_t arr_length, int id_select);
void screen_draw_data_block(char txt_item_label, char txt_item_prop, uint16_t size_x, uint16_t size_y, uint16_t pos_x, uint16_t pos_y, uint16_t col_border);
void screen_draw_data(char txt_items[2][PARAM_DATA_BLOCK_COUNT][25]);
void screen_draw_plaintext(char str_text[255], uint16_t size_x, uint16_t size_y, uint16_t pos_x, uint16_t pos_y);
void screen_draw_chart(void);
void screen_draw_settings(void);

#endif
