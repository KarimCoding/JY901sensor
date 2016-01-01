
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
#include <string>
#include "processData.h"
#include <vector>
#include <memory>

using namespace std;


void handleData(std::vector<dataStick>& buf,std::vector<string> &goodData,std::vector<string> &badData)
{
	unsigned char data[MAXBUFLEN];
	std::string header;
	header = buf.front().getHeader();
	goodData.push_back(header);
	//badData.push_back(header); 
    memcpy(data, buf.front().dat.info,buf.front().numbytes);

/*    char printStr[999];
    string buff;
        for(int x=0; x <buf.front().numbytes ; x++)
        {
//                printf("%02x ",array[x]);
                sprintf(printStr,"%02x ",data[x]);
                buff=buff + string(printStr);
        }
		buff = buff + "\n";
		goodData.push_back(buff);
*/

	unsigned char uc;
	for(int ind = 0;ind <MAXBUFLEN;ind++)
	{
		uc = data[ind];
		packetIdentifier2(std::ref(uc),std::ref(goodData),std::ref(badData),std::ref(header));
	}

}	//End brace for handle
