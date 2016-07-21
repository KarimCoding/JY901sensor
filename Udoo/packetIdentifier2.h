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
#include "timeOutput.h"
#include "AngleOutput.h"
#include <vector>
#include <memory>

using namespace std;

//void handleData(std::vector<dataStick>& buf,std::vector<string> &goodData,std::vector<string> &badData);
void packetIdentifier2(unsigned char uc, std::vector<string> &goodData,std::vector<string> &badData);
//void packetIdentifier2 (unsigned char uc, ofstream& outF,std::ofstream& badData);
//void packetIdentifier2 (unsigned char uc,char *fName);

