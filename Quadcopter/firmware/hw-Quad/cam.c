
#include "cam.h"
#include "soc-hw.h"

//==================================================================

int buffercam[SIZE_BUFFCAM];
int l;

//==================================================================

void buffercam_clear()
{
	uint32_t i;
    for (i=0; i< SIZE_BUFFCAM;i++)
    	buffercam[i]=0;

}

//==================================================================

void buffercam_upload(uint32_t size)
{
	uint32_t i;
        for (i=0; i< size;i++)
    	    buffercam[i]=uart_getchar1();
}	

//==================================================================

void buffercam_uartsend(uint32_t size)
{
	uint32_t i;

    	for (i=1; i< size;i++){
				
		if (buffercam[i]==0x76 && buffercam[i+1]==0x00){
			i=i+5;
		} 
		
    		uart_putchar0(buffercam[i]);
	}
}

//==================================================================

void resetcommand(char c){

	buffercam_clear();

	uart_putchar1(COMMANDSEND);
	uart_putchar1(SERIALNUM);
	uart_putchar1(CMD_RESET);
	uart_putchar1(COMMANDEND);
	buffercam_upload(1);
//	buffercam_uartsend(71);
}

//==================================================================

void getversioncommand(char c)
{

	buffercam_clear();

	uart_putchar1(COMMANDSEND);
	uart_putchar1(SERIALNUM);
	uart_putchar1(CMD_GETVERSION);
	uart_putchar1(COMMANDEND);

	buffercam_upload(15);
	//buffercam_uartsend(15);
}

//==================================================================

//take_picture
void takephotocommand(char c)
{
	uint32_t x='0';	
	
	buffercam_clear();
        
	uart_putchar1(COMMANDSEND);
	uart_putchar1(SERIALNUM);
	uart_putchar1(CMD_TAKEPHOTO);
	uart_putchar1(CONS);	
	uart_putchar1(FBUF_STOPCURRENTFRAME);	

	buffercam_upload(5);
	//buffercam_uartsend(5);

//==================================================================
	
}
//read_size,,, confirmar si tomo la foto (buf[0]==0x76 && buf[2]==0x34)
//hay info importante XL,REVISAR

int getbufflencommand()
{
	uint32_t bytes,  x='0';	
	buffercam_clear();
	//uart1->rxtx;
	//msleep(30);        
	
	uart_putchar1(COMMANDSEND);
	uart_putchar1(SERIALNUM);
	uart_putchar1(CMD_GETBUFFLEN);
	uart_putchar1(CONS);	
	uart_putchar1(FBUF_CURRENTFRAME);	

	buffercam_upload(9);
	//buffercam_uartsend(9);
	
	bytes=buffercam[5];
	bytes=bytes<<8;	
	bytes=buffercam[6];
	bytes=bytes<<8;	
	bytes=buffercam[7];
	bytes=bytes<<8;	
	bytes=buffercam[8];
	bytes=bytes<<8;	

	return bytes;
        //uint32_t sizeX;
	//sizeX= (buffercam[7]<<8) +buffercam[8];
	
}

//==================================================================

//export_buf
void readphotocommand(int  bytes)
{
	uint32_t i,n;
	
int inc = 200;
int addr =0;
int chunk;

	buffercam_clear();	
	
	while( addr < bytes ){

		chunk = inc;
                if (chunk > (bytes-addr)) 
                  chunk = bytes-addr; 
		uart_putchar1(COMMANDSEND);
		uart_putchar1(SERIALNUM);
		uart_putchar1(CMD_READBUFF);
		uart_putchar1(CONS_1);	
		uart_putchar1(FBUF_CURRENTFRAME);	
		uart_putchar1(CONS_2);	
		uart_putchar1((addr >> 24) & 0xff);
		uart_putchar1((addr>>16) & 0xff);
		uart_putchar1((addr>>8 ) & 0xff);
		uart_putchar1(addr & 0xff);

		uart_putchar1((chunk >> 24) & 0xff);
		uart_putchar1((chunk>>16) & 0xff);
		uart_putchar1((chunk>>8 ) & 0xff);
		uart_putchar1(chunk & 0xff);

		uart_putchar1(CONS);
		uart_putchar1(ZERO);

		addr+=chunk;
		/*		
		for (i=0; i< 5;i++){
    	    		uart_getchar1();
		}
		*/
		
                buffercam_upload(chunk+6);
	        buffercam_uartsend(chunk+6);
	}
	
}

