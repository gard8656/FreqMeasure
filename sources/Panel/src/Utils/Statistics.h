#pragma once
#include "defines.h"


class Statistics
{
public:
    static void BeginFrame();

    static void EndFrame();

    static void Show();

private:
    /// ����� ������ �����
    static uint timeStart;
    /// �����, ����������� �� ��������� ������ �����
    static int timeFrame;
    /// ����� ����� ����������� ����� ����� ���������
    static uint timeAccumFrames;
    /// ����� ��������� ���� ������ �� 1 �������
    static int timeAllFrames;
    /// ����� ������ ���������� 1-���������� �������, � ������� �������� ���������� ����� ����� ���������
    static uint timeStartFrames;
};
