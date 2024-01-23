#include "sys.h"
#include "usart.h"	
#include "led.h"
#include <stdio.h>
#include <stdarg.h>
#include "string.h"
#include "tim.h" 
#include "key.h"
/*
{"LED_G_OFF"},{"LED_G_ON"},{"LED_R_OFF"},{"LED_R_ON"},{"LED_B_OFF"},{"LED_B_ON"},
{"ALL_ON"},{"WATER_LED_ON"},{"TRAFFIC_LED_ON"},{"ALL_CLOSE"} };
见名知意  ALL_ON是让3个灯一起亮 ALL_CLOSE是红绿灯和定时器都停止
串口发送&    $ 可以实现对应功能
*/
char mod_table[16][30] = { {"error"},
{"LED_G_OFF"},{"LED_G_ON"},{"LED_R_OFF"},{"LED_R_ON"},{"LED_B_OFF"},{"LED_B_ON"},
{"ALL_ON"},{"WATER_LED_ON"},{"TRAFFIC_LED_ON"},{"ALL_CLOSE"} };

void my_uart_init(u32 BAUD_RATE)
{	

	/*************
	结构体
	*************/
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
 
	/***********
	串口1对应引脚复用映射
	***********/
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	/**********
	gpio初始
	**********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

   /*********
   USART1 初始化设置
   *********/
	USART_InitStructure.USART_BaudRate = BAUD_RATE;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
	/*********
	中断配置
	*********/
	
	NVIC_InitStructure.NVIC_IRQChannel =  USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_Init(&NVIC_InitStructure);
	/********
	Enables or disables the specified USART interrupts启用或禁用指定的USART中断
	********/
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启中断线
	
    USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	
}
uint8_t   res2_data[3];  //存写待转换的数据
int   rx_num_flag=0; //记录数据以及收集满



uint8_t   res1_data[30];  //存写 模式功能
int   bag_start_flag=0;
int   bag_handle_flag=0;//模式数据是否 处理 的标志位

/*************
中断回调函数
*************/
void USART1_IRQHandler(void)
{	
		if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)//接收中断标志位
		{
			static uint8_t   temp_data;//存写模式代码中转
			static int   res_flag = 0;
			
			if(KEY_NUM == 1 && rx_num_flag == 0)//按键为二时   为功能4 接收3位数 转换成小数
			{
				 temp_data = USART_ReceiveData(USART1);
				 res2_data[res_flag] = temp_data;
				 res_flag++;
				if(res_flag > 2)
				{
					rx_num_flag=1;	//表示已经搜集完3个数据;
					LED_G_TURN;
					res_flag = 0 ;
				}
				
			}
			if(KEY_NUM == 0)//判断按键1  默认状态为  1
			{		
				if(bag_handle_flag != 1 )//判断数据处理完才进行接收数据
				{
					temp_data = USART_ReceiveData(USART1);
				}
					if(temp_data == '$' && bag_start_flag == 0)//判断为包头
					{
						res_flag = 0;
						memset((char*)res1_data , 0, strlen((char*)res1_data) );
						bag_start_flag = 1;//进入接收数据状态
					}
					
					if(temp_data != '$' && bag_start_flag == 1 && temp_data != '&')//接收数据
					{
						res1_data[res_flag] = temp_data;
						res_flag++;
						
					}
					
					if(temp_data == '&'&& bag_start_flag == 1)//判断为包尾
					{	
						res_flag = 0;		
						bag_start_flag = 0 ;//退出接收数据状态	
						bag_handle_flag = 1;//数据处理未处理					
					}
			}
//			USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//清除标志位
		}
}
/*
接收小数 数据处理函数
*/
void hand2_res_data(float *NumDat,int *num)
{
	if(rx_num_flag == 1 && KEY_NUM ==1)
	{
		*NumDat = ((float)(res2_data[2]- '0' + (res2_data[1]- '0') *10 +(res2_data[0] -'0')*100))/100;
		*num += 1;
		rx_num_flag =0; // 数据处理完毕
		Serial_SendByte('N');	
		Serial_SendByte('U');
		Serial_SendByte('M');
		Serial_SendByte('_');
		Serial_SendByte('O');	
		Serial_SendByte('K');
		Serial_SendByte('_');
		Serial_SendByte(0x0d);
		Serial_SendByte(0x0a);

	}
	
}

