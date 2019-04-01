#include "stm32f4xx_hal.h"
#include "Hardware/HAL.h"
#include "Keyboard/Keyboard.h"
#include "Display/Draw/Draw.h"
#include "Display/Set/DisplaySet.h"

int main(void)
{
     HAL::Init();
    Display::Init();
	Keyboard::Init();
    uint8_t x = 0;
    uint8_t y = 0;
	Display::SetAdress();
    while (1)
    {
        //Keyboard::Update();
        Draw::Rectangle(x, y, 100, 200, 2);
        HAL_Delay(200);
        Draw::Clear();
        HAL_Delay(100);
    }
}
