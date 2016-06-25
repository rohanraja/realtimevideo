#include "opencvincludes.h"
#include "helpers.h"
#include <iostream>
#include <thread>

using namespace cv;

class RealTimeVideo{

  VideoCapture *capture ;
  Mat *buffer;
  vector<Mat> frameBuffer ;
  int buffLen, sampleLen ;
  int pos, newpos;
  int idx ;
  Mat frame, gray;
  float ans ;

  bool putFrameInBuffer(Mat &f);


public:


  Point pt;

  RealTimeVideo();
  RealTimeVideo(int buffLen, VideoCapture *capture);

  void producer();
  void processor();
  void UI();
  void runThreads();

  virtual float processSample(vector<Mat> );
  virtual vector<Mat> getSample();
  virtual void showFrameOutput();

};

