#include <stm32f4xx.h>
#include <stdio.h>

void USART2_Init(void);
int USART2_write(int ch);
int USART2_read(void);

int main(void){
	int n;
	char str[100];
	
	USART2_Init();
	printf("\r\nHello from the other side\r\n");
	fprintf(stdout,"Test for stdout\r\n");
	fprintf(stderr,"Test for stderr\r\n");
	while(1){
		printf("How old are you? ");
		scanf("%d",&n);
		printf("Your age is : %d\r\n",n);
		printf("Enter your first name : ");
		gets(str);
		printf("I dig your style, ");
		puts(str);
		printf("\r\n");
	}
}
void USART2_Init(void){
	RCC->AHB1ENR |= 1;
	RCC->APB1ENR |= 0x20000;
	
	// GPIO configuration
	
	GPIOA->AFR[0] |= 0x7700;
	GPIOA->MODER |= 0x00A0;	//	Enable alternate function for PA2 & PA3
	
	USART2->BRR = 0x0683;	//	9600 baudrate @16Mhz
	USART2->CR1 = 0x000C;	//	Enable Rx,Tx
	USART2->CR1	|=	0x2000;
	
}

int USART2_write(int ch){
	//	Wait for Tx buffer
	while(!(USART2->SR & 0x0080)){}
		USART2->DR = (ch & 0xFF);
		return USART2->DR;
	}

int USART2_read(void){
	while(!(USART2->SR & 0x0020)){}
		return USART2->DR;
	}

	struct __FILE{int handle;};
	FILE __stdin	=	{0};
	FILE __stdout	=	{1};
	FILE __stderr	=	{2};
	
	int fgetc(FILE *f){
		int c;
		c	=	USART2_read();
		if(c == '\r'){
			USART2_write(c);
			c = '\n';
		}
		USART2_write(c);
		
		return c;
	}
	int fputc(int c, FILE *f){
		return USART2_write(c);
	}
