#include "defines.h"
#include "PageModes.h"
#include "Display/Primitives.h"


using namespace Display::Primitives;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static Page pModes;

Page *PageModes::pointer = &pModes;

static Control *controls[] = { nullptr };


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void DrawClosed(int x, int y)
{
    Rectangle(5, 5).Fill(x + 1, y + 1);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageModes::Init()
{
    pModes.Init(controls, DrawClosed);
}
