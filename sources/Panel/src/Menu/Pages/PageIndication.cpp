#include "defines.h"
#include "PageIndication.h"
#include "Display/Painter.h"


static Page pIndication;

Page *pageIndication = &pIndication;

static Control *controls[] = { nullptr };


static void DrawClosed(int x, int y)
{
    Painter::FillRegion(x + 1, y + 1, 7, 7);
}


void PageIndication::Init()
{
    pageIndication->Init(controls, DrawClosed);
}
