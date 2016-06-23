//
// Function that check if the packet header is right and send True 
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

bool checkPacket(unsigned char packetArray[], int i, string port)
{
  bool flagCheck = true;
  for (int j=0; j<NUMBER_OF_PACKETS; j++ ) {
    if ( (packetArray[i]==packet_header[j][1]) && (packetArray[i-1]==packet_header[j][0])&& flagCheck==true )
      {
	return true;
	flagCheck = false;
      }
  }

  return false;
}
