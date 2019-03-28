
/* Includes ------------------------------------------------------------------*/
#include "main.h"

LTDC_HandleTypeDef hltdc;

/* USER CODE BEGIN PV */
uint32_t ColorTable[4] = {0x00FFFFFF, 0xFF0000, 0x00FF00, 0x0000FF};
uint8_t RGB565_240x320[240][320]={0x00000000};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_LTDC_Init(void);
				void DrawRectangle(int, int, int, int, int);
				void Clear(void);
 
int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_LTDC_Init();
	
	HAL_LTDC_EnableCLUT(&hltdc, 0);
	
	HAL_LTDC_ConfigCLUT(&hltdc, ColorTable, 4, 0);

	HAL_LTDC_SetAddress(&hltdc,(uint32_t)&RGB565_240x320, 0);
		uint8_t x = 0;
		uint8_t y = 0;
	
  while (1)
  {
		/*
		DrawRectangle(0, 0, 100, 100, 0);
			HAL_Delay(100);
		DrawRectangle(0, 0, 100, 100, 1);
			HAL_Delay(100);
		DrawRectangle(0, 0, 100, 100, 2);
			HAL_Delay(100);
		DrawRectangle(0, 0, 100, 100, 3);
			HAL_Delay(100);*/
	
		x++;
		y++;
		Clear();
		HAL_Delay(100);
		DrawRectangle(x, y, 100, 100, 2);
		HAL_Delay(500);
		
  }

}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};


  __HAL_RCC_PLL_PLLM_CONFIG(16);

  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 100;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_LTDC_Init(void)
{

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AH;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IIPC;
  hltdc.Init.HorizontalSync = 0;
  hltdc.Init.VerticalSync = 0;
  hltdc.Init.AccumulatedHBP = 70;
  hltdc.Init.AccumulatedVBP = 13;
  hltdc.Init.AccumulatedActiveW = 390;
  hltdc.Init.AccumulatedActiveH = 253;
  hltdc.Init.TotalWidth = 408;
  hltdc.Init.TotalHeigh = 263;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 320;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 240;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_L8;
  pLayerCfg.Alpha = 0xFF;
  pLayerCfg.Alpha0 = 0xFF;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = (uint32_t)&(RGB565_240x320[0][0]);
  pLayerCfg.ImageWidth = 320;
  pLayerCfg.ImageHeight = 240;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }

}

static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct = {0};
//--------------------------------------------
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void Error_Handler(void)
{

}

//------------------------------------------------------------------------------------------------
void DrawRectangle(int x, int y, int height, int width, int color)
{
	for (int i = x; i < x + width ; i++)
	{
		for (int j = y; j < y + height; j++)
		{
			RGB565_240x320[j][i] = color;
		}
	}
}


void Clear()
{
	uint32_t h = 240;
	uint32_t w = 320;
	for (int y = 0; y < w ; y++)
	{
		for (int x = 0; x < h; x++)
		{
			RGB565_240x320[x][y] = 0;
		}
	}
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
