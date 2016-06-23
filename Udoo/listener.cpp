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

#define MYPORT "8899"    // the port users will be connecting to
#define MAXBUFLEN 518   //4Mb buffer (512 * 8)
#ifdef DEBUG
    #define VERBOSITY 1
#endif
#ifndef DEBUG
    #define VERBOSITY 0
#endif
volatile sig_atomic_t done = 0;
unsigned char uc;

void term(int signum)
{
    done = 1;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{

    char dataHeader[10];
    time_t timer;
    char filename[999];
    char date_buffer[26];
    struct tm* tm_info;
    int flag = 1;
    int c = 0;
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    unsigned char buf[MAXBUFLEN], out_buf[MAXBUFLEN];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];
    FILE *outF;
    FILE *badData;

    //to catch terminate signal
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    time(&timer);
    tm_info = localtime(&timer);
    strftime(date_buffer, 26, "[%Y%m%d_%H:%M:%S].txt",tm_info);

    //Continually listen for socket connections
    while(!done){

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

        printf("listener: waiting to recvfrom...\n");
        addr_len = sizeof their_addr;

        if ((numbytes =  recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
                (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            flag = 0;
            exit(1);
        }

        printf("listener: got packet from %s\n",
                inet_ntop(their_addr.ss_family,
                    get_in_addr((struct sockaddr *)&their_addr),
                        s, sizeof s));

        //oepn stream once a connection has been established
        outF=fopen(date_buffer,"a+");
        buf[numbytes] = '\0';
        strftime(dataHeader, 26, "[%H:%M:%S]",tm_info);
        fprintf(outF,"IP: %s @ %s \n", inet_ntop(their_addr.ss_family,
                get_in_addr((struct sockaddr *)&their_addr),
                    s, sizeof s),dataHeader);

        //pass the data over to be  processed
        int ind = 0;
        for(ind = 0;ind<numbytes;ind++)
        {
    	    uc = buf[ind];
    	    packetIdentifier2(uc,outF,badData,VERBOSITY);
        }
        fclose(outF);
        freeaddrinfo(servinfo);
        close(sockfd);
        printf("closed socket \n");
    }// End brace for while loop
    return 0;
}   //End brace for main()
