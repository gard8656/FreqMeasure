#include "Device.h"
#include "Keyboard/Keyboard.h"
#include "Display/Painter.h"
#include "stm32f4xx_hal.h"
#include "Menu/Menu.h"

#include "Display/Primitives.h"
#include "Display/Display.h"


using namespace Display::Primitives;


void Device::Update()
{
    Display::BeginScene(Color::BLACK);

    static int x0 = 0;
    static int y0 = 0;

    x0++;
    y0++;

    if (x0 == 2)
    {
        x0 = 0;
        y0 = 0;
    }

    int x = x0 + (320 - 256) / 2;
    int y = y0 + (240 - 64) / 2;

    Rectangle(256, 64).Draw(x, y, Color::WHITE);

    Menu::Draw(x + 30, y + 30);

    Display::EndScene();
}
