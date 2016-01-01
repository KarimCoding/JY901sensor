//
//this function check if the checkSum is correct and save the packet to the file
//

//#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <iterator>
#include <stdio.h>
#include "consts.h"
using namespace std;

int numberOfBytes = 11;

void savePacket(unsigned char saveArray[], std::ofstream& outF)
//void savePacket(unsigned char saveArray[],bool verbosity,char *fName)
{
/*	ofstream outF;
	outF.open(fName, std::ofstream::out | std::ofstream::app);
*/
	char printStr[999];
        for(int x=0; x <numberOfBytes ; x++)
    	{
				printf("%02x ",saveArray[x]);
				sprintf(printStr,"%02x ",saveArray[x]);
				outF<<printStr;
		
    	}
		outF<<printStr;
		if(saveArray[1] ==0x51 && VERBOSITY)
			sprintf(printStr,"\t20%d/%d/%d  %02d:%02d:%02d:%03d\n",(int)(saveArray[2]),(int)(saveArray[3]),(int)saveArray[4],(int)saveArray[5],(int)saveArray[6],(int)saveArray[7],(saveArray[9]<<8)|saveArray[8]); 

        else if(saveArray[1] ==0x55 && VERBOSITY) {
			double roll;
			double pitch;
			double yaw;
			double temperature;

	        roll = (  (((int)(saveArray[3])) << 8) + ((int)(saveArray[2])) ) / 32768.0 * 180.0 ;
    	    pitch = (  (((int)(saveArray[5])) << 8) + ((int)(saveArray[4])) ) / 32768.0 * 180.0 ;
        	yaw = (  (((int)(saveArray[7])) << 8) + ((int)(saveArray[6])) ) / 32768.0 * 180.0 ;
        	temperature = (  (((int)(saveArray[9])) << 8) + ((int)(saveArray[8])) ) /100.0 ;
	        sprintf(printStr,"\troll is: %f pitch is: %f yaw is: %f temperature is: %f\n",((long double)(roll)),((long double)(pitch)),((long double)(yaw)),((long double)(temperature)));

		}
		else
        	sprintf(printStr,"\n");
		printf("Save dat: %s \n",printStr);
		outF<<printStr;
//		outF.close();
}


//void write_bad_dat(std::ofstream& badData, unsigned char uc)
void write_bad_dat(unsigned char uc)
{
	ofstream badData;
	badData.open("/home/udooer/Logs/badData.txt", std::ofstream::out | std::ofstream::app);
  badData << uc<<" "<<endl;

  badData.close();
}

void write_bad_dat(unsigned char saveArray[])
{
//check if a stream is open. if so close it and open for bad data
ofstream badData;
    badData.open("/home/udooer/Logs/badData.txt", std::ofstream::out | std::ofstream::app);
    char printStr[999];
        for(int x=0; x <numberOfBytes ; x++)
        {
                sprintf(printStr,"%02x ",(int)saveArray[x]);
        
        }
	badData << printStr<<"\n";

  	badData.close();


}
