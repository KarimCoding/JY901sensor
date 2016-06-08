//
// Function that save the Angle output packet to a text file 
//
//#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>

using namespace std;

bool flagA(false);
int iA = 1;
unsigned char angle[11];
double roll;
double pitch;
double yaw;
double temperature;

void AngleOutput(unsigned char sumCAC,unsigned char angle[], FILE *outF)
{
//    printf("\n AngleOutput \n");
//	std::fstream file;
//	file.open(fileName, std::fstream::app);

	//
	//checking if the Sum is equal to the last byte of the package, if yes save it
	//
	if ( int(sumCAC) == int(angle[10]))
	  {
	    roll = (  (((int)(angle[3])) << 8) + ((int)(angle[2])) ) / 32768.0 * 180.0 ;
	    pitch = (  (((int)(angle[5])) << 8) + ((int)(angle[4])) ) / 32768.0 * 180.0 ;
	    yaw = (  (((int)(angle[7])) << 8) + ((int)(angle[6])) ) / 32768.0 * 180.0 ;
	    temperature = (  (((int)(angle[9])) << 8) + ((int)(angle[8])) ) /100.0 ;
	    for(iA=0; iA < 11 ; iA++)
	      {
		//file << std::setw(2) << std::setfill('0')<< std::hex <<(int)(angle[iA])<<" ";
            fprintf(outF,"%02x ",(int)(angle[iA]));
	      }
        fprintf(outF,"       roll is: %f pitch is: %f yaw is: %f temperature is: %f\n",((long double)(roll)),((long double)(pitch)),((long double)(yaw)),((long double)(temperature)));
	    /*file << "       "<<"roll is: "<< std::dec <<(long double)roll<<"  pitch is: "<<(long double)pitch<<"  yaw is: "<<(long double)yaw<<"  temperature is: "<<(long double)temperature<<"  ";
	    file << endl;*/
	  }
	//file.close();
	iA=1;
      }

