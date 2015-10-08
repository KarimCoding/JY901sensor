# JY901sensor

This c++ code is to read serial data from a JY901 sensor on linux.

This code uses the Libserial library that can be find here : https://github.com/crayzeewulf/libserial/

To be able to compile the code, you need to install libserial-dev and
python-sip-dev. They are available through ubuntu's synaptic or package
manager.

The "Angle output" folder contain the code for writing the Angle output packet, and the "Time output" folder contain the code for writing the time of the packet.

To compile the codes you need to be in the folder that you want to use and write into the command : make

**You may need to change the "/usr/local/lib" to where you installed
seriallib on your machine.
