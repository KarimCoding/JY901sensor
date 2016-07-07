//#include "dataPkt.h"
#include "consts.h"
#include "listener.h"

int main(){

	dataStick *buffer;
	wifi port1;
	unsigned char newBuff[MAXBUFLEN];
	int numbytes = port1.listener(buffer);
	printf("got data \n");
	buffer->getData(newBuff);
	newBuff[sizeof(newBuff)] = '\0';
		printf("%s ",newBuff);
	return 0;
}	//End brace for main
