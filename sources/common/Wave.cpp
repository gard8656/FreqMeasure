#include "CommonTypes.h"
#include "defines.h"
#include "Wave.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pString Form::Name(Language::E lang) const
{
    DEF_STRUCT(StructName, pString) names[Form::Number][2] =
    {
        {"�����",        "Sine"},
        {"����+",        "Ramp+"},
        {"����-",        "Ramp-"},
        {"�����������",  "Triangle"},
        {"������",       "Meander"},
        {"�������",      "Impulse"},
        {"�����",        "Message"},
        {"������������", "Hand"}
    };

    return names[value][lang].val;
}


