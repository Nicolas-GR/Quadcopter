/**
 * 
 */

#include "soc-hw.h"
#include "stdio.h"
#include "stdlib.h"


int main(){

float b;

b = sinf(45.5);

}

/*
inline void writeint(uint32_t val)
{
	uint32_t i, digit;

	for (i=0; i<8; i++) {
		digit = (val & 0xf0000000) >> 28;
		if (digit >= 0xA) 
			uart_putchar('A'+digit-10);
		else
			uart_putchar('0'+digit);
		val <<= 4;
	}
}



char glob[] = "Global";

volatile uint32_t *p;
volatile uint8_t *p2;

extern uint32_t tic_msec;


int main()
{
	//variables de control	
	int speed = 0x0;
	char t='\0';

	msleep(50);

	// iniciar wifi
	init_wifi();

	// iniciar motores

	setMotors();


	for(;;){
		t='\0';
		
		while(t =='\n' || t =='\r'|| t == ' '  || t == '\0' || t =='\v'|| t == 10 || t == 13){
			uart_putchar1(speed);
			//uart_putchar1(0x0D);
			uart_putchar1(0x0A);
			t = wifi_getchar();
			//stab();(Tentativa de función)
		}

		if(t=='u'){
			if((speed >= 0x0) && (speed < 0x69)){
				speed = speed + 0x1;
				up_down_q(speed);
			}
			else{
				speed = 0x69;
				up_down_q(speed);
			}

		}
		else{
			
			if(t=='d'){
				if((speed > 0x0) && (speed <= 0x69)){
					speed = speed - 0x1;
					up_down_q(speed);
				}
				else{
					speed = 0x0;
					up_down_q(speed);
				}
			}

			else{
				if(t=='r'){
					uart_putchar1(speed);
					uart_putchar1(0x0D);
					uart_putchar1(0x0A);
				}
				else{
					if(t=='l'){
						uart_putchar1(speed);
						uart_putchar1(0x0D);
						uart_putchar1(0x0A);
					}
					else{
						if(t=='f'){
							uart_putchar1(speed);
							uart_putchar1(0x0D);
							uart_putchar1(0x0A);
						}
						else {
							if(t=='b'){

								speed = 0x0;
								up_down_q(speed);
							}
							else{
								uart_putchar1(speed);
								uart_putchar1(0x0D);
								uart_putchar1(0x0A);

							}
						}
					}
				}
			}
		}
	}
	
}
*/
