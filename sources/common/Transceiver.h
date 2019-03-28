#pragma once
#include "Message.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Transceiver
{
    friend class Interface;
    friend class Handlers;
private:

    static void Transmit(Message *message);

    static bool Receive(Message *message);
};
