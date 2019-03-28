#include "stdafx.h"
#ifndef WIN32
#include "Display/InputWindow.h"
#include "Display/Painter.h"
#include "Display/Symbols.h"
#include "Display/Text.h"
#include "Menu/Menu.h"
#include "Menu/MenuItems.h"
#include "Settings/Settings.h"
#include "AddPageInput.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pInput;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Draw_Left(int x, int y)
{
    String("�������").Draw(x + 14, y + 12);
    Text::Draw4SymbolsInRect(x + 26, y + 30, Ideograph::_8::FillUp);
}

DEF_SMALL_BUTTON(sbOrderUp,                                                                                           //--- ���� ����� - ������ ����� ---
    "������� ������", "Order up",
    "��������� ������� ������� ���������",
    "Increase the unit order",
    pInput, FuncActive, InputWindow::OrderUp, Draw_Left
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Draw_Right(int x, int y)
{
    String("�������").Draw(x + 14, y + 12);
    Text::Draw4SymbolsInRect(x + 26, y + 30, Ideograph::_8::FillDown);
}

DEF_SMALL_BUTTON(sbOrderDown,                                                                                         //--- ���� ����� - ������ ������ ---
    "������� �������", "Order down",
    "��������� ������� ������� ���������",
    "Reduce the unit order",
    pInput, FuncActive, InputWindow::OrderDown, Draw_Right
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Cancel()
{
    Menu::ResetAdditionPage();
}

static void Draw_Cancel(int x, int y)
{
    String("��������").Draw(x + 13, y + 12);
    Text::Draw4SymbolsInRect(x + 25, y + 28, Ideograph::_8::Delete);
}

DEF_SMALL_BUTTON(sbCancel,                                                                                               //--- ���� ����� - ������ ---
    "������� ���������", "UNITS",
    "���������� �� ����� ������ ��������",
    "Unsubscribe from the new value",
    pInput, FuncActive, OnPress_Cancel, Draw_Cancel
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Draw_Enter(int x, int y)
{
    String("�����������").Draw(x + 3, y + 12);
    Text::Draw4SymbolsInRect(x + 25, y + 28, Ideograph::_8::Save);
}

DEF_SMALL_BUTTON(sbEnter,                                                                                                  //--- ���� ����� - ���� ---
    "����", "ENTER",
    "����������� ���� ������ ��������",
    "Confirm the new value",
    pInput, FuncActive, InputWindow::KeyEnter, Draw_Enter
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool OnControl(Control key)
{
    if(!key.IsFunctional())
    {
        InputWindow::ProcessContorl(key);
        return true;
    }
    return false;
}

Page *AddPageInput::pointer = (Page *)&pInput;

DEF_PAGE_SB( pInput,
    "���� ��������", "VALUE ENTRY",
    "",
    "",
    &sbOrderUp,     ///< ���� ����� - ������ �����
    &sbOrderDown,    ///< ���� ����� - ������ ������
    &sbCancel,   ///< ���� ����� - ������
    &sbEnter,    ///< ���� ����� - ����
    0,
    0,
    Page::SB_Input, 0, FuncActive, FuncPress, FuncDrawPage, OnControl
)
