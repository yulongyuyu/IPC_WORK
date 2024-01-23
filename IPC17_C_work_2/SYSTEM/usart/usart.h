#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

extern uint8_t   res1_data[30];
extern int   bag_handle_flag;

extern uint8_t   res2_data[3];  //��д��ת��������
extern int   rx_num_flag; //��¼�����Ƿ��ռ���

void Serial_SendByte(uint8_t Byte);//����һ���ֽ�
void my_uart_init(u32 BAUD_RATE); //��ʼ��

void handl_res_data(uint8_t *BagDat);
void hand2_res_data(float *NumDat,int *num);

void close_time(void);	
#endif


