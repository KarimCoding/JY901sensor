//
// Function that save the Angle output packet to a text file 
//
#include <SerialStream.h>
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

void AngleOutput(unsigned char uc)
{

  if (uc==0x53 || flagA==true) 
    {
      angle[0]=0x55; // first byte in the packet is always 0x55
      flagA=true;
      angle[iA]= int(uc);
      iA++;
      if(iA>10){
	flagA=false;
	cout<<"iA = "<<iA<<endl;
	int sumA=0;
	std::fstream file;
	file.open("Angle_Output.txt", std::fstream::app);
	
	//
	//Showing the decimal form
	//
	// for(i=0; i < 11 ; i++){
	//   file << int(angle[i]) << " " ;
	// }

	//
	//Calculating the Sum for the 10 bytes of the packet
	//
	for(iA=0; iA < 10 ; iA++)
	  {
	    sumA += (int)(angle[iA]);
	  }
	
	unsigned char sumCA = sumA;
	
	//
	//Testing the checkSUM
	//
	// file << endl ;
	// file << std::hex << int(angle[10]) << endl;
	// // file << sum << endl;
	// file << std::hex <<(int) sumC << endl;
	//  //	 file<< std::setw(2) << std::setfill('0') << std::hex << sum << endl;
	// if( int(sumC) == int(angle[10])){ file<<" correct " << endl;}
	// file.close();
	
	//
	//checking if the Sum is equal to the last byte of the package, if yes save it
	//
	if ( int(sumCA) == int(angle[10]))
	  {
	    for(iA=0; iA < 11 ; iA++)
	      {
		file << std::setw(2) << std::setfill('0')<< std::hex <<(int)(angle[iA])<<" ";
	      }
	    file << endl;
	  }
	file.close();
	iA=1;
      }
    }
}
