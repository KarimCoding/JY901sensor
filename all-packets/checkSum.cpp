//
// Function that calculate the checkSum of the packets 
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


unsigned char checkSum( unsigned char saveArray[])
{
  int sumAC=0;
  for(int xx=0; xx < 10 ; xx++)
    {
      sumAC += (int)(saveArray[xx]);
    }
      
  unsigned char sumCAC = sumAC;
  return sumCAC;
}
