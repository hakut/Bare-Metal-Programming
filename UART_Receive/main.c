#include <stm32f4xx.h>
void delayMs(int delay);
void LED_play(int value);
char USART2_read(void);
void USART_Init(void);
	
int main(void){
	RCC->AHB1ENR |= 1; //Enable Clock for PA
	GPIOA->MODER |= 0x400; //Set pin as output
	
	USART_Init();
	char ch;
	while(1){
		ch = USART2_read();
		LED_play(ch);
		
	}
}

void USART_Init(void){
	RCC->AHB1ENR |= 1;				// Enable GPIIOA Clock
	RCC->APB1ENR |= 0x20000;	// Enable USART2 Clock
	
	// Configure PA3 as USART2 RX
	GPIOA->AFR[0] |= 0x7000;	// Alt7 for USART2
	GPIOA->MODER 	|= 0x0080;	// Enable Alternate function at PA3
	
	USART2->BRR		|= 0x008B;		// 115200 baudrate @16Mhz
	USART2->CR1		|= 0x0004;		// Enable Rx
	USART2->CR1 	|= 0x2000;		// Enable USART2
}

char USART2_read(void){
	while(!(USART2->SR & 0x0020)){}	// wait until char arrives
		return USART2->DR;
	}

	void LED_play(int value){
		value %=16;
		for(;value>0;value--){
			GPIOA->BSRR = 0x20; //Turen on LED
			delayMs(100);
			GPIOA->BSRR = 0x00200000; //Turn off LED
			delayMs(100);
	}
}

	void delayMs(int delay){
		for(;delay>0;delay--){
			for(int i=0;i<3195;i++);
	}
}
