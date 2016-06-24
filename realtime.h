#include "opencvincludes.h"
#include "helpers.h"
#include <iostream>

using namespace cv;

class RealTimeVideo{

  VideoCapture *capture ;
  Mat *buffer;
  Mat frame, gray;
  int buffLen ;
  int pos, newpos;
  int i ;

  bool putFrameInBuffer(Mat &f);


public:

  RealTimeVideo();
  RealTimeVideo(int buffLen, VideoCapture *capture);

  void producer();
  void UI();

};

