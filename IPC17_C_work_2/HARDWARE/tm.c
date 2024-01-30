#include "tm.h"

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
Clock CreateClock(void){
    Clock clock;
    clock.sec = 0;
    clock.min = 0;
    clock.hour = 0;
    clock.show = OLED_ShowTime;
    clock.increment = IncrementTime;
    return clock;
}
