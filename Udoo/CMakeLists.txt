# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
project (listener)
cmake_minimum_required (VERSION 2.8.11)

link_directories(/usr/local/lib)
link_directories(${CMAKE_CURRENT_BINARY_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_BINARY_DIR ${PROJECT_BINARY_DIR}/bin)

set (CMAKE_EXE_LINKER_FLAGS)
set (CMAKE_MODULE_LINKER_FLAGS)
set (CMAKE_SHARED_LINKER_FLAGS)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

#add_library(libs STATIC /usr/local/lib/libserial/src/SerialStream.h)

add_executable (listener listener.cpp serialPort.cpp serialPort.h packetIdentifier2.cpp packetIdentifier2.h checkPacket.cpp checkPacket.h checkSum.cpp checkSum.h savePacket.cpp savePacket.h timeOutput.cpp timeOutput.h AngleOutput.cpp AngleOutput.h wgdaytime.cpp wgdaytime.h)
target_link_libraries(listener serial)


#target_link_libraries(listener ${libserial_SRCS})
#target_link_libraries(listener ${LIBS})

option(VERBOSITY "Option description" ON)
#option(WITH_FEATURE_B "Option description" OFF)

if(VERBOSITY)
  add_definitions(-DDEBUG)
endif()
#if(WITH_FEATURE_B)
#  add_definitions()
#endif()

#add_subdirectory(Time-output)
#add_subdirectory(Angle-output)
