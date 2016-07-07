#include "consts.h"
#include <string.h>
class dataStick
{
    private:
        struct databuf{
            unsigned char data[MAXBUFLEN];
            char ip_addr[13];
            char pkt_time[30];

        };
		databuf pkt;
    public:
		int numbytes;
        void passData(unsigned char (&sData)[MAXBUFLEN], char IPaddr[4],char time[35]){
			memcpy(pkt.data,sData,sizeof(sData));
            memcpy(pkt.ip_addr,IPaddr,4);
			memcpy(pkt.pkt_time,time,35);
		}
        void getData(unsigned char (&pData)[MAXBUFLEN],char IPaddr[4],char time[35]){
			memcpy(pData,pkt.data,sizeof(pkt.data));
	        memcpy(IPaddr,pkt.ip_addr,4);
            memcpy(time,pkt.pkt_time,35);

		}
};

