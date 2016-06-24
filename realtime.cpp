#include "realtime.h"

using namespace cv;
using namespace std;


RealTimeVideo::RealTimeVideo(){


}

RealTimeVideo::RealTimeVideo(int buffLen, VideoCapture *capture)
{

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

  i = 0;

  while(1){

    bool bSuccess = capture->read(frame); 

    if (!bSuccess)
   {
         cout << "ERROR: Cannot read a frame from video file" << endl;
         break;
    }
    putFrameInBuffer(frame);
    
  }
}
void RealTimeVideo::UI(){


}
