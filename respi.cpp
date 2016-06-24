#include "respi.h"

#include <unistd.h>

using namespace cv;
using namespace std;

RespiVision::RespiVision(){


}


RespiVision::RespiVision(int pBuffLen, VideoCapture *pCapture):RealTimeVideo(pBuffLen, pCapture)
{

  cerr << "\nInitialized RespiVision\n" ;

}

float RespiVision::processSample(Mat &sample){

  sleep(1);
  return sum(sample)[0] ;
}
