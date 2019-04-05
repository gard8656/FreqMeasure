#include "defines.h"
#include "MenuItems.h"
#include "Display/Painter.h"


static Control emptyControl;


void Page::Draw(int x, int y)
{
    if (closed)
    {
        DrawClosed(x, y);
    }
    else
    {
        DrawOpened(x, y);
    }
}


void Page::DrawClosed(int x, int y)
{
    Painter::DrawRectangle(x, y, Control::WIDTH, Control::HEIGHT, Color::WHITE);
    drawClosed(x, y);
}


void Page::DrawOpened(int x, int y)
{
    Control *control = FirstOnDisplay();

    while (control)
    {
        control->Draw(x, y);

        x += Control::WIDTH;

        control = NextOnDisplay();

        if (control == LastOnDisplay())
        {
            break;
        }
    }
}


Control *Page::FirstOnDisplay()
{
    if (currentSubPage == 0)
    {
        return controls[0];
    }

    return controls[CONTROLS_ON_PAGE];
}


Control *Page::NextOnDisplay()
{
    return &emptyControl;
}


Control *Page::LastOnDisplay()
{
    return &emptyControl;
}
