//
// Function that identify the packets 
//

#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>
#include <algorithm>    // std::reverse
#include <iterator>

#include "checkPacket.h"
#include "checkSum.h"
#include "savePacket.h"

using namespace std;

#define NUMBER_OF_BYTES 11

int i=0;
int pp = NUMBER_OF_BYTES + 2;
bool resultCheck;
unsigned char saveArray[22]; // an array to save the packets in it
unsigned char packetArray[22]; // an array to get the bytes coming from the sensor
unsigned char sumCAC;

void packetIdentifier2 (unsigned char uc)
{
  
  bool flagon(true); 
  packetArray[i]= uc; // push the bytes coming from the sensor into the packetArray
  resultCheck =  checkPacket(packetArray,i); // call the function "checkPacket" which check for the packet's header
  
  if(resultCheck == true)   
    {
       cout<<" yes "<<endl; // for debugging
      int k=10; // because we are saving the bytes that are before the next packet's header we start from k=10 to be able to save the first value in saveArray[10] 
      int  lk=k;
      for(int p=2;p<pp;p++) // loop is 11 because we have 11 bytes 
	{
	  if((i-p)<0 && flagon==true) // if the bytes before the packet's header are less than 11 it takes from the end of the array because it is a circular array
	    {
	      for(int l=0;l<lk+1;l++)
		{
		  saveArray[k]=packetArray[21-l];
		  k=k-1;
		}
	      flagon=false;
	    }
	  else if ((i-p)>=0) 
	    {
	      saveArray[k]=packetArray[i-p];
	      k=k-1;
	      lk=k;
	    }
	}
      //
      // performing a check Sum
      //
      sumCAC = checkSum(saveArray);
      //
      //if the checkSum is correct save the packet
      //
      savePacket(sumCAC, saveArray);
    }
  i=(i+1)%22;
}



