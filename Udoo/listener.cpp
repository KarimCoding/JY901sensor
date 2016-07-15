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
      	boost::array<unsigned char, MAXBUFLEN> recv_buf;
		udp::endpoint remote_endpoint;
	    boost::system::error_code error;
	    size_t len = socket.receive_from(boost::asio::buffer(recv_buf),
          remote_endpoint, 0, error);
        unsigned char output[MAXBUFLEN];// = (unsigned char*)malloc(len);
        memcpy(output, recv_buf.data(), recv_buf.size());
        gettimeofday(&tv, NULL); 
        curtime=tv.tv_sec;
        strftime(time,30,"%T",localtime(&curtime));
        sprintf(usec, "%ld", tv.tv_usec);
        strcat(time,usec);
		//std::string s = (char) socket.local_endpoint().address();
		std::string s = remote_endpoint.address().to_string();
//		std::cout<<s<<"\n";
		        char* addr = (char*)malloc(s.size());
				memcpy(addr,s.c_str(),s.size());
  //      printf("Listener: data: %02u from%s @  %s\n",output[0],addr,time);
        pkt.passData(output,addr,time );
//		pkt.passData(recv_buf.data(),addr,time);
  return 0;
}




