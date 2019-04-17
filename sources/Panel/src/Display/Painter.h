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
    void BeginScene(Color color = Color::Number);
    void DrawVLine(int x, int y, int height, Color color = Color::Number);
    void EndScene();
};
