#
# http://mrbook.org/blog/tutorials/make/
#

CC=g++
CFLAGS=-c -Wall
LDFLAGS=-L/usr/local/lib -lserial -lpthread
SOURCES=readAndSaveTime.cpp timeOutput.cpp wgdaytime.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=readAndSaveTime

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o *~
