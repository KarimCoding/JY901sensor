#ifndef SAVESTRUCT_H
#define SAVESTRUCT_H
#include "consts.h"
struct saveStruct
{
	unsigned char data[12];
};

struct pktStruct
{
	unsigned char data[MAXBUFLEN];	
};

#endif /* SAVESTRUCT_H */
