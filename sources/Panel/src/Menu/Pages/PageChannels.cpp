#include "PageChannels.h"
#include "Display/Primitives.h"


using Display::Primitives::Rectangle;


static Page pChannels;

Page *pageChannels = &pChannels;

static Control *controls[] = { nullptr };


static void DrawClosed(int x, int y)
{
    Rectangle(3, 3).Fill(x + 1, y + 1);
}


void PageChannels::Init()
{
    pageChannels->Init(controls, DrawClosed);
}
