#include <iostream>
#include "realtime.h"

using namespace std;

int main(int argc, const char *argv[])
{
  
  VideoCapture cap(0); // open the default camera
  RealTimeVideo r(100, &cap) ;
  r.runThreads();

  return 0;
}
