#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"

	
							
/*       
led �ĺ궨��      
*/

#define LED1_PIN             GPIO_Pin_8       		 	// LED1 ����  �̵�
#define LED2_PIN             GPIO_Pin_14       		 	// LED2 ����  ���
#define LED3_PIN             GPIO_Pin_15       		 	// LED3 ����  ����
#define LED1_PORT            GPIOC                 		// LED1 GPIO�˿�  
#define LED2_3_PORT          GPIOD               		// LED2��3 GPIO�˿�         
#define LED1_CLK             RCC_AHB1Periph_GPIOC		// LED1 GPIO�˿�ʱ��
#define LED2_3_CLK           RCC_AHB1Periph_GPIOD		// LED1 GPIO�˿�ʱ��

#define LED1_OFF 	  GPIO_ResetBits(LED1_PORT,LED1_PIN);	// ����͵�ƽ���ر�LED1	
#define LED1_ON 	  GPIO_SetBits(LED1_PORT,LED1_PIN);		// ����ߵ�ƽ������LED1	
#define LED2_OFF 	  GPIO_ResetBits(LED2_3_PORT,LED2_PIN);	// ����͵�ƽ���ر�LED1	
#define LED2_ON 	  GPIO_SetBits(LED2_3_PORT,LED2_PIN);	// ����ߵ�ƽ������LED1	
#define LED3_OFF 	  GPIO_ResetBits(LED2_3_PORT,LED3_PIN);	// ����͵�ƽ���ر�LED1	
#define LED3_ON 	  GPIO_SetBits(LED2_3_PORT,LED3_PIN);	// ����ߵ�ƽ������LED1

#define LED_G_OFF 	  LED1_OFF		// �ر��̵�
#define LED_G_ON 	  LED1_ON		// ���̵�
#define LED_R_OFF 	  LED2_OFF		// �رպ��
#define LED_R_ON 	  LED2_ON		// �򿪺��
#define LED_B_OFF 	  LED3_OFF		// �ر�����
#define LED_B_ON 	  LED3_ON		// ������

#define LED_G_TURN		GPIO_ToggleBits( LED1_PORT,LED1_PIN);			//��ת�̵�,�л�����
#define LED_R_TURN		GPIO_ToggleBits( LED2_3_PORT,LED2_PIN);			//��ת���,�л�����
#define LED_B_TURN		GPIO_ToggleBits( LED2_3_PORT,LED3_PIN);			//��ת�Ƶ�,�л�����

void led_init(void);
#endif 

