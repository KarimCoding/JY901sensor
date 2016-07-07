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
#include "consts.h"
#ifdef DEBUG
    #define VERBOSITY 1
#endif
#ifndef DEBUG
    #define VERBOSITY 0
#endif
        unsigned char uc;

/*void wifi::term(int signum)
{
    done = 1;
}
*/

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

//int wifi::listener(dataStick *data)
int main()
{
	char IPaddr[13];
    char fileName[26];
    char dataHeader[30];
    struct timeval tv;
    time_t curtime;
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    unsigned char buf[MAXBUFLEN];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];
    FILE *outF;
    FILE *badData;

/*    //to catch terminate signal
	    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
*/	

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    gettimeofday(&tv, NULL); 
    curtime=tv.tv_sec;
    
//    strftime(fileName,30,"[%Y%m%d_%H:%M:%S].txt",localtime(&curtime));
 //   printf("%s \n",fileName);


    outF=fopen(fileName,"a+");
//    badData=fopen("/home/udooer/Logs/badData.txt","+a");

    //Continually listen for socket connections
  //  while(!done){
	while(1){
        if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
         return 1;
        }
        // loop through all the results and bind to the first we can
        for(p = servinfo; p != NULL; p = p->ai_next) {
            if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
                perror("listener: socket");
                continue;
            }

            if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                close(sockfd);
                perror("listener: bind");
                continue;
            }
            break;
         }  // End brace for for(p = servinfo..

        if (p == NULL) {
            fprintf(stderr, "listener: failed to bind socket\n");
            return 2;
        }

//        freeaddrinfo(servinfo);

        addr_len = sizeof their_addr;
        if ((numbytes =  recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
                (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            exit(1);
        }

        printf("listener: got packet from %s\n",
                inet_ntop(their_addr.ss_family,
                    get_in_addr((struct sockaddr *)&their_addr),
                        s, sizeof s));
		memcpy(IPaddr,inet_ntop(their_addr.ss_family,
                    get_in_addr((struct sockaddr *)&their_addr),
                        s, sizeof s),sizeof s);
		printf("IP ADDR: %s\n",IPaddr);
        //oepn stream once a connection has been established
        buf[numbytes] = '\0';
		close(sockfd);

		// Data processing section
    	gettimeofday(&tv, NULL); 
    	curtime=tv.tv_sec;
		strftime(dataHeader,30,"%T",localtime(&curtime));
    	fprintf(outF,"IP: %s @ %s%ld \n", inet_ntop(their_addr.ss_family,
                get_in_addr((struct sockaddr *)&their_addr),
                    s, sizeof s),dataHeader,tv.tv_usec);
    	//pass the data over to be  processed
    	for(int ind = 0;ind<numbytes;ind++)
 	   	{
 	    	uc = buf[ind];
  	    	packetIdentifier2(uc,outF,badData,VERBOSITY);
		}
		fprintf(outF,"\n");
        // End Data processing Section
	      freeaddrinfo(servinfo);

    }// End brace for while loop
    fclose(outF);
//    fclose(badData);
	return numbytes;
}   //End brace for main()

