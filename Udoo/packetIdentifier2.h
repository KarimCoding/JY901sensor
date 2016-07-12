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

using namespace std;

//void packetIdentifier2 (unsigned char uc, ofstream& outF,bool verbosity,std::ofstream& badData);
void packetIdentifier2 (unsigned char uc,bool verbosity,char *fName);

