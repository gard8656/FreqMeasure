#include "defines.h"
#include "PageIndication.h"
#include "Display/Primitives.h"


using namespace Display::Primitives;;


static Page pIndication;

Page *pageIndication = &pIndication;

static Control *controls[] = { nullptr };


static void DrawClosed(int x, int y)
{
    Rectangle(7, 7).Fill(x + 1, y + 1);
}


void PageIndication::Init()
{
    pageIndication->Init(controls, DrawClosed);
}
