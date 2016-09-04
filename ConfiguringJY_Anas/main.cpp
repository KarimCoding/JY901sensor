#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "SocketSendTo.h"
#include "UserInput.h"
#include "Command.h"
#include "constants.h"


#define BUFSIZE 2048
#define COMMAND_SIZE 5

using namespace std;


void handleInput (Command , vector <string>);
int findInVector (string, vector <string>);
unsigned char stringToHex (string );


int main(int argc, char *argv [5])
{
    vector <string> arguments;
    for (int x = 0; x< argc ; x++)
    {
        arguments.push_back(argv[x]);
    }


    if (arguments[2].compare("help")==0){Command::printAllCommands();}
    else {


    try
    {

        if (argc >> 1 && argc << 6)
        {



            Command newCommand (arguments[2]);

            if (newCommand.getNumber() < 0)
            {
                throw 1;
            }

            handleInput(newCommand, arguments);


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

    }
    return 0;
}



void handleInput (Command com, vector<string> arguments)
{
    if (com.getIsTwoParam() == 1)
    {
        UserInput::handleTwoParam(com, arguments);

    }
    else
    {

        int index = findInVector(com.getName(), commandName);

        switch (index)
        {


        case 0:
        {

            const char* IPAdd= arguments[1].c_str();
            SocketSendTo::sendToSensor (com, IPAdd);
            SocketSendTo::commandSent(com, IPAdd);
        break;
        }

    case 1:
    case 14:
    case 15:
    case 16:
    case 17:
        UserInput::handleStandard(com, arguments);
        break;


    case 2:
        UserInput::handleReturn (com,arguments);
        break;

    case 3:
        UserInput::handleRate(com,arguments);
        break;

    case 4 :
    case 28:
        UserInput::handleBaud(com,arguments);
        break;

    case 26:
        UserInput::handleIICAddress (com, arguments);
        break;
    case 27:
        UserInput::handleLEDOFF(com, arguments);
        break;


    }
}
}

