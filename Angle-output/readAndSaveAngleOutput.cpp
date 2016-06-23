#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>

#include "AngleOutput.h"

using namespace std;

char next_byte;
unsigned char uc;

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
	 while( serial_port.rdbuf()->in_avail() == 0 );
	 serial_port.get(next_byte); // geting the data from serial port byte by byte
	 uc = next_byte; // storring the byte in an unsigned char
	 std::cerr << std::setw(2) << std::setfill('0') << std::hex <<((int)(uc)) << " "; // showing the bytes in hex form on the terminal
	 AngleOutput(uc); // save the Angle output packet	 
    }
    
    std::cerr << std::endl ;
    return EXIT_SUCCESS ;
}

