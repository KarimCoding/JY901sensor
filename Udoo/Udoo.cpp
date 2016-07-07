//#include "dataPkt.h"
#include "consts.h"
#include "listener.h"
#include "processData.h"
using namespace std;

void collect(wifi port,dataStick packet){

	port.listener(packet);
}

void process(dataStick packet, char file[30],FILE *output){
	handleData(packet,file,output);
}
int main(){
	char fName[30];
    struct timeval tval;
	FILE *output;

    time_t ctime;    

    gettimeofday(&tval, NULL); 
    ctime=tval.tv_sec;
    
    strftime(fName,30,"[%Y%m%d_%H:%M:%S].txt",localtime(&ctime));

	dataStick pkt;
	wifi port1;
	std::thread coll(collect,port1,pkt);
	std::thread proc(process,pkt,fName,output);
	coll.join();
	proc.join();
//	int numbytes = port1.listener(pkt);
//	handleData(pkt);
	/*
	buffer->getData(newBuff);
	newBuff[MAXBUFLEN] = '\0';
		printf("%s ",newBuff);
	*/
	return 0;
}	//End brace for main
