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

void savePacket(unsigned char saveArray[],std::vector<string> &data)
{
    char printStr[999];
    string buf;
        for(int x=0; x <numberOfBytes ; x++)
        {
//                printf("%02x ",array[x]);
                sprintf(printStr,"%02x ",saveArray[x]);
                buf=buf + string(printStr);
        }

		if(saveArray[1] ==0x50 && VERBOSITY){
			sprintf(printStr,"\t20%d/%d/%d  %02d:%02d:%02d:%03d",(int)(saveArray[2]),(int)(saveArray[3]),(int)saveArray[4],(int)saveArray[5],(int)saveArray[6],(int)saveArray[7],(saveArray[9]<<8)|saveArray[8]); 
			buf=buf + string(printStr);
		}
        else if(saveArray[1] ==0x53 && VERBOSITY) {
			double roll;
			double pitch;
			double yaw;
			double temperature;

	        roll = (  (((int)(saveArray[3])) << 8) + ((int)(saveArray[2])) ) / 32768.0 * 180.0 ;
    	    pitch = (  (((int)(saveArray[5])) << 8) + ((int)(saveArray[4])) ) / 32768.0 * 180.0 ;
        	yaw = (  (((int)(saveArray[7])) << 8) + ((int)(saveArray[6])) ) / 32768.0 * 180.0 ;
        	temperature = (  (((int)(saveArray[9])) << 8) + ((int)(saveArray[8])) ) /100.0 ;
	        sprintf(printStr,"\troll is: %f pitch is: %f yaw is: %f temperature is: %f",((long double)(roll)),((long double)(pitch)),((long double)(yaw)),((long double)(temperature)));
//			outF<<printStr;
			buf=buf + string(printStr);
		}
		else
		{}
//			sprintf(printStr,"\n");
//			buf=buf + string(printStr);

//        cout<<buf<<"\n";
        data.push_back(buf); 
}


/*//void write_bad_dat(std::ofstream& badData, unsigned char uc)
void write_bad_dat(unsigned char uc)
{
	ofstream badData;
	badData.open("/home/udooer/Logs/badData.txt", std::ofstream::out | std::ofstream::app);
  badData << uc<<" "<<endl;

  badData.close();
}
*/
void write_bad_dat(unsigned char array[],std::vector<string> &data)
//void write_bad_dat(unsigned char saveArray[])
{
//check if a stream is open. if so close it and open for bad data
//    printf("write bad data\n");
	printf("Write bad data \n");
    char printStr[999];
	string buf;
        for(int x=0; x <numberOfBytes ; x++)
        {
                sprintf(printStr,"%02x ",array[x]);
                buf=buf + string(printStr);
        }
		buf= buf + "\n";
//		cout<<buf;
  		data.push_back(buf);   
//		cout<<data.front();

}
