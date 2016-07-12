#include "consts.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
class dataStick
{
    private:
        struct databuf{
            unsigned char *data;//[MAXBUFLEN];
            char ip_addr[20];
            char pkt_time[40];

        };
		databuf pkt;
    public:
		int numbytes;
		dataStick(){
			numbytes=0;
			pkt.data = new unsigned char[MAXBUFLEN]();
		}
		~dataStick(){
/*			if(pkt.data)
				delete[] pkt.data;*/
		}
        void passData(unsigned char (&sData)[MAXBUFLEN],char *IPaddr,char *time){

			memcpy(pkt.data,sData,MAXBUFLEN);

			// memcpy(pkt.ip_addr,IPaddr,strlen(IPaddr)+1);
			strcpy(pkt.ip_addr,IPaddr);			
			//memcpy(pkt.pkt_time,time,35);
			strcpy(pkt.pkt_time,time);
		}
        void getData(unsigned char (&pData)[MAXBUFLEN], char *IPaddr,char *time){
			memcpy(pData,pkt.data,MAXBUFLEN);
			//memcpy(IPaddr,pkt.ip_addr,15);
			strcpy(IPaddr,pkt.ip_addr);
			strcpy(time,pkt.pkt_time);

		}
		void print_pkt(){
			printf("data:%02u ip:%s time:%s \n",pkt.data[0],pkt.ip_addr,pkt.pkt_time); };
};

