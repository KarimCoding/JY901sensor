#ifndef USERINPUT_H
#define USERINPUT_H
#include "Command.h"


class UserInput
{
    public:
        UserInput();
        static void handleLEDOFF (Command , vector <string> );
        static void handleRate(Command ,vector <string> );
        static void handleBaud(Command ,vector <string> );
        static void handleReturn (Command ,vector <string> );
        static void handleTwoParam(Command, vector <string>);
        static void handleStandard (Command, vector <string>);
        static void handleIICAddress (Command, vector <string>);

    protected:
    private:
};

#endif // USERINPUT_H
