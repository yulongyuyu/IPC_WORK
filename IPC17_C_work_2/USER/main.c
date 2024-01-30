#include "stm32f4xx.h"
#include "tim.h" 
#include "OLED.h"

/*************
记得添加头文件和初始化
*************/
#define PSC 8400 // 预分频系数

typedef struct Clock Clock;

typedef struct Clock {
    int sec;
    int min;
    int hour;
    void (*show)(Clock *);
    void (*increment)(Clock *);
} Clock;

Clock *myClock;

/*
在oled上显示时间
*/
void OLED_ShowTime(Clock *time) {
    OLED_ShowNum(1, 1, time->hour);
    OLED_ShowNum(2, 2, time->min);
    OLED_ShowNum(3, 3, time->sec);
}
/*
 秒进分,分进时.
*/
void IncrementTime(Clock *time) {
    time->sec++;
    if (time->sec == 60) {
        time->min++;
        time->sec = 0;
    }
    if (time->min == 60) {
        time->hour++;
        time->min = 0;
    }
}
/*
创建对象
*/
Clock CreateClock(){
    Clock clock;
    clock.sec = 0;
    clock.min = 0;
    clock.hour = 0;
    clock.show = OLED_ShowTime;
    clock.increment = IncrementTime;
    return clock;
}
  
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
    myClock = &myClockInstance; //不知道怎么改如果 不加全局变量的话定时器中的myClock->increment(myClock);怎么都会报错

    while (1) {
        myClock->show(myClock);
    }
}



