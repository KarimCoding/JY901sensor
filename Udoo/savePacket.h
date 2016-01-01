#include <vector>
#include <memory>
#include <string>
#include <cstring>
using namespace std;
void savePacket(unsigned char saveArray[],std::vector<string> &data);

//void savePacket(std::vector<string> &Data);

void savePacket(bool check,unsigned char saveArray[],std::vector<string> &data);

//void write_bad_dat(unsigned char array[],std::vector<string> &data);
void write_bad_dat(unsigned char array[],std::vector<string> &data,std::string &head);

