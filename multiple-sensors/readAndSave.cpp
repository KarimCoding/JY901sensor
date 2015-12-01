#include <boost/circular_buffer.hpp>
#include <SerialStream.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <new>

#include "packetIdentifier2.h"
#include "packetIdentifier22.h"
#include "writeTime.h"


using namespace std;

char next_byte;
char next_byte2;
unsigned char uc;
unsigned char uc2;
unsigned char saveArray[22];
unsigned char packetArray[22];
unsigned char saveArray2[22];
unsigned char packetArray2[22];
int i=0;
int i2=0;
int mainPacketArrayNumb = 22;

int main(int  /*argc*/, char* /*argv*/[])
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
    //the second sensor
    //
    using namespace LibSerial ;
    SerialStream serial_port2 ;
    string port2;
    cout << "Please specify your second  port. Example: /dev/ttyUSB1"<< endl<<"My port is: ";
    cin >> port2;
    // serial_port.Open( "/dev/ttyUSB1" ) ;
    serial_port2.Open(port2) ;
    if ( ! serial_port2.good() ) 
    {
        std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
                  << "Error: Could not open serial port." 
                  << std::endl ;
        exit(1) ;
    }
    //
    // Set the baud rate of the serial port.
    //
    serial_port2.SetBaudRate( SerialStreamBuf::BAUD_115200 ) ;
    if ( ! serial_port2.good() ) 
    {
        std::cerr << "Error: Could not set the baud rate." << std::endl ;
        exit(1) ;
    }
    //
    // Set the number of data bits.
    //
    serial_port2.SetCharSize( SerialStreamBuf::CHAR_SIZE_8 ) ;
    if ( ! serial_port2.good() ) 
    {
        std::cerr << "Error: Could not set the character size." << std::endl ;
        exit(1) ;
    }
    //
    // Disable parity.
    //
    serial_port2.SetParity( SerialStreamBuf::PARITY_NONE ) ;
    if ( ! serial_port2.good() ) 
    {
        std::cerr << "Error: Could not disable the parity." << std::endl ;
        exit(1) ;
    }
    //
    // Set the number of stop bits.
    //
    serial_port2.SetNumOfStopBits( 1 ) ;
    if ( ! serial_port2.good() ) 
    {
        std::cerr << "Error: Could not set the number of stop bits."
                  << std::endl ;
        exit(1) ;
    }
    //
    // Turn off hardware flow control.
    //
    serial_port2.SetFlowControl( SerialStreamBuf::FLOW_CONTROL_NONE ) ;
    if ( ! serial_port2.good() ) 
    {
        std::cerr << "Error: Could not use hardware flow control."
                  << std::endl ;
        exit(1) ;
    }


    //
    // Keep reading data from serial port and print it to the screen.
    //
    writeTime();// call the writeTime function that write the date and time into the file 
    while(true)
    {
      while( serial_port.rdbuf()->in_avail() == 0 );
      serial_port.get(next_byte); // geting the data from serial port byte by byte
      uc = next_byte; // storring the byte in an unsigned char
      //std::cerr << std::setw(2) << std::setfill('0') << std::hex <<((int)(uc)) <<" "; // showing the bytes in hex form on the terminal
      packetIdentifier22(uc,port,saveArray,packetArray,i); // call the function that identify the packets and save it into the file
      i=(i+1)%((mainPacketArrayNumb));
       

      while( serial_port2.rdbuf()->in_avail() == 0 );
      serial_port2.get(next_byte2); // geting the data from serial port byte by byte
      uc2 = next_byte2; // storring the byte in an unsigned char
      std::cerr << std::setw(2) << std::setfill('0') << std::hex <<((int)(uc2)) << " "; // showing the bytes in hex form on the terminal
      packetIdentifier22(uc2,port2,saveArray2,packetArray2,i2); // call the function that identify the packets and save it into the file
      i2=(i2+1)%((mainPacketArrayNumb));


    }
    std::cerr << std::endl ;
    return EXIT_SUCCESS ;
}

