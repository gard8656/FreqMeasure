#include "stm32f4xx_hal.h"
#include "Hardware/HAL.h"
#include "Keyboard/Keyboard.h"
#include "Display/Painter.h"
#include "Display/Display.h"
#include "Menu/Menu.h"


int main(void)
{
    HAL::Init();
    Display::Init();
	Keyboard::Init();
    Menu::Init();
    
    while (1)
    {
        if (Keyboard::Update() != Button_NULL)
        {
            Painter::DrawRectangle(30, 30, 100, 200, 3);
            HAL_Delay(500);
            Painter::Clear();
            HAL_Delay(20);
        }
        else
        {
            Painter::DrawRectangle(0, 0, 100, 200, 1);
            HAL_Delay(500);
            Painter::Clear();
            HAL_Delay(20);
        }
        
    }
}
