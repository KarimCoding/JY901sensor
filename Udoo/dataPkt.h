#include "consts.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
class dataStick
{
    private:
        struct databuf{
            unsigned char data[MAXBUFLEN];
            char addr[14];
		//	string addr;
            char time[15];

        };
		databuf pkt;
    public:
		int numbytes;
		~dataStick(){
/*			if(pkt.data)
				delete[] pkt.data;*/
		}
        void passData(unsigned char *sData,char *addr,char *time){
//		void passData(unsigned char (&sData)[MAXBUFLEN],string addr,char *time){
			memcpy(pkt.data,sData,MAXBUFLEN);
			pkt.data[MAXBUFLEN-1]='\0';
			//pkt.data[MAXBUFLEN]='\0';
			memcpy(pkt.addr,addr,13);
			pkt.addr[13]='\0';
//			pkt.addr = addr;
			//strcpy(pkt.addr,addr);			
			memcpy(pkt.time,time,14);
			//strcpy(pkt.time,time);
			pkt.time[14]='\0';
//			printf("Pass Data:%02x \n",pkt.data[0]); 

		}
        void getData(unsigned char *pData, char *addr,char *time){
			memcpy(pData,pkt.data,MAXBUFLEN);
			pData[MAXBUFLEN-1]='\0';
	        memcpy(time,pkt.time,14);
            //strcpy(pkt.time,time);
            time[14]='\0';
			memcpy(addr,pkt.addr,13);
			addr[13]='\0';

		}
		void print(){
			printf("data:%02u ip:%s time:%s \n",pkt.data[0],pkt.addr,pkt.time); 
			//printf("ip: %s,time %s \n", pkt.ip_addr,pkt.pkt_time);
	}
};


