//
//http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
//

//
// function that writes the date and time
//
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

void writeTime() {
  std::fstream file; // for saving the data on a file
  file.open("test.txt", std::fstream::app); // open the file that you want to save data in it
  time_t t = time(0);   // get time now
  struct tm * now = localtime( & t );
  // cout << (now->tm_year + 1900) << '-' 
  //      << (now->tm_mon + 1) << '-'
  //      <<  now->tm_mday << '-'
  //      <<  now->tm_hour << ':'
  //      <<  now->tm_min << ':'
  // 	 <<  now->tm_sec 
  //      << endl;
  file <<endl<< endl << (now->tm_year + 1900) << '-' 
       << (now->tm_mon + 1) << '-'
       <<  now->tm_mday << '-'
       <<  now->tm_hour << ':'
       <<  now->tm_min << ':'
       <<  now->tm_sec 
       << endl;
  file.close();
}
