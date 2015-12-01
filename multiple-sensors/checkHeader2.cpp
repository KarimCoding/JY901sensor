//
//  Function that check if the packet header is right and send True when the i-2(i is the index for the second header example 0x50,0x51..., i-1 is the first header which is in our case 0x50 so i-2 is the last byte in the previous packet) is greater or equeal to 0 
//

#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>

#include "globals.h"

using namespace std;
extern int packetArrayNumb;


bool checkHeader2(unsigned char packetArray[], int i, int pp)
{
  bool flagCheck = true;
  for (int j=0; j<NUMBER_OF_PACKETS; j++ ) {
   
    if ( (packetArray[i-pp]==packet_header[j][0]) && (packetArray[i-(pp-1)]==packet_header[j][1])&& flagCheck==true )
      {
	return true;
	flagCheck = false;
      }
  }

  return false;
}
