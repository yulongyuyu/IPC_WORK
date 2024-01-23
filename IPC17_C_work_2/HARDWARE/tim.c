#include "tim.h" 
#include "sys.h"

void TIM3_Init(uint16_t arr,uint16_t psc)
{   
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	NVIC_InitTypeDef NVIC_InitStructure;

	
	TIM_InternalClockConfig(TIM3);//自动配置 定时器

	TIM_TimeBaseInitStruct.TIM_Period = arr-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc-1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);//第一次初始化时清除标志位
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置优先级与抢占优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//配置Interupt ReQuest”中断要求
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	
}
void TIM4_Init(uint16_t arr,uint16_t psc)
{   
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	NVIC_InitTypeDef NVIC_InitStructure;

	
	TIM_InternalClockConfig(TIM4);//自动配置 定时器

	TIM_TimeBaseInitStruct.TIM_Period = arr-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc-1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);//第一次初始化时
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置优先级与抢占优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//配置Interupt ReQuest”中断要求
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
	
}
