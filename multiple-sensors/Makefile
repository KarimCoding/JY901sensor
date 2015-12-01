#
# http://mrbook.org/blog/tutorials/make/
#

CC=g++
CFLAGS=-c -Wall
LDFLAGS=-L/usr/local/lib -lserial -lpthread
SOURCES=readAndSave.cpp packetIdentifier22.cpp checkPacket.cpp checkHeader.cpp checkHeader2.cpp checkSum.cpp savePacket.cpp writeTime.cpp timeOutput.cpp wgdaytime.cpp globals.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=readAndSave

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o *~
