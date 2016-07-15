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
            char ip_addr[14];
            char pkt_time[36];

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

			memcpy(pkt.data,sData,MAXBUFLEN+1);
			 memcpy(pkt.ip_addr,IPaddr,14);
			//strcpy(pkt.ip_addr,IPaddr);			
			memcpy(pkt.pkt_time,time,36);
			//strcpy(pkt.pkt_time,time);
		}
        void getData(unsigned char (&pData)[MAXBUFLEN], char *IPaddr,char *time){
			memcpy(pData,pkt.data,MAXBUFLEN+1);
			memcpy(time,pkt.pkt_time,36);
			memcpy(IPaddr,pkt.ip_addr,14);
			//strcpy(time,pkt.pkt_time);

		}
		void print(){
//-			printf("data:%02u ip:%s time:%s \n",pkt.data[0],pkt.ip_addr,pkt.pkt_time); };
			//printf("ip: %s,time %s \n", pkt.ip_addr,pkt.pkt_time);
	}
};

