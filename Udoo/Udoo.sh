
#!/bin/sh
if [ "$1" = "debug" ]
then
    cmake . -DVERBOSITY=1
    make
    ./bin/listener
else
    cmake . -DVERBOSITY=0
    make
    ./bin/listener
fi

