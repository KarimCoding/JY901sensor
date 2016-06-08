/*
** listener.c -- a datagram sockets "server" demo
*/

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

#include "packetIdentifier2.h"

#include <boost/circular_buffer.hpp>
//#include <SerialStream.h>
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

//void print_data(unsigned char  buf[MAXBUFLEN], FILE *outF, int index)
void print_data(unsigned char  buf[MAXBUFLEN],int numbytes, FILE *outF)
{
    int index =-1;
    int i = 0;
    int j =0;
    //searching for first index where first two bytes of data are  55, 50-61
    // 0x55 =085 decimal, 0x80 == 80
    

    for(i=0;i<numbytes;i++){
        printf("buf[%d] = %0d \n",i,buf[i],(int)buf[i]);
        if(i%11==0)
            fprintf(outF,"\n");
        fprintf(outF,"%d ",buf[i]);

        if((buf[i]==85 ) && ((buf[i+1]>79) && (buf[i+1]<92)))
        {
            index = i;
            break;
        }
    }
   printf("index %0d \n",index);
    //check each packet if checksum is correct save data, otherwise skip
     for (j=index;j<numbytes;j=j+11)
   {
//    printf("j index = %d \n",j);
    int pIndex;
    int sum =0;
        for(pIndex = j;pIndex<(j+10);pIndex++)
        {
            sum = sum + ((int)buf[pIndex]);
        }
        unsigned char sumA = sum;
        //printf("j: %d pIndex %d sum = %d    checksum = %d \n",j,pIndex,sum,((int)buf[pIndex+1]));
        //printf("check sum %d %02x sum %d %02x\n",((int)sumA),sumA, ((int)buf[pIndex+1]),buf[pIndex+1]);
        if (((int)sumA)==((int)buf[pIndex+1]))
        {    
//            fprintf(outF, "\n");
            for(pIndex = j;pIndex<(j+11);pIndex++)
                fprintf(outF,"%02x ",buf[pIndex]);
            for(pIndex = j;pIndex <(j+11);pIndex=pIndex+11)
            {
                if(buf[pIndex+1] == 51)
                    printf("");

                
            }
        }
   }

}


int get_buf_index(unsigned char  buf[MAXBUFLEN]){
    int index =-1;
    int i = 0;
    for(i=0;i<MAXBUFLEN;i++){

        if((buf[i]==85 ) && ((buf[i+1]>79) && (buf[i+1]<91)))
        {
            index = i;
            break;
        }
    }
    return index;    
}

int main(void)
{

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
    //char directory[] = "/home/udooer/Logs/";
//    strcat(directory, date_buffer);   

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
    }

    if (p == NULL) {
        fprintf(stderr, "listener: failed to bind socket\n");
        return 2;
    }

    printf("listener: waiting to recvfrom...\n");
    //outF = fopen(directory,"a+");
//        outF = fopen(date_buffer,"a+");
   // fprintf(outF,"Log for %s",date_buffer);


while(!done){
    outF=fopen(date_buffer,"a+");
    int ind = 0;
    addr_len = sizeof their_addr;
        
    //receive data here
    if ((numbytes =  recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
        (struct sockaddr *)&their_addr, &addr_len)) == -1) {
  //      perror("recvfrom");
        flag = 0;
        exit(1);
    }
    
  //  printf("listener: got packet from %s\n",
       printf("",
        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s));

//    printf("listener: packet is %d bytes long\n", numbytes);

    buf[numbytes] = '\0';
    for(ind = 0;ind<numbytes;ind++)
    {
    	uc = buf[ind];
    	packetIdentifier2(uc,outF,VERBOSITY);
    }


   // print_data(buf,numbytes,outF);
    fclose(outF);
}
   // fclose(outF);
    freeaddrinfo(servinfo);
    close(sockfd);

    return 0;
}

