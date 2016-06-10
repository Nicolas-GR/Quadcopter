#ifndef SPIKEHW_H
#define SPIKEHW_H

#define PROMSTART 0x00000000
#define RAMSTART  0x00000800
#define RAMSIZE   0x400
#define RAMEND    (RAMSTART + RAMSIZE)

#define RAM_START 0x40000000
#define RAM_SIZE  0x04000000

#define FCPU      50000000

#define UART_RXBUFSIZE 32



/****************************************************************************
 * Types
 */
typedef unsigned int  uint32_t;    // 32 Bit
typedef signed   int   int32_t;    // 32 Bit

typedef unsigned char  uint8_t;    // 8 Bit
typedef signed   char   int8_t;    // 8 Bit

typedef unsigned int  uint16_t;    // 16 Bit
typedef signed   int   int16_t;    // 16 Bit

/****************************************************************************
 * Interrupt handling
 */
typedef void(*isr_ptr_t)(void);

void     irq_enable();
void     irq_disable();
void     irq_set_mask(uint32_t mask);
uint32_t irq_get_mak();

void     isr_init();
void     isr_register(int irq, isr_ptr_t isr);
void     isr_unregister(int irq);

/****************************************************************************
 * General Stuff
 */
void     halt();
void     jump(uint32_t addr);


/****************************************************************************
 * Timer
 */
#define TIMER_EN     0x08    // Enable Timer
#define TIMER_AR     0x04    // Auto-Reload
#define TIMER_IRQEN  0x02    // IRQ Enable
#define TIMER_TRIG   0x01    // Triggered (reset when writing to TCR)

typedef struct {
	volatile uint32_t tcr0;
	volatile uint32_t compare0;
	volatile uint32_t counter0;
	volatile uint32_t tcr1;
	volatile uint32_t compare1;
	volatile uint32_t counter1;
} timer_t;
void sleep(int msec);
void msleep(uint32_t msec);
void nsleep(uint32_t nsec);

void prueba();
void tic_init();


/***************************************************************************
 * GPIO0
 */
typedef struct {
        volatile uint32_t gpio_i;
        volatile uint32_t gpio_o;
        volatile uint32_t gpio_dir;
	
} gpio_t;

void write_dir(char dir);
void write_data(char data);
char read_data();

/***************************************************************************
 * UART0
 */
#define UART_DR   0x01                    // RX Data Ready
#define UART_ERR  0x02                    // RX Error
#define UART_BUSY 0x10                    // TX Busy

typedef struct {
   volatile uint32_t ucr;
   volatile uint32_t rxtx;
} uart_t;

void uart_init();
void uart_putchar(char c);
void uart_putstr(char *str);
char uart_getchar();
//UART1
void uart_putchar1(char c);
void uart_putstr1(char *str);
char uart_getchar1();

/***************************************************************************
 *  i2c0
 */

//Register MPU6050
#define ADDRESS_I2C	0x68
#define PWR_MGMT_1 	0x6B
#define PWR_MGMT_2 	0x6C
#define INT_ENABLE 	0x38
#define FIFO_EN    	0x23
#define I2C_MST_CTRL	0x24
#define USER_CTRL 	0x6A
#define CONFIG		0x1A
#define SMPLRT_DIV	0x19
#define GYRO_CONFIG	0x1B
#define ACCEL_CONFIG	0x1C
#define FIFO_EN		0x23
#define ACCEL_XOUT_H 	0x3B
#define ACCEL_XOUT_L    0x3C
#define ACCEL_YOUT_H    0x3D
#define ACCEL_YOUT_L    0x3E
#define ACCEL_ZOUT_H    0x3F
#define ACCEL_ZOUT_L    0x40
#define TEMP_OUT_H      0x41
#define TEMP_OUT_L      0x42
#define GYRO_XOUT_H     0x43
#define GYRO_XOUT_L     0x44
#define GYRO_YOUT_H     0x45
#define GYRO_YOUT_L     0x46
#define GYRO_ZOUT_H     0x47
#define GYRO_ZOUT_L     0x48

typedef struct {  
   volatile uint32_t i2c_data_out;
   volatile uint32_t availWrite;
   volatile uint32_t availRead;	
   volatile uint32_t rw;
   volatile uint32_t data;
   volatile uint32_t startRead;
   volatile uint32_t startWrite;
}i2c_t;
void i2c_write (int dirI2C, int dirIntern, int data);
int8_t i2c_read (int dirI2C, int dirIntern);
void start_Read (int num);
void start_Write (int num);
void rw(int data_rw);

/***************************************************************************
 * PWM0
 */
typedef struct {
	volatile uint32_t period; 		//000 
	volatile uint32_t duty_m1;	 	//001
	volatile uint32_t duty_m2;	 	//010
	volatile uint32_t duty_m3;	 	//011
	volatile uint32_t duty_m4;	 	//100
} pwm_t;

void set_period(int p);
void set_motor1(int wk);
void set_motor2(int wk);
void set_motor3(int wk);
void set_motor4(int wk);

/***************************************************************************
 * MOTORS FUNCTIONS
 */
void setMotors();
void up_down_q(int s);

/***************************************************************************
 * Pointer to actual components
 */
extern timer_t  *timer0;
extern gpio_t   *gpio0;
extern uart_t   *uart0; 
extern uart_t   *uart1; 
extern i2c_t    *i2c0; 
extern pwm_t   *pwm0; 
extern uint32_t *sram0; 

#endif // SPIKEHW_H
