#include <stm32f4xx.h>

void systickDelayMs(int n);

int main(){
    RCC->AHB1ENR |= 1;
    GPIOA->MODER |= 0x400;

    while (1)
    {
        systickDelayMs(1000);
        GPIOA->ODR ^= 0x20;
    }
    
}


void systickDelayMs(int n){
    SysTick->LOAD = 16000;  //  Reload with number of clocks per millisecond
    SysTick->VAL = 0;   //  Clear current value register
    SysTick->CTRL = 0x5;    //  Enable Systick

    for (int i = 0; i < n; i++)
    {
        while ((SysTick->CTRL & 0x10000) == 0){}
        
    }
    SysTick->CTRL = 0;
    
}