#include "defines.h"
#include "Display/Primitives.h"
#include "Display/Display.h"


using namespace Display::Primitives;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Rectangle::Rectangle(int _width, int _height) : width(_width), height(_height)
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Rectangle::Draw(int x, int y, Color color)
{
    Painter::SetColor(color);

    Painter::DrawHLine(x, y, width);
    Painter::DrawHLine(x, y + height, width);
    Painter::DrawVLine(x, y, height);
    Painter::DrawVLine(x + width, y, height);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Rectangle::Fill(int x0, int y0, Color color)
{
    Painter::SetColor(color);

    for (int y = y0; y < y0 + height; y++)
    {
        Painter::DrawHLine(x0, y, width);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Point::Draw(int x, int y, Color color)
{
    Painter::SetColor(color);

    uint8 *address = Display::GetBuff() + 320 * y + x;
    *address = color.value;
}
