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


/*inline void writeint(uint32_t val)*/
/*{*/
/*	uint32_t i, digit;*/

/*	for (i=0; i<8; i++) {*/
/*		digit = (val & 0xf0000000) >> 28;*/
/*		if (digit >= 0xA) */
/*			uart_putchar('A'+digit-10);*/
/*		else*/
/*			uart_putchar('0'+digit);*/
/*		val <<= 4;*/
/*	}*/
/*}*/



/*char glob[] = "Global";*/

/*volatile uint32_t *p;*/
/*volatile uint8_t *p2;*/

/*extern uint32_t tic_msec;*/


/*int main()*/
/*{*/
/*	//variables de control	*/
/*	int speed = 0x0;*/
/*	char t='\0';*/

/*	msleep(50);*/

/*	// iniciar wifi*/
/*	init_wifi();*/

/*	// iniciar motores*/

/*	setMotors();*/

/*	uart_putchar1(speed);*/

/*	for(;;){*/

/*		t='\0';*/
/*		while(t =='\n' || t =='\r'|| t == ' '  || t == '\0' || t =='\v'|| t == 10 || t == 13){*/
/*			uart_putchar1(speed);*/
/*			t = wifi_getchar();*/
/*			//sttc(); // cambiar speed de 0 a af*/
/*		}*/

/*		if(t=='u'){*/
/*			if((speed >= 0x0) && (speed < 0x64)){*/
/*				speed = speed + 0x1;*/
/*				speedM1(speed);*/
/*				speedM2(speed);*/
/*				speedM3(speed);*/
/*				speedM4(speed);*/
/*			}*/
/*			/*if((speed = 0x1) && (speed <= 0x64)){*/
/*				speed = 0x514 * speed + 0xF64A;*/
/*			}*/
/*			else{*/
/*				speed = speed - 0x5;*/
/*			}*/
/*			uart_putchar1(speed);*/
/*			set_motor1(speed);*/	*/
/*		}*/
/*		else{*/
/*			if(t=='d'){*/
/*				if((speed > 0x0) && (speed <= 0x64)){*/
/*				speed = speed - 0x1;*/
/*				speedM1(speed);*/
/*				speedM2(speed);*/
/*				speedM3(speed);*/
/*				speedM4(speed);*/
/*				}*/
/*			}*/
/*			else{*/
/*				if(t=='r'){*/
/*					uart_putchar1(speed);*/
/*				}*/
/*				else{*/
/*					if(t=='l'){*/
/*						uart_putchar1(speed);*/
/*					}*/
/*					else{*/
/*						if(t=='f'){*/
/*							uart_putchar1(speed);*/
/*						}*/
/*						else {*/
/*							if(t=='b'){*/
/*								uart_putchar1(speed);*/
/*							}*/
/*							else{*/
/*								uart_putchar1(speed);*/

/*							}*/
/*						}*/
/*					}*/
/*				}*/
/*			}*/
/*		}*/
/*	}*/
/*	/*set_motor1(0x30D40);*/
/*	msleep(0x2710);*/
/*	uart_putstr1("1");*/
/*	set_motor1(0x2710);*/
/*	msleep(0x2710);*/
/*	uart_putstr1("2");*/
/*	set_motor1(0x186A0);*/
/*	uart_putstr1("OK");*/*/
/*	*/
/*}*/
