#include "helpers.h"


using namespace cv;
using namespace std;

void drawCircle( Mat &img, Point center )
{
 int thickness = -1;
 int lineType = 8;

 circle( img,
         center,
         7,
         Scalar( 23, 23, 255 ),
         thickness,
         lineType );
}

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
