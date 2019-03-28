#include "stdafx.h"
#ifndef WIN32
#include "Console.h"
#include "Display/Font/Font.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "Settings/Settings.h"
#include "Utils/Debug.h"
#include "Utils/String.h"
#include <cstring>
#include <cstdio>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char Console::buffer[MAX_STRINGS][MAX_SYMBOLS_IN_STRING] = {};
int  Console::numStrings = 0;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Console::AddString(const char *string)
{
    static int fullNumber = 0;

    if(numStrings == MAX_STRINGS)
    {
        for(int i = 1; i < MAX_STRINGS; i++)
        {
            std::strcpy(&buffer[i - 1][0], &buffer[i][0]);
        }
        numStrings--;
    }
    sprintf(&buffer[numStrings][0], "%d ", fullNumber);
    std::strcat(&buffer[numStrings][0], string);
    numStrings++;
    fullNumber++;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Console::Draw()
{
    if (!CONSOLE_ENABLED)
    {
        return;
    }

    Text::SetUpperCase(false);

    int y = 1;
    for (int i = 0; i < numStrings; i++)
    {
        int length = Font::GetLengthText(&buffer[i][0]);
        Painter::FillRegion(2, y, length, 9, Color::GREEN_25);
        String(&buffer[i][0]).Draw(2, y, Color::FILL);
        y += 9;
    }

    Text::SetUpperCase(true);
}
