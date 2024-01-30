#include "stm32f4xx.h"
#include "tim.h" 
#include "OLED.h"
#include "tm.h"
/*************
记得添加头文件和初始化
*************/
#define PSC 8400 // 预分频系数

  
void TIM3_IRQHandler(void) {
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {
        myClock->increment(myClock);
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}
int main(void) {
    TIM3_Init(10000, PSC); // 84000000/8400/10000
    OLED_Init();

    Clock myClockInstance = CreateClock();
    myClock = &myClockInstance; //不知道怎么改,发现如果不加全局变量的话定时器中的myClock->increment(myClock);怎么都会报错

    while (1) {
        myClock->show(myClock);
    }
}



