#include "stdafx.h"
#ifndef WIN32
#include "Display/InputWindow.h"
#include "Settings/Settings.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/AddPageInput.h"
#include "Menu/Pages/Include/PageSignals.h"
#include "Generator/Signals.h"
#include "Generator/GeneratorPanel.h"
#include "Menu/Menu.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageSignals;
Page *PageSignals::pointer = (Page *)&pageSignals;
extern ChoiceParameterBase cParameters;
/// ����� ������� ����� ������
static int numForm = 0;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2( cChannel,                                                                                                                                  //--- ��������� �������� - ����� ---
    "�����", "CHANNEL",
    "����� ������ ��� ���������.",
    "Selecting a channel to set up.",
    "A", "A", "���������� ����������� ������� �� ������ A.",
              "Controlling the signal parameters at output A.",
    "B", "B", "���������� ����������� ������� �� ������ B.",
              "Controlling the signal parameters at output B.",
    FLAG_1, BIT_CHANNEL, pageSignals, FuncActive, PageSignals::OnPress_Channel, FuncDraw
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_8( cFormA,                                                                                                                                    //--- ��������� �������� - ����� ---
    "�����", "FORM",
    "����� ����� �������.",
    "Select waveform.",
    FORM_RU(Form::Sine),         FORM_EN(Form::Sine),         "�����",            "Sinus",
    FORM_RU(Form::RampPlus),     FORM_EN(Form::RampPlus),     "����������� ����", "Growing saw",
    FORM_RU(Form::RampMinus),    FORM_EN(Form::RampMinus),    "��������� ����",   "Wrecking saw",
    FORM_RU(Form::Triangle),     FORM_RU(Form::Triangle),     "�����������",      "Triangle",
    FORM_RU(Form::Meander),      FORM_EN(Form::Meander),      "������",           "Meander",
    FORM_RU(Form::Impulse),      FORM_EN(Form::Impulse),      "�����������",      "Triangle",
    FORM_RU(Form::PacketImpuls), FORM_EN(Form::PacketImpuls), "������",           "Packets",
    FORM_RU(Form::DDS),          FORM_EN(Form::DDS),          "������������",     "Free",
    numForm, pageSignals, FuncActive, PageSignals::OnPress_Form, FuncDraw
)

DEF_CHOICE_7( cFormB,                                                                                                                                    //--- ��������� �������� - ����� ---
    "�����", "FORM",
    "����� ����� �������.",
    "Select waveform.",
    FORM_RU(Form::Sine),      FORM_EN(Form::Sine),      "�����",            "Sinus",
    FORM_RU(Form::RampPlus),  FORM_EN(Form::RampPlus),  "����������� ����", "Growing saw",
    FORM_RU(Form::RampMinus), FORM_EN(Form::RampMinus), "��������� ����",   "Wrecking saw",
    FORM_RU(Form::Triangle),  FORM_RU(Form::Triangle),  "�����������",      "Triangle",
    FORM_RU(Form::Meander),   FORM_EN(Form::Meander),   "������",           "Meander",
    FORM_RU(Form::Impulse),   FORM_EN(Form::Impulse),   "�����������",      "Triangle",
    FORM_RU(Form::DDS),       FORM_EN(Form::DDS),       "������������",     "Free",
    numForm, pageSignals, FuncActive, PageSignals::OnPress_Form, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_ChnageParameter()
{
    FORM_CURRENT->ChangeParameter();
}

DEF_BUTTON( bChangeParameter,                                                                                                        //--- ��������� �������� - ������ �������� ��������� ---
    "��������", "Change",
    "��������� ���� ����� ���������.",
    "Opens the parameter input window.",
    pageSignals, FuncActive, OnPress_ChnageParameter, FuncDraw
)

DEF_CHOICE_PARAMETER(cParameters,                                                                                                                     //--- ��������� �������� - �������� ---
    "��������", "PARAMETER",
    "����� ��������� ��� ���������.",
    "Choosing a setting for customization.",
    pageSignals, FuncActive, OnPress_ChnageParameter, WAVE(Chan::A).GetForm(0)
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cTypeTune,                                                                                                                                //--- ��������� �������� - ������� ---
    "�������", "SENDING",
    "���������� ������������� ������� �������� �������� � ���������� ����������.",
    "Specifies the frequency of sending signal settings to the control device.",
    "����������", "SINGLE",         "������� �������� ������� ���������� ����������, ����� ������� ������ �������������.",
                                    "The signal settings are sent once, after you press the confirm button.",
    "����������", "CONTINUOUSLY",   "������� �������� ������� ���������� ��������� � ���������� ���������� �� ������.",
                                    "Sending of signal settings occurs synchronously with changing information on the screen.",
    FLAG_1, BIT_TUNE_FULL, pageSignals, FuncActive, FuncChangedChoice, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool OnKey(Control key)
{
    if(key.Is(Control::Esc) && key.action.IsRelease())
    {
        return FORM_CURRENT->CloseOpenedParameter();
    }

    return false;
}

DEF_PAGE_8( pageSignals,
    "��������� ��������", "SIGNAL SETTINGS",
    "", "",
    &cChannel,                                      ///< ��������� �������� - �����
    &cFormA,                                        ///< ��������� �������� - �����
    &cParameters,                                   ///< ��������� �������� - ��������
    &bChangeParameter,                              ///< ��������� �������� - ������ �������� ���������
    PageSignals::PageLoad::pointer,                 ///< ��������� �������� - ��������
    &cTypeTune,                                     ///< ��������� �������� - �������
    PageSignals::PageCalibration::PageA::pointer,   ///< ��������� �������� - ���������� A
    PageSignals::PageCalibration::PageB::pointer,   ///< ��������� �������� - ���������� B
    Page::Settings, Menu::mainPage, FuncActive, FuncPress, OnKey, FuncBeforeDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageSignals::Init()
{
    OnPress_Channel(true);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageSignals::OnPress_Form(bool)
{
    ChoiceBase *choice = (ChoiceBase *)pageSignals.items[1];

    WAVE_CURRENT.SetForm(choice->CurrentIndex());

    cParameters.form = FORM_CURRENT;

    Generator::TuneChannel(CURRENT_CHANNEL);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageSignals::OnPress_Channel(bool)
{
    cParameters.form = FORM_CURRENT;
    numForm = FORM_CURRENT->value;
    pageSignals.items[1] = Chan(CURRENT_CHANNEL).IsA() ? (Item *)&cFormA : (Item *)&cFormB;
}
