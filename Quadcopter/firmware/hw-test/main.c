/**
 *
 */
#include "soc-hw.h"
#include "softfloat.h"

//Ratios de conversion
#define A_R 16384.0
#define G_R 131.0

//Conversion de radianes a grados 180/PI
#define RAD_TO_DEG = 57.295779

void printdec2hex(char l){

        char t = ((l & 0xf0 )>>4)+0x30;
	if (t > 0x39)
		t+=0x07;
	uart_putchar1(t);
	t = (l & 0x0f)+0x30;
	if (t > 0x39)
		t+=0x07;
	uart_putchar1(t);

}
void printxyz(int8_t AcH, char AcL){
		if(AcH<0){
			uart_putchar1('-');
			printdec2hex(AcH & 0X7F);
		}
		else		
			printdec2hex(AcH);
		
		printdec2hex(AcL);
		uart_putstr1(" ");
}

int main(){

	int s1=0x00;
	int s2=0x00;
	int s3=0x00;	
	int s4=0x00;

	int32_t AcX;
	int32_t AcY;
	int32_t AcZ;
	
	int8_t AcXh;
	int8_t AcYh;	
	int8_t AcZh;
	int i=0;
	setMotors();
	msleep(50);	
	initImu();
	msleep(50);
	//init_wifi()
	//msleep(50);
	testMotos();
	uart_putchar(0);
	uart_putchar1(0);
	
	int32_t z=0x01;
	float32 a = int32_to_float32(z);	
	for(;;){
		for(i=0;i<5;i++){
			AcZh = i2c_read (ADDRESS_I2C, ACCEL_ZOUT_H);
			sleep(1);
		}
		
		for(i=0;i<5;i++){			
			AcYh = i2c_read (ADDRESS_I2C, ACCEL_YOUT_H);
			sleep(1);
		}
		
		for(i=0;i<5;i++){				
			AcXh = i2c_read (ADDRESS_I2C, ACCEL_XOUT_H);
			sleep(1);
		}	

		printxyz(AcXh, 0x00);
		printxyz(AcYh, 0x00);
		printxyz(AcZh, 0x00);			
		uart_putchar1(13);
		uart_putchar1(10);
		
		sleep(200);
	}
	/*for(;;){
		//AcX=getAcX();
		//AcY=getAcY();
		//AcZ=getAcZ();
		if(AcZ<0x32){
			if(AcX>-115 && AcX<0x0){	
				if(s2<0x69)
					s2=s2+0x01;
				else{
					s2=0x69;
					s4=s4-0x01;
					set_motor4(0x5DC * s4 + 0xFD20);
				}
				set_motor2(0x5DC * s2 + 0xFD20);
			}
			if(AcX>0x1F){
				if(s4<0x69)
					s4=s4+0x01;
				else{
					s4=0x69;
					s2=s2-0x01;
					set_motor2(0x5DC * s2 + 0xFD20)
				}
				set_motor4(0x5DC * s4 + 0xFD20);			
			}
			if(AcY>-115 && AcY<0x0){
				if(s1<0x69)
					s1=s1+0x01;
				else{
					s1=0x69;
					s3=s3-0x01;			
					set_motor3(0x5DC * s3 + 0xFD20);								
				}
				set_motor1(0x5DC * s1 + 0xFD20);								
			}
			if(AcY>0x15){
				if(s4<0x69)
					s3=s3+0x01;
				else{
					s3=0x69;
					s1=s1-0x01;			
					set_motor1(0x5DC * s1 + 0xFD20);								
				}
				set_motor3(0x5DC * s3 + 0xFD20);
			}
		}
		else{
			set_motor1(0xEA60); 
			set_motor2(0xEA60);
			set_motor3(0xEA60);
			set_motor4(0xEA60);
		}
	}*/
}


/*printxyz(AcXh, 0x00); visualizar en cutecome x-y-z
		printxyz(AcYh, 0x00);
		printxyz(AcZh, 0x00);			
		uart_putchar1(13);
		uart_putchar1(10);
		sleep(200);*/
