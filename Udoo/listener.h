#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <thread>

#include "packetIdentifier2.h"

#include <boost/circular_buffer.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>
#include "dataPkt.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>


using boost::asio::ip::udp;


//#include "consts.h"

#ifdef DEBUG
    #define VERBOSITY 1
#endif
#ifndef DEBUG
    #define VERBOSITY 0
#endif
class wifi
{
	private:

	    char time[35];
	    char ip[4];
		char usec[5];
		struct timeval tv;
    time_t curtime;

	public:
		int listener(dataStick& pkt,udp::socket& socket);

		

};
