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

using namespace std;

#define NUMBER_OF_PACKETSSS2 9
unsigned char packet_headerss2 [NUMBER_OF_PACKETSSS2][2]={ {0x55,0x50},{0x55,0x51},{0x55,0x52},{0x55,0x53},{0x55,0x54},{0x55,0x55},{0x55,0x56},{0x55,0x57},{0x55,0x58} };
extern int packetArrayNumb;


bool checkHeader2(unsigned char packetArray[], int i, int pp)
{
  bool flagCheck = true;
  for (int j=0; j<NUMBER_OF_PACKETSSS2; j++ ) {
   
    if ( (packetArray[i-pp]==packet_headerss2[j][0]) && (packetArray[i-(pp-1)]==packet_headerss2[j][1])&& flagCheck==true )
      {
	//	cout<< "   "<<std::setw(2) << std::setfill('0')<< std::hex <<(int)(packet_header[0][1])<<"     ";
	return true;
	flagCheck = false;
      }
  }

  return false;
}
