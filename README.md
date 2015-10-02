# JY901sensor

This c++ code is to read serial data from a JY901 sensor on linux.

This code uses the Libserial library that can be find here : https://github.com/crayzeewulf/libserial/

To be able to compile the code, you need to install libserial-dev and
python-sip-dev. They are available through ubuntu's synaptic or package
manager.

You will need to compile it using the following command:
g++ -o readAndSave readAndSave.cpp -L/usr/local/lib -lserial -lpthread

You may need to change the "/usr/local/lib" to where you installed
seriallib on your machine.
