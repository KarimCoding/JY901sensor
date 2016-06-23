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
#include <string> 

#include "checkPacket.h"
#include "checkHeader.h"
#include "checkHeader2.h"
#include "checkSum.h"
#include "savePacket.h"
#include "timeOutput.h"


using namespace std;

bool resultCheck;
bool resultHeader;
bool resultHeader2;
int packetArrayNumb = 22;
unsigned char sumCAC;

void packetIdentifier22 (unsigned char uc, string port, unsigned char saveArray[],unsigned char packetArray[],int i )
{
  bool flagon(true);
  packetArray[i]= uc;
  
  resultCheck =  checkPacket(packetArray,i,port); // calling a function that checks if the input byte is a ptential header of a packet 
 
  if(resultCheck == true)
    {
     
      int k=0;
      int l=0;
      bool flagContinue = true;
      bool flagCont = true;
      int pp =2;

      while( flagContinue == true )
	{
	  if((i-pp)<0 && flagon==true) // if the index of the packet's byte is less than 0 take from the end of the array because it is a circular array 
	    {
	      while( flagCont == true ){
		saveArray[k]=packetArray[(packetArrayNumb-1)-l];
		k=k+1;
		resultHeader = checkHeader( packetArray, l); // call a function that retuen true when it detect a potential header of a packet
		if ( resultHeader == true)
		  {
		    flagCont = false;
		    flagContinue=false;
		  }
		l=l+1;
	      }
	      
	      flagon=false;
	    }
	  
	  else if ((i-pp)>=0) // if the index of the packet's byte is greater or equal to 0  
	    {
	      saveArray[k]=packetArray[i-pp];
	      k=k+1;
	      resultHeader2 = checkHeader2( packetArray, i, pp);// call a function that retuen true when it detect a potential header of a packet
	      if ( resultHeader2 == true)
		{
		  flagContinue = false;
		}     
	      pp=pp+1;
	    }
	}
      //
      // save the packet in the right order
      //
      unsigned char temp;
      for (int i = 0; i < (k)/2; i++) 
	{
	  temp = saveArray[(k)-i-1];
	  saveArray[(k)-i-1] = saveArray[i];
	  
	  saveArray[i] = temp;
	}
    
      sumCAC = checkSum(saveArray, k); // call a function that calculate the checkSum
     
      savePacket( sumCAC, saveArray, k,port); // If the checkSum is right save it to a file

      timeOutput(saveArray);
      
    }
}



