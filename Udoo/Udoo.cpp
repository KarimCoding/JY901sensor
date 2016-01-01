//#include "dataPkt.h"
#include "consts.h"
#include "listener.h"
#include "processData.h"
#include <iostream>
#include <fstream>
std::mutex mtx;
using namespace std;
void collect(wifi& port,dataStick& packet){
	mtx.lock();
	//std::lock_guard<std::mutex> lck(mtx);
	port.listener(packet);
	mtx.unlock();
}

void process(dataStick& pkt,std::ofstream& outF, std::ofstream& badD){
//void process(dataStick& packet,char *fName){

	mtx.lock();
	handleData(std::ref(pkt),std::ref(outF),std::ref(badD));
//	handleData(packet,outF,VERBOSITY, badD);
	//handleData(packet,fName);
	mtx.unlock();
}


int main(){
	char fName[30];
    struct timeval tval;

	//FILE *output;

    time_t ctime;

    gettimeofday(&tval, NULL);
    ctime=tval.tv_sec;

	//Create filename for logfile
    strftime(fName,30,"[%Y%m%d_%H:%M:%S].txt",localtime(&ctime));
	 std::ofstream outF(fName);
	std::ofstream badD("badData.txt");

	dataStick pkt;
	wifi port1;
	std::thread coll(collect,std::ref(port1),std::ref(pkt));
//	std::thread proc(process,std::ref(pkt),std::ref(outF));
	coll.join();

	pkt.print_pkt();
	if(pkt.numbytes==0)
		printf("joining\n");
	else{
		  std::thread proc(process,std::ref(pkt),std::ref(outF),std::ref(badD));
//		std::thread proc(process,std::ref(pkt),std::ref(fName));

		proc.join();
	}
//	int numbytes = port1.listener(pkt);
//	handleData(pkt);
	/*
	buffer->getData(newBuff);
	newBuff[MAXBUFLEN] = '\0';
		printf("%s ",newBuff);
	*/
	return 0;
}	//End brace for main
