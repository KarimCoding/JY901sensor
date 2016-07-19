//#include "dataPkt.h"
#include "consts.h"
#include "listener.h"
#include "processData.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
std::mutex mtx;
using namespace std;
using boost::asio::ip::udp;

void collect(wifi& port,dataStick& pkt,vector<dataStick>& buf, udp::socket& socket){
//while(1){
        if(buf.size()<MAXBUFSIZE){
//            printf("Coll: size %d \n",buf.size());
			pkt.numbytes = port.listener(pkt,socket);
            buf.push_back(pkt); 
//            printf("buf size on push %d \n",buf.size());
        }
        else{
        //printf("blocking buffer from receiving more data \n");
        

		}
	//	mtx.unlock();
//	}
}

void process(std::ofstream& outF, std::ofstream& badD,vector<dataStick>& buf, char fName[30]){
//while (1){
       if(buf.size()==0){
//      printf("Buffer empty waiting for data\n");
        }
        else{
//          printf("Processing data \n");
//            printf("Process: buffer size before pop %d \n", buf.size());
//			outF.open(fName, ios::out|ios::ate);
			handleData(std::ref(buf.front()),std::ref(outF),std::ref(badD));
		 	buf.erase(buf.begin());
//			printf("After pop: %d \n",buf.size());
//			outF.close();
//			usleep(5000);
		}
//}
}


int main(){
	char fName[30];
    struct timeval tval;
    time_t ctime;
    gettimeofday(&tval, NULL);
    ctime=tval.tv_sec;

	//Create filename for logfile
    strftime(fName,30,"[%Y%m%d_%H:%M:%S].txt",localtime(&ctime));
	 //std::ofstream outF(fName);
	std::ofstream outF;
	outF.open(fName, ios::out|ios::ate);


	std::ofstream badD("badData.txt");

	dataStick pkt;
	wifi port1;
	vector<dataStick> buf; 
    boost::asio::io_service io_service;
    udp::socket socket(io_service, udp::endpoint(udp::v4(), 8899));

	while(1){
	//dataStick pkt;
	
			std::thread coll(collect,std::ref(port1),std::ref(pkt),std::ref(buf),std::ref(socket));
	        std::thread proc(process,std::ref(outF),std::ref(badD),std::ref(buf),fName);
			coll.join();
			proc.join();

	}//	End brace for while(1)
	return 0;
}	//End brace for main
