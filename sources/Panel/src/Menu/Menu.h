#pragma once
#include "Menu/MenuItems.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Menu
{
public:
    /// ������� ��������� ���� ���������� �� ������� ������������
    static const int NUM_ITEMS_ON_DISPLAY = 4;

    static void Init();
        
    static void Update();

    static void Draw();
    /// ���������� true, ���� ����� ��������� �������������� ���������� ����
    static bool RegIsControlSubPages();
    /// ���������� ����� ��������� �������� ����
    static Item* GetOpenedItem() { return openedItem; };
    /// ���������� Item, ������� ����� ��������� ��������
    static void SetOpenedItem(Item *item) { openedItem = item; };
    /// ���������� ������� Item - ������ � ���� ����� ��������� ������� ����� � ESC
    static void SetCurrentItem(Item *item) { currentItem = item; };
    /// ����� �������� Item - �������� Item'a ������ ���
    static void ResetCurrentItem() { currentItem = 0; };
    /// ���������� ������� Item
    static Item* GetCurrentItem() { return currentItem; };
    /// �������� �������� ���� - ���� ������
    static void ResetOpenedItem() { openedItem = 0; };
    ///\brief  ����� �������� ����� �������� ����, ���������������� �������������� ������� [F1..F4], ���� ��� ��������� � ������ ���������, � 0, 
    /// ���� �� ���� ������ �� ������.
    static Item *pressedItem;
    /// ���������� ������� �������� �� ��������. ������ ���� �������� ����������� �������� ����. ����� -1
    static int GetPosition(Page *page);
    /// ������������� ��� ��������� ��������������� ��������
    static void SetAdditionPage(Page *page);
    /// ������� �������������� �������� � ���������
    static void ResetAdditionPage();
    /// ��������� �� ������� ��������
    static Page *mainPage;
private:
    /// ���������� �����
    static int DrawTitle();
    /// ���������� ����������� ����������� control
    static void ProcessContorl(Control control);
    /// ������������ ��������� �������. ���������� true, ���� ��������� ������ ����������
    static bool ProcessOutputs(Control control);

    static void DrawPagesUGO(int x);
    /// ���� �����-�� ���� �������, �� ����� ��� �����
    static Item *openedItem;
    /// ���� ���������� ��������� �� �������� ��������� ���� � ������, ���� ����� ��������� �������������� ��������
    static Page *oldPage;

    static Item *currentItem;
};