/*
模式切换数据处理函数
*/
void handl_res_data(uint8_t *BagDat)
{   
	static int mod_flag = 0;//
	int mode = 0;
	if(bag_handle_flag == 1)
	{	 
		for( int i=0; i<=10;i++ )
			{
				if( strcmp(mod_table[i],(char*)BagDat) == 0)
				{
					mode = i;	   //存储模式 序号
					mod_flag = 1; //mod_flag置1 表示有模式待执行
					break;
				}
			}
		if(mode != 0)//向上位机发送模式几 或 错误信息
		{

		Serial_SendByte('_');	
		Serial_SendByte('M');
		Serial_SendByte('O');
		Serial_SendByte('D');
		Serial_SendByte('_');	
		Serial_SendByte( mode+'0');
		Serial_SendByte(' ');
		Serial_SendByte(0x0d);
		Serial_SendByte(0x0a);	
						
		}
		if(mode == 0) //发送 错误信息表示 没有 该功能
		{
		Serial_SendByte('e');
		Serial_SendByte('r');
		Serial_SendByte('r');	
		Serial_SendByte('o');
		Serial_SendByte('r');		
		Serial_SendByte('_');
		Serial_SendByte( mode+'0');
		Serial_SendByte(' ');
		Serial_SendByte(0x0d);
		Serial_SendByte(0x0a);
		mod_flag = 0 ;	
		}		
		bag_handle_flag = 0; //数据处理完毕 该执行模式了			
	}
	
	if(mod_flag == 1)//执行模式
	{
		
	 if(mode == 1)
	 {
		 close_time();//确保切换到该模式时 两个定时器关闭
		 LED_G_OFF;
	 }
	 if(mode == 2)
	{
		close_time();
		LED_G_ON;
	 }
	 if(mode == 3)
	 { 
		close_time();
		LED_R_OFF;
	 }
	 if(mode == 4)
	 {
		 close_time();
		 LED_R_ON;
	 }
	 if(mode == 5)
	 {
		 close_time();
		 LED_B_OFF;
	 }
	 if(mode == 6)
	 {
		 close_time();
		 LED_B_ON ;
	 }
	 if(mode == 7)//全亮
	 {
		close_time();
		LED_G_ON;
		LED_R_ON;
		LED_B_ON;
	 }
	 if(mode == 8)//开启流水灯
	 {
	LED_G_OFF;
	LED_R_OFF;
	LED_B_OFF;
    TIM_Cmd(TIM4,DISABLE);	
	TIM_Cmd(TIM3,ENABLE);
		
	 }
	 if(mode == 9)//开启红绿灯
	 {
	LED_G_OFF;
	LED_R_OFF;
	LED_B_OFF;	 
	TIM_Cmd(TIM3,DISABLE);
	TIM_Cmd(TIM4,ENABLE);	
	 }
	 if(mode == 10)//全部关闭
	 {
	LED_G_OFF;
	LED_R_OFF;
	LED_B_OFF;	 
	TIM_Cmd(TIM3,DISABLE);
	TIM_Cmd(TIM4,DISABLE);
	 }
	 if(mode != 10)
	 {
		Serial_SendByte('_');	
		Serial_SendByte('M');
		Serial_SendByte('O');
		Serial_SendByte('D');
		Serial_SendByte('_');	
		Serial_SendByte( mode+'0');
	    Serial_SendByte('_');
		Serial_SendByte('O');
		Serial_SendByte('K');
		Serial_SendByte('_');
		Serial_SendByte(' ');
	 }
	 if(mode == 10)//模式10 发送 全部关闭
	 {
			
		Serial_SendByte('A');
		Serial_SendByte('L');
		Serial_SendByte('L');
		Serial_SendByte('_');	
		Serial_SendByte('C');
	    Serial_SendByte('L');
		Serial_SendByte('O');
		Serial_SendByte('S');
		Serial_SendByte('E');

	 }
		Serial_SendByte(0x0d);
		Serial_SendByte(0x0a);
		mod_flag = 0; //表示 模式切换完毕
	}
}

void close_time(void)//关闭两个定时器
{
	TIM_Cmd(TIM3,DISABLE);
	TIM_Cmd(TIM4,DISABLE);
}
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);		//将字节数据写入数据寄存器，写入后USART自动生成时序波形
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//等待发送完成
	/*下次写入数据寄存器会自动清除发送完成标志位，故此循环后，无需清除标志位*/
}
