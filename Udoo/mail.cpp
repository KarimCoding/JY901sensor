//#include "dataPkt.h"
#include "consts.h"
#include "listener.h"
#include "processData.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
//std::mutex mtx;
using namespace std;
using boost::asio::ip::udp;
std::string path;

void collect(wifi& port,dataStick& pkt,vector<dataStick>& buf, udp::socket& socket,vector<string>& rawData,std::ofstream& outF)
{
	if(buf.size()<MAXBUFSIZE)
	{
		pkt.numbytes = port.listener(std::ref(pkt),socket);
        buf.push_back(pkt); 
//		printf("buffer size: %d \n",buf.size());
    }
}


void process(std::ofstream& outF, std::ofstream& badD,vector<dataStick>& buf,std::vector<string> &goodData,std::vector<string> &badData,char fName[30],std::ofstream& raw,vector<string> &rawData)
{
	if(buf.size()!=0)
	{
		handleData(std::ref(buf),std::ref(goodData),std::ref(badData));


			if(goodData.size() )
			{
				//mutex
                outF.open(path+string(fName), ios::out|ios::app);
/*                while(rawData.size()!=0)
                {
					//cout<<"print raw dat \n";
                    outF<<rawData.front();
                    outF<<"\n";
                    rawData.erase(rawData.begin());
                }   
*/
                while(goodData.size()!=0)
                {
                //mutex
					
                    outF<<goodData.front();
					outF<<"\n";
                    goodData.erase(goodData.begin());
                }
                outF.close();
            }	//End brace for good data write

			if(badData.size())
			{
				badD.open(path+"badData_"+string(fName), ios::out|ios::app);
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
}

void writeGood(std::ofstream& outF,std::vector<string> &goodData,char fName[30])
{
//	printf("write good data\n");
	if(goodData.size()>200)
    {
    //          mutex
    	outF.open(fName, ios::out|ios::app);
        while(goodData.size()!=0)
        {
        	outF<<goodData.front();
            outF<<"\n";
            goodData.erase(goodData.begin());
        }
        outF.close();
	}   //End brace for good data write
}

void writeBad(std::ofstream& badD,std::vector<string> &badData)
{
	if(badData.size()>50)
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

	dataStick pkt;
	wifi port1;
	vector<string> goodData;
	vector<string> badData;
	vector<string> rawData;
	vector<dataStick> buf; 
	
    boost::asio::io_service io_service;
    udp::socket socket(io_service, udp::endpoint(udp::v4(), 8899));
// 	goodData.push_back(fName);	
	while(1){
	//dataStick pkt;
	
			std::thread coll(collect,std::ref(port1),std::ref(pkt),std::ref(buf),std::ref(socket),std::ref(rawData),std::ref(outF));
			std::thread proc(process,std::ref(outF),std::ref(badD),std::ref(buf),std::ref(goodData),std::ref(badData),fName,std::ref(raw),std::ref(rawData));
//			std::thread good(writeGood,std::ref(outF),std::ref(goodData),fName);
			//std::thread bad(writeBad,std::ref(badD),std::ref(badData));

			coll.join();
			proc.join();
//			good.join();
			//bad.join();

	}//	End brace for while(1)
	return 0;
}	//End brace for main
