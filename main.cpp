#include <iostream>
#include "respi.h"

using namespace std;
using namespace cv;

Mat toGray(Mat &m){

  Mat ret ;

  cvtColor(m, ret, COLOR_BGR2GRAY);

  return ret ;

}

int main2(int argc, const char *argv[])
{
  
  VideoCapture cap(0); // open the default camera
  RealTimeVideo r(100, &cap) ;
  r.runThreads();

  return 0;
}

int main(int argc, const char *argv[])
{
  
  if(argc > 1){

    VideoCapture cap(argv[1]); // open the default camera
    RespiVision r(1000, &cap) ;
    r.runThreads();
  }
  else{

    VideoCapture cap(0); // open the default camera
    RespiVision r(1000, &cap) ;
    r.runThreads();
  }

  return 0;
}
