#pragma once
#include "stm32f4xx_hal.h"

class Display
{
    public:
        static void Init();  
		static uint8_t* GetBuff();
		static void SetAdress();
};
