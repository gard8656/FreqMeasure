#pragma once
#include "stm32f4xx_hal.h"
#include "Display/Colors.h"


namespace Display
{
    void Init();  
    uint8_t* GetBuff();
    void BeginScene(Color color);
    /// �������� ������ ����� �� �����
    void EndScene();
};
