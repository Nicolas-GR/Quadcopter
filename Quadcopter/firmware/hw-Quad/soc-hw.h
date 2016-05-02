#ifndef SPIKEHW_H
#define SPIKEHW_H

#define PROMSTART 0x00000000
#define RAMSTART  0x00000800
#define RAMSIZE   0x400
#define RAMEND    (RAMSTART + RAMSIZE)

#define RAM_START 0x40000000
#define RAM_SIZE  0x04000000

#define FCPU      100000000

#define UART_RXBUFSIZE 32


/****************************************************************************
 * Types
 */
typedef unsigned int  uint32_t;    // 32 Bit
typedef signed   int   int32_t;    // 32 Bit

typedef unsigned char  uint8_t;    // 8 Bit
typedef signed   char   int8_t;    // 8 Bit

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

void msleep(uint32_t msec);
void nsleep(uint32_t nsec);

void prueba();
void tic_init();


/***************************************************************************
 * GPIO0
 */
typedef struct {
	volatile uint32_t ctrl;
	volatile uint32_t dummy1;
	volatile uint32_t dummy2;
	volatile uint32_t dummy3;
	volatile uint32_t in;
	volatile uint32_t out;
	volatile uint32_t oe;
} gpio_t;

/***************************************************************************
 * UART
 */
#define UART_DR   0x01                    // RX Data Ready
#define UART_ERR  0x02                    // RX Error
#define UART_BUSY 0x10                    // TX Busy

typedef struct {
   volatile uint32_t ucr;
   volatile uint32_t rxtx;
} uart_t;

void uart_init();
void uart_putchar0(char c);
void uart_putstr0(char *str);
char uart_getchar0();

void uart_putstr1(char *str);
void uart_putchar1(char c);
char uart_getchar1();

void uart_putstr2(char *str);
void uart_putchar2(char c);
char uart_getchar2();

/***************************************************************************
 * SPI0
 */
#define SPI_RUN   0x01                    //RUN SPI

typedef struct {
   volatile uint32_t rxtx;
   volatile uint32_t status;
   volatile uint32_t cs;
   volatile uint32_t nop;
   volatile uint32_t divisor;
} spi_t;

void spi_init();
void spi_putchar(char c);
char spi_getchar();
char spi_putget(char c);

/***************************************************************************
 * KEY0
 */
typedef struct {
	volatile uint32_t code;
	volatile uint32_t key_av;
} key_t;

uint32_t read_number();

/***************************************************************************
 * lcd0
 */
typedef struct {
	volatile uint32_t in_lcd;
	volatile uint32_t RS;
} lcd_t;

void lcd_putchar(char c);

/***************************************************************************
 * Pointer to actual components
 */
extern timer_t  *timer0;
extern uart_t   *uart0;
extern uart_t   *uart1; 
extern key_t	*key0;
extern gpio_t   *gpio0;
extern lcd_t	*lcd0;
extern uart_t   *uart2; 
extern uint32_t *sram0; 

//buffer teclado 

#define SIZE_BUFFTEC 60
extern int buffertec[SIZE_BUFFTEC];

#endif // SPIKEHW_H
