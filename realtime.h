#include "opencvincludes.h"
#include "helpers.h"
#include <iostream>
#include <thread>

using namespace cv;

class RealTimeVideo{

  VideoCapture *capture ;
  Mat *buffer;
  int buffLen ;
  int pos, newpos;
  int i ;

  bool putFrameInBuffer(Mat &f);


public:


  Mat frame, gray;
  RealTimeVideo();
  RealTimeVideo(int buffLen, VideoCapture *capture);

  void producer();
  void processor();
  void UI();
  void runThreads();

};

