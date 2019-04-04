#include "stm32f4xx_hal.h"
#include "Hardware/HAL.h"
#include "Keyboard/Keyboard.h"
#include "Display/Draw.h"
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
        if (Keyboard::Update() != 0)
        {
            Draw::Rectangle(30, 30, 100, 200, 3);
            HAL_Delay(500);
            Draw::Clear();
            HAL_Delay(20);
        }
        else if(Keyboard::Update() == Button_NULL)
        {
            Draw::Rectangle(0, 0, 100, 200, 1);
            HAL_Delay(500);
            Draw::Clear();
            HAL_Delay(20);
        }
        
    }
}
