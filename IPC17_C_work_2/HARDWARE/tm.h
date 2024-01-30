#ifndef _TM_H
#define _TM_H
#include "stm32f4xx.h"
#include "OLED.h"

typedef struct Clock Clock;

typedef struct Clock {
    int sec;
    int min;
    int hour;
    void (*show)(Clock *);
    void (*increment)(Clock *);
} Clock;

Clock CreateClock(void);
extern Clock *myClock;//将全局变量引用到引用文件

#endif
