#include "realtime.h"

using namespace cv;
using namespace std;


RealTimeVideo::RealTimeVideo(){


}

RealTimeVideo::RealTimeVideo(int pBuffLen, VideoCapture *pCapture)
{
  capture = pCapture;
  buffLen = pBuffLen;
  frameBuffer.resize(buffLen);

  ans = 0;
  sampleLen = 200;


  cerr << "\nInitialized RealtimeVideo\n" ;

}

bool RealTimeVideo::putFrameInBuffer(Mat &f){
    
    pos = idx%buffLen;
    frameBuffer[pos] = f.clone();
    idx++;

    return true;

}

void RealTimeVideo::producer(){

  cerr << "\nStarting Producer Thread\n" ;

  idx = 0;
  Mat f;

  while(1){

    capture->read(f); 
    frame = f.clone();
    putFrameInBuffer(f);
    
    
  }
}

void RealTimeVideo::showFrameOutput(){

          drawText(frame, to_string(ans));
          drawCircle(frame, pt);
          imshow("output", frame);

}
void RealTimeVideo::UI(){

  cerr << "\nStarting UI Thread\n" ;
    waitKey(1000);
  while(true){

      if(waitKey(50) >= 0) break;

        try{
          showFrameOutput();
        }catch(exception &e){

        }
  }

}

void RealTimeVideo::runThreads(){

    thread producer_t(&RealTimeVideo::producer, this);
    waitKey(10);
    thread UI_t(&RealTimeVideo::UI, this);
    waitKey(10);
    thread processor_t(&RealTimeVideo::processor, this);
    waitKey(10);

    cerr << "\nLaunched Threads\n" ;

    waitKey(0);
    producer_t.join();

}

void RealTimeVideo::processor(){

  cerr << "\nStarting Processor Thread\n" ;
  vector<Mat> sample;
  while(1){

    sample = getSample();
    ans = processSample(sample);

  }

}

vector<Mat> RealTimeVideo::getSample(){
  
  int end = pos ;
  int st = pos - sampleLen;
  if(st < 0)
    st = 0;

  vector<Mat> ret(frameBuffer.begin()+st, frameBuffer.begin()+end);
  return ret ;
}
float RealTimeVideo::processSample(vector<Mat> sample){

  return 1 ;
}
