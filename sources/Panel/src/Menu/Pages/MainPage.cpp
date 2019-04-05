#include "defines.h"
#include "MainPage.h"
#include "PageChannels.h"
#include "PageModes.h"
#include "PageIndication.h"


static Page pMain;

Page *pageMain = &pMain;

static Control *controls[] = { pageChannels, pageModes, pageIndication, nullptr };


static void DrawClosed(int, int)
{

}


void PageMain::Init()
{
    PageChannels::Init();

    PageModes::Init();

    PageIndication::Init();

    pMain.Init(controls, DrawClosed);

    pMain.Open();
}
