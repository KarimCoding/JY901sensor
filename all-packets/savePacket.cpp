//
//this function check if the checkSum is correct and save the packet to the file
//

#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <iterator>

using namespace std;

int numberOfBytes = 11;

void savePacket(unsigned char sumCAC,unsigned char saveArray[])
{
  std::fstream file; // for saving the data on a file
  file.open("test.txt", std::fstream::app); // open the file that you want to save data in it
  if ( int(sumCAC) == int(saveArray[(numberOfBytes-1)]))
    {
      for(int x=0; x <numberOfBytes ; x++)
	{
	  file << std::setw(2) << std::setfill('0')<< std::hex <<(int)(saveArray[x])<<" ";
	}
      file << "       " ;
    }
  
  file<<endl;
  file.close();
}
