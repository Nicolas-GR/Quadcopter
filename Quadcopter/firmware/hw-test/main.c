/**
 *
 */
#include "soc-hw.h"
#include "softfloat.h"


int s1 = 0x0;
int s2 = 0x0;
int s3 = 0x0;
int s4 = 0x0;

void printdec2hex(char l){
	char t = ((l & 0xF0) >> 4) + 0x30;
	if (t > 0x39)
		t+=0x07;
	uart_putchar1(t);
	t = (l & 0x0f) + 0x30;
	if (t > 0x39)
		t+=0x07;
	uart_putchar1(t);
}

void printxyz(int8_t AcH, char AcL){
	if(AcH<0){
		uart_putchar1('-');
		printdec2hex((~AcH) + 0x1);
	}else{
		printdec2hex(AcH);
	}		
	printdec2hex(AcL);
	uart_putstr1(" ");
}

int getRoll(float32 AcX, float32 AcZ){
	float32 a = 0x0;
	float32 b = 0x0;
	float32 roll = 0x0;
	int ROLL = 0x0;
	char print;
	
	a = float32_mul (NEG, AcX);
	b = float32_div(a, AcZ);
	roll = float32_artan(b);
	roll = float32_mul(roll, RtoD);
	uart_putchar1(13);
	uart_putchar1(10);	
	uart_putstr1("> ROLL  : ");
	roll = float32_round_to_int(roll);
	ROLL = float32_to_int32(roll);
	print = ROLL;
	printdec2hex(print);
	uart_putchar1(13);
	uart_putchar1(10);		
	return ROLL;
}

int getPitch(float32 AcX, float32 AcY, float32 AcZ){
	float32 a = 0x0;
	float32 b = 0x0;
	float32 pitch = 0x0;
	int PITCH = 0x0;
	char print;
	
	a = float32_add(float32_pow2(AcX), float32_pow2(AcZ)); // b² + c²
	a = float32_sqrt(a);// (b² + c²)^0.5
	b = float32_div(AcY, a);// a/((b² + c²)^0.5)
	pitch = float32_artan(b); // ARCTAN(a/((b² + c²)^0.5))
	pitch = float32_mul(pitch, RtoD); //Rad_to_Deg
	uart_putchar1(13);
	uart_putchar1(10);	
	uart_putstr1("> PITCH : ");
	pitch = float32_round_to_int(pitch);
	PITCH = float32_to_int32(pitch); 
	print = PITCH;
	printdec2hex(print);
	uart_putchar1(13);
	uart_putchar1(10);
	return PITCH;
}

int updateMotors(int roll, int pitch){
	int control = 0;
	if(pitch < (-5)){
		control += 1000; //M4
	}else if(pitch > 5){
		control += 10; //M2
	}
	
	if(roll < (-5)){
		control += 1; //M1
	}else if(roll > 5){
		control += 100; //M3
	}
	return control;
}

float32 readIMU(int adr_h, int adr_l){
	int8_t high = 0x0;
	uint8_t low = 0x0;
	int read = 0x0;
	int i = 0;
	
	for(i=0;i<5;i++){
		high = i2c_read (ADDRESS_I2C, adr_h);
		sleep(1);
	}
	for(i=0;i<5;i++){
		low = i2c_read (ADDRESS_I2C, adr_l);
		sleep(1);
	}
	printxyz(high, low);
	read = high;
	read = read<<8;
	if(read < 0x0){
		read = read - low;
	}else{
		read = read - low;;
	} 
	return int32_to_float32(read);
}


