#include "stm32f4xx.h"                  // Device header


int main(){
	
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x800;	//	Set PA5 as alternate function
	GPIOA->AFR[0] |= 0x00100000;	//	Set pin to AF1 for TIM2 CH1
	
}