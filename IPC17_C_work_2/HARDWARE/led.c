#include "led.h" 


/*
@brief	led³õÊ¼»¯  ÈÃºìµÆ ÂÌµÆ´¦ÓÚ OFF×´Ì¬ 
*/
void led_init(void)
{
	//RCC->AHB1ENR |=  RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOC;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 ;

	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	LED_R_OFF;
	LED_G_OFF;
	LED_B_OFF;
}

