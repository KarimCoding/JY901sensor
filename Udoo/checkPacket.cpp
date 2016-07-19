//
// Function that check if the packet header is right and send True 
//

//#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>

using namespace std;

#define NUMBER_OF_PACKETS 9
unsigned char packet_header [NUMBER_OF_PACKETS][2]={ {0x55,0x50},{0x55,0x51},{0x55,0x52},{0x55,0x53},{0x55,0x54},{0x55,0x55},{0x55,0x56},{0x55,0x57},{0x55,0x58} };

bool checkPacket(unsigned char packetArray[], int i)
{
//	printf("check packet i: %d \n ",i);
  bool flagCheck = true;
  for (int j=0; j<NUMBER_OF_PACKETS; j++ ) {
   
    if ( (packetArray[i]==packet_header[j][1]) && (packetArray[i-1]==packet_header[j][0])&& flagCheck==true )
      {
	//	cout<< "   "<<std::setw(2) << std::setfill('0')<< std::hex <<(int)(packet_header[0][1])<<"     ";
//    printf("%02x %02x \n",packetArray[i-1], packetArray[i]);
	return true;
	flagCheck = false;
      }
  }

  return false;
}
