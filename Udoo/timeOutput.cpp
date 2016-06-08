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

void timeOutput(unsigned char sumCAC,unsigned char timeArray[], FILE *outF)
{
//	  std::fstream file; // for saving the data on a file
//	  file.open(fileName, std::fstream::app); // open the file that you want to save data in it
	//
	//checking if the Sum is equal to the last byte of the package, if yes save it
	//
	if ( int(sumCAC) == int(timeArray[10]))
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
//		file << std::setw(2) << std::setfill('0')<< std::hex <<(int)(timeArray[iTime])<<" "; // writing the time packet
	        fprintf(outF,"%02x ",timeArray[iTime]); 
         }
        fprintf(outF,"       %d",((long int)gettimeofdayInMilliSeconds()));
        fprintf(outF,"    %f",((long double)(timeP)) );
        fprintf(outF,"    %f\n", ((long double)(timeP)) - ((long int)gettimeofdayInMilliSeconds()));
/*	    file << "       ";
	    file << std::dec <<  ((long int)gettimeofdayInMilliSeconds()) ; //writing the time of the pc in milliseconds
	    file << fixed << "   " << ((long double)(timeP))  ; // writing the time from the first packet 
	    file << fixed << "   " << ((long double)(timeP)) - ((long int)gettimeofdayInMilliSeconds()) << endl ; // the difference between the two times
*/	    
	    // file << std::dec << (int)(timeArray[2])<< " "<<(int)(timeArray[3])<<" "<<(int)(timeArray[4])<<" "<<(int)(timeArray[5])<<" "<<(int)(timeArray[6])<<" "<<(int)(timeArray[7])<<" "<<(int)(timeArray[8])<<" "<<(int)(timeArray[9])<< endl << endl ; // writing the packet in decimal
	  }
//	file.close();
	iTime=1;
      }
