/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "theme.h"
#include "l10n.h"
#include "pins.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int id_page=0;
int id_item=0;
char str_id_page[6];
char str_id_item[6];
/* USER CODE END 0 */


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */

  ILI9341_Init();
 // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
  ILI9341_FillScreen(BLACK);
  ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
  ILI9341_DrawText("STARTING...", FONT4, 90, 110, BLACK, WHITE);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  ILI9341_DrawRectangle(0, 0, 320, 240, COL_BG_PAGE);
  while (1)
  {
	  itoa(id_page, str_id_page, PARAM_PAGE_COUNT);
	  itoa(id_item, str_id_item, 10);
	  os_worker_buttons(id_page);
	  screen_draw_page(id_page);
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* SPI1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SPI1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(SPI1_IRQn);
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB10 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void screen_draw_page(int page) //TODO: Reorganize arrays into something better
{
	switch (page)
	{
	case 0:;
		char txt_label0[2][PARAM_DATA_BLOCK_COUNT][25] = {{"memes", "pivo", "hitler", "nigger!", "kaef", "govno", "dudes", "pelmeni"},{"15%","0%","2%","0%","60%","3%","7%","10%"}};
		screen_draw_data(txt_label0);
	break;

	case 1:;
		char txt_label1[10][25] = {"memes", "pivo", "hitler", "nigger!", "piss on you!"};
		screen_draw_menu(txt_label1, 5);
	break;

	case 2:
		ILI9341_DrawText(L10N_PAG_NAM_MEMES1, FONT4, 10, 40, COL_TXT_PAGE, COL_BG_PAGE);
		ILI9341_DrawText(L10N_PAG_NAM_MEMES2, FONT4, 10, 60, COL_TXT_PAGE, COL_BG_PAGE);
	break;

	case 3:;
		char txt_label2[10][25] = {"welcome", "to", "my", "gachi", "dungeon", "master", "oooooh!", "MEMES!"};
		screen_draw_menu(txt_label2, 8);
	break;

	default:
		ILI9341_DrawText(L10N_ID_ERROR, FONT_PAGE, 10, 40, COL_TXT_PAGE, COL_BG_PAGE);
	break;
	}
	screen_draw_statusbar(page);
}

void screen_draw_helper(char* txt_b1, char* txt_b2, char* txt_b3, char* txt_b4, char* txt_b5, char* txt_b6)
{
	ILI9341_DrawText(txt_b1, FONT_HELPER, POS_HELPER_B1, COL_TXT_HELPER, COL_BG_HELPER);
	ILI9341_DrawText(txt_b2, FONT_HELPER, POS_HELPER_B2, COL_TXT_HELPER, COL_BG_HELPER);
	ILI9341_DrawText(txt_b3, FONT_HELPER, POS_HELPER_B3, COL_TXT_HELPER, COL_BG_HELPER);
	ILI9341_DrawText(txt_b4, FONT_HELPER, POS_HELPER_B4, COL_TXT_HELPER, COL_BG_HELPER);
	ILI9341_DrawText(txt_b5, FONT_HELPER, POS_HELPER_B5, COL_TXT_HELPER, COL_BG_HELPER);
	ILI9341_DrawText(txt_b6, FONT_HELPER, POS_HELPER_B6, COL_TXT_HELPER, COL_BG_HELPER);
}

void screen_draw_statusbar(uint8_t id_mode)
{
	char out[50];
	ILI9341_DrawRectangle(0, 0, 320, PARAM_WIDTH_STATUSBAR, COL_BG_STATUSBAR);
	switch (id_mode)
	{
	case 0:;
		strcpy(out, L10N_BAR_DATA);
		strcat(out, " | ");
		strcat(out, L10N_BAR_PAGE);
		strcat(out, ": ");
		strcat(out, str_id_page);
		strcat(out, " | ");
		ILI9341_DrawText(out, FONT_STATUSBAR, 1, 1, COL_TXT_STATUSBAR, COL_BG_STATUSBAR);
	break;
	case 1:;
		strcpy(out, L10N_BAR_MENU);
		strcat(out, " | ");
		strcat(out, L10N_BAR_PAGE);
		strcat(out, ": ");
		strcat(out, str_id_page);
		strcat(out, " | ");
		strcat(out, L10N_BAR_ITEM);
		strcat(out, ": ");
		strcat(out, str_id_item);
		ILI9341_DrawText(out, FONT_STATUSBAR, 1, 1, COL_TXT_STATUSBAR, COL_BG_STATUSBAR);
	break;
	case 2:
		strcpy(out, L10N_BAR_VER);
		strcat(out, " | ");
		strcat(out, L10N_BAR_PAGE);
		strcat(out, ": ");
		strcat(out, str_id_page);
		ILI9341_DrawText(out, FONT_STATUSBAR, 1, 1, COL_TXT_STATUSBAR, COL_BG_STATUSBAR);
	break;
	case 3:;
		strcpy(out, L10N_BAR_MENU);
		strcat(out, " | ");
		strcat(out, L10N_BAR_PAGE);
		strcat(out, ": ");
		strcat(out, str_id_page);
		strcat(out, " | ");
		strcat(out, L10N_BAR_ITEM);
		strcat(out, ": ");
		strcat(out, str_id_item);
		ILI9341_DrawText(out, FONT_STATUSBAR, 1, 1, COL_TXT_STATUSBAR, COL_BG_STATUSBAR);
	break;
	default:
		ILI9341_DrawText(L10N_ID_ERROR, FONT_STATUSBAR, 1, 1, COL_TXT_STATUSBAR, COL_BG_STATUSBAR);
	break;
	}
}

void screen_draw_menu(char txt_items[10][25], uint16_t arr_length)
{

	if (id_item>=arr_length) id_item=arr_length-1;
	for (int y=0; y<arr_length; y++){
		ILI9341_DrawHLine(0, (y*PARAM_WIDTH_MENUBAR)+PARAM_WIDTH_STATUSBAR, 320, COL_MENU_LINES);
		if (y==id_item)
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

//Rewrite it on "For" cycle please, fucking imbecil
void screen_draw_data(char txt_items[2][PARAM_DATA_BLOCK_COUNT][25])
{

	for (int i=0; i<PARAM_DATA_BLOCK_COUNT/2; i++){
		screen_draw_data_block(txt_items[0][i], txt_items[1][i], PARAM_DATA_BLOCK_SIZE, PARAM_DATA_BLOCK_SIZE, i*PARAM_DATA_BLOCK_SIZE, PARAM_WIDTH_STATUSBAR, BLACK);
	}
	for (int i=0; i<PARAM_DATA_BLOCK_COUNT/2; i++){
		screen_draw_data_block(txt_items[0][i+PARAM_DATA_BLOCK_COUNT/2], txt_items[1][i+PARAM_DATA_BLOCK_COUNT/2], PARAM_DATA_BLOCK_SIZE, PARAM_DATA_BLOCK_SIZE, i*PARAM_DATA_BLOCK_SIZE, PARAM_WIDTH_STATUSBAR+PARAM_DATA_BLOCK_SIZE, BLACK);
	}

}

void screen_draw_data_block(char* txt_item_label, char* txt_item_prop, uint16_t size_x, uint16_t size_y, uint16_t pos_x, uint16_t pos_y, uint16_t col_border){
	ILI9341_DrawHollowRectangleCoord(pos_x, pos_y, pos_x+size_x, pos_y+size_y, col_border);
	ILI9341_DrawText(txt_item_label, FONT_DATA_SMALL, pos_x+size_x/3, pos_y+5, COL_TXT_DATA_SMALL, COL_BG_DATA_SMALL);
	ILI9341_DrawText(txt_item_prop, FONT_DATA_BIG, pos_x+size_x/3, pos_y+size_y/2, COL_TXT_DATA_BIG, COL_BG_DATA_BIG);
}

//Rewrite that shit please (Maybe EXTI?)
void os_worker_buttons(uint8_t id_mode)
{
		switch (id_mode){
		default:
			screen_draw_helper(L10N_BUT_PAGE_PREV, L10N_BUT_SLEEP, L10N_BUT_UP, L10N_BUT_DOWN, L10N_BUT_PAGE_NEXT, L10N_BUT_OK);
			if (HAL_GPIO_ReadPin(PIN_BUT1))
			{
				  id_page--;
				  if (id_page<0) id_page=PARAM_PAGE_COUNT-1;
				  HAL_Delay(PARAM_DELAY_KEYS);
				  ILI9341_DrawRectangle(0, 0, 320, 240, COL_BG_PAGE);
			}
			if (HAL_GPIO_ReadPin(PIN_BUT5))
			{
				  id_page++;
				  if (id_page>PARAM_PAGE_COUNT-1) id_page=0;
				  HAL_Delay(PARAM_DELAY_KEYS);
				  ILI9341_DrawRectangle(0, 0, 320, 240, COL_BG_PAGE);
			}
			if (HAL_GPIO_ReadPin(PIN_BUT3))
			{
				  id_item--;
				  if (id_item<0) id_item=0;
				  HAL_Delay(PARAM_DELAY_KEYS);
				  ILI9341_DrawRectangle(0, 0, 320, 240, COL_BG_PAGE);
			}
			if (HAL_GPIO_ReadPin(PIN_BUT4))
			{
				  id_item++;
				  if (id_item>9) id_item=9;
				  HAL_Delay(PARAM_DELAY_KEYS);
				  ILI9341_DrawRectangle(0, 0, 320, 240, COL_BG_PAGE);
			}
			if (HAL_GPIO_ReadPin(PIN_BUT5))
			{

			}
			if (HAL_GPIO_ReadPin(PIN_BUT6))
			{

			}
		break;
		}
}

//Somehow..................
void os_worker_modloader(void)
{

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

