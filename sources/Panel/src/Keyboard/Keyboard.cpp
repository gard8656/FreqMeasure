//dodelat vibor knopki i sdelat 4erez define nazvaniya knopok 4tob vozvrs4alo
#include "HAL.h"
#include "stm32f4xx_hal.h"
#include "Keyboard.h"

Buttons ArrBut[2][4] = {{Button_0, Button_1, Button_2, Button_4},{Button_5, Button_6, Button_7, Button_8}}; 
Buttons button; 
int ChoisePin();
int ChoiseButton(int);
void Set_All_SL(int);
void Set_SL(int, int);
int Read_RL(int);

Buttons Keyboard::Update()
{
    for(int bus=0; bus<4; bus++)
    {
        Set_All_SL(1);
        Set_SL(bus, 0);
        for(int pin=0; pin<4; pin++)
        {
            int state = Read_RL(pin);
            if (state == 0)
            {
             button = ArrBut[bus][pin];
            }
            else button = Button_NULL;
        }
    }
    return button;
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
    
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);
    //HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
    //HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_SET);
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_SET);
}

void Set_All_SL(int st)
{
     //GPIO_PinState state [2] = {GPIO_PIN_RESET, GPIO_PIN_SET};
     //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, state[st]);
     //HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, state[st]);
    for(int i = 0; i<5; i++)
    {
        Set_SL(i, st);
    }
}
   
void Set_SL(int bus, int st)
{
    GPIO_TypeDef *ports[5]= {GPIOB, GPIOB, GPIOB, GPIOB, GPIOD};
    uint16_t pins[5] = {GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15,GPIO_PIN_8};
    GPIO_PinState state [2] = {GPIO_PIN_RESET, GPIO_PIN_SET};
    HAL_GPIO_WritePin(ports[bus], pins[bus], state[st]);
}

int Read_RL(int pin)
{
    GPIO_TypeDef *ports[5]= {GPIOA, GPIOA, GPIOA, GPIOD, GPIOD};
    uint16_t pins[5] = {GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_13,GPIO_PIN_12};
    return HAL_GPIO_ReadPin(ports[pin], pins[pin]);
}
   
