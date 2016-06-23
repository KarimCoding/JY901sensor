//
// Function that save the time output packet to a text file 
//
#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>

#include "wgdaytime.h"

using namespace std;

bool flag(false);
int i = 1;
unsigned char timeArray[11];
long double yearP;
long double monthP;
long double dayP;
long double hourP;
long double minuteP;
long double secondP;
long double msecondP;
long double timeP;

void timeOutput(unsigned char uc)
{
  if (uc==0x50 || flag==true) 
    {
      timeArray[0]=0x55; // first byte in the packet is always 0x55
      flag=true;
      timeArray[i]= int(uc);
      i++;
      if(i>10){
	flag=false;
	cout << "i = " << i <<" ||| " << ((long int)(gettimeofdayInMilliSeconds())) <<endl;
	int sum=0;
	std::fstream file;
	file.open("Time_Output.txt", std::fstream::app);
	
	//
	//Showing the decimal form
	//
	// for(i=0; i < 11 ; i++){
	//   file << int(angle[i]) << " " ;
	// }

	//
	//Calculating the Sum for the 10 bytes of the packet
	//
	for(i=0; i < 10 ; i++)
	  {
	    sum+=(int)(timeArray[i]);
	  }
	
	unsigned char sumC = sum;
	
	//
	//Testing the checkSUM
	//
	// file << endl ;
	// file << std::hex << int(angle[10]) << endl;
	// // file << sum << endl;
	// file << std::hex <<(int) sumC << endl;
	//  //	 file<< std::setw(2) << std::setfill('0') << std::hex << sum << endl;
	// if( int(sumC) == int(angle[10])){ file<<" correct " << endl;}
	// file.close();
	
	//
	//checking if the Sum is equal to the last byte of the package, if yes save it
	//
	if ( int(sumC) == int(timeArray[10]))
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
       
	    for(i=0; i < 11 ; i++)
	      {
		file << std::setw(2) << std::setfill('0')<< std::hex <<(int)(timeArray[i])<<" "; // writing the time packet
	      }
	    file << "       ";
	    file << std::dec <<  ((long int)gettimeofdayInMilliSeconds()) ; //writing the time of the pc in milliseconds
	    file << fixed << "   " << ((long double)(timeP))  ; // writing the time from the first packet 
	    file << fixed << "   " << ((long double)(timeP)) - ((long int)gettimeofdayInMilliSeconds()) << endl ; // the difference between the two times
	    
	    // file << std::dec << (int)(timeArray[2])<< " "<<(int)(timeArray[3])<<" "<<(int)(timeArray[4])<<" "<<(int)(timeArray[5])<<" "<<(int)(timeArray[6])<<" "<<(int)(timeArray[7])<<" "<<(int)(timeArray[8])<<" "<<(int)(timeArray[9])<< endl << endl ; // writing the packet in decimal
	  }
	file.close();
	i=1;
      }
    }
}
