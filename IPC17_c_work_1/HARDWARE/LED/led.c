#define _LED_C_
#include "led.h"
#include "stdio.h"
#include "string.h"

    void led_set_level(pLED_Class pthis, const int led_n, const led_bit led_level);
    void led_set_level_arr(pLED_Class pthis, const led_bits led_sta);
    
    // void led_flip_level(const int led_n);
    // void led_flip_level_arr(led_bits led_sta);

    void led_read_level(pLED_Class pthis, const int led_n, led_bit *led_level);
    void led_read_level_arr(pLED_Class pthis, led_bits* led_sta);
	
pLED_Class CreatLedClass(void){
    pLED_Class led_c= (pLED_Class )malloc(sizeof(LED_Class));
    //assert(person != NULL);
    if(led_c == NULL){
        return NULL;
    }
	led_c -> led_amount = 0;
	led_c -> led_curent_level = (led_bits)0;
	
	led_c -> set_level = led_set_level;
	led_c -> set_level_arr = led_set_level_arr;

	led_c -> set_level_arr(led_c,(led_bits)0x00);
	
    return led_c;
}

pLED_Class createLedClassWtihArgs(int led_amount){
    pLED_Class led_c = CreatLedClass();
    if(led_c == NULL){
 
        return NULL;
    }
	led_c -> led_amount = led_amount;
    return led_c;
}
void led_set_level(pLED_Class pthis, const int led_n, const led_bit led_level){
	led_out_gpio((uint8_t)led_level,led_n);
	pthis -> led_curent_level	&= ~(0x1 << led_n);
	pthis -> led_curent_level	!= (led_level << led_n);
}
void led_set_level_arr(pLED_Class pthis, const led_bits led_sta){
	for(int i = 0;i < pthis -> led_amount ; ++i ){
	led_out_gpio((uint8_t)(led_sta >> i)&1,i);
	}
	pthis -> led_curent_level	= led_sta ;
		
}
