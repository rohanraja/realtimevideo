#include "realtime.h"

using namespace cv;
using namespace std;

class RespiVision : public RealTimeVideo{

  public:

  RespiVision();

  RespiVision(int buffLen, VideoCapture *capture);

  float processSample(Mat &);

};
