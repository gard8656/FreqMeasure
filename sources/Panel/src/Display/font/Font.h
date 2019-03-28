#pragma once
#include "defines.h"
#include "Display/DisplayTypes.h"


struct Symbol
{
    uchar width;
    uchar bytes[8];
};


struct Font
{
    struct Type
    {
        enum E
        {
            _5,
            _7,
            _8,
            Number,
            None
        } value;
        Type(E v) : value(v) {};
        operator uint8() const { return (uint8)value; };
    };

    static int GetSize();
    static int GetLengthText(const char *text);
    static int GetHeightSymbol(char symbol);
    static int GetLengthSymbol(char symbol);
    static void SetType(Type typeFont);
    static void ToggleCharacterSize();
    
    int height;
    Symbol symbol[256];
};


extern const Font *font;
extern const Font *fonts[Font::Type::Number];

extern const uchar font5display[3080];
extern const uchar font8display[3080];
extern const uchar fontUGOdisplay[3080];
extern const uchar fontUGO2display[3080];
