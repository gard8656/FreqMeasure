#pragma once
#include "Menu/MenuItems.h"
#include "Hardware/Controls.h"


class Hint
{
public:
    /// ��������� ���������
    static void Draw();
    /// ����� ����������. ���������� false, ���� ��������� �� ���������
    static bool ProcessControl(Control control);

private:
    /// \brief ������������ ��������� � �����������
    /// start, end - ��������� � �������� ������ choice ��� ������
    /// calculate - ���� true, �� ��������� �� ������������ - ������ ������ ��������
    static int DrawDetailedHint(Choice *choice, int x, int y, int width, int start, int end, bool calculate = false);
    /// ���������� ����� ������� � ���������
    static int NumPagesInHint(Choice *choice, int x, int y, int width);
    /// ������������ ������, ����������� ��� �������� ��������� �� ��������
    static void Calcualte(Choice *choice, int x, int y, int width);
    /// ������ ��� ������� � ��������������� ���������
    static void DrawPagesUGO(const int xRight, const int y);
    /// ���� true - ����� �������� ��������� �� �����
    static bool show;
    /// �������, ��� �������� ����� �������� ���������
    static const Item *item;
    /// ����� ����������, ��� �������� ����� �������� ���������
    static Control::E control;
    /// ���������� ������� � ���������
    static int numPages;
    /// ������� �������������� ��������
    static int currentPage;
    /// � ������ ������ ���������� ������ ��������
    static int firstItemOnSecondPage;
    /// ������������� � true �������� ��������, ��� Item ��� ������ ��� �������� � ��������� �������� �� ��������
    static bool needCalculate;
};
