#include <stm32f4xx.h>

void delayMs(int delay);
void	LED_play(int value);
char USART2_read(void);
void USART_Init(void);
int printValue(void);

int main(void){
	USART_Init();
	GPIOA->MODER |= 0x400; //Set pin as output
	char read;
	int button;
	while(1){
		button = printValue();
		LED_play(button);
		
		
	}
}

void USART_Init(void){
	
	//	 Enabling Buses
	RCC->AHB1ENR = 1;	//	PortA Bus enable
	RCC->AHB1ENR |= 0x4;	//	PortC Bus enable
	RCC->APB1ENR = 0x20000;	// USART Bus enable
	
	//	Configure PA2 & PA3 as Tx and Rx respectively
	
	GPIOA->MODER |= 0x20;	// PA2 Alternate function
	GPIOA->MODER |= 0x80;	// PA3 Alternate function
	
	GPIOA->AFR[0] = 0x700;	//	USART alternate function for PA2
	GPIOA->AFR[0] |= 0x7000;	//	USART alternate function for PA3
	
	USART2->BRR = 0x0683;	//	9600 baudrate
	USART2->CR1 = 0x0008;	// Enable Tx mode
	USART2->CR1 |= 0x0004;	// Enable Rx mode
	USART2->CR1 |= 0x2000;	//Enable USART on Control Register
	
}

char USART2_read(void){
	while(!(USART2->SR & 0x0020)){}	//	wait for data input
		return USART2->DR;	// return data read
}

void	LED_play(int value){
	value %= 16;
	for(;value>0;value--){
		GPIOA->BSRR = 0x20;	//Turn on LED
		delayMs(100);
		GPIOA->BSRR = 0x200000;	//	Turn off LED
		delayMs(100);
	}
}
	
void delayMs(int delay){
	for(;delay>0;delay--){
		for(int i = 0; i<3195; i++);
	}
}

int printValue(void){
	int counter = 0;
	while(GPIOC->IDR & 0x2000){
		counter++;
	}
	USART2->DR = (counter & 0xFF);
	return USART2->DR;
}

