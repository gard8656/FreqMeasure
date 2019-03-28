#pragma once
#include "Message.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FDrive
{
public:
    /// ��������� �������������
    static void Init();

    /// ��� ���������� - �������� ��� �����
    enum View
    {
        Dirs,
        Files
    };
    
    static View view;

    /// ��������� �����-���������
    static void Draw();
    /// ��������� ������� ������ "�����"
    static void PressUp();
    /// ��������� ������� ������ "����"
    static void PressDown();
    /// ��������� ������� ������ "�������"
    static void PressChoose();

    class Handler
    {
    friend class Handlers;
        static bool Processing(Message *msg);
    };

    /// ���� � �������� ��������
    static char directory[255];
};
