#include "realtime.h"

using namespace cv;
using namespace std;

void drawText(Mat &f, string text){

        int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
        double fontScale = 1.8;
        int thickness = 2;
        int baseline=0;
        Size textSize = getTextSize(text, fontFace,
                            fontScale, thickness, &baseline);
        Point textOrg((f.cols - textSize.width)/2 - 100,
              (f.rows + textSize.height)/2 - 100);
        putText(f, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 1);


}

RealTimeVideo::RealTimeVideo(){


}

RealTimeVideo::RealTimeVideo(int pBuffLen, VideoCapture *pCapture)
{
  capture = pCapture;
  buffLen = pBuffLen;

  ans = 34;

  cerr << "\nInitialized RealtimeVideo\n" ;

}

bool RealTimeVideo::putFrameInBuffer(Mat &f){

    
    // gray = preProcesor(frame);
    gray = f;
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

    try{
      capture->read(f); 
    }
    catch(exception &e){
      cout << e.what() ;
    }

      waitKey(5);
    frame = f;
    
   //  if (!bSuccess)
   // {
   //       cout << "ERROR: Cannot read a frame from video file" << endl;
   //       break;
   //  }
    // putFrameInBuffer(frame);
    
  }
}

void RealTimeVideo::showFrameOutput(){

          drawText(frame, to_string(ans));
          imshow("output", frame);

}
void RealTimeVideo::UI(){

  cerr << "\nStarting UI Thread\n" ;
    waitKey(1000);
  while(true){

      if(waitKey(5) >= 0) break;

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
    producer_t.join();

}

void RealTimeVideo::processor(){

  cerr << "\nStarting Processor Thread\n" ;
  Mat sample;
  while(1){

    sample = getSample();
    ans = processSample(sample);

  }

}

Mat RealTimeVideo::getSample(){

  Mat ret;
  return frame ;
}
float RealTimeVideo::processSample(Mat &sample){

  return 12 ;
}
