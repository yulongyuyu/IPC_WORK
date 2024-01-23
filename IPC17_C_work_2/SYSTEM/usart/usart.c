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
����֪��  ALL_ON����3����һ���� ALL_CLOSE�Ǻ��̵ƺͶ�ʱ����ֹͣ
���ڷ���&    $ ����ʵ�ֶ�Ӧ����
*/
char mod_table[16][30] = { {"error"},
{"LED_G_OFF"},{"LED_G_ON"},{"LED_R_OFF"},{"LED_R_ON"},{"LED_B_OFF"},{"LED_B_ON"},
{"ALL_ON"},{"WATER_LED_ON"},{"TRAFFIC_LED_ON"},{"ALL_CLOSE"} };

void my_uart_init(u32 BAUD_RATE)
{	

	/*************
	�ṹ��
	*************/
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	/***********
	����1��Ӧ���Ÿ���ӳ��
	***********/
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	/**********
	gpio��ʼ
	**********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   /*********
   USART1 ��ʼ������
   *********/
	USART_InitStructure.USART_BaudRate = BAUD_RATE;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
	/*********
	�ж�����
	*********/
	
	NVIC_InitStructure.NVIC_IRQChannel =  USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_Init(&NVIC_InitStructure);
	/********
	Enables or disables the specified USART interrupts���û����ָ����USART�ж�
	********/
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//�����ж���
	
    USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	
}
uint8_t   res2_data[3];  //��д��ת��������
int   rx_num_flag=0; //��¼�����Լ��ռ���



uint8_t   res1_data[30];  //��д ģʽ����
int   bag_start_flag=0;
int   bag_handle_flag=0;//ģʽ�����Ƿ� ���� �ı�־λ

/*************
�жϻص�����
*************/
void USART1_IRQHandler(void)
{	
		if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)//�����жϱ�־λ
		{
			static uint8_t   temp_data;//��дģʽ������ת
			static int   res_flag = 0;
			
			if(KEY_NUM == 1 && rx_num_flag == 0)//����Ϊ��ʱ   Ϊ����4 ����3λ�� ת����С��
			{
				 temp_data = USART_ReceiveData(USART1);
				 res2_data[res_flag] = temp_data;
				 res_flag++;
				if(res_flag > 2)
				{
					rx_num_flag=1;	//��ʾ�Ѿ��Ѽ���3������;
					LED_G_TURN;
					res_flag = 0 ;
				}
				
			}
			if(KEY_NUM == 0)//�жϰ���1  Ĭ��״̬Ϊ  1
			{		
				if(bag_handle_flag != 1 )//�ж����ݴ�����Ž��н�������
				{
					temp_data = USART_ReceiveData(USART1);
				}
					if(temp_data == '$' && bag_start_flag == 0)//�ж�Ϊ��ͷ
					{
						res_flag = 0;
						memset((char*)res1_data , 0, strlen((char*)res1_data) );
						bag_start_flag = 1;//�����������״̬
					}
					
					if(temp_data != '$' && bag_start_flag == 1 && temp_data != '&')//��������
					{
						res1_data[res_flag] = temp_data;
						res_flag++;
						
					}
					
					if(temp_data == '&'&& bag_start_flag == 1)//�ж�Ϊ��β
					{	
						res_flag = 0;		
						bag_start_flag = 0 ;//�˳���������״̬	
						bag_handle_flag = 1;//���ݴ���δ����					
					}
			}
//			USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//�����־λ
		}
}
/*
����С�� ���ݴ�����
*/
void hand2_res_data(float *NumDat,int *num)
{
	if(rx_num_flag == 1 && KEY_NUM ==1)
	{
		*NumDat = ((float)(res2_data[2]- '0' + (res2_data[1]- '0') *10 +(res2_data[0] -'0')*100))/100;
		*num += 1;
		rx_num_flag =0; // ���ݴ������
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
ģʽ�л����ݴ�����
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
					mode = i;	   //�洢ģʽ ���
					mod_flag = 1; //mod_flag��1 ��ʾ��ģʽ��ִ��
					break;
				}
			}
		if(mode != 0)//����λ������ģʽ�� �� ������Ϣ
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
		if(mode == 0) //���� ������Ϣ��ʾ û�� �ù���
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
		bag_handle_flag = 0; //���ݴ������ ��ִ��ģʽ��			
	}
	
	if(mod_flag == 1)//ִ��ģʽ
	{
		
	 if(mode == 1)
	 {
		 close_time();//ȷ���л�����ģʽʱ ������ʱ���ر�
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
	 if(mode == 7)//ȫ��
	 {
		close_time();
		LED_G_ON;
		LED_R_ON;
		LED_B_ON;
	 }
	 if(mode == 8)//������ˮ��
	 {
	LED_G_OFF;
	LED_R_OFF;
	LED_B_OFF;
    TIM_Cmd(TIM4,DISABLE);	
	TIM_Cmd(TIM3,ENABLE);
		
	 }
	 if(mode == 9)//�������̵�
	 {
	LED_G_OFF;
	LED_R_OFF;
	LED_B_OFF;	 
	TIM_Cmd(TIM3,DISABLE);
	TIM_Cmd(TIM4,ENABLE);	
	 }
	 if(mode == 10)//ȫ���ر�
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
	 if(mode == 10)//ģʽ10 ���� ȫ���ر�
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
		mod_flag = 0; //��ʾ ģʽ�л����
	}
}

void close_time(void)//�ر�������ʱ��
{
	TIM_Cmd(TIM3,DISABLE);
	TIM_Cmd(TIM4,DISABLE);
}
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);		//���ֽ�����д�����ݼĴ�����д���USART�Զ�����ʱ����
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//�ȴ��������
	/*�´�д�����ݼĴ������Զ����������ɱ�־λ���ʴ�ѭ�������������־λ*/
}
