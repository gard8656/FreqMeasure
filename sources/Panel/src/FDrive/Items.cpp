#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "FDrivePanel.h"
#include "Items.h"
#include "File.h"
#include "Interface/InterfacePanel.h"
#include <cstring>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������ ����� ����� � ���������� ������� number
static void SendRequestForNameFile(int number);
/// ������ ������� ����� � ���������� ������� number
//static void SendRequestForSizeFile(int number);
/// ���������� i-� ����
static void DrawItem(int i, int x, int y, bool highlight);
/// ���������� ��� i-�� �����
static String GetNameItem(int i);
/// ���������� ������ i-�� �����
//static int GetSizeItem(int i);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���������� ������ � ������� ��������
static int numFiles;
bool Items::requestIsSend = false;

#define NUM_ITEMS 15

struct StructFile
{
    char name[50];
    uint8 nutUsed[2];
    int size;
    StructFile() : size(-1) { name[0] = 0; }
    void Clear() { name[0] = 0; size = -1; }
}
files[NUM_ITEMS];

/// ������� ����
static int curItem = 0;
/// ���������� ��������� � ������� ��������
static int numDirs = -1;
/// �������� ����
static File file;



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Items::Init()
{
    numDirs = numFiles = -1;
    requestIsSend = false;
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        files[i].Clear();
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Items::NumberCurrentFile()
{
    return curItem;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Items::SendRequest()
{
    Message message(Command::FDrive_NumDirsAndFiles, FDrive::directory);

    Interface::Send(&message);

    requestIsSend = true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Items::Handler::Processing(Message *msg)
{
    msg->ResetPointer();

    uint8 command = msg->TakeByte();

    if (command == Command::FDrive_NumDirsAndFiles)
    {
        numDirs = (int)msg->TakeWord();
        numFiles = (int)msg->TakeWord();
        requestIsSend = false;
        return true;
    }
    else if (command == Command::FDrive_RequestFile)
    {
        int num = msg->TakeByte();
        std::strcpy(files[num].name, msg->String(2));

        if (num == curItem)
        {
            file.Open(num);
        }

        return true;
    }
    else if (command == Command::FDrive_RequestFileSize)
    {
        int num = msg->TakeByte();
        files[num].size = (int)msg->TakeWord();
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool EqualsRequestNameFile(Task *task1, Task *task2)
{
    Message *msg1 = task1->GetMessage();

    Message *msg2 = task2->GetMessage();

    uint8 com = Command::FDrive_RequestFile;

    return  (com == msg1->TakeByte()) &&
            (com == msg2->TakeByte()) &&
            (msg1->TakeByte() == msg2->TakeByte());
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void SendRequestForNameFile(int number)
{
    Message *message = new Message(Command::FDrive_RequestFile, (uint8)number, FDrive::directory);
    
    Task *task = new Task(message, Items::Handler::Processing, EqualsRequestNameFile);
    
    Interface::AddTask(task);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
static bool EqualsRequestSizeFile(Task *task1, Task *task2)
{
    Message *msg1 = task1->GetMessage();

    Message *msg2 = task2->GetMessage();

    uint8 com = Command::FDrive_RequestFileSize;

    return  (com == msg1->TakeByte()) &&
            (com == msg2->TakeByte()) &&
            (msg1->TakeByte() == msg2->TakeByte());
}
*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
static void SendRequestForSizeFile(int number)
{
    Message *message = new Message(Command::FDrive_RequestFileSize, (uint8)number, FDrive::directory);
    
    Task *task = new Task(message, Items::Handler::Processing, EqualsRequestSizeFile);
    
    Interface::AddTask(task);
}
*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
String GetNameItem(int i)
{
    if (files[i].name[0] == 0)
    {
        SendRequestForNameFile(i);
    }
    
    return String(files[i].name);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
static int GetSizeItem(int i)
{
    if (files[i].size == -1)
    {
        SendRequestForSizeFile(i);
    }

    return files[i].size;
}
*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Items::NumberDirs()
{
    return numDirs;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Items::PressUp()
{
    if (curItem > 0)
    {
        curItem--;
        file.Open(curItem);
    }
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Items::PressDown()
{
    if (curItem < numFiles - 1)
    {
        curItem++;
        file.Open(curItem);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Items::Draw(int x, int y)
{
    Text::SetUpperCase(false);

    for (int i = 0; i < numFiles; i++)
    {
        DrawItem(i, x, y, (curItem == i));
        y += 10;
    }

    file.Draw(5, 235);

    Text::SetUpperCase(true);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawItem(int i, int x, int y, bool highlight)
{
    Color color = Color::FILL;
    if (highlight)
    {
        Painter::FillRegion(x - 1, y, 230, 9, color);
        color = Color::BACK;
    }
    GetNameItem(i).Draw(x, y, color);
    //String("%d", GetSizeItem(i)).Draw(x + 180, y);
}
