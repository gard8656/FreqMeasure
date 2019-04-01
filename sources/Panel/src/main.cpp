#include "stm32f4xx_hal.h"
#include "Hardware/HAL.h"
#include "Keyboard/Keyboard.h"
#include "Display/Draw.h"
#include "Display/Display.h"

int main(void)
{
    HAL::Init();
    Display::Init();
	Keyboard::Init();
    
    while (1)
    {
        //Keyboard::Update();
        Draw::Rectangle(10, 10, 100, 200, 2);
        HAL_Delay(200);
        Draw::Clear();
        HAL_Delay(100);
    }
}
