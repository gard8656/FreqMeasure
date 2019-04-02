#pragma once

enum buttons 
{
    Button_0, 
    Button_1, 
    Button_2,
    Button_4,
    Button_5,
    Button_6, 
    Button_7, 
    Button_8, 
};

namespace Keyboard
{
    void Init();
    buttons Update();	
};
