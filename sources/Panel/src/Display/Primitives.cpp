#include "defines.h"
#include "Display/Primitives.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Display::Primitives::Rectangle::Rectangle(int _width, int _height) : width(_width), height(_height)
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display::Primitives::Rectangle::Draw(int x, int y, Color color)
{
    Painter::SetColor(color);
    Painter::DrawHLine(x, y, width);
    Painter::DrawHLine(x, y + height, width);
    Painter::DrawVLine(x, y, height);
    Painter::DrawVLine(x + width, y, height);
}
