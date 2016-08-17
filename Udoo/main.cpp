//#include "dataPkt.h"
#include "consts.h"
#include "listener.h"
#include "processData.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <cstdlib>

extern "C" void __libc_freeres(void);

std::mutex mtx;
using namespace std;
using boost::asio::ip::udp;
std::string path;
bool print_on(true);
void collect(wifi& port,dataStick pkt,vector<dataStick>& buf, udp::socket& socket)
{
	if(buf.size()<MAXBUFSIZE)
	{
		int numbytes;
		numbytes = port.listener(std::ref(pkt),socket);
		mtx.lock();
        buf.push_back(pkt);
		mtx.unlock();
    }
} //end brace for collect


void process(vector<dataStick>& buf,std::vector<string> &goodData,std::vector<string> &badData,char fName[30])
{
	if(buf.size()!=0)
	{
		std::string writeBuff;
		handleData(std::ref(buf),std::ref(badData),std::ref(writeBuff));
		mtx.lock();
		goodData.push_back(writeBuff);
		buf.erase(buf.begin());
		mtx.unlock();
	}
}//end process

void writeData(std::ofstream& outF,std::vector<string> &goodData,char fName[30])
{
	if(goodData.size())
	{
    	outF.open(path+string(fName), ios::out|ios::app);
        while(goodData.size()>0)
        {
			if(print_on)
        		cout<<goodData.front()<<"\n";
            outF<<goodData.front()<<"\n";
            mtx.lock();
			goodData.erase(goodData.begin());
			mtx.unlock();

		}
        outF.close();
	}
}

void writeBad(std::ofstream& badD,std::vector<string> &badData,char fName[30])
{
	if(badData.size())
    {
    	badD.open(path+"badData_"+string(fName), ios::out|ios::app);
        while(badData.size()>0)
        { 
        	badD<<badData.front()<<"\n";
			mtx.lock();
            badData.erase(badData.begin());
			mtx.unlock();
        }
        badD.close();
	}
}
int main(){
	char fName[30];
    struct timeval tval;
    time_t ctime;
    gettimeofday(&tval, NULL);
    ctime=tval.tv_sec;

	//Create filename for logfile
    strftime(fName,30,"[%Y%m%d_%H:%M:%S].txt",localtime(&ctime));
	path = "/home/udooer/LOGS/";
//	path = "";

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
	

	 atexit(__libc_freeres);

	while(1){
			std::thread coll(collect,std::ref(port1),pkt,std::ref(buf),std::ref(socket));
			std::thread proc(process,std::ref(buf),std::ref(goodData),std::ref(badData),fName);
			std::thread good(writeData,std::ref(outF),std::ref(goodData), fName);
			std::thread bad(writeBad,std::ref(badD),std::ref(badData),fName);
		
			coll.join();
			proc.join();
			good.join();
			bad.join();
	}//	End brace for while(1)
	return 0;
}	//End brace for main
