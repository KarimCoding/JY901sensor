// For more details:
// http://stackoverflow.com/questions/588307/c-obtaining-milliseconds-time-on-linux-clock-doesnt-seem-to-work-properl

#include <sys/time.h>
#include <unistd.h>

long int gettimeofdayInMilliSeconds ()
{
  struct timeval thedaytime;
  
  long mtime;    

  gettimeofday(&thedaytime, NULL);
  mtime = ((thedaytime.tv_sec) * 1000 + thedaytime.tv_usec/1000.0) + 0.5;

  return (mtime);
}
