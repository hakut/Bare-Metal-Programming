#include <stm32f4xx.h>

int main(){
    RCC->AHB1ENR |= 1;
    GPIOA->MODER |= 0x400;

    //TIM2 Config
    RCC->APB1ENR |= 1;
    TIM2->PSC = 1600-1; //  16 000 000 divided by 1600 = 10 000
    TIM2->ARR = 10000-1;    //  10 000 divided by 10 000 = 1 Hertz
    TIM2->CNT = 0;  //  Clear timer counter
    TIM2->CR1 = 1;  //  Enable TIM2

    while (1)
    {
			  while ((!TIM2->SR && 1)){}
        TIM2->SR &=~ 1;
        GPIOA->ODR ^= 0x20; //  Toggle LED

        
    }
    
}