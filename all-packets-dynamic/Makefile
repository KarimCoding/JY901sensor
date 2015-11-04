#
# http://mrbook.org/blog/tutorials/make/
#

CC=g++
CFLAGS=-c -Wall
LDFLAGS=-L/usr/local/lib -lserial -lpthread
SOURCES=readAndSave.cpp packetIdentifier2.cpp checkPacket.cpp checkHeader.cpp checkHeader2.cpp checkSum.cpp savePacket.cpp writeTime.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=readAndSave

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o *~
