//#include "dataPkt.h"
#include "consts.h"
#include "listener.h"
#include "processData.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
std::mutex mtx;
using namespace std;
using boost::asio::ip::udp;

void collect(wifi& port,dataStick& pkt,vector<dataStick>& buf, udp::socket& socket){
        if(buf.size()<MAXBUFSIZE){
//            printf("Coll: size %d \n",buf.size());
			pkt.numbytes = port.listener(pkt,socket);
            buf.push_back(pkt); 
//            printf("buf size on push %d \n",buf.size());
        }
        else{
		}
	//	mtx.unlock();
}


void process(std::ofstream& outF, std::ofstream& badD,vector<dataStick>& buf,std::vector<string> &goodData,std::vector<string> &badData){
//void process(std::ofstream& outF, std::ofstream& badD,vector<dataStick>& buf, char fName[30]){
       if(buf.size()==0){
//      printf("Buffer empty waiting for data\n");
        }
        else{
//          printf("Processing data \n");
//            printf("Process: buffer size before pop %d \n", buf.size());
//			outF.open(fName, ios::out|ios::ate);

/*	      unsigned char output[MAXBUFLEN];// = (unsigned char*)malloc(len);
			//buf.front().dat.info,buf.front().numbytes)
       		memcpy(output, buf.front().dat.info,buf.front().numbytes);
		    printf("from mail buf.front() data: %d \n",sizeof(output));
        	for(int i = 0;i<sizeof(output);i++){
            	printf("%02x ",output[i]);
        		if(i>0&&i%12==0)
            		printf("\n");
        	}
*/
			printf("before handle data %d %d \n",goodData.size(),badData.size());
			handleData(std::ref(buf),std::ref(goodData),std::ref(badData));

			printf("after handle data %d %d \n",goodData.size(),badData.size());

//			cout<<badData.front();

			if(goodData.size()>200)
			{
		//			mutex
                outF.open("goodData.txt", ios::out|ios::ate);
                while(badData.size()!=0)
                {
                //mutex
                    outF<<goodData.front();
//					outF<<"\n";
                    cout<<goodData.front();
                    goodData.erase(goodData.begin());
                }
                outF.close();
            }

			if(badData.size()>200)
			{
				badD.open("badData.txt", ios::out|ios::ate);
				while(badData.size()!=0)
				{
				//mutex
					badD<<badData.front();
					badD<<"\n";
//					cout<<badData.front();
					badData.erase(badData.begin());
				}
				badD.close();
			}

		 	buf.erase(buf.begin());


//			printf("After pop: %d \n",buf.size());
//			outF.close();
//			usleep(5000);
		}
//}
}


int main(){
	char fName[30];
    struct timeval tval;
    time_t ctime;
    gettimeofday(&tval, NULL);
    ctime=tval.tv_sec;

	//Create filename for logfile
    strftime(fName,30,"[%Y%m%d_%H:%M:%S].txt",localtime(&ctime));
	 //std::ofstream outF(fName);
	std::ofstream outF;
	std::ofstream badD("badData.txt");

	dataStick pkt;
	wifi port1;
	vector<string> goodData;
	vector<string> badData;
	vector<dataStick> buf; 
    boost::asio::io_service io_service;
    udp::socket socket(io_service, udp::endpoint(udp::v4(), 8899));
 	
	while(1){
	//dataStick pkt;
	
			std::thread coll(collect,std::ref(port1),std::ref(pkt),std::ref(buf),std::ref(socket));
//	        std::thread proc(process,std::ref(outF),std::ref(badD),std::ref(buf),fName);
			std::thread proc(process,std::ref(outF),std::ref(badD),std::ref(buf),std::ref(goodData),std::ref(badData));
			//add thread for writing good data
			//add thread for writing bad data

			coll.join();
			proc.join();
		//	good.join();
		//	bad.join();

	}//	End brace for while(1)
	return 0;
}	//End brace for main
