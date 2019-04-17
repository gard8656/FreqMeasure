#include "defines.h"
#include "Painter.h"
#include "Display/Display.h"
#include "Display/Primitives.h"


using namespace Display::Primitives;

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

void Painter::BeginScene(Color col)
{
    Rectangle(320, 240).Fill(0, 0, col);
}

void Painter::EndScene()
{
    Display::Present();
}
