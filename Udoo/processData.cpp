
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
using namespace std;
//void handleData(dataStick pkt, std::ofstream& outF, std::ofstream& badData){
void handleData(dataStick pkt, char *fName){	
	unsigned char data[MAXBUFLEN];
	char ip_addr[4];
	char time[35];
	int numbytes = pkt.numbytes;
	pkt.getData(data,ip_addr,time);
	unsigned char uc;
	printf("%s \n",data);
	for(int ind = 0;ind < numbytes;ind++)
	{
		uc = data[ind];
		//packetIdentifier2(uc,std::ref(outF),VERBOSITY,std::ref(badData));
		packetIdentifier2(uc,VERBOSITY,fName);

	}
}	//End brace for handle
