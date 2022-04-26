
#include "stm8s.h"
#include "milis.h"
#include "stm8_hd44780.h"
#include "delay.h"
#include <stdio.h>
#include "uart1.h"
//#include "../lib/uart.c"*/

#define _ISOC99_SOURCE
#define _GNU_SOURCE

#define BTN_PORT GPIOE
#define BTN_PIN  GPIO_PIN_4
#define BTN_PUSH (GPIO_ReadInputPin(BTN_PORT, BTN_PIN)==RESET) 


void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);// nastavuji PE4 jako vstup (tlačítko)
    GPIO_Init(GPIOB, GPIO_PIN_0,GPIO_MODE_IN_FL_NO_IT); // PB0 (tlačítko)

    init_milis();
    init_uart1();

    

    }
int main(void)
{
    uint32_t time = 0;
    uint32_t time2 = 0;
    

    uint32_t stav;
    uint8_t sekundy;
    uint8_t minuty;
    uint8_t hodiny;

    uint8_t x = 0;
    uint8_t x2 = 0;
    
    
    char text[32];
     
 
    setup();

        while (1) {

             if (milis() - time > 1000) { 
                time = milis();
                stav += 1;  
             }

                sekundy = stav % 60; 
			        minuty = (stav % 3600) / 60; 
			        hodiny = stav / 3600;  
                   
                 

            
            if(GPIO_ReadInputPin(BTN_PORT, BTN_PIN)==RESET){
                if(x2 == 0){
                printf("sekundy: %u\r\n", sekundy);
                printf("minuty: %u\r\n", minuty);
                printf("hodiny: %u\r\n", hodiny);
                } 
                x2 = 1;
            }
            else{
                x2 = 0;
            }
            //tlačítko nepajive pole, po stisku resetuje stopky
            if(GPIO_ReadInputPin(GPIOB, GPIO_PIN_0)!=RESET){
                if(x == 0){
                    stav = 0; 
                }
                x = 1;

            }
            else{
                x = 0;
            }
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"