
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "packetIdentifier2.h"
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>
#include "dataPkt.h"
#include "consts.h"
#include <string>
#include "processData.h"
#include <vector>
#include <memory>

using namespace std;


void handleData(std::vector<dataStick>& buf,std::vector<string> &goodData,std::vector<string> &badData)
{
	unsigned char data[MAXBUFLEN];
	unsigned char uc;

	std::string header;
	std::string writeBuff;
	
	header = buf.front().getHeader();
    memcpy(data, buf.front().dat.info,buf.front().numbytes);
	writeBuff = header + "\n";
//this commented block will store raw data to badData to save 

    char printStr[999];
    string buff;
	header = header + "\n";
	buff = header;
	printf("\n");
    for(int x=0; x <buf.front().dat.numbytes ; x++)
    {
        printf("%02x ",data[x]);
		sprintf(printStr,"%02x ",data[x]);
        buff=buff + string(printStr);
        if(x>0&&x%11==0)
        	buff = buff+ "\n";
    }
//    badData.push_back(buff);
	goodData.push_back(buff);

	for(int ind = 0;ind <buf.front().dat.numbytes ;ind++)
	{
		uc = data[ind];
		packetIdentifier2(std::ref(uc),std::ref(goodData),std::ref(badData),std::ref(writeBuff),header);
	}
	goodData.push_back(writeBuff);
}	//End brace for handle


