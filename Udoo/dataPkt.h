#include "consts.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
class dataStick
{
    private:
            std::string pkt_header;
			unsigned char data[MAXBUFLEN];

    public:
		int numbytes;
		struct dat_struct{
			unsigned char info[MAXBUFLEN];
		};
		dat_struct dat; 
		void passData(dataStick::dat_struct &pData, std::string &header)//;
		{
    		memcpy(data,pData.info,numbytes);
    		data[numbytes]='\0';
    		pkt_header = header;
/*			printf("from passdata \n");
		        unsigned char output[MAXBUFLEN];// = (unsigned char*)malloc(len);
        memcpy(output, data, numbytes);
        for(int i = 0;i<numbytes;i++)
		{
            printf("%02x ",output[i]);
        	if(i>0&&i%12==0)
            	printf("\n");
        }
*/



		}
//		void getData(dataStick::dat_struct &gData, std::string &head )//;
		void getData(std::string &head )
		{
/*    		memcpy(gData.info,data,numbytes);
    		gData.info[numbytes]='\0';
*/    		head = pkt_header;
		}
		void print()//;
		{



		}

};

/*
void dataStick::passData(dataStick::dat_struct &pData, std::string &header)
{
	memcpy(data,pData.info,numbytes);
	data[numbytes]='\0';
	pkt_header = header;
}

void dataStick::getData(dataStick::dat_struct &gData, std::string &head)
{
	memcpy(gData.info,data,numbytes);
	gData.info[numbytes]='\0';
	head = pkt_header;
}

void dataStick::print()
{ 
	//printf("data:%02u ip:%s  \n",pkt.data[0],pkt_header); //printf("ip: %s,time %s \n", pkt.ip_addr,pkt.pkt_time);
}
*/
