#include "defines.h"
#include "PageModes.h"
#include "Display/Painter.h"


static Page pModes;

Page *pageModes = &pModes;

static Control *controls[] = { nullptr };


static void DrawClosed(int x, int y)
{
    Painter::FillRegion(x + 1, y + 1, 5, 5);
}


void PageModes::Init()
{
    pageModes->Init(controls, DrawClosed);
}
