#pragma once
#include "Menu/MenuItems.h"


class PageDebug
{
public:
    static Page * pointer;

    class PageRegisters
    {
    public:

        static void Draw();

    private:
        /// �������� ��������
        static void DrawRegisters(int x, int y);

        static void DrawInputWindow();
    };
};
