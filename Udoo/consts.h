// PORT CONFIG
#define MYPORT "8899"    // the port users will be connecting to

//BUFFER CONFIG
#define MAXBUFLEN 518   //4Mb buffer (512 * 8)

//COMMANDS
#define     SAVE    0x00;
#define     CALSW   0x01;
#define     RSW     0x02;
#define     RATE    0x03;
#define     BAUD    0x04;

//RETURN RATE
#define     R_01    0x01;
#define     R_05    0x02;
#define     R_1     0x03;
#define     R_2     0x04;
#define     R_5     0x05;
#define     R_10    0x06;
#define     R_20    0x07;
#define     R_50    0x08;
#define     R_100   0x09;
#define     R_200   0x0a;
#define     R_SINGLE 0x0b;
#define     R_NO    0x0c;

//BAUD RATE
#define     B_2400  0x00;
#define     B_4800  0x01;
#define     B_9600  0x02;
#define     B_19200 0x03;
#define     B_38400 0x04;
#define     B_57600 0x05;
#define     B_115200 0x06;
#define     B_230400 0x07;
#define     B_460800 0x08;
#define     B_921600 0x09;
