#pragma once
#include "DisplayTypes.h"
#include "defines.h"
#include "Hardware/Controls.h"
#include "Settings/SettingsTypes.h"



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DISPLAY_SHOW_WARNING(warn)

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240

#ifdef OPEN
#define BUFFER_WIDTH    1024            /* ������ ������ ��� ��������� */
#define BUFFER_HEIGHT   600             /* ������ ������ ��� ��������� */
#else
#define BUFFER_WIDTH    SCREEN_WIDTH    /* ������ ������ ��� ��������� */
#define BUFFER_HEIGHT   SCREEN_HEIGHT   /* ������ ������ ��� ��������� */
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Display
{
public:
    static void Init();

    static void Update();

    static uint8 *GetBuffer();

private:
    /// �����
    static uint8 frontBuffer[BUFFER_WIDTH * BUFFER_HEIGHT];
    /// ������ �����. � �� ���������� ���������, � ����� ����������� ���������� �� frontBuffer
    static uint8 backBuffer[BUFFER_WIDTH * BUFFER_HEIGHT];
};
