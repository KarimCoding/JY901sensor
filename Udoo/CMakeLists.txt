project (udoo)
cmake_minimum_required (VERSION 2.8.11)

link_directories(/usr/local/lib)
link_directories(${CMAKE_CURRENT_BINARY_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_BINARY_DIR ${PROJECT_BINARY_DIR}/bin)

set (CMAKE_EXE_LINKER_FLAGS)
set (CMAKE_MODULE_LINKER_FLAGS)
set (CMAKE_SHARED_LINKER_FLAGS)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

find_package (Threads)

add_executable	(udoo main.cpp collector.cpp listener.h dataPkt.h consts.h processData.cpp processData.h pktIden.cpp packetIdentifier2.h checkPacket.cpp checkPacket.h checkSum.cpp checkSum.h savePacket.cpp savePacket.h saveStruct.h)
#add_executable (udoo mail.cpp listener.cpp listener.h processData.cpp processData.h dataPkt.h consts.h packetIdentifier2.cpp packetIdentifier2.h checkPacket.cpp checkPacket.h checkSum.cpp checkSum.h savePacket.cpp s1avePacket.h timeOutput.cpp timeOutput.h AngleOutput.cpp AngleOutput.h wgdaytime.cpp wgdaytime.h)
#add_executable (udoo dumpFiles.cpp serialPort.cpp consts.h serialPort.h packetIdentifier2.cpp packetIdentifier2.h checkPacket.cpp checkPacket.h checkSum.cpp checkSum.h savePacket.cpp savePacket.h timeOutput.cpp timeOutput.h AngleOutput.cpp AngleOutput.h wgdaytime.cpp wgdaytime.h)

target_link_libraries(udoo -lboost_system)


option(VERBOSITY "Option description" ON)

if(VERBOSITY)
  add_definitions(-DDEBUG)
endif()

