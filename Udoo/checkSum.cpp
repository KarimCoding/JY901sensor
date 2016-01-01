//
// Function that calculate the checkSum of the packets 
//

//#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>
#include <algorithm>    // std::reverse
#include <iterator>
#include "saveStruct.h"
bool checkSum(saveStruct &save, unsigned char &sum)
{
    bool result = false;
    int sumAC=0;
    for(int xx=0; xx < 10 ; xx++)
    {
      sumAC += (int)(save.data[xx]);
    }
      
    unsigned char sumCAC = sumAC;

    if((int)(sumCAC) == (int)(save.data[10])){
        result = true;
	}
	sum = sumCAC;
    return result;
}
