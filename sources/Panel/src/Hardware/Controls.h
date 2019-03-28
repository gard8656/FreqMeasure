#pragma once
#include "defines.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Control
{
    enum E
    {
        None      = 0x00,
        F1        = 0x01,
        F2        = 0x02,
        F3        = 0x03,
        F4        = 0x04,
        _0        = 0x05,
        _1        = 0x06,
        _2        = 0x07,
        _3        = 0x08,
        _4        = 0x09,
        _5        = 0x0a,
        _6        = 0x0b,
        _7        = 0x0c,
        _8        = 0x0d,
        _9        = 0x0e,
        Dot       = 0x0f,
        Minus     = 0x10,
        Esc       = 0x11,
        Left      = 0x12,
        Right     = 0x13,
        On1       = 0x15,
        On2       = 0x16,
        RegLeft   = 0x17,
        RegRight  = 0x18,
        RegButton = 0x19
    } value;

    struct Action
    {
        enum E
        {
            Down,
            Long,
            Up
        } value;
        Action(E v = Down) : value(v) {};
        operator uint8() const { return (uint8)value; };
        bool Is(Action a) const { return a.value == value; };
        /// ���������� true, ���� Up ��� Long
        bool IsRelease() const;
    } action;

    explicit Control(E v = None, Action::E a = Action::Down) : value(v), action(a) {};
    Control &operator=(Control rval)
    {
        value = rval.value;
        action = rval.action;
        return *this;
    }
    Control(const Control &c)
    {
        value = c.value;
        action = c.action;
    }
    operator uint8() const { return (uint8)value; };
    bool Is(Control::E c) { return c == value; };
    bool Is(Control::E c, Action::E a) { return value == c && action == a; };
    bool IsDigit() const;
    char ToChar() const;
    pString Name() const;
    bool IsFunctional() const;
    /// ���������� true, ���� ������� �����
    bool IsRotate() const;
    /// ���������� true, ���� ������ ���������� �������� (�����-������)
    bool IsCursors() const { return value == Left || value == Right; };
};
