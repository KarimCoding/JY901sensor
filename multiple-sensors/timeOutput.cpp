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

long double yearP;
long double monthP;
long double dayP;
long double hourP;
long double minuteP;
long double secondP;
long double msecondP;
long double timeP;

void timeOutput(unsigned char saveArray[])
{
  if ( saveArray[1] == 0x50)
    {
      std::fstream file; // for saving the data on a file
      file.open("test.txt", std::fstream::app); // open the file that you want to save data in it
      //converting into milliseconds
  
      yearP= ((int)(saveArray[2]))*31540000000;
      monthP= ((int)(saveArray[3]))*2628000000;
      dayP= ((int)(saveArray[4]))*86400000;
      hourP= ((int)(saveArray[5]))*3600000;
      minuteP= ((int)(saveArray[6]))*60000;
      secondP= ((int)(saveArray[7]))*1000;
      msecondP= ((int)(((int)(saveArray[9])) << 8)) + ((int)(saveArray[8]));
      timeP = yearP + monthP + dayP + hourP + minuteP + secondP + msecondP; // adding the time together, all in milliseconds
      
      file << "***";
      file << std::dec <<  ((long int)gettimeofdayInMilliSeconds()) ; //writing the time of the pc in milliseconds
      file << fixed << "   " << ((long double)(timeP))  ; // writing the time from the first packet 
      file << fixed << "   " << ((long double)(timeP)) - ((long int)gettimeofdayInMilliSeconds()) << endl ; // the difference between the two times
      
file.close();
    }
  
}
