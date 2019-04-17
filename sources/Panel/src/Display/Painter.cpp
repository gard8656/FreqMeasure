#include "defines.h"
#include "Painter.h"
#include "Display/Display.h"


Color Color::BLACK(0);
Color Color::WHITE(1);
Color Color::Number(2);


static Color color = Color::BLACK;

void Painter::SetColor(Color col)
{
    if (col.value != Color::Number.value)
    {
        color = col;
    }
}

/*
void Painter::SetPoint(int x, int y, Color col)
{
    SetColor(col);

	uint8* address = Display::GetBuff() + 320 * y + x;
	*address = color.value;
}
*/

void Painter::FillRegion(int x0, int y0, int width, int height, Color col)
{
    SetColor(col);

    for (int y = y0; y < y0 + height; y++)
    {
        DrawHLine(x0, y, width, color);
    }
}

void Painter::DrawHLine(int x, int y, int width, Color col)
{
    SetColor(col);

    uint8 *address = Display::GetBuff() + 320 * y + x;

    while (width > 0)
    {
        *address = color.value;
        address++;
        width--;
    }
}

void Painter::DrawVLine(int x, int y, int height, Color col)
{
    SetColor(col);

    uint8 *address = Display::GetBuff() + 320 * y + x;

    while (height > 0)
    {
        *address = color.value;
        address += 320;
        height--;
    }
}

/*
void Painter::DrawRectangle(int x, int y, int width, int height, Color col)
{
    SetColor(col);

    DrawHLine(x, y, width);
    DrawHLine(x, y + height, width);
    DrawVLine(x, y, height);
    DrawVLine(x + width, y, height);
}
*/

void Painter::BeginScene(Color col)
{
    SetColor(col);
    FillRegion(0, 0, 320, 240);
}

void Painter::EndScene()
{
    Display::Present();
}
