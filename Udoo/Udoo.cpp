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

void collect(wifi& port,dataStick& pkt,vector<dataStick>& buf, udp::socket& socket)
{
    if(buf.size()<MAXBUFSIZE)
    {
        pkt.numbytes = port.listener(pkt,socket);
        buf.push_back(pkt); 
    }
}


void process(std::ofstream& outF, std::ofstream& badD,vector<dataStick>& buf,std::vector<string> &goodData,std::vector<string> &badData,char fName[30]){
       if(buf.size()==0){
        }
        else{
            handleData(std::ref(buf),std::ref(goodData),std::ref(badData));
            if(goodData.size()>200)
            {
        //          mutex
                outF.open(fName, ios::out|ios::ate);
                while(goodData.size()!=0)
                {
                //mutex
                    outF<<goodData.front();
                    outF<<"\n";
                    goodData.erase(goodData.begin());
                }
                outF.close();
            }   //End brace for good data write

            if(badData.size()>50)
            {
                badD.open("badData.txt", ios::out|ios::ate);
                while(badData.size()!=0)
                {
                //mutex
                    badD<<badData.front();
                    badD<<"\n";
                    badData.erase(badData.begin());
                }
                badD.close();
            }

            buf.erase(buf.begin());
        }
}


int main(){
    char fName[30];
    struct timeval tval;
    time_t ctime;
    gettimeofday(&tval, NULL);
    ctime=tval.tv_sec;

    //Create filename for logfile
    strftime(fName,30,"[%Y%m%d_%H:%M:%S].txt",localtime(&ctime));
    std::ofstream outF;
    std::ofstream badD;

    dataStick pkt;
    wifi port1;
    vector<string> goodData;
    vector<string> badData;
    vector<dataStick> buf; 
    boost::asio::io_service io_service;
    udp::socket socket(io_service, udp::endpoint(udp::v4(), 8899));
    goodData.push_back(fName);  
    while(1){
    //dataStick pkt;
    
            std::thread coll(collect,std::ref(port1),std::ref(pkt),std::ref(buf),std::ref(socket));
//          std::thread proc(process,std::ref(outF),std::ref(badD),std::ref(buf),fName);
            std::thread proc(process,std::ref(outF),std::ref(badD),std::ref(buf),std::ref(goodData),std::ref(badData),fName);
            //add thread for writing good data
            //add thread for writing bad data

            coll.join();
            proc.join();
        //  good.join();
        //  bad.join();

    }// End brace for while(1)
    return 0;
}   //End brace for main







