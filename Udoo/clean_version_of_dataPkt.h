#include "consts.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
class dataStick
{
    private:
            unsigned char data[MAXBUFLEN];
            char addr[14];
            char time[15];
    public:
		int numbytes;
		~dataStick(){
/*			if(pkt.data)
				delete[] pkt.data;*/
		}
		
		void passData(unsigned char *sData,char *addr,char *time);
//		void passData(unsigned char (&sData)[MAXBUFLEN],string addr,char *time){
		void getData(unsigned char *pData, char *addr,char *time);
		void print();
	}
};


void dataStick::passData(unsigned char *sData,char *sAddr,char *sTime)
{
	memcpy(data,sData,MAXBUFLEN);
	data[MAXBUFLEN-1]='\0';
	memcpy(addr,sAddr,13);
	addr[13]='\0';
	memcpy(time,sTime,14);
	time[14]='\0';
}

void dataStick::getData(unsigned char *pData, char *pAddr,char *pTime)
{
	memcpy(pData,pkt.data,MAXBUFLEN);
	pData[MAXBUFLEN-1]='\0';
	memcpy(pTtime,time,14);
	time[14]='\0';
	memcpy(pAddr,addr,13);
	aPddr[13]='\0';

}

void dataStick::print()
{ 
	printf("data:%02u ip:%s time:%s \n",pkt.data[0],pkt.addr,pkt.time); //printf("ip: %s,time %s \n", pkt.ip_addr,pkt.pkt_time);
}

