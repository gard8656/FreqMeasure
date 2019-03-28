#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Math.h"
#include "Settings/Settings.h"
#include <cmath>
#if __ARMCLIB_VERSION < 6070001
#include <cstdlib>
#include <string.h>
#else
#include <cstdlib>
#include <cstring>
#endif
#include <limits>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LowSignedBit(uint value)
{
    int verValue = 1;

    for (int i = 0; i < 32; i++)
    {
        if (verValue & ((int)value))
        {
            return i;
        }

        verValue <<= 1;
    }

    return -1;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Math::Smoothing(uint8 *data, int numPoints, int numSmooth)
{
    if (numSmooth == 0 || numSmooth == 1)
    {
        return;
    }

    float *buffer = (float *)std::malloc((size_t)(numPoints * (int)sizeof(float)));
    int  *num = (int *)std::malloc((size_t)(numPoints * (int)sizeof(int)));

    for (int i = 1; i < numPoints; i++)
    {
        buffer[i] = 0.0f;

        num[i] = 0;
        for (int j = -numSmooth / 2; j < numSmooth / 2; j++)
        {
            int index = i + j;
            if (index >= 1 && index < numPoints)
            {
                buffer[i] += data[index];
                ++num[i];
            }
        }
    }
    
    for (int i = 1; i < numPoints; i++)
    {
        data[i] = (uint8)(buffer[i] / num[i] + 0.5f);
    }

    std::free(buffer);
    std::free(num);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool IntInRange(int value, int min, int max)
{
    return (value >= min) && (value <= max);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float MaxFloat(float val1, float val2, float val3)
{
    float retValue = val1;
    if (val2 > retValue)
    {
        retValue = val2;
    }
    if (val3 > retValue)
    {
        retValue = val3;
    }
    return retValue;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Math::MinFrom2Int(int val0, int val1)
{
    if (val0 < val1)
    {
        return val0;
    }
    return val1;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint Pow10(int pow)
{
    uint result = 1;

    while (pow--)
    {
        result *= 10;
    }

    return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 Math::MaxFromArray(const uint8 *data, int firstPoint, int lastPoint)
{

#define MAX_IF_ABOVE if(d > max) { max = d; }

    uint8 max = 0;
    const uint8 *pointer = &data[firstPoint];

    for (int i = firstPoint; i < lastPoint; i += 2)
    {
        uint8 d = *pointer++;
        MAX_IF_ABOVE;
        d = *pointer++;
        MAX_IF_ABOVE;
    }
    if ((lastPoint - firstPoint + 1) & 1)
    {
        uint8 d = *pointer;
        MAX_IF_ABOVE
    }

    return max;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 Math::MinFromArray(const uint8 *data, int firstPoint, int lastPoint)
{

#define MIN_IF_LESS if(d < min) { min = d; }

    uint8 min = 255;
    const uint8 *pointer = &data[firstPoint];

    for (int i = firstPoint; i < lastPoint; i += 2)
    {
        uint8 d = *pointer++;
        MIN_IF_LESS
            d = *pointer++;
        MIN_IF_LESS
    }
    if ((lastPoint - firstPoint + 1) & 1)
    {
        uint8 d = *pointer;
        MIN_IF_LESS
    }

    return min;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float RandFloat(float min, float max)
{
    float delta = max - min;
    return min + ((std::rand() / (float)RAND_MAX) * delta);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float Math::GetIntersectionWithHorizontalLine(int x0, int y0, int x1, int y1, int yHorLine)
{
    if (y0 == y1)
    {
        return (float)x1;
    }

    return (yHorLine - y0) / ((float)(y1 - y0) / (float)(x1 - x0)) + x0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 Math::CalculateFiltr(const uint8 *data, int x, int numPoints, int numSmoothing)
{
    if (numSmoothing < 2)
    {
        return data[x];
    }

    int count = 1;
    int sum = data[x];
    int startDelta = 1;

    int endDelta = numSmoothing / 2;

    for (int delta = startDelta; delta <= endDelta; delta++)
    {
        if (((x - delta) >= 0) && ((x + delta) < (numPoints)))
        {
            sum += data[x - delta];
            sum += data[x + delta];
            count += 2;
        }
    }

    if ((numSmoothing % 2) == 1)
    {
        int delta = numSmoothing / 2;
        if ((x + delta) < numPoints)
        {
            sum += data[x + delta];
            count++;
        }
    }

    return (uint8)(sum / (float)count);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Math::CalculateFiltrArray(const uint8 *dataIn, uint8 *dataOut, int numPoints, int numSmoothing)
{
    if (numSmoothing < 2)
    {
        std::memcpy(dataOut, dataIn, (size_t)numPoints);
    }
    else
    {
        bool addCalculation = (numSmoothing % 2) == 1;
        int endDelta = numSmoothing / 2;
        int startDelta = 1;
        int d = numSmoothing / 2;

        for (int i = 0; i < numPoints; i++)
        {
            int count = 1;
            int sum = dataIn[i];

            for (int delta = startDelta; delta <= endDelta; delta++)
            {
                if (((i - delta) >= 0) && ((i + delta) < (numPoints)))
                {
                    sum += dataIn[i - delta];
                    sum += dataIn[i + delta];
                    count += 2;
                }
            }

            if (addCalculation)
            {
                if ((i + d) < numPoints)
                {
                    sum += dataIn[i + d];
                    count++;
                }
            }

            dataOut[i] = (uint8)(sum / (float)count);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 Math::MaxFromArray_RAM(const uint16 *data, int firstPoint, int lastPoint)
{
    uint8 max = 0;

    const uint16 *pointer = &data[firstPoint];

    const int endPoint = lastPoint / 2;

    for (int i = firstPoint; i < endPoint; i++)
    {
        uint16 d16 = *pointer++;

        uint8 d8 = (uint8)d16;
        if (d8 > max)
        {
            max = d8;
        }

        d8 = (uint8)(d16 >> 8);
        if (d8 > max)
        {
            max = d8;
        }
    }

    return max;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 Math::MinFromArray_RAM(const uint16 *data, int firstPoint, int lastPoint)
{
    uint8 min = 255;

    const uint16 *pointer = &data[firstPoint];

    const int endPoint = lastPoint / 2;

    for (int i = firstPoint; i < endPoint; i++)
    {
        uint16 d16 = *pointer++;

        uint8 d8 = (uint8)d16;
        if (d8 < min)
        {
            min = d8;
        }
        d8 = (uint8)(d16 >> 8);
        if (d8 < min)
        {
            min = d8;
        }
    }

    return min;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Math::FindAnotherElement(uint8 *data, uint8 value, int numElements)
{
    for (int i = 0; i < numElements; i++)
    {
        if (data[i] != value)
        {
            return i;
        }
    }

    return -1;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Math::DigitsInIntPart(float value)
{
    float absValue = std::fabsf(value);

    int num = 0;

    do
    {
        ++num;
        absValue /= 10.0f;
    } while (absValue >= 1.0f);

    return num;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float Math::RoundFloat(float value, int numDigits)
{
    float absValue = std::fabsf(value);

    int digsInInt = Math::DigitsInIntPart(absValue);

    if (digsInInt < numDigits)  // �������������
    {
        uint pow = Pow10(numDigits - digsInInt);
        absValue = ((int)(absValue * pow + 0.5f)) / (float)pow;
    }

    return value > 0.0f ? absValue : -absValue;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool IsEquals(float x, float y)
{
    return std::fabsf(x - y) < std::numeric_limits<float>::epsilon();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool FloatsIsEquals(float value0, float value1, float epsilonPart)
{
    float max = std::fabsf(value0) > std::fabsf(value1) ? std::fabsf(value0) : std::fabsf(value1);

    float epsilonAbs = max * epsilonPart;

    return std::fabsf(value0 - value1) < epsilonAbs;
}
