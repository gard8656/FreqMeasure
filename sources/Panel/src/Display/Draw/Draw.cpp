#include "stm32f4xx_hal.h"
#include "Draw.h"
#include "Display/Set/DisplaySet.h"

void SetPoint(int x, int y, uint8_t color)
{
	uint8_t* point = Display::GetBuff()+320*y+x;
	*point = color;
}

void Draw::Rectangle(int x, int y, int height, int width, int color)
{
	for (int i = x; i < x + width ; i++)
	{
		for (int j = y; j < y + height; j++)
		{
			SetPoint(i, j, color);
		}
	}
}

void Draw::Clear()
{
	uint32_t h = 240;
	uint32_t w = 320;
	for (int x = 0; x < w ; x++)
	{
		for (int y = 0; y < h; y++)
		{
			SetPoint(x, y, 0);
		}
	}
} 
