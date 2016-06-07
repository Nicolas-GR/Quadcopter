/**
 * 
 */

#include "soc-hw.h"
//#include "tgmath.h"
//#include "string.h"

//Ratios de conversion
#define A_R 16384.0
#define G_R 131.0
 
//Conversion de radianes a grados 180/PI
#define RAD_TO_DEG = 57.295779
int main(){

	//Reset device, reset all registers, clear gyro and accelerometer bias registers		
		i2c_write(ADDRESS_I2C,PWR_MGMT_1,0x80);
		sleep(100); 
		//Get stable time source
		i2c_write(ADDRESS_I2C,PWR_MGMT_1,0x01);
		i2c_write(ADDRESS_I2C,PWR_MGMT_2,0x00);
		sleep(200);
		// Configure device for bias calculation
		i2c_write(ADDRESS_I2C,INT_ENABLE,0x00);
		i2c_write(ADDRESS_I2C,FIFO_EN,0x00);
		i2c_write(ADDRESS_I2C,PWR_MGMT_1,0x00);
		i2c_write(ADDRESS_I2C,I2C_MST_CTRL,0x00);
		i2c_write(ADDRESS_I2C,USER_CTRL,0x00);
		i2c_write(ADDRESS_I2C,USER_CTRL,0x0C);
		sleep(15);
		// Configure MPU6050 gyro and accelerometer for bias calculation
		i2c_write(ADDRESS_I2C,CONFIG,0x01);
		i2c_write(ADDRESS_I2C,SMPLRT_DIV,0x00);
		i2c_write(ADDRESS_I2C,GYRO_CONFIG,0x01);
		i2c_write(ADDRESS_I2C,ACCEL_CONFIG,0x00);
		// Configure FIFO to capture accelerometer and gyro data for bias calculation
		i2c_write(ADDRESS_I2C,USER_CTRL,0x40);
		i2c_write(ADDRESS_I2C,ACCEL_CONFIG,0x78);
		sleep(80);
	
		
	while(1){	
		//i2c_write(ADDRESS_I2C,PWR_MGMT_1,0x80);
		char AcXh = i2c_read (ADDRESS_I2C, ACCEL_XOUT_H);
		uart_putchar1(AcXh);
		sleep(1000);
		char AcXl = i2c_read (ADDRESS_I2C, ACCEL_XOUT_L);
		uart_putchar1(AcXl);
		sleep(1000);
		char AcYh = i2c_read (ADDRESS_I2C, ACCEL_YOUT_H);
		uart_putchar1(AcYh);
		sleep(1000);
		char AcYl = i2c_read (ADDRESS_I2C, ACCEL_YOUT_L);
		uart_putchar1(AcYl);
		sleep(1000);
		char AcZh = i2c_read (ADDRESS_I2C, ACCEL_ZOUT_H);
		uart_putchar1(AcZh);
		sleep(1000);
		char AcZl = i2c_read (ADDRESS_I2C, ACCEL_ZOUT_L);
		uart_putchar1(AcZl);
		sleep(1000);
		char Gxh = i2c_read (ADDRESS_I2C, GYRO_XOUT_L);
		uart_putchar1(Gxh);
		sleep(1000);
		char Gxl = i2c_read (ADDRESS_I2C, GYRO_XOUT_L);
		uart_putchar1(Gxh);
		sleep(1000);
		char Gyh = i2c_read (ADDRESS_I2C, GYRO_YOUT_L);
		uart_putchar1(Gxh);
		sleep(1000);
		char Gyl = i2c_read (ADDRESS_I2C, GYRO_YOUT_L);
		uart_putchar1(Gxh);
		sleep(1000);
		char Gzh = i2c_read (ADDRESS_I2C, GYRO_ZOUT_L);
		uart_putchar1(Gxh);
		sleep(1000);
		char Gzl = i2c_read (ADDRESS_I2C, GYRO_ZOUT_L);
		uart_putchar1(Gxh);
		sleep(1000);
	} 
}

