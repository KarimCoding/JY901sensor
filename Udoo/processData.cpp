
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
void handleData(dataStick& pkt,std::ofstream& outF, std::ofstream& badD){
//void handleData(dataStick pkt, std::ofstream& outF,bool VERBOSITY, std::ofstream& badData){
//void handleData(dataStick pkt, char *fName){	
//    ofstream outF;
//    outF.open(fName, std::ofstream::out | std::ofstream::app);

	unsigned char data[MAXBUFLEN];
	char ip_addr[4];
	char times[35];
	int numbytes = pkt.numbytes;
	pkt.getData(data,ip_addr,times);
	unsigned char uc;
	printf("Handle Dat: %s \n",data);
	outF<<"Data from "<<ip_addr<<" @ "<<times<<endl;
	for(int ind = 0;ind < numbytes;ind++)
	{
		uc = data[ind];
		packetIdentifier2(uc,std::ref(outF),std::ref(badD));
		//packetIdentifier2(uc,VERBOSITY,fName);

	}
}	//End brace for handle
