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

Color Painter::CurrentColor()
{
    return color;
}

void Painter::BeginScene(Color col)
{
    Rectangle(320, 240).Fill(0, 0, col);
}

void Painter::EndScene()
{
    Display::Present();
}