//==================================================================

void imagesize(char c)
{
	buffercam_clear();
	uart_putchar1(COMMANDSEND);
	uart_putchar1(SERIALNUM);
	uart_putchar1(WRITE_DATA);
	uart_putchar1(0X05);	
	uart_putchar1(0X04);	
	uart_putchar1(CONS);
	uart_putchar1(ZERO);
	uart_putchar1(0X19);	
	uart_putchar1(RESOLUTION);

	buffercam_upload(5);
	//buffercam_uartsend(5);

//==================================================================

}

/*
void takephotocommand(char c)
{
	uint32_t x='0';	

	uart_putchar1(COMMANDSEND);
	//msleep(5);
	uart_putchar1(SERIALNUM);
	//msleep(5);
	uart_putchar1(CMD_TAKEPHOTO);
	//msleep(5);
	uart_putchar1(CONS);	
	uart_putchar1(FBUF_STOPCURRENTFRAME);	
	//x=uart_getchar1();
	//uart_putchar0(uart_getchar1());
	//msleep(1000);
	
}
*/
void pppp()
{
// esta es mi version para la recepcion de lo que manda la camara; la funcion esta comentariada en el main
	/*	
	int32_t  *p;
	int32_t arreglo[30];
	int8_t start=0;
    	int32_t	size=29;
    	//int32_t	size_1=9;
	int8_t i=0;
	//int8_t j=0;
*/
	/*
	for (p = (int8_t *) start; p < (int8_t *) (start+size); p++)
	{
		*p = uart_getchar1();

	}
    	for (p = (int8_t *) start; p < (int8_t *) (start+size); p++)
	{
		uart_putchar0( *p );
	} 
*/

//msleep(1000);

/*
for (j =  start; j <  (start+size_1); j++)
	{

		for (i =  start; i <  (start+size); i++)
			{
		arreglo[j][i]=uart_getchar1();

			}
}
  

for (j =  start; j <  (start+size_1); j++)
	{
p = &arreglo[j][0];
		for (i =  start; i <  (start+size); i++)
			{
		uart_putchar0( *(p+i) );

			}
}


for (j =  start; j <  (start+size_1); j++)
	{
p = &arreglo[j][0];
		for (i =  start; i <  (start+size); i++)
			{
		arreglo[j][i]=0;

			}
}

*/

//msleep(1000);

//p = &arreglo[0]; 

		
	
}


















/*

uint8_t buffcam[5];

void uart_buff(uint8_t tam)
{
	uint8_t ind=0;

	while(ind<tam)
		buffcam[ind++]=uart_getchar1();
}

void debug_buff(uint8_t tam)
{
	uint8_t ind=0;

	while(ind<tam)
		uart_putchar0(buffcam[ind++]);
}

void ppcomm()
{
	buffcam[0]=31;
	buffcam[1]=32;
	buffcam[2]=33;
	buffcam[3]=34;
	buffcam[4]=35;
}

void getversioncommand(char c)
{
	
	
	uint32_t x = '3';
	uint32_t y = '5';
	x=uart_getuart_putchar1(COMMANDSEND);char0();
	uart_putchar1(x);
	y=uart_getchar1();
	uart_putchar0(y);
	
	
	uart_putchar0(buffcam[0]);
	uart_putchar0(buffcam[1]);
	uart_putchar0(buffcam[2]);
	uart_putchar0(buffcam[3]);
	uart_putchar0(buffcam[4]);
	uart_putchar0(buffcam[5]);
	

	uart_putchar1(COMMANDSEND);
	uart_putchar1(SERIALNUM);
	uart_putchar1(CMD_GETVERSION);
	uart_putchar1(COMMANDEND);

	uart_buff(17);
	debug_buff(17);

}*/
