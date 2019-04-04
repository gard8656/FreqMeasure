#include "Device.h"
#include "Keyboard/Keyboard.h"
#include "Display/Painter.h"
#include "stm32f4xx_hal.h"


void Device::Update()
{
    static int x = 0;
    static int y = 0;

    x++;
    y++;

    if (x == 30)
    {
        x = 0;
        y = 0;
    }


    if (Keyboard::Update() != Button_NULL)
    {
        Painter::BeginScene(Color::WHITE);
        Painter::DrawRectangle(x + 30, y + 30, 200, 100, Color::BLACK);
    }
    else
    {
        Painter::BeginScene(Color::BLACK);
        Painter::DrawRectangle(x + 0, y + 0, 200, 100, Color::WHITE);
    }

    Painter::EndScene();
}
