// define what a parameter is

#ifndef CONSTANTS_H
#define CONSTANTS_H


#include <vector>
#include <string>

using namespace std;


static std::vector <string> commandName = { "SAVE", "CALSW", "RSW", "RATE", "BAUD", "AXOFFSET", "AYOFFSET", "AZOFFSET", "GXOFFSET", "GYOFFSET", "GZOFFSET", "HXOFFSET", "HYOFFSET", "HZOFFSET", "D0MODE", "D1MODE",
                                     "D2MODE", "D3MODE", "D0PWMH", "D1PWMH", "D2PWMH", "D3PWMH", "D0PWMT", "D1PWMT", "D2PWMT", "D3PWMT", "IICADDR", "LEDOFF", "GPSBAUD", "YYMM", "DDHH", "MMSS", "MS", "AX",  "AY", "AZ", "GX", "GY", "GZ", "HX", "HY", "HZ",
                                     "ROLL", "PITCH", "YAW", "TEMP", "D0STATUS", "D1STATUS", "D2STATUS", "D3STATUS", "PRESSUREL", "PRESSUREH", "HEIGHTL", "HEIGHTH", "LONL", "LONH", "LATL", "LATH", "GPSHEIGHT", "GPSYAW", "GPSVL", "GPSVH", "Q0",
                                     "Q1", "Q2", "Q3"
                                   };


static std::vector <unsigned char> hexArray = {0x00 ,0x01 ,0x02 ,0x03 ,0x04 ,0x05 ,0x06 ,0x07 ,0x08 ,0x09 ,0x0a ,0x0b ,0x0c ,0x0d ,0x0e, 0x0f,0x10 ,0x11 ,0x12 ,0x13 ,0x14 ,0x15 ,0x16, 0x17, 0x18, 0x19, 0x1a ,0x1b ,0x1c ,0x30 ,
                                        0x31 ,0x32 ,0x33 ,0x34 ,0x35 ,0x36 ,0x37 ,0x38 ,0x39 ,0x3a ,0x3b ,0x3c ,0x3d ,0x3e ,0x3f ,0x40 ,0x41 ,0x42 ,0x43 ,0x44 ,0x45 ,0x46 ,0x47 ,0x48 ,0x49 ,0x4a ,0x4b ,0x4c ,0x4d ,0x4e ,0x4f ,0x50 ,0x51 ,0x52 ,0x53 ,0x54
                                       };



static  std::vector <string> commandDescriptoin = {"Save" ,"Calibration","Return data content","Return data Speed","Baud rate","X axis Acceleration bias","Y axis Acceleration bias", "Z axis Acceleration bias","X axis angular velocity bias","Y axis angular velocity bias","Z axis angular velocity bias",
                                           "X axis Magnetic bias","Y axis Magnetic bias","Z axis Magnetic bias","D0 mode","D1 mode","D2 mode","D3 mode","D0PWM High-level width","D1PWM High-level width","D2PWM High-level width","D3PWM High-level width","D0PWM Period","D1PWM Period","D2PWM Period","D3PWM Period",
                                           "IIC address","Turn off LED","GPS baud rate","Year、Month","Day、Hour","Minute、Second","Millisecond","X axis Acceleration","Y axis Acceleration","Z axis Acceleration","X axis angular velocity","Y axis angular velocity","Z axis angular velocity","X axis Magnetic","Y axis Magnetic",
                                           "Z axis Magnetic","X axis Angle","Y axis Angle","Z axis Angle","Temperature","D0Status","D1Status","D2Status","D3Status","Pressure Low Byte","Pressure High Byte","Height Low Byte","Height High Byte","Longitude Low Byte","Longitude High Byte","Latitude Low Byte","Latitude High Byte",
                                           "GPS Height","GPS Yaw","GPS speed Low byte","GPS speed High byte","Quaternion Q0","Quaternion Q1","Quaternion Q2","Quaternion Q3"
                                          };



static int twoParamCommands [] {5,6,7,8,9,10,11,12,13,18,19,20,21,22,23,24,25
                        };






#endif // COMMAND_H
