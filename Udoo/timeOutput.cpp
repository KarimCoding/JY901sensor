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

#include "wgdaytime.h"

using namespace std;

bool flag(false);
int iTime = 0;
unsigned char timeArray[11];
long double yearP;
long double monthP;
long double dayP;
long double hourP;
long double minuteP;
long double secondP;
long double msecondP;
long double timeP;

void timeOutput(unsigned char timeArray[], FILE *&outF)
{
	    //converting into milliseconds 
	    yearP= ((int)(timeArray[2]))*31540000000;
	    monthP= ((int)(timeArray[3]))*2628000000;
	    dayP= ((int)(timeArray[4]))*86400000;
	    hourP= ((int)(timeArray[5]))*3600000;
	    minuteP= ((int)(timeArray[6]))*60000;
	    secondP= ((int)(timeArray[7]))*1000;
	    msecondP= ((int)(((int)(timeArray[9])) << 8)) + ((int)(timeArray[8]));
	    timeP = yearP + monthP + dayP + hourP + minuteP + secondP + msecondP; // adding the time together, all in milliseconds
       
	    for(iTime=0; iTime < 11 ; iTime++)
        {
	     fprintf(outF,"%02x ",timeArray[iTime]); 
        }
        fprintf(outF,"       %d",((long int)gettimeofdayInMilliSeconds()));
        fprintf(outF,"    %f",((long double)(timeP)) );
        fprintf(outF,"    %f\n", ((long double)(timeP)) - ((long int)gettimeofdayInMilliSeconds()));
	iTime=1;
}
