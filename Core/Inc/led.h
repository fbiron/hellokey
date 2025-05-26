// 这是常用的一种防止头文件重复包含的方式
// 头文件保护符号
#ifndef LED_H
#define LED_H

// 这是一种方便C++代码与C代码互操作的方式，增加extern "C"来避免C++编译器对函数名进行重命名。目的是告诉C++编译器
// 使用C语言的链接方式来处理这些函数名，从而使得C++代码可以调用这些C语言编写的函数。
#ifdef __cplusplus
extern "C" {
#endif

// 头文件包含,即使这里已经在main.h中包含了stm32f1xx_hal.h，还是要在这里再次包含，目的是为了让这个头文件独立，提高可移植性，健壮性。好的编程习惯都是要实现头文件的自包含。避免隐形依赖。
#include "stm32f1xx_hal.h"

// 宏定义：为什么要做宏定义 ，因为可以方便修改程序，或代码移值，或使用条件编译。
//这是定义了具体的引脚
#define LED_PIN     GPIO_PIN_13
//这是定义了芯片的端口的基地址，可以简单理解为端口。STM32 的 GPIO 被组织成多个端口（Port），如 GPIOA、GPIOB、GPIOC 等，每个端口包含 16 个引脚（Pin0~Pin15）。
//每个端口在 STM32 的内存映射中占据一段连续的地址空间，这段空间的起始地址就是基地址。例如：
//GPIOA 的基地址可能是 0x48000000
//GPIOB 的基地址可能是 0x48000400
//不同型号的 STM32 基地址可能不同，具体参考芯片的数据手册。
#define LED_PORT    GPIOC

//以上的定义端口与具体引脚的，可以不写，因为cubemx中已经配置了，所以以上是重复的。



// 函数声明
//void LED_Init(void);
void LED0_on(void);
void LED0_off(void);
void LED1_on(void);
void LED1_off(void);

#ifdef __cplusplus
}
#endif

#endif // LED_H