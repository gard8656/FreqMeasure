#include "defines.h"
#include "Painter.h"
#include "Display/Display.h"


Color Color::BLACK(0);
Color Color::WHITE(1);


void Painter::SetPoint(int x, int y, Color color)
{
	uint8* address = Display::GetBuff() + 320 * y + x;
	*address = color.value;
}

void Painter::DrawRectangle(int x0, int y0, int width, int height, Color color)
{
    for (int y = y0; y < y0 + height; y++)
    {
        DrawHLine(x0, y, width, color);
    }
}

void Painter::DrawHLine(int x, int y, int width, Color color)
{
    uint8 *address = Display::GetBuff() + 320 * y + x;

    while (width > 0)
    {
        *address = color.value;
        address++;
        width--;
    }
}

void Painter::BeginScene(Color color)
{
    DrawRectangle(0, 0, 320, 240, color);
}

void Painter::EndScene()
{
    Display::Present();
}
