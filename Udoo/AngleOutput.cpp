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

void AngleOutput(unsigned char angle[], FILE *&outF)
{
	    roll = (  (((int)(angle[3])) << 8) + ((int)(angle[2])) ) / 32768.0 * 180.0 ;
	    pitch = (  (((int)(angle[5])) << 8) + ((int)(angle[4])) ) / 32768.0 * 180.0 ;
	    yaw = (  (((int)(angle[7])) << 8) + ((int)(angle[6])) ) / 32768.0 * 180.0 ;
	    temperature = (  (((int)(angle[9])) << 8) + ((int)(angle[8])) ) /100.0 ;
	    for(iA=0; iA < 11 ; iA++)
	      {
            fprintf(outF,"%02x ",(int)(angle[iA]));
	      }
        fprintf(outF,"       roll is: %f pitch is: %f yaw is: %f temperature is: %f\n",((long double)(roll)),((long double)(pitch)),((long double)(yaw)),((long double)(temperature)));
}

