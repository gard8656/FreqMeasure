#pragma once
#include "defines.h"
#include "SettingsTypes.h"
#include "Menu/MenuItems.h"
#include "FrequencyMeter/FrequencyMeter.h"
#include "Generator/GeneratorPanel.h"


#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4623)
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pInput;

#define COLOR(x)                (set.disp_Colors[x])
#define CURRENT_PAGE            (set.menu_currentPage)

#define MENU_POS_ACT_ITEM(x)    (set.menu_posActItem[x])
#define MENU_CURRENT_SUBPAGE(x) (set.menu_currentSubPage[x])

#define BIT_FL1(numBit)         ((FLAG_1 >> (numBit)) & 0x01)

#define CONSOLE_ENABLED         (BIT_FL1(BIT_CONSOLE))
#define DEBUG_MODE_ENABLED      (BIT_FL1(BIT_DBG_MODE))
#define BACKGROUND_BLACK        (BIT_FL1(BIT_BACK_BLACK))
#define SHOW_STATISTICS         (BIT_FL1(BIT_STATISTICS))
/// ���� true, �� ������� � ������ ����������� ��� ������ �������� �����
#define TUNE_FULL               (BIT_FL1(BIT_TUNE_FULL))
#define PARITY                  ((Parity)BIT_FL1(BIT_PARITY))
#define DEBUG_SHOW_SENDS        (BIT_FL1(BIT_SHOW_SENDS))

#define CHANNEL_ENABLED(ch)     ((FLAG_1 >> ((ch) + BIT_CHAN_A)) & 0x01)
#define SWITCH_CHANNEL_A        (FLAG_1 ^= (1 << (BIT_CHAN_A)))
#define SWITCH_CHANNEL_B        (FLAG_1 ^= (1 << (BIT_CHAN_B)))
#define LANG                    ((Language::E)BIT_FL1(BIT_LANG))
#define LANG_RU                 (LANG == Language::RU)
#define CURRENT_CHANNEL         ((Chan::E)BIT_FL1(BIT_CHANNEL))
#define CURRENT_CHANNEL_IS_A    (CURRENT_CHANNEL == Chan::A)
#define CURRENT_CHANNEL_IS_B    (CURRENT_CHANNEL == Chan::B)
#define SIZE_BYTE               ((SizeByte)BIT_FL1(BIT_SIZE_BYTE))
#define STOP_BIT                ((StopBit)BIT_FL1(BIT_STOP_BIT))

#define FREQ_RESIST                 ((FreqResist)BIT_FL1(BIT_FREQ_RESIST))
#define FREQ_COUPLE                 ((FreqCouple)BIT_FL1(BIT_FREQ_COUPLE))
#define FREQ_FILTR                  ((FreqFiltr)BIT_FL1(BIT_FREQ_FILTR))
#define FREQ_INTERVAL               ((FreqInterval)BIT_FL1(BIT_FREQ_INTERVAL))
#define FREQ_METER_MEASURE          (set.freq_measure)
#define FREQ_METER_MEASURE_IS_FREQ   (FREQ_METER_MEASURE == FreqMeasure::Freq)
#define FREQ_METER_MEASURE_IS_PERIOD (FREQ_METER_MEASURE == FreqMeasure::Period)
#define FREQ_METER_ENABLED           (FREQ_METER_MEASURE != FreqMeasure::Disable)
#define FREQ_AVE_PERIOD             (set.freq_avePeriod)
#define FREQ_BILLING_TIME           (set.freq_billingTime)
#define FREQ_TIME_STAMPS            (set.freq_timeStamps)
#define FREQ_TEST                   ((FreqTest)BIT_FL1(BIT_FREQ_TEST))
#define FREQ_LEVEL                  (set.freq_level)
#define FREQ_HYSTERESIS             (set.freq_hysteresis)

#define BIG_SYMBOLS             ((BIT_FL1(BIT_BIG_SYMBOLS)))

#define SINE_MANIPULATION_ENABLED(ch)   (set.sine_ManipulationEnabled[ch])
#define SINE_MANIPULATION_MODE(ch)      (set.sine_ManipulationMode[ch])

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)

class Settings // -V690
{
public:
    uint16              size;                           ///< ������ ��������� Settings
    col_val                     disp_Colors[32];                            ///< �����
    ParameterValue              sig_parameter[Form::Number];                ///< ������� ��������� �������� �������
    Page*                       menu_currentPage;                           ///< ����� �������� �������� ����. 0, ���� ������� ������� ��������
    int8                        menu_posActItem[Page::Number];              ///< ������� ��������� ������ ���� ��� ������ ��������
    int8                        menu_currentSubPage[Page::Number];          ///< ����� ������� ����������� ��� ������ ��������
    FrequencyMeter::BillingTime freq_billingTime;                           ///< ����� �����
    FrequencyMeter::AvePeriod   freq_avePeriod;                             ///< ����� ����������� �������� � ������ ��������� �������
    FreqTimeStamps              freq_timeStamps;                            ///< ����� �������
    FreqMeasure::E              freq_measure;                               ///< ����� ��������� �����������
    int16                       freq_level;                                 ///< ������� �������������
    int16                       freq_hysteresis;                            ///< �������� �����������
    bool                        sine_ManipulationEnabled[Chan::Number];     ///< true, ���� �������� ��������� ��������� �����
    uint8                       sine_ManipulationMode[Chan::Number];

#define FLAG_1      set.flag1
    uint            flag1;
#define BIT_PARITY        0   ///< Parity   - ���� �������� Parity
#define BIT_FREQ_INTERVAL 1   ///< Interval - �������� ������� ���������
#define BIT_CONSOLE       2   ///<          - ����� ���������� �������
#define BIT_BACK_BLACK    3   ///<          - ���� 1, �� ���� ���� - ������
#define BIT_TUNE_FULL     4   ///<          - ���� 1, �� ������� ��������� ���������� ���������� �� ����� ���������
#define BIT_DBG_MODE      5   ///<          - ���� 1, �� ������� ���������� ����� - ����������� ������� � �������

#define BIT_STATISTICS    7   ///<          - ���� 1, �� ���������� ����������
#define BIT_LANG          8   ///< Language - ��������� ����
#define BIT_CHAN_A        9   ///<          - ���, ���������� �� ���������� ����� A
#define BIT_CHAN_B        10  ///<          - ���, ���������� �� ���������� ����� B
#define BIT_CHANNEL       11  ///< Chan  - ������� ��������� �����
#define BIT_SIZE_BYTE     12  ///< SizeByte - ������ ����� ��� ����� �� USB
#define BIT_STOP_BIT      13  ///< StopBit  - ���������� ����-���
#define BIT_FREQ_RESIST   14  ///< FreqResist - ������������� ����� �����������
#define BIT_FREQ_COUPLE   15  ///< FreqCouple - ��������/�������� ���� �����������
#define BIT_FREQ_FILTR    16  ///< FreqFiltr   - ��� �����������

#define BIT_FREQ_TEST     18  ///< FreqTest    - ��������� ��������� ������
#define BIT_BIG_SYMBOLS   19  ///< ���� 1, �� ������� ��������� ���� ������������
#define BIT_SHOW_SENDS    20  ///< ���� 1, �� ����� ���������� ���������� ���������

    void Save();
    void Load(bool _default = false);

    Settings& operator=(const Settings &rhs);
};

#pragma pack(pop)

extern Settings set;


#ifdef WIN32
#pragma warning(pop)
#endif