int main(){
	int pitch;
	int roll;

	float32 AcX;
	float32 AcY;
	float32 AcZ;	
	
	setMotors();
	msleep(50);	
	initImu();
	msleep(50);
	//init_wifi()
	//msleep(50);
	testMotos();
	uart_putchar(0);
	uart_putchar1(0);
			
	for(;;){
		uart_putchar1(13);
		uart_putchar1(10);
		AcX = readIMU(ACCEL_XOUT_H, ACCEL_XOUT_L);
		AcY = readIMU(ACCEL_YOUT_H, ACCEL_YOUT_L);
		AcZ = readIMU(ACCEL_ZOUT_H, ACCEL_ZOUT_L);
		uart_putchar1(13);
		uart_putchar1(10);
		roll = getRoll(AcX, AcZ);
		pitch = getPitch(AcX, AcY, AcZ);
		uart_putchar1(13);
		uart_putchar1(10);		
		switch (updateMotors(pitch, roll)){
	    		case 0: // ALL: OFF
	    			set_motor1(0xEA60);
	    			set_motor2(0xEA60);
	    			set_motor3(0xEA60);
	    			set_motor4(0xEA60);
	    			break;
	    		case 1: // M1: ON
	    			uart_putchar1(13);
				uart_putchar1(10);
				uart_putstr1(" M1");
	    			set_motor1(0x186A0); //ON
	    			set_motor2(0xEA60);
	    			set_motor3(0xEA60);
	    			set_motor4(0xEA60);
	    			break;
	    		case 10: // M2: ON
	    			uart_putchar1(13);
					uart_putchar1(10);
					uart_putstr1(" M2");
	    			set_motor1(0xEA60); 
	    			set_motor2(0x186A0); //ON
	    			set_motor3(0xEA60);
	    			set_motor4(0xEA60);
	    			break;
	    		case 100: // M3: ON
	    			uart_putchar1(13);
					uart_putchar1(10);
					uart_putstr1(" M3");
	    			set_motor1(0xEA60); 
	    			set_motor2(0xEA60); 
	    			set_motor3(0x186A0); //ON
	    			set_motor4(0xEA60);
	    			break;
	    		case 1000: // M4: ON
	    			uart_putchar1(13);
					uart_putchar1(10);
					uart_putstr1(" M4");
	    			set_motor1(0xEA60); 
	    			set_motor2(0xEA60); 
	    			set_motor3(0xEA60); 
	    			set_motor4(0x186A0); //ON
	    			break;
	    		case 11: // M1: ON; M2: ON;
	    			uart_putchar1(13);
					uart_putchar1(10);
					uart_putstr1(" M1 M2");
	    			set_motor1(0x186A0); //ON
	    			set_motor2(0x186A0); //ON
	    			set_motor3(0xEA60); 
	    			set_motor4(0xEA60);
	    			break;
	    		case 110: // M2: ON; M3: ON;
	    			uart_putchar1(13);
					uart_putchar1(10);
	    			uart_putstr1(" M2 M3");
	    			set_motor1(0xEA60); 
	    			set_motor2(0x186A0); //ON
	    			set_motor3(0x186A0); //ON
	    			set_motor4(0xEA60);
	    			break;
	    		case 1100: // M3: ON; M4: ON;
	    			uart_putchar1(13);
					uart_putchar1(10);
	    			uart_putstr1(" M3 M4");
	    			set_motor1(0xEA60); 
	    			set_motor2(0xEA60); 
	    			set_motor3(0x186A0); //ON
	    			set_motor4(0x186A0); //ON
	    			break;
	    		case 1001: // M1: ON; M4: ON;
	    			uart_putchar1(13);
					uart_putchar1(10);
	    			uart_putstr1(" M1 M4");
	    			set_motor1(0x186A0); //ON
	    			set_motor2(0xEA60); 
	    			set_motor3(0xEA60); 
	    			set_motor4(0x186A0); //ON
	    			break;
	    		case 1111: // ALL ON;
	    			uart_putchar1(13);
					uart_putchar1(10);
	    			uart_putstr1(" M1 M2 M3 M4");
	    			set_motor1(0x186A0); //ON
	    			set_motor2(0x186A0); //ON
	    			set_motor3(0x186A0); //ON
	    			set_motor4(0x186A0); //ON
	    			break;
				default:
				uart_putstr1("problema");
				break;
		};
	uart_putchar1(13);
	uart_putchar1(10);
	}
}
