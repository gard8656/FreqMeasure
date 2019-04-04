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
    void SetPoint(int x, int y, Color color);
    void DrawRectangle(int x, int y, int width, int height, Color color);
    void DrawHLine(int x, int y, int width, Color color);
    void EndScene();
};
