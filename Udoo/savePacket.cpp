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

using namespace std;

int numberOfBytes = 11;

void savePacket(unsigned char saveArray[], FILE *&outF)
{
        for(int x=0; x <numberOfBytes ; x++)
    	{
	        fprintf(outF,"%02x ",(int)saveArray[x]);
    	}
        fprintf(outF,"\n");
}
