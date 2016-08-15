#include "processData.h"

using namespace std;


void handleData(std::vector<dataStick>& buf,std::vector<string> &badData,std::string &writeBuff)
{
	pktStruct pkt;

	unsigned char data[MAXBUFLEN];
	unsigned char uc;

	std::string header;
	//std::string writeBuff;

	int numbytes = 0;
	buf.front().getData(pkt,header,numbytes);
	writeBuff = header + "\n";
	for(int ind = 0;ind <numbytes ;ind++)
	{
		uc = pkt.data[ind];
		packetIdentifier2(std::ref(uc),std::ref(badData),std::ref(writeBuff),header);
	}
	//goodData.push_back(writeBuff);
}	//End brace for handle


