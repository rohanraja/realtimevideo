#include "respi.h"

#include <unistd.h>

using namespace cv;
using namespace std;

RespiVision::RespiVision(){


}


RespiVision::RespiVision(int pBuffLen, VideoCapture *pCapture):RealTimeVideo(pBuffLen, pCapture)
{

  cerr << "\nInitialized RespiVision\n" ;
  Fs = 24 ;

}

template <typename T>
cv::Mat plotGraph(std::vector<T>& vals, int YRange[2])
{

    auto it = minmax_element(vals.begin(), vals.end());
    float scale = 1./ceil(*it.second - *it.first); 
    float bias = *it.first;
    int rows = YRange[1] - YRange[0] + 1;
    cv::Mat image = Mat::zeros( rows, vals.size(), CV_8UC3 );
    image.setTo(0);
    for (int i = 0; i < (int)vals.size()-1; i++)
    {
        cv::line(image, cv::Point(i, rows - 1 - (vals[i] - bias)*scale*YRange[1]), cv::Point(i+1, rows - 1 - (vals[i+1] - bias)*scale*YRange[1]), Scalar(0, 0, 255), 1);
    }

    return image;
}

float getDominantFreqs(Mat &timeSeries, float low, float high, int Fs, Point *pt, int width){

    cv::Mat fft;

    int n = timeSeries.cols ;

    cv::dft(timeSeries, fft, DFT_ROWS);

    int low_ind = (low * n ) / Fs ;
    int high_ind = ( high * n ) / Fs ;
    
    float amp ,x,y, curMax = 0, freqMax;

    for(int j=30000; j < timeSeries.rows; j++){

     if (low_ind <= 1)
       low_ind = 2 ;
      for(int i=low_ind-1; i< high_ind+1; i++){
        x = fft.at<double>(j , 2*i - 1);
        y = fft.at<double>(j , 2*i);
        amp = x*x + y*y ;

        if(amp > curMax){
          curMax = amp;
          freqMax =  (float)(i* Fs)/(float)(n) ;
          pt->y = j / width ; 
          pt->x = j % width ; 
        }

      }
    }

    return freqMax*60 ;

}

float RespiVision::processSample(vector<Mat> sample){

  if(sample.size() < 1)
    return -1;

  Mat sampleMat(sample[0].cols * sample[0].rows ,sample.size(), CV_8U) ;
  Mat gray ;
  uchar *arr;

  int width = sample[0].cols;

  rep(i, sample.size()){

    cvtColor(sample[i], gray, COLOR_BGR2GRAY);
    arr = gray.data ;
    rep(j, gray.total())
    sampleMat.at<uchar>(j, i) = arr[j];

  }

  sampleMat.convertTo(sampleMat, CV_64F) ;
  float ret = getDominantFreqs(sampleMat, 0.1, 0.9, Fs, &pt, width) ;

    Mat ys = sampleMat.row( pt.y*width + pt.x ).clone() ;

    double *y = ys.ptr<double>(0) ;
    vector<double> numbers(y, y + sample.size());

    int range[2] = {0, sample.size()};
    Mat plotted = plotGraph( numbers , range);

    imshow("plot" , plotted);
    waitKey(1);
  return ret ;
}
