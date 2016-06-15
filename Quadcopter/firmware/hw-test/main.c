/**
 *
 */
#include "soc-hw.h"
#include "softfloat.h"

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

int getRoll(int rollOLD, float32 AcX, float32 AcY, float32 AcZ, float32 GyX, int dt){
	float32 a = 0x0;
	float32 AccRoll = 0x0;
	float32 GyrRoll = 0x0;
	float32 roll = int32_to_float32(rollOLD);
	int ROLL = 0x0;
	int8_t print;
	// Roll from Acc
	a = float32_add(float32_pow2(AcX), float32_pow2(AcZ)); // b² + c²
	a = float32_sqrt(a);// (b² + c²)^0.5
	a = float32_div(AcY, a);// a/((b² + c²)^0.5)
	AccRoll = float32_artan(a); // ARCTAN(a/((b² + c²)^0.5))
	AccRoll = float32_mul(AccRoll, RtoD); //Rad_to_Deg
	// Roll from Gyr
	GyrRoll = float32_div(GyX, G_R);
	//Filter
	roll = float32_filterKom(roll, AccRoll, GyrRoll, dt);
	//print
	uart_putchar1(13);
	uart_putchar1(10);	
	uart_putstr1("> ROLL : ");
	roll = float32_round_to_int(roll);
	ROLL = float32_to_int32(roll); 
	print = ROLL;
	printdec2hex(print);
	uart_putchar1(13);
	uart_putchar1(10);
	return ROLL;
}

int getPitch(int pitchOLD, float32 AcX, float32 AcZ, float32 GyY, int dt){
	float32 a = 0x0;
	float32 AccPitch = 0x0;
	float32 GyrPitch = 0x0;
	float32 pitch = int32_to_float32(pitchOLD);
	int PITCH = 0x0;
	int8_t print;
	// Pitch from Acc
	a = float32_mul (NEG, AcX);
	a = float32_div(a, AcZ);
	AccPitch = float32_artan(a);
	AccPitch = float32_mul(AccPitch, RtoD);
	// Picth from Gyr
	GyrPitch = float32_div(GyY, G_R);
	//Filter
	pitch = float32_filterKom(pitch, AccPitch, GyrPitch, dt);
	//print
	uart_putchar1(13);
	uart_putchar1(10);	
	uart_putstr1("> PITCH  : ");
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
		read = read + low;
	} 
	return int32_to_float32(read);
}


int main(){
	int pitch = 0x0;
	int roll = 0x0;
	float32 AcX = 0x0;
	float32 AcY = 0x0;
	float32 AcZ = 0x0;	
	float32 GyX = 0x0;
	float32 GyY = 0x0;
	uint32_t dt = 0x0;
	timer0->counter0 =0;
	timer0->compare0=0xFFFFFFFF;	
	
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
		timer0->tcr0 = 0;
		dt=timer0->counter0;
		AcX = readIMU(ACCEL_XOUT_H, ACCEL_XOUT_L);
		AcY = readIMU(ACCEL_YOUT_H, ACCEL_YOUT_L);
		AcZ = readIMU(ACCEL_ZOUT_H, ACCEL_ZOUT_L);
		GyX = readIMU(GYRO_XOUT_H, GYRO_XOUT_L);
		GyY = readIMU(GYRO_YOUT_H, GYRO_YOUT_L);
		timer0->counter0 =0;
		timer0->tcr0 = TIMER_EN;		
		uart_putchar1(13);
		uart_putchar1(10);
		roll = getRoll(roll, AcX, AcY, AcZ, GyX, dt);
		pitch = getPitch(pitch, AcX, AcZ, GyY, dt);
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
