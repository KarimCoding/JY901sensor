//This code is intended for file streaming purposes

bool openstream(FILE*& outF,char filename[]){

}   //End brace for openstream
bool print2file(FILE *&outF){
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



}   //End brace for print2File


bool closestream(FILE *&outF){


}   //End brace for closestream

