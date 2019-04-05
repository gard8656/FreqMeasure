#include "defines.h"
#include "MainPage.h"
#include "PageChannels.h"
#include "PageModes.h"
#include "PageIndication.h"


static Page pMain;

Page *pageMain = &pMain;

static Control *controls[] = { pageChannels, nullptr };


static void DrawClosed(int, int)
{

}


void PageMain::Init()
{
    PageChannels::Init();

    pMain.Init(controls, DrawClosed);

    pMain.Open();
}
