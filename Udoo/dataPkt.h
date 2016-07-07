#include "consts.h"
#include <string.h>
class dataStick
{
    private:
        struct databuf{
            unsigned char data[MAXBUFLEN];
            char ip_addr[12];
            char pkt_time[30];

        };
		databuf pkt;
    public:
        void passData(unsigned char (&sData)[MAXBUFLEN]){

			memcpy(pkt.data,sData,sizeof(sData));
		}
        void getData(unsigned char (&pData)[MAXBUFLEN]){
			 memcpy(pData,pkt.data,sizeof(pkt.data));
		}
};

