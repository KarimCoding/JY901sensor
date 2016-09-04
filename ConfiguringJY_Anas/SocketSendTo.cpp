#include "SocketSendTo.h"
#include <iostream>
#include <string>
#include <vector>
#include "Command.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
//#include "port.h"
#include <time.h>
#include <unistd.h>


#define BUFSIZE 2048
#define COMMAND_SIZE 5



int SERVICE_PORT = 8899;
//char static IPAddress[] = "192.168.1.1";


void saveConfig (struct sockaddr_in , socklen_t, int );
void sendToSensor (Command , struct sockaddr_in, socklen_t, int);
void sendToSensor_externalSocket (Command, struct sockaddr_in, socklen_t, int);
void saveConfig_externalSocket (struct sockaddr_in , socklen_t, int );

using namespace std;



void SocketSendTo::sendToSensor (Command comm, const char* IPAddress)
{

    struct sockaddr_in myaddr;	/* our address */
    struct sockaddr_in remaddr;	/* remote address */
    remaddr.sin_addr.s_addr = inet_addr(IPAddress);
    remaddr.sin_port = htons(SERVICE_PORT);
    socklen_t addrlen = sizeof(remaddr);		/* length of addresses */
    int recvlen;			/* # bytes received */
    int fd;				/* our socket */
    int msgcnt = 0;			/* count # of messages we received */
    unsigned char buf[BUFSIZE];	/* receive buffer */
    remaddr.sin_family = AF_INET;

    /* create a UDP socket */

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("cannot create socket\n");
        // return 0;
    }

    /* bind the socket to any valid IP address and a specific port */

    memset((char *)&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(SERVICE_PORT);

    if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
    {
        perror("bind failed");
//        return 0;
    }

    //sendToSensor_externalSocket (comm, newSocket.remaddr, newSocket.addrlen, newSocket.fd);

    unsigned char buff = 0x00;
    if (sendto(fd, &buff, 1, 0, (struct sockaddr *)&remaddr, addrlen) < 0)
        perror("sendto");


    sendToSensor_externalSocket (comm, remaddr, addrlen, fd );
    saveConfig_externalSocket (remaddr, addrlen, fd);

}



void sendToSensor_externalSocket (Command comm, struct sockaddr_in remaddr, socklen_t addrlen, int fd)
{
    for (int i = 0; i < COMMAND_SIZE ; i++)
    {
        unsigned char buff = comm.getCommandFormatIndex(i);
        if (sendto(fd, &buff, 1, 0, (struct sockaddr *)&remaddr, addrlen) < 0)
            perror("sendto");
    }

    usleep (500000);
    // saveConfig (remaddr, addrlen, fd);

}


void saveConfig_externalSocket (struct sockaddr_in remaddr, socklen_t addrlen, int fd)
{
    Command saveCommand ("save");
    unsigned char buff ;
    for (int i = 0; i < COMMAND_SIZE; i ++)
    {
        buff = saveCommand.getCommandFormatIndex(i);
        if (sendto(fd, &buff, 1, 0, (struct sockaddr *)&remaddr, addrlen) < 0)
            perror("sendto");
        usleep(5000);

    }
    close (fd);
    usleep (500000);

}




void SocketSendTo::commandSent(Command com, const char* IP_Address)
{
    cout<< com.getName()<<": Command"<< " [";
    for (int i = 0 ; i<5; i++)
    {
        cout << hex <<(int) com.getCommandFormatIndex(i)<< " ";
    }
    cout <<"]"<< " Has been to: " << IP_Address << endl;
}

