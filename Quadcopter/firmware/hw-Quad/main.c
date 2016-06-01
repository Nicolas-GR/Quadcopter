#include "soc-hw.h"

#include "cam.h"

int buffertec[SIZE_BUFFTEC];
void buffertec_upload(uint32_t size);
//void buffertec_uartsend(uint32_t size);
void buffertec_clear();


int main()
{
	char t;
	msleep(100);
	init_wifi();
	for(;;){
		t='\0';
		while(t =='\n' || t =='\r'|| t == ' '  || t == '\0' || t =='\v'|| t == 10 || t == 13){
			t = wifi_getchar();
			sttc();
		}
		switch (t)
		{
		case 'u':
			up();
			break;

		case 'd':
			down();
			break;

		case 'r':
			right();
			break;

		case 'l':
			left();
			break;

		case 'f':
			forward();
			break;

		case 'b':
			backward();
			break;

		default:
			sttc();
		}
	}

}
