#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void Error_Handler(void);

#ifdef __cplusplus
}
#endif


class HAL
{
public:
    static void Init();
};
