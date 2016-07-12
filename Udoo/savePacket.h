/*
void savePacket(unsigned char saveArray[], std::ofstream& outF,bool verbosity);
void write_bad_dat(std::ofstream& badData, unsigned char uc);
void write_bad_dat(std::ofstream& badData, unsigned char saveArray[]);
*/

void savePacket(unsigned char saveArray[], bool verbosity, char *fName);
void write_bad_dat(unsigned char uc);
void write_bad_dat(unsigned char saveArray[]);

