#include "realtime.h"

using namespace cv;
using namespace std;


RealTimeVideo::RealTimeVideo(){


}

RealTimeVideo::RealTimeVideo(int pBuffLen, VideoCapture *pCapture)
{
  capture = pCapture;
  buffLen = pBuffLen;

  cerr << "\nInitialized RealtimeVideo\n" ;

}

bool RealTimeVideo::putFrameInBuffer(Mat &f){

    cvtColor(frame, gray, COLOR_BGR2GRAY);
    // gray = gray(roi);

    newpos = i%buffLen;
    uchar *arr = gray.data ;
    rep(j, gray.total())
      buffer->at<uchar>(j, newpos) = arr[j];
    pos = newpos;

    i++;
  return true;
}

void RealTimeVideo::producer(){

  cerr << "\nStarting Producer Thread\n" ;

  i = 0;
  Mat f;

  while(1){

    bool bSuccess = capture->read(f); 

    frame = f ;
    
    if (!bSuccess)
   {
         cout << "ERROR: Cannot read a frame from video file" << endl;
         break;
    }
    // putFrameInBuffer(frame);
    
  }
}
void RealTimeVideo::UI(){

  cerr << "\nStarting UI Thread\n" ;

  waitKey(1000);
  while(true){

      if(waitKey(1) >= 0) break;

        try{
          imshow("output", frame);
        }catch(exception &e){
        }

  }

}

void RealTimeVideo::runThreads(){

    thread producer_t(&RealTimeVideo::producer, this);
    thread UI_t(&RealTimeVideo::UI, this);

    cerr << "\nLaunched Threads\n" ;

    waitKey(0);
}

void RealTimeVideo::processor(){

  cerr << "\nStarting Processor Thread\n" ;

}
