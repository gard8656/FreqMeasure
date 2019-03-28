#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Display/Console.h"
#include "Display/Painter.h"
#include "Hardware/Timer.h"
#include "log.h"
#include "SPI.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��� ����� � �������� �����������
static SPI_HandleTypeDef handleSPI4 =
{
	SPI4,
	{
		SPI_MODE_MASTER,
		SPI_DIRECTION_2LINES,
		SPI_DATASIZE_8BIT,
		SPI_POLARITY_HIGH,
		SPI_PHASE_2EDGE,
		SPI_NSS_SOFT,
		SPI_BAUDRATEPRESCALER_32,
		SPI_FIRSTBIT_MSB,
		SPI_TIMODE_DISABLED,
		SPI_CRCCALCULATION_DISABLED,
		7
	},
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, HAL_UNLOCKED, HAL_SPI_STATE_RESET, 0
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SPI4_::Init()
{
	GPIO_InitTypeDef isGPIO =
	{   //  CLK         MI           MO
		GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6,
		GPIO_MODE_AF_PP,
		GPIO_PULLUP,
		GPIO_SPEED_HIGH,
		GPIO_AF5_SPI4
	};

	HAL_GPIO_Init(GPIOE, &isGPIO);

	HAL_SPI_Init(&handleSPI4);

	// �� ���� ���� ����� ������ ��������� ���������� ����������
	isGPIO.Pin = GPIO_PIN_4;
	isGPIO.Mode = GPIO_MODE_INPUT;
	isGPIO.Alternate = 0;
	HAL_GPIO_Init(GPIOE, &isGPIO);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SPI4_::Transmit(const void *buffer, uint size, uint timeout)
{
	if (HAL_SPI_Transmit(&handleSPI4, (uint8 *)buffer, (uint16)size, timeout) != HAL_OK)
	{
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SPI4_::Transmit(uint value, uint timeout)
{
    return Transmit(&value, 4, timeout);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SPI4_::Receive(void *recv, uint size, uint timeout)
{
	if (HAL_SPI_Receive(&handleSPI4, (uint8 *)recv, (uint16)size, timeout) != HAL_OK)
	{
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint SPI4_::ReceiveAndCompare(const void *compared, uint size)
{
    uint result = 0;

    uint8 byte = 0;

    uint8 *data = (uint8 *)compared;

    for (uint i = 0; i < size; i++)
    {
        if (Receive(&byte, 1, 10) && data[i] != byte)
        {
            result++;
        }
    }

    return result;
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void SPI4_::WaitFreedom()
{
	while (!IsReady())
	{
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void SPI4_::WaitFalling()
{
    while (IsReady())
    {
    };   // ���� ������ � ����� ������� ����������, ��������� ���, ����� ���������� �������������� ���������� ����� ������������ ������

    while (!IsReady())
    {
    };  // ������ �������, ����� ����� ������ ����������
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SPI4_::IsReady()
{
	return HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == GPIO_PIN_SET;
}
