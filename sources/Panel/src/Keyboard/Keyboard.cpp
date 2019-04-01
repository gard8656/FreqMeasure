//dodelat vibor knopki i sdelat 4erez define nazvaniya knopok 4tob vozvrs4alo
#include "HAL.h"
#include "stm32f4xx_hal.h"
#include "Keyboard.h"

#define Button_0 11;
#define Button_1 12;
#define Button_2 13;
#define Button_3 14;
#define Button_4 15;

int button;
int ChoisePin();
int ChoiseButton(int);

void Keyboard::Update()
{
	
	/*HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);// + set
    if(ChoisePin() != 0)
    {
		int ChoiseButton(10);
    }
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
    if(ChoisePin() != 0)
    {
		int ChoiseButton(20);
    }
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
    if(ChoisePin() != 0)
    {
		int ChoiseButton(30);
    }
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
    if(ChoisePin() != 0)
    {
		int ChoiseButton(40);
    }
	
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
    if(ChoisePin() != 0)
    {
		int ChoiseButton(50);
    }
    */
}

void Keyboard::Init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
      
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_SET);
}
/*
int ChoisePin()
{
    int butt;
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)== GPIO_PIN_RESET)
			{
			butt=1;
			}
			else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)== GPIO_PIN_RESET)
				{
				butt=2;
				}
				else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)== GPIO_PIN_RESET)
					{
					butt=3;
					} 
					else if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13)== GPIO_PIN_RESET)
						{
						butt=4;
						}
						else if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12)== GPIO_PIN_RESET)
							{
							butt=5;
							}
			else
				{
				butt = 0;
				}
        return butt;
}

int ChoiseButton(int bus)
{
	if(ChoisePin() == 1)
		{
		button = bus+1;
		}
		else if(ChoisePin() == 2)
			{
			button = bus+2;
			}
				else if(ChoisePin() == 3)
			    {
				button = bus+3;
				}
					else if(ChoisePin() == 4)
					{
					button = bus+4;
					}
	return button;
}*/
