
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
void handleData(dataStick &pkt,std::ofstream& outF, std::ofstream& badD){
//void handleData(dataStick pkt, std::ofstream& outF,bool VERBOSITY, std::ofstream& badData){
//void handleData(dataStick pkt, char *fName){	
//    ofstream outF;
//    outF.open(fName, std::ofstream::out | std::ofstream::app);
//printf("process data \n ");
	unsigned char data[MAXBUFLEN];
	char addr[14];
	char times[15];
	int numbytes = pkt.numbytes;
	pkt.getData(data,addr,times);

/*	printf("\n \n handldata: \n\n");
    for(int i = 0;i<MAXBUFLEN;i++){
            printf("%02x ",data[i]);
        if(i>0&&i%12==0)
            printf("\n");
        }

*/

	unsigned char uc;
	outF<<"Data from "<<addr<<" @ "<<times<<endl;
	for(int ind = 0;ind <MAXBUFLEN;ind++)
	{
		uc = data[ind];
//		packetIdentifier2(uc,std::ref(outF),std::ref(badD));
		packetIdentifier2(data[ind],std::ref(outF),std::ref(badD));

//		printf("%02x ",uc);
		//packetIdentifier2(uc,VERBOSITY,fName);

	}
}	//End brace for handle
