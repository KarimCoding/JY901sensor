// server.cpp
// ~~~~~~~~~~
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include "listener.h"
using boost::asio::ip::udp;


int wifi::listener(dataStick& pkt,udp::socket& socket)
//int main()
{
//  printf("listener \n ");

     char ctime[35];
        char ip[4];
        char usec[5];
        struct timeval tv;
    time_t curtime;


        boost::array<unsigned char, MAXBUFLEN> recv_buf;
        udp::endpoint remote_endpoint;
        boost::system::error_code error;
        size_t len = socket.receive_from(boost::asio::buffer(recv_buf),remote_endpoint, 0, error);


//        unsigned char output[MAXBUFLEN];// = (unsigned char*)malloc(len);
        memcpy(pkt.dat.info, recv_buf.data(), recv_buf.size());
		pkt.numbytes = recv_buf.size();
		pkt.dat.info[pkt.numbytes] = '\0';

/*
        unsigned char output[MAXBUFLEN];// = (unsigned char*)malloc(len);
        memcpy(output, pkt.dat.info, pkt.numbytes);
	    printf("data: %d \n",sizeof(pkt.dat.info));
        for(int i = 0;i<len;i++){
            printf("%02x ",output[i]);
        if(i>0&&i%12==0)
            printf("\n");
        }
*/
        gettimeofday(&tv, NULL); 
        curtime=tv.tv_sec;
        strftime(ctime,30,"%T",localtime(&curtime));
        sprintf(usec, "%ld", tv.tv_usec);
        strcat(ctime,usec);
        std::string time(ctime);
        std::string pkt_header = remote_endpoint.address().to_string();
        pkt_header = pkt_header + " @ " + time;
        pkt.passData(pkt.dat,pkt_header );
		cout<<pkt_header<<endl;
        return 0;
}

