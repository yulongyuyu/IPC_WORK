#ifndef _KEY_H
#define _KEY_H
#include "delay.h"

int extern KEY_NUM ;

void key_get_num( int *KEY_NUM);
void key_init(void);
void key_control_bee(void);

#include "stm32f4xx.h"
#endif
