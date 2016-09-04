#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

using namespace std;



class Command
{
    public:
        Command(string name);
        static void printCommand(Command comm);
        static void printAllCommands ();

        std::string getName() { return name; }
        void setName(string val) { name = val; }

        string getDescription() { return description; }
        void setDescription(string val) { description = val; }

        int getNumber() { return number; }
        void setNumber(int val) { number = val; }

        bool getIsTwoParam() { return isTwoParam; }
        void setIsTwoParam(bool val) { isTwoParam = val; }

        unsigned char getHexAddress() { return hexAddress; }
        void setHexAddress(unsigned char val) { hexAddress = val; }

        unsigned char getCommandFormatIndex (int index) {return commandFormat [index];}
        void setCommandFormatIndex (unsigned char newVal, int index) {commandFormat [index] = newVal;}

       // int getCommandSize () {return commandSize ;}


    private:
        string name;
        string description;
        int number;
        bool isTwoParam = false;
        unsigned char hexAddress;
        unsigned char commandFormat [5] ;

};

#endif // COMMAND_H
