#include "Menu.h"
#include "MenuItems.h"


void Menu::Init()
{
}


void Menu::Draw()
{
    CurrentPage()->Draw();
}


Page *Menu::CurrentPage()
{
    static Page page;
    return &page;
}
