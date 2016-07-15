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

void collect(wifi& port,dataStick& packet){
//	mtx.lock();
	//std::lock_guard<std::mutex> lck(mtx);
	port.listener(packet);
//	mtx.unlock();
}

void process(dataStick& pkt,std::ofstream& outF, std::ofstream& badD){
//void process(dataStick& packet,char *fName){

//	mtx.lock();
	handleData(std::ref(pkt),std::ref(outF),std::ref(badD));
//	handleData(packet,outF,VERBOSITY, badD);
	//handleData(packet,fName);
//	mtx.unlock();
}


int main(){
	char fName[30];
    struct timeval tval;
    time_t ctime;
    gettimeofday(&tval, NULL);
    ctime=tval.tv_sec;

	//Create filename for logfile
    strftime(fName,30,"[%Y%m%d_%H:%M:%S].txt",localtime(&ctime));
	 std::ofstream outF(fName);
	std::ofstream badD("badData.txt");

	dataStick pkt;
	wifi port1;
	vector<dataStick> buf; 
	while(1){
		if(buf.size()<MAXBUFSIZE){
			printf("buf size %d \n",buf.size());
			std::thread coll(collect,std::ref(port1),std::ref(pkt));
//			std::thread proc(process,std::ref(pkt),std::ref(outF));
			coll.join();
			buf.push_back(pkt);	
//	 		printf("buf size %d \n",buf.size());
		}
		else{
		//printf("blocking buffer from receiving more data \n");
		}
//	pkt.print_pkt();
//	if(pkt.numbytes==0)
		if(buf.size()==0){
//		printf("Buffer empty waiting for data\n");
		}
		else{
//			printf("Processing data \n");
			printf("buffer size before pop %d \n", buf.size());

			std::thread proc(process,std::ref(buf.front()),std::ref(outF),std::ref(badD));
			buf.erase(buf.begin());
			printf("buffer size after pop %d \n", buf.size());
	//  	std::thread proc(process,std::ref(pkt),std::ref(outF),std::ref(badD));
	//		std::thread proc(process,std::ref(pkt),std::ref(fName));
			proc.join();
		}

	}//	End brace for while(1)
	return 0;
}	//End brace for main
