//#include "dataPkt.h"
#include "consts.h"
#include "listener.h"
#include "processData.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
std::mutex mtx;
using namespace std;
using boost::asio::ip::udp;
std::string path;

void collect(wifi& port,dataStick& pkt,vector<dataStick>& buf, udp::socket& socket,vector<string>& rawData,std::ofstream& outF)
{
	if(buf.size()<MAXBUFSIZE)
	{
		pkt.numbytes = port.listener(std::ref(pkt),socket);
        buf.push_back(pkt); 

    }
} //end brace for collect


void process(std::ofstream& outF, std::ofstream& badD,vector<dataStick>& buf,std::vector<string> &goodData,std::vector<string> &badData,char fName[30],std::ofstream& raw,vector<string> &rawData)
{
	if(buf.size()!=0)
	{
		handleData(std::ref(buf),std::ref(goodData),std::ref(badData));
		printf("Datasize: %d \n",goodData.size());
			
		if(goodData.size()>GBUFFSIZE)
		{
		//			mutex
	        outF.open(fName, ios::out|ios::app);
            while(goodData.size()!=0)
            {
                //mutex
    	        outF<<goodData.front();
				outF<<"\n";
                goodData.erase(goodData.begin());
            }
                outF.close();
		}	//End brace for good data write

		if(badData.size()>BBUFFSIZE)
		{
			badD.open("badData.txt", ios::out|ios::app);
			while(badData.size()!=0)
			{
				//mutex
				badD<<badData.front();
				badD<<"\n";
				badData.erase(badData.begin());
			}
			badD.close();
		}
		buf.erase(buf.begin());
	}
} //end brace for Process



int main(){
	char fName[30];
    struct timeval tval;
    time_t ctime;
    gettimeofday(&tval, NULL);
    ctime=tval.tv_sec;

	//Create filename for logfile
    strftime(fName,30,"[%Y%m%d_%H:%M:%S].txt",localtime(&ctime));
	std::ofstream outF;
	std::ofstream badD;
	std::ofstream raw;
	path = "/home/udooer/LOGS/";
	dataStick pkt;
	wifi port1;
	vector<string> goodData;
	vector<string> badData;
	vector<string> rawData;
	vector<dataStick> buf; 
	
    boost::asio::io_service io_service;
    udp::socket socket(io_service, udp::endpoint(udp::v4(), 8899));
 	goodData.push_back(fName);	
	while(1){
			std::thread coll(collect,std::ref(port1),std::ref(pkt),std::ref(buf),std::ref(socket),std::ref(rawData),std::ref(outF));
			std::thread proc(process,std::ref(outF),std::ref(badD),std::ref(buf),std::ref(goodData),std::ref(badData),fName,std::ref(raw),std::ref(rawData));
			coll.join();
			proc.join();
	}//	End brace for while(1)
	return 0;
}	//End brace for main
