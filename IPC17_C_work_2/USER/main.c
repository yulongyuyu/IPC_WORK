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
<<<<<<< HEAD
记得添加头文件和初始化
*************/
int psc=8400;//预分频系数
=======
璁板緱娣诲姞澶存枃浠跺拰鍒濆鍖�
*************/
int psc=8400;//棰勫垎棰戠郴鏁�
>>>>>>> 76e7c77 (ipcwork_1_23)
typedef struct tm
{
	int sec ;
	int min ;
	int hour ;
	
}tm;
tm mytime = {.sec = 0, .min = 0, .hour = 0};
<<<<<<< HEAD
void OLED_Show( tm  *pthis)
{
	OLED_ShowNum(1,1,pthis->hour);
	OLED_ShowNum(2,2,pthis->min);
	OLED_ShowNum(3,3,pthis->sec);
}
void display_sec(tm *pthis)
=======

/* 
	瀵硅鏁拌繘琛屽鐞�
	鍙傛暟  tm *pthis 鍦板潃
*/
void handle_sec(tm *pthis)
>>>>>>> 76e7c77 (ipcwork_1_23)
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
<<<<<<< HEAD
}	
	
=======
}

/*
	OLED鏄剧ず鏃堕棿鍑芥暟
*/	
void OLED_Show(tm *pthis)
{
	OLED_ShowNum(1,1,pthis->hour);
	OLED_ShowNum(2,2,pthis->min);
	OLED_ShowNum(3,3,pthis->sec);
}	
>>>>>>> 76e7c77 (ipcwork_1_23)


int main(void)
{	
	
	led_init();
	TIM3_Init(10000,psc);//84000000/8400/10000
	OLED_Init();
	
  while(1){
<<<<<<< HEAD
	  display_sec(&mytime);
=======
	  handle_sec(&mytime);
>>>>>>> 76e7c77 (ipcwork_1_23)
	  OLED_Show(&mytime);
   }
 }
/******
<<<<<<< HEAD
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
=======
瀹氭椂鍣ㄤ腑鏂洖璋冨嚱鏁�
******/
 void TIM3_IRQHandler(void)//绉掍腑鏂竴娆�
 {
	 if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
		{
			tm_sec(&mytime);
	 		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		}
 }

>>>>>>> 76e7c77 (ipcwork_1_23)

 
