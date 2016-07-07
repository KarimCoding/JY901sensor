
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include "packetIdentifier2.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>
#include "dataPkt.h"
#include "consts.h"
#include "processData.h"

void handleData(dataStick pkt, char fileName[30], FILE *output){
	

	unsigned char data[MAXBUFLEN];
	FILE *badD;
	char ip_addr[4];
	char time[35];
	pkt.getData(data,ip_addr,time);
	unsigned char uc;
	output=fopen(fileName,"a+");
	for(int ind = 0;ind < (pkt.numbytes);ind++)
	{
		uc = data[ind];
		packetIdentifier2(uc,output,badD,VERBOSITY);
	}


}	//End brace for handle
