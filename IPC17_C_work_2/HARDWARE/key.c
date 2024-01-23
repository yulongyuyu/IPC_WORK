#include "led.h" 
#include "delay.h"
int keynum=0;
/*
@brief	key初始化 
*/
void key_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 ;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

}

/*
@brief	判断按键按下 
*/
int KEY_NUM = 0;
void key_get_num( int *KEY_NUM)
{
	 
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0)
			{
				delay_ms(20);
				while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0);
				delay_ms(20);
				*KEY_NUM =0;//
			}
		else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4) == 0)
				{
					delay_ms(20);
					while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4) == 0);
					delay_ms(20);
					*KEY_NUM =1;
					LED_G_ON;
				}
	
}


