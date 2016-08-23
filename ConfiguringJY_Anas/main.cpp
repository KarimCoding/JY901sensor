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
#include "SocketSendTo.h"
//#include "port.h"
#include <time.h>
#include <unistd.h>
#include <map>

#define BUFSIZE 2048
#define COMMAND_SIZE 5

using namespace std;

static int SERVICE_PORT = 8899;
//char IPAddress[] = "192.168.1.1";

void saveConfig (struct sockaddr_in , socklen_t, int );
void sendToSensor (Command , struct sockaddr_in, socklen_t, int);
void handleInput (Command , vector <string>);
int findInVector (string, vector <string>);
void handleLEDOFF (Command, vector <string> );
void handleRate(Command, vector <string> );
void handleBaud(Command,vector <string>);
void handleReturn (Command,vector <string>);


int main(int argc, char *argv [5])
{

    /*
    argc = 5;
    //char* argv[5];
    argv[1] = "192.168.1.1";
    argv[2] = "ledoff";
    argv[3] = "On";
    argv[4] = "Anas";
    */


    vector <string> arguments;
    for (int x = 0; x< argc ; x++)
    {
        arguments.push_back(argv[x]);
    }


    try
    {

        if (argc >> 1 && argc << 6)
        {
            cout << arguments[2] << endl;
            cout << " step a"<< endl;

            Command newCommand (arguments[2]);
            cout << " step b"<< endl;
            if (newCommand.getNumber() < 0)
            {
                throw 1;
            }
            cout << " step c"<< endl;
            handleInput(newCommand, arguments);
            cout << " step unknown"<< endl;

        }

        else
        {
            cout << "Use correct number of arguments, seperated by a space. Usage: ./program_name arg1 arg2 arg3" << endl;
        }

    }
    catch (int e)
    {
        cout <<"This is not a valid Command. Please Check the list for correct spelling"<<endl;
    }

    return 0;
}



void handleInput (Command com, vector<string> arguments)
{
    if (com.getIsTwoParam() == 1)
    {
        cout << " step d"<< endl;
    }
    else
    {

        int index = findInVector(com.getName(), commandName);

        switch (index)
        {

        case 2:
            handleReturn (com,arguments);
            break;

        /*case "SAVE":
        break;
        case "CALSW":
        break;
        */
        case 3:
            handleRate(com,arguments);
            break;

        case 4:
            handleBaud(com,arguments);
            break;

        /*case "D0MODE":
            break;
        case "D1MODE":
            break;
        case "D2MODE":
            break;
        case "D3MODE":
            break;
        case "D0PWMHL":
            break;
        case "D1PWMHL":
            break;
        case "D2PWMHL":
            break;
        case "D3PWMHL":
            break;
        case "D0PWMTL":
            break;
        case "D1PWMTL":
            break;
        case "D2PWMTL":
            break;
        case "D3PWMTL":
            break;
        case "IICADDR":
            break;*/
        case 27:
            handleLEDOFF(com, arguments);
            break;
            // case "GPSBAUD":
            //  break;


        }
    }
}



void handleLEDOFF (Command com, vector <string> arguments)
{
    if (arguments[3].compare("off") ==0 || arguments[3].compare(  "OFF" ) == 0)
    {
        com.setCommandFormatIndex((unsigned char) 0x01, 3 );
    }

    const char* IPAdd= arguments[1].c_str();
    SocketSendTo::sendToSensor (com, IPAdd);
    cout<< com.getName()<<": Command Has been to: " << arguments[1]<< endl;
}


void handleRate(Command com,vector <string> arguments)
{
    vector <string> options = {"0.1", "0.5", "1", "2", "5", "10", "20", "50", "100" , "200", "single", "not"};
    vector <unsigned char> unsignedChars= {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c};

    int index = findInVector(arguments[3], options);
    if (index < 0)
        cout << "Choose a valid option [argument]"<< endl;
    else
    {
        com.setCommandFormatIndex(unsignedChars[index], 3);
        const char* IPAdd= arguments[1].c_str();
        SocketSendTo::sendToSensor (com, IPAdd);

        cout<< com.getName()<<": Command Has been to: " << arguments[1] << endl;
    }
}


void handleBaud(Command com,vector <string> arguments)
{
    vector <string> options = {"2400", "4800", "9600", "19200", "38400", "57600", "115200", "230400", "460800" , "921600"};
    vector <unsigned char> unsignedChars= {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};

    int index = findInVector(arguments[3], options);
    if (index < 0)
        cout << "Choose a valid option [arg3]"<< endl;
    else
    {
        com.setCommandFormatIndex(unsignedChars[index], 3);
        const char* IPAdd= arguments[1].c_str();
        SocketSendTo::sendToSensor (com, IPAdd);
        cout<< com.getName()<<": Command Has been to: " << arguments[1]<< endl;
    }
}

void handleReturn (Command com,vector <string> arguments)
{
    if (arguments[3].compare("all") || arguments[3].compare("ALL"))
    {
        com.setCommandFormatIndex((unsigned char) 0xFF, 3);
        const char* IPAdd= arguments[1].c_str();
        SocketSendTo::sendToSensor (com, IPAdd);
        cout<< com.getName()<<": Command Has been to: " << arguments[1]<< endl;
    }
    else
        cout << "Choose a valid option [arg3]"<< endl;

}



/*

int findInVector (string item, vector <string> listOfItems)
{
    for (int x = 0; x<listOfItems.size(); x++ )
    {
        if (listOfItems.at(x)== item)
        {
            return x;
        }
    }
    return -1;
}


*/











// main function
/*
 bool flag = 1;
 while (flag)
 {
 cout << "Sending Command using external socket" << endl;
 unsigned char LEDOFF = 0x00;
 Command ledOff ("ledoff");
 ledOff.setCommandFormatIndex(LEDOFF, 3);
 SocketSendTo::sendToSensor(ledOff, IPAddress);

 cout << "Your command has been sent" << endl;


 int x ;
 cin>>x;


 cout << "Sending Command using external socket" << endl;
 LEDOFF = 0x01;
 ledOff.setCommandFormatIndex(LEDOFF, 3);
 SocketSendTo::sendToSensor(ledOff, IPAddress);

 cout << "Your command has been sent" << endl;
 cin>>x;

 }

 */

