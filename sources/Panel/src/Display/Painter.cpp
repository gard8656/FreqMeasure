#include "defines.h"
#include "Painter.h"
#include "Display/Display.h"


Color Color::BLACK(0);
Color Color::WHITE(1);


void SetPoint(int x, int y, Color color)
{
	uint8_t* point = Display::GetBuff() + 320 * y + x;
	*point = color.value;
}

void Painter::DrawRectangle(int x, int y, int width, int height, Color color)
{
	for (int i = x; i < x + width ; i++)
	{
		for (int j = y; j < y + height; j++)
		{
			SetPoint(i, j, color);
		}
	}
}

void Painter::BeginScene(Color color)
{
    DrawRectangle(0, 0, 320, 240, color);
} 
