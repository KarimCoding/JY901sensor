#ifndef SOCKETSENDTO_H
#define SOCKETSENDTO_H
#include "Command.h"


class SocketSendTo
{
    public:
        SocketSendTo();
        static void sendToSensor (Command comm,const char* IPAddress);
    protected:
    private:
};

#endif // SOCKETSENDTO_H
