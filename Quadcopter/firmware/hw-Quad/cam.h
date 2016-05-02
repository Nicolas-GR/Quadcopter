/***************************************************************************
 * CAMERA
 */

#ifndef CAM_H
#define CAM_H

//Page 1:Command   CAMARA
#define SERIALNUM  0

#define CONS 0x01
#define CONS_1 0x0C
#define CONS_2 0x0A

#define COMMANDSEND 0x56
#define COMMANDREPLY  0x76
#define COMMANDEND  0x00
#define ZERO 0X00

#define CMD_GETVERSION  0x11
#define RESOLUTION  0X22
#define CMD_RESET  0x26
#define CMD_TAKEPHOTO  0x36
#define WRITE_DATA  0X31
#define CMD_READBUFF  0x32
#define CMD_GETBUFFLEN 0x34

#define FBUF_CURRENTFRAME 0x00
#define FBUF_NEXTFRAME 0x01

#define FBUF_STOPCURRENTFRAME 0x00

#define RAM_START 0x40000000
#define RAM_SIZE  0x04000000


#define SIZE_BUFFCAM 256 //16x16
extern int buffercam[SIZE_BUFFCAM];


void getversioncommand(char c); 
void resetcommand(char c);
void takephotocommand(char c); 
int getbufflencommand();
void readphotocommand(int bytes);
void imagesize(char c);
void pppp();






#endif

