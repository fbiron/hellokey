#include "key.h"
#include "stm32f1xx_hal.h"
#include "main.h"


// 模块内静态变量，非全局。
// static LedCtrlTypeDef g_led_ctrl = {
//     .state = LED_STATE_OFF,
//     .last_tick = 0
// };
//copliot建议也是不在函数内定义static变量，会有风险。

uint8_t Key_Scan(GPIO_TypeDef *port,uint16_t pin,LedCtrlTypeDef *led_ctrl){
    if(HAL_GPIO_ReadPin(port,pin) == GPIO_PIN_RESET){
        HAL_Delay(20);
        if (HAL_GPIO_ReadPin(port,pin) == GPIO_PIN_RESET)
        {
            while(HAL_GPIO_ReadPin(port,pin) == GPIO_PIN_RESET);
            if (port == KEY0_GPIO_Port && pin == KEY0_Pin)
            {
                if (led_ctrl->state == LED_STATE_FLASH_0)
                {
                    led_ctrl->state = LED_STATE_OFF;
                }else
                {
                    led_ctrl->state = LED_STATE_FLASH_0;
                }
                
                
            }else if (port == KEY1_GPIO_Port && pin == KEY1_Pin){
                   if (led_ctrl->state == LED_STATE_FLASH_0){
                        led_ctrl->state = LED_STATE_OFF;
                   } else{
                    led_ctrl->state = LED_STATE_FLASH_01;
                    }
            }else if(port == KEY2_GPIO_Port && pin == KEY2_Pin){
                led_ctrl->state = LED_STATE_OFF;
            }

            return 1; // 按键有效
        }
        
    }
    return 0 ; // 按键无效
}

// LED 状态更新函数
void LED_Update(LedCtrlTypeDef *led_ctrl) {
    uint32_t current_tick = HAL_GetTick();

    switch (led_ctrl->state) {
        case LED_STATE_FLASH_0:
            if (current_tick - led_ctrl->last_tick >= 500) {
                HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
                led_ctrl->last_tick = current_tick;
            }
            break;
        case LED_STATE_FLASH_01:
            if (current_tick - led_ctrl->last_tick >= 500) {
                HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
                HAL_GPIO_TogglePin(LED1_GPIO_Port, LED0_Pin);
                led_ctrl->last_tick = current_tick;
            }
            break;
        case LED_STATE_OFF:
            HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED1_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
            break;
    }
}

// 需要将 LedCtrlTypeDef 结构体作为参数传递进来
void Key_Process(LedCtrlTypeDef *led_ctrl) {
    Key_Scan(KEY0_GPIO_Port, KEY0_Pin, led_ctrl);
    Key_Scan(KEY1_GPIO_Port, KEY1_Pin, led_ctrl);
    Key_Scan(KEY2_GPIO_Port, KEY2_Pin, led_ctrl);
    LED_Update(led_ctrl);
}
