#pragma once


class Item
{
public:
    virtual void Draw() {}
};


class Page : public Item
{
public:
    virtual void Draw();
};
