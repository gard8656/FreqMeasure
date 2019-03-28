#pragma once
#include "Display/Colors.h"
#include "Display/Display.h"
#include "Hardware/Controls.h"
#include "MenuItemsDefs.h"
#include "Hardware/Controls.h"
#include "Command.h"
#include "Utils/String.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Menu
 *  @{
 *  @defgroup MenuItems Menu Items
 *  @{
 */

typedef bool (*pFuncBKey)(Control);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ����� ����� ��� ���� ����� ��������� ����
#define COMMON_PART_MENU_ITEM                                                                                                                   \
    uint8           type;           /* ��� ����� */                                                                                             \
    int8            num;            /* ����� ��������� ��� Choice ��� ����� ��������� ��� Page*/                                                \
    bool            isPageSB;       /* ���� true, �� ��� �������� ����� ������, ����� type == Item_Page */                                      \
                                    /* ���� type == Item_Choice, �� ������� �������� �������� Choice - ����� ������ �� ���� ��������� */        \
    uint8           nameOrNumBit;   /* ��� �� ������������ NamePage, ���� type == Item_Page */                                                  \
                                    /* � ������, ���� type == Item_Choice,  ���������� ����� ���� */                                            \
    const PageBase  *keeper_;       /* ����� ��������, ������� �����������. ��� Page_Main = 0 */                                                \
    pFuncBV         funcOfActive;   /* ������� �� ������ ������� */                                                                             \
    const char      *titleHint[4]   /* �������� �������� �� ������� � ���������� ������. ����� ��������� ��� ������ ������ */

class PageBase;
class Page;

   
class Item
{
public:
    COMMON_PART_MENU_ITEM;
    /// ������ ���� ������� ����
    struct Type
    {
        enum E
        {
            None,
            Choice,             ///< ����� ������ - ��������� ������� ���� �� ���������� �������� ��������.
            Button,             ///< ������.
            Page,               ///< ��������.
            Governor,           ///< ��������� - ��������� ������� ����� ����� �������� �������� �� ������� ��������� ����������.
            GovernorColor,      ///< ��������� ������� ����.
            SmallButton,        ///< ������ ��� ������ ����� ������
            ChoiceParameter,
            Number
        } value;
        Type(E v) : value(v) {};
        operator uint8() const { return (uint8)value; };
        bool Is(E v) const     { return v == value;   };
    };
    /// \brief ���������� true, ���� ������� ���� control ������ (��������� �� �� ����� ������� ����. ��� �������, ��� ��������, ��� ������� 
    /// �������������� ������� ���� ����� Choice ��� Governor
    bool IsShade() const;
    /// ���������� true, ���� ������, ��������������� �������� ���� control, ��������� � ������� ���������
    bool IsPressed() const;
    /// ���������� true, ���� ������� ���� �� ������ control ������
    bool IsOpened() const;

    void Open(bool open);
    /// ���������� �������� ��������, ��� ��� �������� �� ������� �������
    String GetTitle() const;

    void Draw(bool opened, int x = -1, int y = -1) const;
    /// ������������ ������� ������. ���������� ��������� �� ����, ���� ��������� � �������� ��������� ����� �������, � 0 � ��������� ������
    void Press(Control control);

    Type GetType() const;

    /// ���������� ���������� ����� ������ ���� �� ��������
    int PositionOnPage();
    /// ���������� ������ ���� � �������� ����
    String FullPath();
    /// ������� ��������� � �������� ����� ������. ���������� ������ ���������� ����������� ������
    int DrawHint(int x, int y, int width, Color color = Color::NUMBER) const;

    Page *Keeper() { return (Page *)keeper_; };

    bool IsActive() const { return funcOfActive(); };

    static const int WIDTH = 69;

    static const int HEIGHT = 55;

    struct Title
    {
        static const int HEIGHT = 12;

    };
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Page ///

/// ��������� �������� ����.
class PageBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// \brief ����� ��������� �� ������ ���� �������� (� ������� ��������) ��� �������� ����� ������  ����� �������� 6 ���������� �� SButton : 
    /// 0 - B_Menu, 1...5 - B_F1...B_F5
    Item **items;
    /// ����� ���������� ��� ������� �� �������� ��������
    pFuncVV funcOnPress;
    /// ����� ���������� ����� ��������� ������
    pFuncVV funcOnDraw;

    pFuncBKey funcOnKey;

    bool CurrentItemIsOpened() const;
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define SMALL_BUTTON_FROM_PAGE(page, numButton)     ((SButton *)((Page *)page)->items[numButton])

class Page : public Item
{
public:

    enum E
    {
         NoPage,
         Settings,
         Service,
         Debug,
         FrequencyCounter,
         USB,
         SB_Input,
         Registers,
         Main,
         Settings_Load,
         Settings_CalibrationA,
         Settings_CalibrationB,
         Number
    };
    

    /// ���������� true, ���� ������� ������� �������� ������
    bool CurrentItemIsOpened() const;
    /// \brief ����� ��������� �� ������ ���� �������� (� ������� ��������) ��� �������� ����� ������  ����� �������� 6 ���������� �� SButton : 
    /// 0 - B_Menu,  1...5 - B_F1...B_F5
    const Item * const *items;   
    /// ����� ���������� ��� ������� �� �������� ��������
    pFuncVV  funcOnPress;
    /// ����� ���������� ����� ��������� ������
    pFuncVV  funcOnDraw;
    /// � �������� ����� ������ ���������� ��� �������� ����� ���������
    pFuncBKey funcOnKey;
    /// D��������� ����� ���������� � �������� �� ������ page
    int NumSubPages() const;
    /// ���������� ���������� ��������� � �������� �� ������ page
    int NumItems() const;
    /// ���������� ����� ������� �����������
    int CurrentSubPage() const;
    /// ������ �������� ��������
    void DrawOpened() const;
    /// ������ �������� ��������
    void DrawClosed(int x, int y) const;

    void SetCurrentSubPage(int pos);
    /// ������������� ������� ��������� ������ ����
    void SetPosActItem(int pos);
    /// ���������� ����� �������� ����, ���������������� ������� �������������� �������
    Item *GetItem(Control key) const;
    /// ���������� ������� �������� �������� ������� page
    int8 PosCurrentItem() const;

    void ChangeSubPage(int delta);
    /// ������������ ������� ������. ���������� ��������� �� ����, ���� ��������� � �������� ��������� ����� �������, � 0 � ��������� ������
    bool Press(Control control);

    struct Title
    {
        static const int HEIGHT = 18;
    };
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Button ///

/// ��������� ������.
class ButtonBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// �������, ������� ���������� ��� ������� �� ������.
    pFuncVV     funcOnPress;
    /// ������� ����� ���������� �� ����� ��������� ������.
    pFuncVII    funcForDraw;
};

class Button : public Item
{
public:
    /// �������, ������� ���������� ��� ������� �� ������.
    pFuncVV     funcOnPress;
    /// ������� ����� ���������� �� ����� ��������� ������.
    pFuncVII    funcForDraw;
    /// ������������ ������� ������. ���������� ����, ������ ��� �� ����� ���������� � �������� ���������.
    Item *Press(Control::Action action);

    void Draw(int x, int y);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// SButton ///

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4623 4626 5027)
#endif
struct StructHelpSmallButton
{
    /// ��������� �� ������� ��������� ����������� �������� ������
    pFuncVII    funcDrawUGO;
    /// ������� � ������� �����������.
    pString     helpUGO[2];
};
#ifdef WIN32
#pragma warning(pop)
#endif


/// ��������� ������ ��� ��������������� ������ ����.
class SButtonBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// ��� ������� ��������� ��� ��������� ������� ������.
    pFuncVV                         funcOnPress;
    /// ��� ������� ���������� ��� ��������� ������ � ����� � ������������ x, y.
    pFuncVII                        funcForDraw;

    const StructHelpSmallButton    *hintUGO;

    int                             numHints;
};


class SButton : public Item
{
public:
    /// ��� ������� ��������� ��� ��������� ������� ������.
    pFuncVV                         funcOnPress;
    /// ��� ������� ���������� ��� ��������� ������ � ����� � ������������ x, y.
    pFuncVII                        funcForDraw;

    const StructHelpSmallButton    *hintUGO; 

    int                             numHints;
    /// ������������ ������� ������. ���������� 0, ������ ��� �� ����� ���������� � �������� ���������
    Item *Press(Control::Action action);

    void Draw(int x, int y);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Governor ///

/// ��������� ���������.
class GovernorBase
{
public:
    COMMON_PART_MENU_ITEM;
    int16   minValue;
    int16   maxValue;
    int16  *cell;
    pFuncVV funcOfChanged;
    pFuncVV funcBeforeDraw;
    pFuncVB funcPress;
};

class Governor : public Item
{
public:
    /// ���������� ��������, ������� ����� ��������� ���������.
    int16   minValue;
    /// ������������ ��������.
    int16   maxValue;

    int16  *cell;
    /// �������, ������� ����� �������� ����� ����, ��� �������� ���������� ����������.
    pFuncVV funcOfChanged;
    /// �������, ������� ���������� ����� ����������
    pFuncVV funcBeforeDraw;
    /// ������� ���������� ��� ������� �� item. �������� bool == true ��������, ��� item ��������������� ��������
    pFuncVB funcPress;
    /// ��������� �������� �������� ���������� ��� ���������� �������� ���� ���� Governor (� ����������� �� ����� delta).
    void StartChange(int detla);
    /// ���������� ��������� ������� ��������, ������� ����� ������� governor.
    int16 NextValue() const;
    /// ���������� ��������� ������� ��������, ������� ����� ������� governor.
    int16 PrevValue() const;
    /// ������������ ��������� ���� ��������.
    float Step();
    /// �������� �������� � ������� ������� ��� ��������� ��������.
    void ChangeValue(int delta);
    /// ��� �������� �������� ������������ ������ �� ��������� �������.
    void NextPosition();
    /// ���������� ����� ��������� � ���� ��� ����� �������� governor. ������� �� ������������� ��������, ������� ����� ��������� governor.
    int  NumDigits() const;
    /// ���������� ����������� ����������, ��������������� ��� �������� ���������
    static char GetSymbol(int value);

    void Draw(int x, int y) const;

    void DrawValue(int x, int y) const;
    /// ��������� �����������
    void Press(Control control);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Choice ///
class ChoiceBase
{
public:
    COMMON_PART_MENU_ITEM;

    int8    *cell;
    /// �������� ������ �� ������� � ���������� ������.
    pString *names;
    /// ��������� ��� ������� �������� �� ������� �����
    pString *hintsRu;
    /// ��������� ��� ������� �������� �� ���������� �����
    pString *hintsEn;
    /// ������� ������ ���������� ����� ��������� �������� ��������.
    pFuncVB	 funcOnChanged;
    /// ������� ���������� ����� ��������� ��������. 
    pFuncVII funcForDraw;

    int8 CurrentIndex() const;
};

class Choice : public Item
{
public:

    int8 * cell;
    /// �������� ������ �� ������� � ���������� ������.
    pString *names;
    /// ��������� ��� ������� �������� �� ������� �����
    pString *hintsRu;
    /// ��������� ��� ������� �������� �� ���������� �����
    pString *hintsEn;
    /// ������� ������ ���������� ����� ��������� �������� ��������.
    pFuncVB	 funcOnChanged;
    /// ������� ���������� ����� ��������� ��������. 
    pFuncVII funcForDraw;

    void StartChange(int delta) const;
    /// ������������ ��������� ���� ��������.
    float Step();
    /// ���������� ���������� ��������� ������ � �������� �� ������ choice
    int8 NumSubItems() const;

    void Draw(bool opened, int x = -1, int y = -1);
    /// ���������� ��� �������� �������� ������ �������� choice, ��� ��� �������� � �������� ���� ���������
    const char *NameCurrentSubItem();
    /// ���������� ��� ���������� �������� ������ �������� choice, ��� ��� �������� � �������� ���� ���������
    String NameNextSubItem();
    /// ���������� ������ ����������
    int GetHeightOpened() const;

    const char *NamePrevSubItem();
    /// ���������� ��� �������� ������ �������� choice � ������� i ��� ��� �������� � �������� ���� ���������
    String NameSubItem(int i) const;
    /// ���������� ��������� �� ����, ���� ��������� � �������� ���������, � 0, ���� � ��������
    Item *Press(Control control);

    int8 CurrentIndex();
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///
class ChoiceParameterBase
{
public:
    COMMON_PART_MENU_ITEM;
    pFuncVV     funcOnPress;
    Form  *form;
};


class ChoiceParameter : public Item
{
public:
    pFuncVV     funcOnPress;
    Form  *form;
    /// ������������ ������� ������. ���������� ��������� �� ����, ���� ��������� � �������� ��������� � 0 � ���������.
    Item *Press(Control::Action action);

    pString NameSubItem(int num) const;

    pString NameCurrentSubItem() const;

    void Draw(bool opened, int x, int y);
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Formula ////

/// ��������� ������� ���� ��� ��������� ������������� � ������ �������������� �������
#define FIELD_SIGN_MEMBER_1_ADD 0
#define FIELD_SIGN_MEMBER_1_MUL 1
#define FIELD_SIGN_MEMBER_2_ADD 2
#define FIELD_SIGN_MEMBER_2_MUL 3
#define POS_SIGN_MEMBER_1       0
#define POS_KOEFF_MEMBER_1      1
#define POS_SIGN_MEMBER_2       2
#define POS_KOEFF_MEMBER_2      3

class FormulaBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// ����� ������, ��� �������� Function, �� ������� ������ ���� ��������
    int8 *function;
    /// ����� ������������ ��� ������ ����� ��� ��������
    int8 *koeff1add;
    /// ����� ������������ ��� ������ ����� ��� ��������
    int8 *koeff2add;
    /// ����� ������������ ��� ������ ����� ��� ���������
    int8 *koeff1mul;
    /// ����� ������������ ��� ������ ����� ��� ���������
    int8 *koeff2mul;
    /// ������� ������ : 0 - ���� ������� �����, 1 - ����������� ������� �����, 2 - ���� ������� �����, 3 - ����������� ������� �����
    int8 *curDigit;
    /// ��� ������� ���������� ����� ��������� ��������� �������� ����������.
    pFuncVV funcOfChanged;
};

class Formula : public Item
{
public:
    /// ����� ������, ��� �������� Function, �� ������� ������ ���� ��������
    int8 *function;
    /// ����� ������������ ��� ������ ����� ��� ��������
    int8 *koeff1add;
    /// ����� ������������ ��� ������ ����� ��� ��������
    int8 *koeff2add;
    /// ����� ������������ ��� ������ ����� ��� ���������
    int8 *koeff1mul;
    /// ����� ������������ ��� ������ ����� ��� ���������
    int8 *koeff2mul;
    /// ������� ������ : 0 - ���� ������� �����, 1 - ����������� ������� �����, 2 - ���� ������� �����, 3 - ����������� ������� �����
    int8 *curDigit;
    /// ��� ������� ���������� ����� ��������� ��������� �������� ����������.
    pFuncVV funcOfChanged;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// GovernorColor ///
class ColorType;

class GovernorColorBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// ��������� ��� �������� �����.
    ColorType *ct;
    /// ��� ������� ����� �������� ����� ��������� �������� ��������.
    pFuncVV funcOnChanged;
};

class GovernorColor : public Item
{
public:
    /// ��������� ��� �������� �����.
    ColorType *ct;
    /// ��� ������� ����� �������� ����� ��������� �������� ��������.
    pFuncVV funcOnChanged;
    /// �������� ������� ����� � governor.
    void ChangeValue(int delta);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Time ///

#define iEXIT   0
#define iDAY    1
#define iMONTH  2
#define iYEAR   3
#define iHOURS  4
#define iMIN    5
#define iSEC    6
#define iSET    7

class TimeBase
{
public:
    COMMON_PART_MENU_ITEM;
    /// ������� ���� ���������. 0 - �����, 1 - ���, 2 - ���, 3 - ����, 4 - ����, 5 - �����, 6 - ���, 7 - ����������.
    int8 *curField;

    int8 *hours;

    int8 *minutes;

    int8 *seconds;

    int8 *month;

    int8 *day;

    int8 *year;
};

#define CHOICE_RUN_FUNC_CHANGED(c, val)     \
    if(c->funcOnChanged)                    \
    {                                       \
        c->funcOnChanged(val);              \
    }


typedef void * pVOID;
#define MAX_NUM_ITEMS_IN_PAGE 15
typedef pVOID arrayItems[MAX_NUM_ITEMS_IN_PAGE];


/** @}  @}
 */
