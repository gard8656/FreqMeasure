#include "Menu.h"
#include "MenuItems.h"
#include "Menu/Pages/MainPage.h"


void Menu::Init()
{
    PageMain::Init();
}


void Menu::Draw(int x, int y)
{
    CurrentPage()->Draw(x, y);
}


Page *Menu::CurrentPage()
{
    return pageMain;
}
