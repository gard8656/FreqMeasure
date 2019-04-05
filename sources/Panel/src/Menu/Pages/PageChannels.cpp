#include "PageChannels.h"
#include "Display/Painter.h"


static Page pChannels;

Page *pageChannels = &pChannels;

static Control *controls[] = { nullptr };


static void DrawClosed(int x, int y)
{
    Painter::FillRegion(x + 1, y + 1, 3, 3);
}


void PageChannels::Init()
{
    pageChannels->Init(controls, DrawClosed);
}
