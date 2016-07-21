
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
#include <vector>
#include <memory>

using namespace std;


void handleData(std::vector<dataStick>& buf,std::vector<string> &goodData,std::vector<string> &badData){
	unsigned char data[MAXBUFLEN];
	std::string header;
//	buf.front().pkt.getData(header);
//	cout<<"header: "<<header<<"\n";
    memcpy(data, buf.front().dat.info,buf.front().numbytes);
 /*   printf("from process data data: %d \n",sizeof(data));
    for(int i = 0;i<sizeof(data);i++)
	{
	    printf("%02x ",data[i]);
        if(i>0&&i%12==0)
        	printf("\n");
	}
*/
	unsigned char uc;
	
	for(int ind = 0;ind <MAXBUFLEN;ind++)
	{
		uc = data[ind];
		packetIdentifier2(std::ref(uc),std::ref(goodData),std::ref(badData));
	//	packetIdentifier2(data[ind],std::ref(outF),std::ref(badD));

	}
}	//End brace for handle
