#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>

using namespace std;
void AngleOutput(unsigned char uc);

bool flag(false);
int i = 1;
unsigned char angle[11];

int main( int    argc, char** argv  )
{
    
    //
    // Open the serial port.
    //
    using namespace LibSerial ;
    SerialStream serial_port ;
    string port;
    cout << "Please specify your port. Example: /dev/ttyUSB0"<< endl<<"My port is: ";
    cin >> port;
    // serial_port.Open( "/dev/ttyUSB1" ) ;
    serial_port.Open(port) ;
    if ( ! serial_port.good() ) 
    {
        std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
                  << "Error: Could not open serial port." 
                  << std::endl ;
        exit(1) ;
    }
    //
    // Set the baud rate of the serial port.
    //
    serial_port.SetBaudRate( SerialStreamBuf::BAUD_115200 ) ;
    if ( ! serial_port.good() ) 
    {
        std::cerr << "Error: Could not set the baud rate." << std::endl ;
        exit(1) ;
    }
    //
    // Set the number of data bits.
    //
    serial_port.SetCharSize( SerialStreamBuf::CHAR_SIZE_8 ) ;
    if ( ! serial_port.good() ) 
    {
        std::cerr << "Error: Could not set the character size." << std::endl ;
        exit(1) ;
    }
    //
    // Disable parity.
    //
    serial_port.SetParity( SerialStreamBuf::PARITY_NONE ) ;
    if ( ! serial_port.good() ) 
    {
        std::cerr << "Error: Could not disable the parity." << std::endl ;
        exit(1) ;
    }
    //
    // Set the number of stop bits.
    //
    serial_port.SetNumOfStopBits( 1 ) ;
    if ( ! serial_port.good() ) 
    {
        std::cerr << "Error: Could not set the number of stop bits."
                  << std::endl ;
        exit(1) ;
    }
    //
    // Turn off hardware flow control.
    //
    serial_port.SetFlowControl( SerialStreamBuf::FLOW_CONTROL_NONE ) ;
    if ( ! serial_port.good() ) 
    {
        std::cerr << "Error: Could not use hardware flow control."
                  << std::endl ;
        exit(1) ;
    }
    //
    // Keep reading data from serial port and print it to the screen.
    //
    while(true)
    {
         char next_byte;
	 unsigned char uc;

	 while( serial_port.rdbuf()->in_avail() == 0 );
	 serial_port.get(next_byte); // geting the data from serial port byte by byte
	 uc = next_byte; // storring the byte in an unsigned char 
	 std::cerr << std::setw(2) << std::setfill('0') << std::hex << ((int)(uc)) << " "; // showing the bytes in hex form on the terminal
       	 AngleOutput(uc);	
    }
    
    std::cerr << std::endl ;
    return EXIT_SUCCESS ;
}

//
// Function that save the Angle output packet to a text file 
//
void AngleOutput(unsigned char uc)
{

  if (uc==0x53 || flag==true) 
	   {
	     angle[0]=0x55; // first byte in the packet is always 0x55
	     flag=true;
	     angle[i]= int(uc);
	     i++;
	     if(i>10){
	       flag=false;
	       cout<<"i = "<<i<<endl;
	       int sum=0;
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
	       for(i=0; i < 10 ; i++)
		 {
		   sum+=(int)(angle[i]);
		 }

	       unsigned char sumC = sum;
		  
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
	       if ( int(sumC) == int(angle[10]))
		 {
		   for(i=0; i < 11 ; i++)
		     {
		       file << std::setw(2) << std::setfill('0')<< std::hex <<(int)(angle[i]) << " " ;
		     }
		   file << endl ;
		 }
	        file.close();
	       i=1;
	     }
	   }
}
