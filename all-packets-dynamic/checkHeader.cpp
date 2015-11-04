//
// Function that check if the packet header is right and send True when the i-2(i is the index for the second header example 0x50,0x51..., i-1 is the first header which is in our case 0x50 so i-2 is the last byte in the previous packet) is less than 0
//

#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>

using namespace std;

using namespace std;

#define NUMBER_OF_PACKETSSS 9
unsigned char packet_headerss [NUMBER_OF_PACKETSSS][2]={ {0x55,0x50},{0x55,0x51},{0x55,0x52},{0x55,0x53},{0x55,0x54},{0x55,0x55},{0x55,0x56},{0x55,0x57},{0x55,0x58} };
extern int packetArrayNumb;

bool checkHeader(unsigned char packetArray[], int l)
{
  bool flagCheck = true;
  for (int j=0; j<NUMBER_OF_PACKETSSS; j++ ) {
   
    if ( (packetArray[(packetArrayNumb-1)-l]==packet_headerss[j][0]) && (packetArray[(packetArrayNumb-1)-(l-1)]==packet_headerss[j][1])&& flagCheck==true )
      {
	//	cout<< "   "<<std::setw(2) << std::setfill('0')<< std::hex <<(int)(packet_header[0][1])<<"     ";
	return true;
	flagCheck = false;
      }
  }

  return false;
}
