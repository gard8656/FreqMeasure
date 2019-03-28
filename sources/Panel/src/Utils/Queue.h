#pragma once


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Queue
{
public:
    Queue();

    T *Front();

    bool Push(T *message);

    void Pop();

    int Size();
    /// ���������� true, ���� ������� ��������� ��������� (Push() ����������)
    bool Full() const;

private:
    int first;

    int last;

    static const uint SIZE = 100U;

    T *storage[SIZE];
};
