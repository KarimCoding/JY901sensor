#ifndef PROCESSDATA_H
#define PROCESSDATA_H
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "packetIdentifier2.h"
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>
#include "dataPkt.h"
#include "consts.h"
#include <string>
#include <vector>
#include <memory>




#include <vector>
#include <memory>
void handleData(std::vector<dataStick>& buf,std::vector<string> &badData,std::string &writeBuff);

//void handleData(std::vector<dataStick>& buf,std::vector<string> &goodData,std::vector<string> &badData);

#endif /* PROCESSDATA_H */

