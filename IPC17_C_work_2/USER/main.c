#include "stm32f4xx.h"
#include "tim.h" 
#include "OLED.h"

/*************
记得添加头文件和初始化
*************/
#define PSC 8400 // 预分频系数

typedef struct {
    int sec;
    int min;
    int hour;
} TimeStruct;

typedef struct {
    TimeStruct* time;
    void (*show)(TimeStruct*);
    void (*increment)(TimeStruct*);
} Clock;

TimeStruct mytime = {.sec = 0, .min = 0, .hour = 0};
Clock myClock; 

void OLED_ShowTime(TimeStruct* time) {
    OLED_ShowNum(1, 1, time->hour);
    OLED_ShowNum(2, 2, time->min);
    OLED_ShowNum(3, 3, time->sec);
}

void IncrementTime(TimeStruct* time) {
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

Clock CreateClock(TimeStruct* time) {
    Clock clock;
    clock.time = time;
    clock.show = OLED_ShowTime;
    clock.increment = IncrementTime;
    return clock;
}


int main(void) {
    led_init();
    TIM3_Init(10000, PSC); // 84000000/8400/10000
    OLED_Init();

    myClock = CreateClock(&mytime);

    while (1) {
		myClock.show(&mytime);
    }
}

void TIM3_IRQHandler(void) {
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {
		
        myClock.increment(&mytime);

        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}
 
