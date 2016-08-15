#ifndef DATAPKT_H
#define DATAPKT_H


#include "consts.h"
#include "saveStruct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
class dataStick
{
    private:
            std::string pkt_header;
			unsigned char data[MAXBUFLEN];
			int numbytes;
    public:
		//int numbytes;
		struct dat_struct{
			unsigned char info[MAXBUFLEN];
			int numbytes = 0;
		};
		dat_struct dat; 

		dataStick()
		{
			numbytes = 0;
			pkt_header = "";
		}			//constructor
		dataStick(const dataStick &obj)	//copy constructor
		{
			numbytes = obj.numbytes;
    		memcpy(data,obj.data,obj.numbytes);
    		data[numbytes]='\0';
    		pkt_header = obj.pkt_header;//obj.getHeader();
		}
		void setData(pktStruct &pData, std::string header,int length)//;
		{
			numbytes = length;
    		memcpy(data,pData.data,numbytes);
    		data[numbytes]='\0';
    		pkt_header = header;
		}
	
        void getData(pktStruct &pData, std::string &header, int &length)//;
        {
            length = numbytes;
            memcpy(pData.data,data,numbytes);
            pData.data[numbytes]='\0';
            header = pkt_header;
        }


		std::string getHeader( )
		{
    		return pkt_header;
		}

		void print()//;
		{
        	cout<<pkt_header<<" with "<<numbytes<<endl;
            unsigned char output[MAXBUFLEN];// = (unsigned char*)malloc(len$
        	memcpy(output, data, numbytes);
        	for(int i = 0;i<dat.numbytes;i++)
        	{
            	printf("%02x ",output[i]);
            	if(i>0&&i%10==0)
                	printf("\n");
        	}
        	printf("\n");
		}

};
#endif /* DATAPKT_H */

/*void dataStick::passData(pktStruct &pData, std::string header,int length)
{
	numbytes = length;
    memcpy(data,pData.data,numbytes);
    data[numbytes]='\0';
	pkt_header = header;
}
*/
/*
dataStick::dataStick(const dataStick &obj)
{
	memcpy(dat.info,obj.dat.info,obj.numbytes);
    dat.info[numbytes]='\0';
    pkt_header = obj.pkt_header;//obj.getHeader();
}
*/

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
//#endif /* DATAPKT_H */

