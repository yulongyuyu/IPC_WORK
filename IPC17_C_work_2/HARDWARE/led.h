#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"

	
							
/*       
led 的宏定义      
*/

#define LED1_PIN             GPIO_Pin_8       		 	// LED1 引脚  绿灯
#define LED2_PIN             GPIO_Pin_14       		 	// LED2 引脚  红灯
#define LED3_PIN             GPIO_Pin_15       		 	// LED3 引脚  蓝灯
#define LED1_PORT            GPIOC                 		// LED1 GPIO端口  
#define LED2_3_PORT          GPIOD               		// LED2和3 GPIO端口         
#define LED1_CLK             RCC_AHB1Periph_GPIOC		// LED1 GPIO端口时钟
#define LED2_3_CLK           RCC_AHB1Periph_GPIOD		// LED1 GPIO端口时钟

#define LED1_OFF 	  GPIO_ResetBits(LED1_PORT,LED1_PIN);	// 输出低电平，关闭LED1	
#define LED1_ON 	  GPIO_SetBits(LED1_PORT,LED1_PIN);		// 输出高电平，点亮LED1	
#define LED2_OFF 	  GPIO_ResetBits(LED2_3_PORT,LED2_PIN);	// 输出低电平，关闭LED1	
#define LED2_ON 	  GPIO_SetBits(LED2_3_PORT,LED2_PIN);	// 输出高电平，点亮LED1	
#define LED3_OFF 	  GPIO_ResetBits(LED2_3_PORT,LED3_PIN);	// 输出低电平，关闭LED1	
#define LED3_ON 	  GPIO_SetBits(LED2_3_PORT,LED3_PIN);	// 输出高电平，点亮LED1

#define LED_G_OFF 	  LED1_OFF		// 关闭绿灯
#define LED_G_ON 	  LED1_ON		// 打开绿灯
#define LED_R_OFF 	  LED2_OFF		// 关闭红灯
#define LED_R_ON 	  LED2_ON		// 打开红灯
#define LED_B_OFF 	  LED3_OFF		// 关闭蓝灯
#define LED_B_ON 	  LED3_ON		// 打开蓝灯

#define LED_G_TURN		GPIO_ToggleBits( LED1_PORT,LED1_PIN);			//翻转绿灯,切换开关
#define LED_R_TURN		GPIO_ToggleBits( LED2_3_PORT,LED2_PIN);			//翻转红灯,切换开关
#define LED_B_TURN		GPIO_ToggleBits( LED2_3_PORT,LED3_PIN);			//翻转黄灯,切换开关

void led_init(void);
#endif 

