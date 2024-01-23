#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

extern uint8_t   res1_data[30];
extern int   bag_handle_flag;

extern uint8_t   res2_data[3];  //存写待转换的数据
extern int   rx_num_flag; //记录数据是否收集满

void Serial_SendByte(uint8_t Byte);//发送一个字节
void my_uart_init(u32 BAUD_RATE); //初始化

void handl_res_data(uint8_t *BagDat);
void hand2_res_data(float *NumDat,int *num);

void close_time(void);	
#endif


