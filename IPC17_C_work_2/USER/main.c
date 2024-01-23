#include "stm32f4xx.h"
#include "tim.h" 
#include "delay.h"
#include "led.h"
#include "bee.h"
#include "key.h"
#include "usart.h"
#include "string.h"
#include "OLED.h"
#include "IIC1.h"
/*************
记得添加头文件和初始化
*************/
int psc=8400;//预分频系数
typedef struct tm
{
	int sec ;
	int min ;
	int hour ;
	
}tm;
tm mytime = {.sec = 0, .min = 0, .hour = 0};
void OLED_Show( tm  *pthis)
{
	OLED_ShowNum(1,1,pthis->hour);
	OLED_ShowNum(2,2,pthis->min);
	OLED_ShowNum(3,3,pthis->sec);
}
void display_sec(tm *pthis)
{
	if (pthis->sec ==60)
	{
		pthis->min++;
		pthis->sec = 0;
	}
	if (pthis->min ==60)
	{
		pthis->hour ++;
		pthis->min =0;
	}
}
void tm_sec(tm *pthis)
{
	pthis->sec++;
}	
	


int main(void)
{	
	
	led_init();
	TIM3_Init(10000,psc);//84000000/8400/10000
	OLED_Init();
	
  while(1){
	  display_sec(&mytime);
	  OLED_Show(&mytime);
   }
 }
/******
定时器中断回调函数
******/
 void TIM3_IRQHandler(void)//秒中断一次
 {
	 if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
		{
		tm_sec(&mytime);
	 		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		}
 }
 
 
 
 
 
  void TIM4_IRQHandler(void)
 {		 
	 if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)
		 {
		
			TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
		 }
 }

 
