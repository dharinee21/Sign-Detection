#include "opencv2\highgui\highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argv, char** argc)
{
    int largest_area=0;
    int largest_contour_index=0;
    Rect bounding_rect;

    namedWindow("Control", CV_WINDOW_AUTOSIZE);

    int iLowH=0;
    int iHighH=179;

    int iLowS=0;
    int iHighS=255;

    int iLowV=0;
    int iHighV=255;

    cvCreateTrackbar("LowH","Control",&iLowH,179);
    cvCreateTrackbar("HighH","Control",&iHighH,179);

    cvCreateTrackbar("LowS","Control",&iLowS,255);
    cvCreateTrackbar("HighS","Control",&iHighS,255);

    cvCreateTrackbar("LowV","Control",&iLowV,255);
    cvCreateTRackbar("HighV","Control",&iHighV,255);

    Mat imgOriginal=imread("Pic.jpg");
    if(imgOriginal.empty())
    {
      cout<<"Error! image can't be loaded \n";
      system("pause");
      return -1;
  }

  Mat imgHSV;
  cvtColor(imgOriginal,imgHSV,color_BGR2HSV);

  Mat imgThreshold;

  inRange(imgHSV, Scalar(iLowH,iLowS,iLowV), Scalar(iHighH,iHighS,iHighV),imgThreshold);

  erode(imgThreshold,imgThreshold,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
  dilate(imgThreshold,imgThreshold,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));

  dilate(imgThreshold,imgThreshold,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
  erode(imgThreshold,imgThreshold,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));

  imshow("Thresholded image:", imgThreshold);

  vector<vector<point>> contours;
  vector<Vec4i> hierarchy;

  findContours(imgThreshold, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPRoX_SIMPLE);
  for(int i=0; i<contours.size(),i++)
  {
      double a=contourArea( contour[i],false);
      if(a>largest_area){
        largest_area=a;
        largest_contour_index=i;
        bounding_rect=boundingRect(contours[i]);
      }
  }

  Scalar color(255,255,255);
  drawContours(imgThreshold,contours,largest_contour_index,color,CV_FILLED,8,hierarchy);
  rectangle(imgOriginal,bounding_rect,Scalar(0,255,0),1,8,0);
  imshow("largest Contour", imgThreshold);

   waitKey(0);
  destroyWindow("Mywindow");



    return 0;
}
