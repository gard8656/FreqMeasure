#include "HAL.h"
#include "stm32f4xx_hal.h"
#include "Keyboard.h"

int ChoisePin();

void Keyboard::Update()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
    if(ChoisePin() != 0)
    {
    //dodelat vibor knopki i sdelat 4erez define nazvaniya knopok 4tob vozvrs4alo
    }
    
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

int ChoisePin()
{
    HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);
    int button;
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)== GPIO_PIN_RESET)
    {
        button=1;
    }
        else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)== GPIO_PIN_RESET)
        {
            button=2;
        }
        else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)== GPIO_PIN_RESET)
        {
            button=3;
        } 
        else if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13)== GPIO_PIN_RESET)
        {
            button=4;
        }
        else if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12)== GPIO_PIN_RESET)
        {
            button=5;
        }
        else
        {
            button = 0;
        }
        return button;
}

