#ifndef SOCKETSENDTO_H
#define SOCKETSENDTO_H
#include "Command.h"


class SocketSendTo
{
    public:
        SocketSendTo();
        static void sendToSensor (Command comm,const char* IPAddress);
        static void commandSent (Command, const char*);
    protected:
    private:
};

#endif // SOCKETSENDTO_H




