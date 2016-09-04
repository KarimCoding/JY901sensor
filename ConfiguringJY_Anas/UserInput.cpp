#include "UserInput.h"
#include "SocketSendTo.h"
#include "Command.h"
#include "constants.h"
#include <iostream>
#include <string>
#include <bitset>

int findInVector (int , vector <int> );
int findInVector (string , vector <string> );
unsigned char stringToHex (string);



using namespace std;

UserInput::UserInput()
{
}

void UserInput::handleLEDOFF (Command com, vector <string> arguments)
{
    if (arguments[3].compare("off") ==0 || arguments[3].compare(  "OFF" ) == 0)
    {
        com.setCommandFormatIndex((unsigned char) 0x01, 3 );
    }

    const char* IPAdd= arguments[1].c_str();
    SocketSendTo::sendToSensor (com, IPAdd);
    SocketSendTo::commandSent (com, IPAdd);
}


void UserInput::handleRate(Command com,vector <string> arguments)
{
    vector <string> options = {"0.1", "0.5", "1", "2", "5", "10", "20", "50", "100" , "200", "single", "not"};
    vector <unsigned char> rateOptions= {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c};

    int index = findInVector(arguments[3], options);
    if (index < 0)
        cout << "Choose a valid option [argument]"<< endl;
    else
    {
        com.setCommandFormatIndex(rateOptions[index], 3);
        const char* IPAdd= arguments[1].c_str();
        SocketSendTo::sendToSensor (com, IPAdd);
        SocketSendTo::commandSent (com, IPAdd);
    }
}


void UserInput::handleBaud(Command com,vector <string> arguments)
{


    int index = findInVector(arguments[3], options);
    if (index < 0)
        cout << "Choose a valid option [arg3]"<< endl;
    else
    {
        com.setCommandFormatIndex(unsignedChars[index], 3);
        const char* IPAdd= arguments[1].c_str();
        SocketSendTo::sendToSensor (com, IPAdd);
        SocketSendTo::commandSent (com, IPAdd);
    }
}

void UserInput::handleReturn (Command com,vector <string> arguments)
{
    if (arguments[3].compare("all")==0 || arguments[3].compare("ALL")==0)
    {
        com.setCommandFormatIndex((unsigned char) 0xFF, 3);
        const char* IPAdd= arguments[1].c_str();
        SocketSendTo::sendToSensor (com, IPAdd);
        SocketSendTo::commandSent (com, IPAdd);
    }
    else
    {
        unsigned long long_binary = std::bitset<8>(arguments[3]).to_ulong();
        unsigned char hexVal = long_binary;
        com.setCommandFormatIndex((unsigned char) long_binary, 3);
        const char* IPAdd= arguments[1].c_str();
        SocketSendTo::sendToSensor (com, IPAdd);
        SocketSendTo::commandSent (com, IPAdd);
    }
}


void UserInput::handleTwoParam (Command com, vector <string> arguments)
{
    cout << "Usage(in Hex): ./Program_name IP_Address "<< com.getName()<< " LowByte HighByte"<<endl;

    unsigned char lowByte = stringToHex(arguments[3]);
    unsigned char highByte = stringToHex(arguments[4]);

    com.setCommandFormatIndex(lowByte, 3);
    com.setCommandFormatIndex(highByte, 4);

    const char* IPAdd= arguments[1].c_str();
    SocketSendTo::sendToSensor (com, IPAdd);
    SocketSendTo::commandSent (com, IPAdd);
}




/// Please note: This is a Generic function, it is the users' responsibility to ensure the selection of a valid
/// option. For example; if users' are to use an invalid option (such as option 8) this function will still work
void UserInput::handleStandard (Command com, vector <string> arguments)
{
    cout << "Usage: ./Program_name IP_Address " << com.getName() << " Option_Number(starts at 0)"<< endl;
    std::string str_dec = arguments [3];
    std::string::size_type sz;   // alias of size_t
    int index = std::stoi (str_dec,&sz);

    com.setCommandFormatIndex(hexOptions[index],3);
    const char* IPAdd= arguments[1].c_str();
    SocketSendTo::sendToSensor (com, IPAdd);
    SocketSendTo::commandSent (com, IPAdd);
}



void UserInput::handleIICAddress (Command com,vector <string> arguments)

{
    unsigned char IICAdd = stringToHex(arguments[3]);
    com.setCommandFormatIndex(IICAdd, 3);
    const char* IPAdd= arguments[1].c_str();
    SocketSendTo::sendToSensor (com, IPAdd);
    SocketSendTo::commandSent (com,IPAdd );

}




unsigned char stringToHex (string userInput)
{
    string str = userInput;
    char *cstr = &str[0u];
    int d;
    unsigned char c;
    sscanf(cstr ,"%02x", &d);
    c=(unsigned char)d;

    return c;
}


