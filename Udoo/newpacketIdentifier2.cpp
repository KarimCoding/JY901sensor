#include "packetIdentifier2.h"
#include "savePacket.h"
#include "saveStruct.h"
#define NUMBER_OF_BYTES 11

int i=0;
int pp = NUMBER_OF_BYTES + 2;
bool resultCheck;
unsigned char saveArray[11]; // an array to save the packets in it
unsigned char packetArray[11]; // an array to get the bytes coming from the sensor
unsigned char sumCAC;
bool flagon(false);

//passing header by value as to not corrupt the data packet in previous function call
void packetIdentifier2(unsigned char uc, std::vector<string> &goodData,std::vector<string> &badData,std::string &buf,std::string header)
{
	unsigned char sum = 0;
	saveStruct save;
	packetArray[i]= uc; // push the bytes coming from the sensor into the packetArray
	if(!flagon && uc==0x55)
	{
		flagon = true;
		packetArray[0] = uc;
		i=0;	//start saving from here
	}
	if(i==1&&flagon)
	{
		packetArray[1] = uc;
    	resultCheck =  checkPacket(packetArray); // call the function "checkPacket" which check for the packet's header
	}
	if(i>1&&resultCheck==false)
	{
		i=0;
		flagon=false;
	}
	if(resultCheck == true && i>9)
    {
		for(int l=0;l<11;l++)
			saveArray[l]=packetArray[l];
		memcpy(save.data,saveArray,12);
		save.data[11]='\0';
        if( checkSum(std::ref(save),std::ref(sum)))
			savePacket(std::ref(save),std::ref(goodData),std::ref(buf));

		else{
			//sending header by ref just to use same memory space no need to worry about corruption here
			write_bad_dat(std::ref(save),std::ref(badData),std::ref(header),std::ref(sum));
			printf("\nbad checksum\n");
			}
		flagon = false;
		resultCheck = false;
    }   // End brace for if(result ...
   	i=(i+1)%11;
}



