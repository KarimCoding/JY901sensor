//
//this function check if the checkSum is correct and save the packet to the file
//

//#include <SerialStream.h>
#include "savePacket.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <iterator>
#include <stdio.h>
#include "consts.h"

int numberOfBytes = 11;

void savePacket(saveStruct &save,std::string &buf)
{
    char printStr[999];
    for(int x=0; x <numberOfBytes ; x++)
    {
    	sprintf(printStr,"%02x ",save.data[x]);
        buf=buf + string(printStr);
    }

	if(save.data[1] ==0x50 && VERBOSITY)
	{
		sprintf(printStr,"\t20%d/%d/%d  %02d:%02d:%02d:%03d",(int)(save.data[2]),(int)(save.data[3]),(int)save.data[4],(int)save.data[5],(int)save.data[6],(int)save.data[7],(save.data[9]<<8)|save.data[8]); 
		buf=buf + string(printStr);
	}
    else if(save.data[1] ==0x53 && VERBOSITY) 
	{
		double roll;
		double pitch;
		double yaw;
		double temperature;

	    roll = (  (((int)(save.data[3])) << 8) + ((int)(save.data[2])) ) / 32768.0 * 180.0 ;
        pitch = (  (((int)(save.data[5])) << 8) + ((int)(save.data[4])) ) / 32768.0 * 180.0 ;
       	yaw = (  (((int)(save.data[7])) << 8) + ((int)(save.data[6])) ) / 32768.0 * 180.0 ;
       	temperature = (  (((int)(save.data[9])) << 8) + ((int)(save.data[8])) ) /100.0 ;
	    sprintf(printStr,"\troll is: %f pitch is: %f yaw is: %f temperature is: %f",((double)(roll)),((double)(pitch)),((double)(yaw)),((double)(temperature)));
		buf=buf + string(printStr);
	}
	else
	{}
	buf = buf + "\n";
}



void savePacket(bool check,saveStruct &save,std::vector<string> &data)
{
    char printStr[999];
    string buf;
	buf="****";
    for(int x=0; x <numberOfBytes ; x++)
    {
    	sprintf(printStr,"%02x ",save.data[x]);
    	buf=buf + string(printStr);
    }
	buf = buf + "****";
	data.push_back(buf);
}



void write_bad_dat(saveStruct &save,std::vector<string> &data,std::string &buf,unsigned char sum)
{
	char printStr[999];
	savePacket(std::ref(save),std::ref(buf));
    sprintf(printStr,"%02x\n",sum);
    buf = buf+ "checksum should be: " + string(printStr);
//    cout<<buf;
    data.push_back(buf);
}

