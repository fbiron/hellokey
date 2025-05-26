#ifndef KEY_H
#define KEY_H

#ifdef __cplusplus
extern "C" {
#endif
//以下是正式的代码

#include "stm32f1xx_hal.h"
#include "main.h"

//状态枚举
typedef enum
{
    LED_STATE_OFF,
    LED_STATE_FLASH_0,
    LED_STATE_FLASH_01
}LedStateTypeDef;

//LED控制结构体，用于封装状态，避免使用全局变量，方便控制，在函数中传递。
typedef struct{
    LedStateTypeDef state;
    uint32_t last_tick;
}LedCtrlTypeDef;

uint8_t Key_Scan(GPIO_TypeDef *port,uint16_t pin,LedCtrlTypeDef *led_ctrl);
void LED_Update(LedCtrlTypeDef *led_ctrl);
void Key_Process(LedCtrlTypeDef *led_ctrl);







//以上是正式的代码


#ifdef __cplusplus
}
#endif

#endif //KEY_H
