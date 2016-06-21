# JY901sensor

This c++ code is to read data from a JY901 sensor on linux over wifi utilizing UDP packets.

To compile the code you need to download and install cmake. 

    sudo apt-get install cmake

Once cmake is installed create a build folder inside the Udoo folder and create the makefile with the following commands

    mkdir build
    cd build
    cmake ../
    make

Once the compiliation is completed run the program with the following command

    ./bin/listener
This code will begin listening on port 8899 for a packets sent as UDP packets and store the data in a text file with the date of when the code was executed as long as the data is in the correct data headers such as 0x55 0x50, 0x55 0x51, ... 0x55 0x58 followed by 9 bytes of data. If the data does not follow this format it will be stored in bad_data.txt


There are build options for the precompiler directives
By typing the following in place of cmake ../

    cmake ../ -DVERBOSITY=1

The output text file will also include calculations for roll,pitch, yaw, temperature, and the time provided by the JY sensor



