#include <vector>
#include <memory>
#include <string>
#include <cstring>
using namespace std;
void savePacket(unsigned char saveArray[],std::vector<string> &data);
//void savePacket(unsigned char saveArray[], std::ofstream& outF);
/*void write_bad_dat(std::ofstream& badData, unsigned char uc);
void write_bad_dat(std::ofstream& badData, unsigned char saveArray[]);
*/
//void savePacket(unsigned char saveArray[], bool verbosity, char *fName);
void write_bad_dat(unsigned char uc);
//void write_bad_dat(unsigned char saveArray[]);
void write_bad_dat(unsigned char array[],std::vector<string> &data);

