#pragma once
#include "defines.h"


struct Color
{
    uint8 value;

    static Color BLACK;
    static Color WHITE;
    static Color Number;

    explicit Color(uint8 val) : value(val) {};
};



namespace Painter
{
    void SetColor(Color color);
    Color CurrentColor();
};
