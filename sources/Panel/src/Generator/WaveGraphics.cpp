#include "stdafx.h"
#ifndef WIN32
#include "Signals.h"
#include "Wave.h"
#include "Display/DisplayTypes.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "Menu/Menu.h"
#include "Menu/Pages/Include/PageSignals.h"
#include "Settings/Settings.h"
#include "Utils/Debug.h"
#include <cmath>
#include <string.h>
#include <cstdlib>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Wave::Graphics::Draw(Chan::E ch)
{
    if(FREQ_METER_ENABLED && ch != CURRENT_CHANNEL)
    {
        return;
    }

    int x0 = X();
    int y0 = Y(ch);
    Painter::FillRegion(x0 + 1, y0 + 1, Width() - 2, Height() - 2, Color::GREEN_5);
    if (CHANNEL_ENABLED(ch))
    {
        Painter::DrawRectangle(x0, y0, Width(), Height(), Color::FILL);
        Text::DrawBigText(x0 + 5, y0 + 5, 2, ch == Chan::A ? "A" : "B", Color::FILL);
        FORM(ch)->DrawUGO(ch, y0);
        DrawParameters(ch, y0);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Wave::Graphics::X()
{
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Wave::Graphics::Y(Chan::E ch)
{
    return (ch == Chan::A || FREQ_METER_ENABLED) ? Page::Title::HEIGHT : Page::Title::HEIGHT + SIGNAL_HEIGHT;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Wave::Graphics::Width()
{
    return SIGNAL_WIDTH;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Wave::Graphics::Height()
{
    return SIGNAL_HEIGHT;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Wave::Graphics::DrawParameters(Chan::E ch, int y0)
{
    Form *form = FORM(ch);

    int x0 = 107;

    y0 += 5;

    String(form->Name(LANG)).Draw(22, y0 + 3, Color::FILL);
    
    for (int i = 0; i < form->NumParameters(); i++)
    {
        ParameterBase *param = form->GetParameter(i);
        
        if ((ch == CURRENT_CHANNEL) && std::strcmp(PARAM_CURRENT->Name(), param->Name()) == 0 && CURRENT_PAGE == PageSignals::pointer)
        {
            Painter::FillRegion(x0, y0, 139, 9, Color::GRAY_25);
        }
        
        String(param->Name()).Draw(x0 + 1, y0, Color::FILL);
        
        if(i == 3 && Chan(ch).IsA())
        {
            i = i;
        }
        
        DrawParameterValue(param, x0 + 80, y0);
        y0 += 11;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Wave::Graphics::DrawParameterValue(ParameterBase *param, int x, int y)
{
    if(param->IsChoice() && ((ParameterChoice *)param)->DrawChoice(x + 6, y))
    {
        return;
    }

    if(param->IsChoice())
    {
        param = param;
    }
    x = String(param->GetStringValue()).Draw(x, y);

    char buffer[10];
    Text::SetUpperCase(false);
    String(param->NameUnit(buffer)).Draw(x + 2, y);
    Text::SetUpperCase(true);
}
