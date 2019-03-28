#pragma once


class SPI4_
{
friend class CPU;
private:
    static void Init();
public:
    /// ��������� ������ ������
    static bool Transmit(const void *buffer, uint size, uint timeout);

    static bool Transmit(uint value, uint timeout);
    /// ������� ������ ������
    static bool Receive(void *recv, uint size, uint timeout);
    /// ������� ��������� size ���� � ���������� �� � compared. ���������� ���������� ��������� ����
    static uint ReceiveAndCompare(const void *compared, uint size);
    /// ���������� true, ���� ������ ����� � ������
    static bool IsReady();
    /// ����� ���� ����������� ����������
    static void WaitFreedom();
    /// �������� �������� ������� ���������� �� ��������� "�����" � ��������� "��������"
    static void WaitFalling();
};
