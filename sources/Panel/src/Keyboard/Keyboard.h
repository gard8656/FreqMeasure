#pragma once

enum Buttons 
{
    Button_0, 
    Button_1, 
    Button_2,
    Button_3,
    Button_4,
    Button_5,
    Button_6, 
    Button_7, 
    Button_8,
    Button_9,
    Button_F1,
    Button_F2,
    Button_F3,
    Button_F4,
    Button_F5,
    Button_ESC,
    Button_Left,
    Button_Right,
    Button_NULL
};

namespace Keyboard
{
    void Init();
    Buttons Update();	
};
