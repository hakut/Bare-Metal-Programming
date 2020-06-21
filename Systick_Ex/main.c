#include <stm32f4xx.h>

#include <stm32f4xx.h>

int main(){
    RCC->AHB1ENR |= 1;
    GPIOA->MODER |= 0x400;


    // Configure SysTick

    SysTick->LOAD = 1600000 - 1; // For 100ms delay
    SysTick->VAL = 0;
    SysTick->CTRL = 5;

    while (1)
    {
        if(SysTick->CTRL & 0x10000){

            GPIOA->ODR ^= 0x20; // Toggle LED

        }
    }
    


}