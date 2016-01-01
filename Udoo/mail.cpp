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

void collect(wifi& port,dataStick& pkt,vector<dataStick>& buf, udp::socket& socket,vector<string>& rawData,std::ofstream& outF)
{
	if(buf.size()<MAXBUFSIZE)
	{
		pkt.numbytes = port.listener(std::ref(pkt),socket);
        buf.push_back(pkt); 

/*            if(rawData.size()>1)
            {
        //          mutex
				printf("raw dat printing \n");
                outF.open("rawDat.txt", ios::out|ios::ate);
                while(rawData.size()!=0)
                {
                //mutex
                    outF<<rawData.front();
                    outF<<"\n";
                    rawData.erase(rawData.begin());
                }
                outF.close();
				buf.erase(buf.begin());
            } */


    }
}


void process(std::ofstream& outF, std::ofstream& badD,vector<dataStick>& buf,std::vector<string> &goodData,std::vector<string> &badData,char fName[30],std::ofstream& raw,vector<string> &rawData)
{
	if(buf.size()==0)
	{
	}
	else
	{
		handleData(std::ref(buf),std::ref(goodData),std::ref(badData));
		printf("Datasize: %d \n",goodData.size());
			
/*			if(goodData.size()>GBUFFSIZE)
			{
				raw.open("raw.txt",ios::out|ios::ate);
				while(goodData.size()!=0)
				{
					raw<<goodData.front();
					raw<<"\n";
					rawData.erase(goodData.begin());
				}	
				raw.close();
			}*/

			if(goodData.size()>GBUFFSIZE)
			{
		//			mutex
                outF.open(fName, ios::out|ios::ate);
                while(goodData.size()!=0)
                {
                //mutex
                    outF<<goodData.front();
					outF<<"\n";
                    goodData.erase(goodData.begin());
                }
                outF.close();
            }	//End brace for good data write

/*			if(badData.size()>BBUFFSIZE)
			{
				badD.open("badData.txt", ios::out|ios::ate);
				while(badData.size()!=0)
				{
				//mutex
					badD<<badData.front();
					badD<<"\n";
					badData.erase(badData.begin());
				}
				badD.close();
			}
*/
		
		buf.erase(buf.begin());
	}
}

void writeGood(std::ofstream& outF,std::vector<string> &goodData,char fName[30])
{
	if(goodData.size()>200)
    {
    //          mutex
    	outF.open(fName, ios::out|ios::ate);
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
    	badD.open("badData.txt", ios::out|ios::ate);
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
 	goodData.push_back(fName);	
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
