#include "opencvincludes.h"

#define rep(i,n) for(int i=0; i<n; i++)
#define trace(x)                 cerr << #x << ": " << x << endl;
#include <iostream>

using namespace cv;
using namespace std;


void drawCircle( Mat &img, Point center );
void drawText(Mat &f, string text);

template <typename T>
cv::Mat plotGraph(std::vector<T>& vals, int YRange[2]);
