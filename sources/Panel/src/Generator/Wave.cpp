#include "stdafx.h"
#ifndef WIN32
#include "Command.h"
#include "defines.h"
#include "Log.h"
#include "Display/Painter.h"
#include "Settings/Settings.h"
#include "Display/InputWindow.h"
#include "Display/Symbols.h"
#include "GeneratorPanel.h"
#include "Signals.h"
#include "Utils/Debug.h"
#include "Utils/Math.h"
#include "Menu/Menu.h"
#include "Menu/Pages/AddPageInput.h"
#include <cstdio>
#include <cstdlib>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SIZE_BUFFER     300
static uint8 formFlash[Chan::Number][SIZE_BUFFER];


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pString Form::Name(Language::E lang) const
{
    DEF_STRUCT(StructName, const char *) names[Form::Number][2] =
    {
        {"�����",        "Sine"},
        {"����+",        "Ramp+"},
        {"����-",        "Ramp-"},
        {"�����������",  "Triangle"},
        {"������",       "Meander"},
        {"�������",      "Impulse"},
        {"�����",        "Message"},
        {"������������", "Hand"}
    };

    return names[value][lang].val;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString Register::Name() const
{
    DEF_STRUCT(StrName, const char *) names[Register::Number] =
    {
        "������������� 1",
        "������������� 2",
        "5697 �������� 1",
        "5697 �������� 2",
        "5697 ���� �������",
        "5697 ���� ����������",
        "RG0 ����������",
        "RG1 �������",
        "RG2 ����������",
        "RG3 ������� �",
        "RG4 ������� B",
        "RG5 ������ ��������� �",
        "RG6 ����. ��������� �",
        "RG7 ������ ��������� B",
        "RG8 ����. ��������� B",
        "RG9 �����. �����������",
        "RG10 ��������",
        "���������� - �������������",
        "���������� - �����",
        "���������� - ������"
    };

    return names[value].val;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterValue::Name() const
{
    DEF_STRUCT(StructName, const char *) nameParameter[ParameterValue::Number][2] =
    {
        {"�������",        "Frequency"},
        {"������",         "Period"},
        {"������",         "Amplitude"},
        {"��������",       "Offset"},
        {"������������",   "Duration"},
        {"����������",     "Duty ratio"},
        {"����",           "Phapse"},
        {"��������",       "Delay"},
        {"�� ����������",  "Build-up time"},
        {"�� �����",       "Release time"},
        {"�� ����",        "Peak time"},
        {"����� ������",   "Duty factor"},
        {"������������",   "Duration"},
        {"������",         "Period"},
        {"������ ������",  "Message period"},
        {"���-�� ���",     "Num of puls"},
        {"     ����� ( ESC )", "     Exit ( ESC )"}
    };

    return nameParameter[value][LANG].val;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Form *Wave::GetCurrentForm()
{
    return forms[currentForm];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Wave::SetForm(int8 num)
{
    currentForm = num;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Wave::NumberOfForms() const
{
    return numForms;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Wave::Wave(Chan::E ch, Form **f) : channel(ch), forms(f)
{
    numForms = 0;
    
    Form *form = forms[numForms];
    
    while(form)
    {
        numForms++;
        form = forms[numForms];
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Form::Form(E v, ParameterBase **parameters, Wave *w) : value(v), wave(w), params(parameters), currentParam(0)
{
    numParams = 0;

    if(params)
    {
        while(params[numParams])
        {
            numParams++;
        }
    }

    for(int i = 0; i < numParams; i++)
    {
        params[i]->form = this;
    }

    if (v == DDS)
    {
        std::memset(&formFlash[0][0], 127, SIZE_BUFFER * 2);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ParameterBase *Form::CurrentParameter()
{
    return params[currentParam];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Form::NumParameters() const 
{
    return numParams;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ParameterBase *Form::GetParameter(int i)
{
    if(i < numParams)
    {
        return params[i];
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Form *Wave::GetForm(int i)
{
    if(i < numForms)
    {
        return forms[i];
    }
    
    LOG_ERROR("������������ ������ %d", i);
    
    return nullptr;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Form *Wave::GetForm(Form::E form)
{
    for(int i = 0; i < numForms; i++)
    {
        if(forms[i]->value == form)
        {
            return forms[i];
        }
    }
    
    LOG_ERROR("�� ������� ����� %d", (int)form);
    
    return nullptr;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::SetNextParameter()
{
    currentParam++;
    if(currentParam >= NumParameters())
    {
        currentParam = 0;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::TuneGenerator(Chan::E ch)
{
    Generator::SetFormWave(GetWave());

    if(value == Form::Sine)
    {
        if(CurrentParameter()->GetParent())                                 // ������� �������� �����������
        {
            SendParameterToGenerator(ParameterChoice::ManipulationMode);
            SendParameterToGenerator(ParameterChoice::ManipulationEnabled);
            SendParameterToGenerator(ParameterValue::ManipulationDuration);
            SendParameterToGenerator(ParameterValue::ManipulationPeriod);

            int opened = currentParam;

            CloseOpenedParameter();

            SendParameterToGenerator(ParameterValue::Frequency);
            SendParameterToGenerator(ParameterValue::Amplitude);
            SendParameterToGenerator(ParameterValue::Offset);

            OpenCurrentParameter();

            currentParam = opened;
        }
        else                                                                // �������� ����������� ������
        {
            OpenCurrentParameter();

            SendParameterToGenerator(ParameterChoice::ManipulationMode);
            SendParameterToGenerator(ParameterChoice::ManipulationEnabled);
            SendParameterToGenerator(ParameterValue::ManipulationDuration);
            SendParameterToGenerator(ParameterValue::ManipulationPeriod);

            CloseOpenedParameter();

            SendParameterToGenerator(ParameterValue::Frequency);
            SendParameterToGenerator(ParameterValue::Amplitude);
            SendParameterToGenerator(ParameterValue::Offset);
        }

        if(!Chan(ch).IsA())
        {
            SendParameterToGenerator(ParameterValue::Phase);
        }
    }
    else
    {
        SendParameterToGenerator(ParameterValue::Frequency);
        SendParameterToGenerator(ParameterValue::Amplitude);
        SendParameterToGenerator(ParameterValue::Offset);
        SendParameterToGenerator(ParameterValue::Period);
        SendParameterToGenerator(ParameterValue::Duration);
        SendParameterToGenerator(ParameterValue::PacketNumber);
        SendParameterToGenerator(ParameterValue::PacketPeriod);
        SendParameterToGenerator(ParameterChoice::Polarity);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ParameterBase *Form::FindParameter(ParameterValue::E p)
{
    for(int i = 0; i < numParams; i++)
    {
        ParameterBase *param = params[i];

        if(param->IsValue() && ((ParameterValue *)param)->value == p)
        {
            return param;
        }
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ParameterBase *Form::FindParameter(ParameterChoice::E p)
{
    for(int i = 0; i < numParams; i++)
    {
        ParameterBase *param = params[i];
        if(param->IsChoice() && ((ParameterChoice *)param)->value == p)
        {
            return param;
        }
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::SendParameterToGenerator(ParameterValue::E p)
{
    ParameterBase *param = FindParameter(p);
    if (param)
    {
        Generator::SetParameter((ParameterValue *)param);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::SendParameterToGenerator(ParameterChoice::E p)
{
    ParameterBase *param = FindParameter(p);
    if(param)
    {
        Generator::SetParameter((ParameterChoice *)param);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::OpenCurrentParameter()
{
    if(!CurrentParameter()->IsComplex())
    {
        return;
    }

    oldParams = params;
    oldNumParams = numParams;
    oldCurrentParams = currentParam;

    ParameterComplex *parent = (ParameterComplex *)CurrentParameter();

    numParams = parent->numParams;
    params = parent->params;
    currentParam = 0;

    for(int i = 0; i < numParams; i++)
    {
        params[i]->form = this;
        params[i]->parent = parent;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Form::CloseOpenedParameter()
{
    if (ParameterIsOpened())
    {
        params = oldParams;
        numParams = oldNumParams;
        currentParam = oldCurrentParams;
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Form::ParameterIsOpened() const
{
    return params[0]->parent != 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ParamValue ParameterValue::GetValueNano() const
{
    StructValue input((ParameterValue *)this);
    return input.ValueNano();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterValue::GetStringValue() const
{
    StructValue input((ParameterValue *)this);
    return input.StringValue();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterComplex::GetStringValue() const
{
    if(Is(Manipulation))
    {
        static const char *values[2][2] =
        {
            {" ����", " ���"},
            {" Off",  " On"}
        };

        ParameterValue *pointer = (ParameterValue *)this;   // -V1027
        return values[LANG][SINE_MANIPULATION_ENABLED(pointer->GetForm()->GetWave()->GetChannel()) ? 1 : 0];
    }

    return "";
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterValue::NameUnit(char buf[10]) const
{
    DEF_STRUCT(StructName, const char *) names[ParameterValue::Number][2] =
    {
        {"��",  "Hz"},
        {"�",   "s"},
        {"�",   "V"},
        {"�",   "V"},
        {"�",   "s"},
        {"",    ""},
        {"\x7b","\x7b"},
        {"�",   "s"},
        {"",    ""},
        {"",    ""},
        {"",    ""},
        {"",    ""},
        {"c",   "s"},
        {"c",   "s"},
        {"c",   "s"},
        {"",    ""},
        {"",    ""}
    };

    sprintf(buf, "%s%s", order.Name(), names[value][LANG].val);
    return buf;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterBase::NameUnit(char buffer[10]) const
{
    if(IsValue())
    {
        return ((ParameterValue *)this)->NameUnit(buffer);
    }
    return "";
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ParameterValue::IsOpened()
{
    return IsComplex() && GetForm()->ParameterIsOpened();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterChoice::Name() const
{
    DEF_STRUCT(StructName, const char *) namesParam[ParameterChoice::Number][2] =
    {
        {"����������",  "Polarity"},
        {"������",      "Mode start"},
        {"���",         "Type"},
        {"�����������", "Manipulation"}
    };

    return namesParam[value][LANG].val;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterComplex::Name() const
{
    DEF_STRUCT(StructName, const char *) namesParams[ParameterComplex::Number][2] =
    {
        {"�����������", "Manipulation"}
    };

    return namesParams[value][LANG].val;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterBase::Name() const
{
    if(IsValue())
    {
        return ((ParameterValue *)this)->Name();
    }
    else if(IsChoice())
    {
        return ((ParameterChoice *)this)->Name();
    }
    else if(IsComplex())
    {
        return ((ParameterComplex *)this)->Name();
    }

    return "";
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterBase::GetStringValue() const
{
    if(IsValue())
    {
        return ((ParameterValue *)this)->GetStringValue();
    }
    else if(IsChoice())
    {
        return ((ParameterChoice *)this)->GetStringValue();
    }
    else if(IsComplex())
    {
        return ((ParameterComplex *)this)->GetStringValue();
    }
    return "";
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterChoice::GetStringValue() const
{
    return names[choice][LANG];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::ChangeParameter()
{
    ParameterBase *param = CurrentParameter();

    if(param->IsChoice())
    {
        ((ParameterChoice *)param)->NextChoice();
    }
    else if(param->IsValue() && ((ParameterValue *)param)->IsInputValue())
    {
        InputWindow::Init();
        Menu::SetAdditionPage((Page *)AddPageInput::pointer);
    }
    else if (param->IsExit())
    {
        CloseOpenedParameter();
    }
    else if (param->IsComplex())
    {
        OpenCurrentParameter();
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ParameterChoice::NextChoice()
{
    CircleIncrease(&choice, 0, num - 1);

    Chan::E ch = form->GetWave()->GetChannel();

    if(value == ModeStart)
    {
        Generator::LoadStartMode(ch, choice);
    }
    else
    {
        if(value == ManipulationEnabled)
        {
            SINE_MANIPULATION_ENABLED(ch) = choice;
        }
        else if(value == ManipulationMode)
        {
            SINE_MANIPULATION_MODE(ch) = (uint8)choice;
        }
        Generator::TuneChannel(ch);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ParameterChoice::DrawChoice(int x, int y)
{
    if(func[choice])
    {
        func[choice](x, y);
    }

    return func[choice] != 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Wave::StartModeIsSingle()
{
    ParameterChoice* param = (ParameterChoice *)GetCurrentForm()->FindParameter(ParameterChoice::ModeStart);

    if(param)
    {
        return param->GetChoice() == 1;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ParameterBase::IsExit() const
{
    return IsValue() && ((ParameterValue *)this)->IsExit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Order& Order::operator++(int)
{
    value = (E)(value + 1);
    return *this;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Order& Order::operator--(int)
{
    value = (E)(value - 1);
    return *this;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ParameterChoice::ParameterChoice(E v, pString var0ru, pString var0en,
                                pString var1ru, pString var1en, funcDraw func0, funcDraw func1) :
    ParameterBase(Choice), value(v), choice(0), num(2)
{
    names[0][0] = (char *)var0ru;
    names[0][1] = (char *)var0en;
    names[1][0] = (char *)var1ru;
    names[1][1] = (char *)var1en;

    func[0] = func0;
    func[1] = func1;
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ParameterChoice::ParameterChoice(E v, pString var0ru, pString var0en, pString var1ru, pString var1en, 
                                      pString var2ru, pString var2en, pString var3ru, pString var3en) : 
    ParameterBase(Choice), value(v), choice(0), num(4)
{
    names[0][0] = (char *)var0ru;
    names[0][1] = (char *)var0en;
    names[1][0] = (char *)var1ru;
    names[1][1] = (char *)var1en;
    names[2][0] = (char *)var2ru;
    names[2][1] = (char *)var2en;
    names[3][0] = (char *)var3ru;
    names[3][1] = (char *)var3en;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ParameterComplex::ParameterComplex(ParameterBase *param[]) : ParameterBase(Complex), params(param)
{
    numParams = 0;
    while (params[numParams])
    {
        numParams++;
    }
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ParameterValue::ParameterValue(int v, float _min, float _max, pString buf, int8 pos, Order o, int8 hd, char s) : ParameterBase(Value),
    value((E)v), order(o), hightLightDigit(hd), posComma(pos), sign(s), min(_min), max(_max), inNumLockMode(false)
{
    std::strcpy(buffer, buf);
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Form::IsDDS() const
{
    return  (value == RampPlus) || 
            (value == RampMinus) ||
            (value == Triangle) ||
            (value == DDS);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::DrawUGO(Chan::E ch, int y0)
{
    y0 += 30;
    int height = 50;
    int width = 90;
    int aveY = y0 + 5 + height / 2;
    int minY = y0 + 5;
    int maxY = minY + height;
    int x0 = 10;


    static bool first = true;

    static volatile int yNoise[100];
    static volatile int yExp[100];

    if (first)
    {
        std::srand(2);
        for (int i = 0; i < 100; i++)
        {
            yNoise[i] = aveY - (int)(std::rand() % 50 - 25);

            yExp[i] = aveY - (int)(std::expf(i / 12.5f) + 0.5f) + 1;
        }

        first = false;
    }

    Painter::DrawVLine(x0, minY - 3, maxY + 3);
    Painter::DrawHLine(aveY, x0, x0 + width);

    typedef void(*pFuncIIII)(Chan::E, int, int, int, int);

    DEF_STRUCT(StructFunc, pFuncIIII) func[Form::Number] =
    {
        DrawSine,
        DrawRampPlus,
        DrawRampMinus,
        DrawTriangle,
        DrawMeander,
        DrawImpulse,
        DrawPacketImpulse,
        DrawDDS
    };

    func[value].val(ch, x0, minY, width, height);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::DrawSine(Chan::E, int x0, int y0, int width, int height)
{
    float speed = 0.2f;
    int delta = 1;
    y0 += height / 2;

    for (int i = delta; i < width; i++)
    {
        int y1 = y0 - (int)(std::sinf((i - delta) * speed) * height / 2.0f);
        int y2 = y0 - (int)(std::sinf(i * speed) * height / 2.0f);

        Painter::DrawLine(x0 + i - delta, y1, x0 + i, y2);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::DrawRampPlus(Chan::E, int x0, int y0, int, int height)
{
    y0 += height;
    int dX = 28;
    for (int x = x0; x < x0 + 80; x += dX)
    {
        Painter::DrawLine(x, y0, x + dX, y0 - height);
        Painter::DrawLine(x + dX, y0, x + dX, y0 - height);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::DrawRampMinus(Chan::E, int x0, int y0, int, int height)
{
    int aveY = y0 + height / 2;
    int dX = 28;
    int dY = 20;
    for (int x = x0; x < x0 + 80; x += dX)
    {
        Painter::DrawLine(x, aveY - dY, x + dX, aveY + dY);
        Painter::DrawVLine(x + dX, aveY - dY, aveY + dY);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::DrawTriangle(Chan::E, int x, int y, int width, int height)
{
    int min = y + height;
    Painter::DrawLine(x, min, x + width / 2, y);
    Painter::DrawLine(x + width / 2, y, x + width, y + height);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::DrawMeander(Chan::E, int x0, int y0, int, int height)
{
    int dX = 40;
    int dY = 20;
    int aveY = y0 + height / 2;
    for (int x = x0; x < x0 + 80; x += dX)
    {
        Painter::DrawHLine(aveY - dY, x, x + dX / 2);
        Painter::DrawVLine(x + dX / 2, aveY - dY, aveY + dY);
        Painter::DrawHLine(aveY + dY, x + dX / 2, x + dX);
        Painter::DrawVLine(x + dX, aveY - dY, aveY + dY);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::DrawImpulse(Chan::E ch, int x0, int y0, int, int height)
{
    int minY = y0;
    int maxY = y0 + height;

    ParameterChoice *param = (ParameterChoice *)WAVE(ch).GetCurrentForm()->FindParameter(ParameterChoice::Polarity);

    if (param->GetChoice() == 1)
    {
        minY = maxY;
        maxY = y0;
    }

    int deltaX = 20;

    for (int i = 0; i < 5; i++)
    {
        Painter::DrawVLine(x0, minY, maxY);
        Painter::DrawVLine(x0 + 5, minY, maxY);
        Painter::DrawHLine(minY, x0, x0 + 5);
        Painter::DrawHLine(maxY, x0 + 5, x0 + (i == 4 ? 7 : deltaX));
        x0 += deltaX;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::DrawPacketImpulse(Chan::E, int x0, int y0, int, int height)
{
    int minY = y0;
    int maxY = y0 + height;
    int deltaX = 8;
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            Painter::DrawVLine(x0, minY, maxY);
            Painter::DrawHLine(minY, x0, x0 + 4);
            Painter::DrawVLine(x0 + 4, minY, maxY);
            Painter::DrawHLine(maxY, x0 + 4, x0 + deltaX);
            x0 += deltaX;
        }

        if (j == 0)
        {
            Painter::DrawHLine(maxY, x0, x0 + 35);
        }

        x0 += 37;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::DrawDDS(Chan::E ch, int x0, int y0, int width, int height)
{
    int numPoints = 240;

    float sX = width / (float)numPoints;
    float sY = height / 255.0f;

    for (int i = 0; i < numPoints; i++)
    {
        Painter::SetPoint((int)(x0 + sX * i), (int)(y0 + height - formFlash[ch][i] * sY));
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Form::SetFormFlash(Chan::E ch, const uint8 data[SIZE_BUFFER])
{
    std::memcpy(&formFlash[ch][0], data, SIZE_BUFFER);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 *Form::GetFormFlash(Chan::E ch)
{
    return &formFlash[ch][0];
}
