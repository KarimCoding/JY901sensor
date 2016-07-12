#include "listener.h"
void wifi::term(int signum)
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

int wifi::listener(dataStick &pkt)
{

	char time[35] = {};
	char *ip;
	char usec[5] = {};
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


    //Continually listen for socket connections
  //  while(!done){
//	while(1){
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
        freeaddrinfo(servinfo);
        addr_len = sizeof their_addr;
        if ((pkt.numbytes =  recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
                (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            exit(1);
        }
        printf("listener: got packet from %s\n",
                inet_ntop(their_addr.ss_family,
                    get_in_addr((struct sockaddr *)&their_addr),
                        s, sizeof s));
        //oepn stream once a connection has been established
        buf[pkt.numbytes] = '\0';
		close(sockfd);

	 	gettimeofday(&tv, NULL); 
        curtime=tv.tv_sec;
		strftime(time,30,"%T",localtime(&curtime));
		sprintf(usec, "%ld", tv.tv_usec);
		strcat(time,usec);
		pkt.passData(buf,s,time );

//    }// End brace for while loop
	return pkt.numbytes;
}   //End brace for main()


