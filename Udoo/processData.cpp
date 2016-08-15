#include "processData.h"

using namespace std;


void handleData(std::vector<dataStick>& buf,std::vector<string> &goodData,std::vector<string> &badData,std::string &writeBuff)
{
	pktStruct pkt;

	printf("Handle data\n");
	unsigned char data[MAXBUFLEN];
	unsigned char uc;

	std::string header;
	//std::string writeBuff;

	int numbytes = 0;
	printf("before getting  data \n");
	buf.front().getData(pkt,header,numbytes);
	printf("after getting data \n"); 
	writeBuff = header + "\n";
	
	for(int ind = 0;ind <numbytes ;ind++)
	{
		uc = pkt.data[ind];
		packetIdentifier2(std::ref(uc),std::ref(goodData),std::ref(badData),std::ref(writeBuff),header);
	}
	//goodData.push_back(writeBuff);
}	//End brace for handle


