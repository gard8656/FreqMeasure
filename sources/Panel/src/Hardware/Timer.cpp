#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Timer.h"
#include "Log.h"
#ifdef OPEN
#include <stm32f7xx.h>
#include "Hardware/Timer7XX.h"
#else
#include <stm32f4xx.h>
#include "Hardware/Timer4XX.h"
#endif
#include <limits>
#include "Hardware/CPU.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef OPEN
static Timer7XX tim2;   // ��� �����
static Timer7XX tim3;   // ��� ��������
#else
static Timer4XX tim2;   // ��� �����
static Timer4XX tim3;   // ��� ��������
#endif


typedef struct
{
    pFuncVV func;       // ������� �������
    uint    dTms;          // ������ ������������, ��
    uint    timeNextMS;    // ����� ���������� ������������. ���� == 0xffffffff, �� ������ ���������
    bool    repeat;        // ���� true, ����� �����������, ���� �� ����� ������� ������� Timer_Disable()
    uint8   notUsed0;
    uint8   notUsed1;
    uint8   notUsed2;
} TimerStruct;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static TimerStruct timers[Timer::Type::Number];
static uint timeStartLogging = 0;
static uint timePrevPoint = 0;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#undef TIME_NEXT
#define TIME_NEXT(type) (timers[type].timeNextMS)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������� �����, ������� ����������� � timeStop ��
static void StartTIM(uint timeStop);

static void StopTIM();
/// ���������� ����� ������������ ���������� �������, ���� 0, ���� �������� ���
static uint NearestTime();
/// ��������� ������� �� ������
static void TuneTIM(Timer::Type type);
/// ���������� ��� ������������ �������
static void ElapsedCallback();


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Timer::IsRun(Type type)
{
    return TIME_NEXT(type) != UINT_MAX;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::Init()
{
    for(uint i = 0; i < Timer::Type::Number; i++)
    {
        timers[i].timeNextMS = UINT_MAX;
    }
   
    tim3.Init(TIM3, 54000 - 1, TIM_COUNTERMODE_UP, 1, TIM_CLOCKDIVISION_DIV1);
    tim3.EnabledIRQ(1, 1);

    tim2.Init(TIM2, 0, TIM_COUNTERMODE_UP, (uint)-1, TIM_CLOCKDIVISION_DIV1);
    tim2.Start();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::DeInit()
{
    tim2.Stop();
    tim2.DeInit();
    
    tim3.DisableIRQ();
    tim3.StopIT();
    tim3.DeInit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void ElapsedCallback()
{
    uint time = TIME_MS;

    if (NearestTime() > time)
    {
        return;
    }

    StopTIM();

    for (uint type = 0; type < Timer::Type::Number; type++)
    {
        if (TIME_NEXT(type) <= time)            // ���� ������ ����� ������������
        {
            TimerStruct *timer = &timers[type];
            timer->func();
            if (timer->repeat)
            {
                do      // ���� ����� ������, ��� ��������� ������ SysTick, ������� ����������� ������������, ����� ��������� ���������,
                {       // � ���� ������� ����������� ������, ��� timer->dTm ��, �� ��� ��� ��������
                    timer->timeNextMS += timer->dTms;
                } while (timer->timeNextMS < TIME_MS);

            }
            else
            {
                timer->timeNextMS = UINT_MAX;
            }
        }
    }

    StartTIM(NearestTime());
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::Set(Type type, pFuncVV func, uint dTms)
{
    TimerStruct *timer = &timers[type];
    timer->func = func;
    timer->dTms = dTms;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::SetAndStartOnce(Type type, pFuncVV func, uint dTms)
{
    Timer::Set(type, func, dTms);
    StartOnce(type);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::SetAndEnable(Type type, pFuncVV func, uint dTms)
{
    Set(type, func, dTms);
    Enable(type);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::StartOnce(Type type)
{
    timers[type].repeat = false;
    TuneTIM(type);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::Enable(Type type)
{
    timers[type].repeat = true;
    TuneTIM(type);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void TuneTIM(Timer::Type type)
{
    TimerStruct *timer = &timers[type];

    uint timeNearest = NearestTime();

    uint timeNext = TIME_MS + timer->dTms;
    timer->timeNextMS = timeNext;

    if(timeNext < timeNearest)      // ���� ������ ������ ��������� ������ ��������
    {
        StartTIM(timeNext);         // �� ������� ������ �� ���� �����
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::Disable(Type type)
{
    timers[type].timeNextMS = UINT_MAX;
    timers[type].repeat = false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static uint NearestTime()
{
    uint time = UINT_MAX;

    for(uint type = 0; type < Timer::Type::Number; type++)
    {
        if(TIME_NEXT(type) < time)
        {
            time = TIME_NEXT(type);
        }
    }
    
    return time;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void StartTIM(uint timeStopMS)
{
    StopTIM();

    if(timeStopMS == UINT_MAX)
    {
        return;
    }

    uint dT = timeStopMS - TIME_MS;

    tim3.StartIT((dT * 2) - 1);             // 10 ������������� 0.1��. �.�. ���� ��� ����� 1��, ����� �������� (100 - 1)
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void StopTIM()
{
    tim3.StopIT();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::PauseOnTime(uint timeMS)
{
    HAL_Delay(timeMS);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::PauseOnTicks(uint numTicks)
{
    uint startTicks = TIME_TICKS;
    while (TIME_TICKS - startTicks < numTicks)
    {
    };
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::StartMultiMeasurement()
{
    TIM2->CR1 &= (uint)~TIM_CR1_CEN;
    TIM2->CNT = 0;
    TIM2->CR1 |= TIM_CR1_CEN;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Timer::StartLogging()
{
    timeStartLogging = TIME_TICKS;
    timePrevPoint = timeStartLogging;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint Timer::LogPointUS(char *)
{
    uint interval = TIME_TICKS - timePrevPoint;
    timePrevPoint = TIME_TICKS;
    //LOG_WRITE("%s %.2f us", name, interval / 120.0);
    return interval;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint Timer::LogPointMS(char *)
{
    uint interval = TIME_TICKS - timePrevPoint;
    timePrevPoint = TIME_TICKS;
    //LOG_WRITE("%s %.2f ms", name, interval / 120e3);
    return interval;
}

#ifdef __cplusplus
extern "C" {
#endif

    //------------------------------------------------------------------------------------------------------------------------------------------------
    void TIM3_IRQHandler()
    {
        if ((TIM3->SR & TIM_SR_UIF) == TIM_SR_UIF)
        {
            if((TIM3->DIER & TIM_DIER_UIE) == TIM_DIER_UIE)
            {
                TIM3->SR = ~TIM_DIER_UIE;
                ElapsedCallback();
            }
        }
    }

#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#undef TIME_NEXT
