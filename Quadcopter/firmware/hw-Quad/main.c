#include "soc-hw.h"

#include "cam.h"

int buffertec[SIZE_BUFFTEC];
void buffertec_upload(uint32_t size);
//void buffertec_uartsend(uint32_t size);
void buffertec_clear();


int main()
{
 int t;
for(;;){
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
