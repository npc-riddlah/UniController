#include "stm32f1xx_hal.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "pins.h"
#include "l10n.h"
#include "theme.h"

void screen_draw_page(int id_page, int id_item) //TODO: Reorganize arrays into something better
{
	char str_id_page[6];
	char str_id_item[6];
	itoa(id_page, str_id_page, PARAM_PAGE_COUNT);
	//itoa(id_item, str_id_item, 10);
	screen_draw_helper(L10N_BUT_PAGE_PREV, L10N_BUT_SLEEP, L10N_BUT_UP, L10N_BUT_DOWN, L10N_BUT_PAGE_NEXT, L10N_BUT_OK);
	switch (id_page)
	{
	case 0:;
		char txt_label0[2][PARAM_DATA_BLOCK_COUNT][25] = {{"memes", "pivo", "hitler", "nigger!", "kaef", "govno", "dudes", "pelmeni"},{"15%","0%","2%","0%","60%","3%","7%","10%"}};
		screen_draw_data(txt_label0);
	break;

	case 1:;
		char txt_label1[10][25] = {"memes", "pivo", "hitler", "nigger!", "piss on you!"};
		screen_draw_menu(txt_label1, 5, id_item);
	break;

	case 2:
		ILI9341_DrawText(L10N_PAG_NAM_MEMES1, FONT4, 10, 40, COL_TXT_PAGE, COL_BG_PAGE);
		ILI9341_DrawText(L10N_PAG_NAM_MEMES2, FONT4, 10, 60, COL_TXT_PAGE, COL_BG_PAGE);
	break;

	case 3:;
		char txt_label2[10][25] = {"welcome", "to", "my", "gachi", "dungeon", "master", "oooooh!", "MEMES!"};
		screen_draw_menu(txt_label2, 8, id_item);
	break;

	default:
		ILI9341_DrawText(L10N_ID_ERROR, FONT_PAGE, 10, 40, COL_TXT_PAGE, COL_BG_PAGE);
	break;
	}
	screen_draw_statusbar(str_id_page);
}

void screen_draw_helper(char txt_b1[10], char txt_b2[10], char txt_b3[10], char txt_b4[10], char txt_b5[10], char txt_b6[10])
{
	ILI9341_DrawText(txt_b1, FONT_HELPER, POS_HELPER_B1, COL_TXT_HELPER, COL_BG_HELPER);
	ILI9341_DrawText(txt_b2, FONT_HELPER, POS_HELPER_B2, COL_TXT_HELPER, COL_BG_HELPER);
	ILI9341_DrawText(txt_b3, FONT_HELPER, POS_HELPER_B3, COL_TXT_HELPER, COL_BG_HELPER);
	ILI9341_DrawText(txt_b4, FONT_HELPER, POS_HELPER_B4, COL_TXT_HELPER, COL_BG_HELPER);
	ILI9341_DrawText(txt_b5, FONT_HELPER, POS_HELPER_B5, COL_TXT_HELPER, COL_BG_HELPER);
	ILI9341_DrawText(txt_b6, FONT_HELPER, POS_HELPER_B6, COL_TXT_HELPER, COL_BG_HELPER);
}

void screen_draw_statusbar(char str_text[6])
{
	ILI9341_DrawRectangle(0, 0, 320, PARAM_WIDTH_STATUSBAR, COL_BG_STATUSBAR);
	ILI9341_DrawText(str_text, FONT_STATUSBAR, 1, 1, COL_TXT_STATUSBAR, COL_BG_STATUSBAR);
}

void screen_draw_menu(char txt_items[10][25], uint16_t arr_length, int id_select)
{

	if (id_select>=arr_length) id_select=arr_length-1;
	for (int y=0; y<arr_length; y++){
		ILI9341_DrawHLine(0, (y*PARAM_WIDTH_MENUBAR)+PARAM_WIDTH_STATUSBAR, 320, COL_MENU_LINES);
		if (y==id_select)
		{
			ILI9341_DrawRectangle(0, (y*PARAM_WIDTH_MENUBAR)+PARAM_WIDTH_STATUSBAR+1, 320, PARAM_WIDTH_MENUBAR-1, COL_BG_PAGE_SELECT);
			ILI9341_DrawText(txt_items[y], FONT_MENU, 1, (y*PARAM_WIDTH_MENUBAR)+PARAM_WIDTH_STATUSBAR+1, COL_TXT_MENUBAR_SELECT, COL_BG_PAGE_SELECT);
		}
		else
		{
			ILI9341_DrawText(txt_items[y], FONT_MENU, 1, (y*PARAM_WIDTH_MENUBAR)+PARAM_WIDTH_STATUSBAR+1, COL_TXT_MENUBAR, COL_BG_PAGE);
		}
	}
	ILI9341_DrawHLine(0, (arr_length*PARAM_WIDTH_MENUBAR)+PARAM_WIDTH_STATUSBAR, 320, COL_MENU_LINES);
}

void screen_draw_data(char txt_items[2][PARAM_DATA_BLOCK_COUNT][25])
{

	for (int i=0; i<PARAM_DATA_BLOCK_COUNT/2; i++){
		screen_draw_data_block(txt_items[0][i], txt_items[1][i], PARAM_DATA_BLOCK_SIZE, PARAM_DATA_BLOCK_SIZE, i*PARAM_DATA_BLOCK_SIZE, PARAM_WIDTH_STATUSBAR, BLACK);
	}
	for (int i=0; i<PARAM_DATA_BLOCK_COUNT/2; i++){
		screen_draw_data_block(txt_items[0][i+PARAM_DATA_BLOCK_COUNT/2], txt_items[1][i+PARAM_DATA_BLOCK_COUNT/2], PARAM_DATA_BLOCK_SIZE, PARAM_DATA_BLOCK_SIZE, i*PARAM_DATA_BLOCK_SIZE, PARAM_WIDTH_STATUSBAR+PARAM_DATA_BLOCK_SIZE, BLACK);
	}

}

void screen_draw_data_block(char txt_item_label[25], char txt_item_prop[6], uint16_t size_x, uint16_t size_y, uint16_t pos_x, uint16_t pos_y, uint16_t col_border)
{
	ILI9341_DrawHollowRectangleCoord(pos_x, pos_y, pos_x+size_x, pos_y+size_y, col_border);
	ILI9341_DrawText(txt_item_label, FONT_DATA_SMALL, pos_x+size_x/3, pos_y+5, COL_TXT_DATA_SMALL, COL_BG_DATA_SMALL);
	ILI9341_DrawText(txt_item_prop, FONT_DATA_BIG, pos_x+size_x/3, pos_y+size_y/2, COL_TXT_DATA_BIG, COL_BG_DATA_BIG);
}

void screen_draw_plaintext(char str_text[255], uint16_t size_x, uint16_t size_y, uint16_t pos_x, uint16_t pos_y)
{

}
void screen_draw_chart(void)
{

}

void screen_draw_settings(void)
{

}
