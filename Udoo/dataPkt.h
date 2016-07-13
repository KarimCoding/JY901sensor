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
            char ip_addr[13];
            char pkt_time[35];

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
			printf("pkt: %02u %02u %02u %02u %02u %02u %02u %02u %02u %02u %02u %02u \n",pkt.data[0],pkt.data[1],pkt.data[2],pkt.data[3],pkt.data[4],pkt.data[5],pkt.data[6],pkt.data[7],pkt.data[8],pkt.data[9],pkt.data[10],pkt.data[11]);
			printf("sData: %02u %02u %02u %02u %02u %02u %02u %02u %02u %02u %02u %02u \n",sData[0],sData[1],sData[2],sData[3],sData[4],sData[5],sData[6],sData[7],sData[8],sData[9],sData[10],sData[11]);
			 memcpy(pkt.ip_addr,IPaddr,13);
			//strcpy(pkt.ip_addr,IPaddr);			
			memcpy(pkt.pkt_time,time,35);
			//strcpy(pkt.pkt_time,time);
		}
        void getData(unsigned char (&pData)[MAXBUFLEN], char *IPaddr,char *time){
			memcpy(pData,pkt.data,MAXBUFLEN);
			memcpy(time,pkt.pkt_time,35);
			memcpy(IPaddr,pkt.ip_addr,13);
			//strcpy(IPaddr,pkt.ip_addr);
			//strcpy(time,pkt.pkt_time);

		}
		void print_pkt(){
			printf("data:%02u ip:%s time:%s \n",pkt.data[0],pkt.ip_addr,pkt.pkt_time); };
};

