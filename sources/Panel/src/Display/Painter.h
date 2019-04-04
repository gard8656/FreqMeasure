#pragma once
#include "defines.h"


struct Color
{
    uint8 value;

    static Color BLACK;
    static Color WHITE;

    explicit Color(uint8 val) : value(val) {};
};



namespace Painter
{
    void BeginScene(Color color);
    void DrawRectangle(int, int, int, int, Color color);
};
