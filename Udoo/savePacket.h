#include <vector>
#include <memory>
#include <string>
#include <cstring>
#include "saveStruct.h"
using namespace std;

void savePacket(saveStruct &save,std::vector<string> &data,std::string &buf);
void savePacket(bool check,saveStruct &save,std::vector<string> &data);
//void write_bad_dat(saveStruct &save,std::vector<string> &data,std::string &buf);
void write_bad_dat(saveStruct &save,std::vector<string> &data,std::string &buf,unsigned char &sum);
