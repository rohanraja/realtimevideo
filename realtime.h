#include "opencvincludes.h"
#include "helpers.h"
#include <iostream>
#include <thread>

using namespace cv;

class RealTimeVideo{

  VideoCapture *capture ;
  Mat *buffer;
  vector<Mat> frameBuffer ;
  int buffLen ;
  int pos, newpos;
  int i ;
  Mat frame, gray;
  float ans ;

  bool putFrameInBuffer(Mat &f);


public:


  RealTimeVideo();
  RealTimeVideo(int buffLen, VideoCapture *capture);

  void producer();
  void processor();
  void UI();
  void runThreads();

  virtual float processSample(Mat &);
  virtual Mat getSample();
  virtual void showFrameOutput();

};

