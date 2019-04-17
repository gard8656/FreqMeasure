#pragma once
#include "stm32f4xx_hal.h"
#include "Display/Painter.h"


namespace Display
{
    void Init();  
    uint8_t* GetBuff();
    void BeginScene(Color color);
    /// Копирует задний буфер на экран
    void EndScene();
};
