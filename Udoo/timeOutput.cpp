//
// Function that save the time output packet to a text file 
//
//#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>

#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

bool flag(false);
int iTime = 0;
unsigned char timeArray[11];
void timeOutput(unsigned char timeArray[], FILE *&outF)
{

	    for(iTime=0; iTime < 11 ; iTime++)
        {
	     fprintf(outF,"%02x ",timeArray[iTime]); 
        }

		fprintf(outF,"		20%d/%d/%d	%02d:%02d:%02d:%03d\n",(int)(timeArray[2]),(int)(timeArray[3]),(int)timeArray[4],(int)timeArray[5],(int)timeArray[6],(int)timeArray[7],(timeArray[9]<<8)|timeArray[8]); 


	iTime=1;
}

