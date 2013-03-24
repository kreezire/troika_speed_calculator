//============================================================================
// Name        : troika_IP.cpp
// Author      : vipul
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#define pretest 1
#include <iostream>
#include <time.h>
#include"highgui.h"
#include "cv.h"
using namespace std;

void detectRed(IplImage *abc, int a[1000][1000])
{
	IplImage* imageRed = cvCreateImage(cvGetSize(abc), 8, 1);
	IplImage* imageGreen = cvCreateImage(cvGetSize(abc), 8, 1);
	IplImage* imageBlue = cvCreateImage(cvGetSize(abc), 8, 1);
	IplImage* imageAdd = cvCreateImage(cvGetSize(abc), 8, 1);
	IplImage* imageSub = cvCreateImage(cvGetSize(abc), 8, 1);
	cvSplit(abc, imageBlue, imageGreen, imageRed, NULL);
	//cvShowImage("assfasf", imageRed);
	cvAdd(imageBlue,imageGreen, imageAdd);
	cvSub(imageRed, imageAdd, imageSub);
	//cvShowImage("assfasf", imageSub);
	cvThreshold(imageSub,imageSub, 2, 255, CV_THRESH_BINARY );
	//cvInRangeS(imageRed, CvSc200, 255, imageSub);
	cvShowImage("Red Threshhold", imageSub);
	cvWaitKey(10);
	for(int i =0 ; i<imageSub->height; ++i )
	{
		for(int j= 0; j<imageSub->width; ++j)
		{
			if((uchar)(imageSub->imageData[i*imageSub->widthStep+j])>200)
				a[i][j]=1;
			else
				a[i][j]=0;

		}
	}
}
void detectGreen(IplImage* abc, int a[1000][1000])
{
	//IplImage* imageHSV = cvCreateImage(cvGetSize(abc), 8 , 3);
	IplImage* imageHue = cvCreateImage(cvGetSize(abc), 8 , 1);
	IplImage* imageSat = cvCreateImage(cvGetSize(abc), 8 , 1);
	IplImage* imageVal = cvCreateImage(cvGetSize(abc), 8 , 1);
	IplImage* imageRed = cvCreateImage(cvGetSize(abc), 8, 1);
	IplImage* imageGreen = cvCreateImage(cvGetSize(abc), 8, 1);
	IplImage* imageBlue = cvCreateImage(cvGetSize(abc), 8, 1);
	IplImage* imageAdd = cvCreateImage(cvGetSize(abc), 8, 1);
	IplImage* imageSub = cvCreateImage(cvGetSize(abc), 8, 1);
	cvSplit(abc, imageBlue, imageGreen, imageRed, NULL);
	//cvShowImage("sf", imageGreen);
	//cvCvtColor(abc, imageHSV, CV_BGR2HSV);
	//cvSplit(imageHSV, imageHue, imageSat, imageVal);
	//cvInRangeS(imageHSV, cvScalar(40,0,0), cvScalar(70,255,255), imageSub);
	//cvAdd(imageBlue,imageRed, imageAdd);
	//cvSub(imageGreen, imageAdd, imageSub);
	//cvShowImage("Green Threshholdvdsvsdv", imageSub);
	//cvThreshold(imageGreen,imageSub,80, 150, CV_THRESH_BINARY );
	cvInRangeS(imageGreen, cvScalar(100,0,0), cvScalar(255,255,255), imageSub);
	cvShowImage("Green Threshhold", imageSub);
	cvWaitKey(10);
	for(int i =0 ; i<imageSub->height; ++i )
	{
		for(int j= 0; j<imageSub->width; ++j)
		{
			if((uchar)(imageSub->imageData[i*imageSub->widthStep+j])>200)
				a[i][j]=2;
			else
				a[i][j]=0;


		}
	}


}

long count(int height, int width , int a[1000][1000], int num)
{
	long s=0;
	for(int i=0; i<height; ++i)
	{
		for(int j=0; j<width; ++j)
		{
			if(a[i][j]==num)
			{
				s++;
			}
		}
	}
	//cout<<" "<<s;
	return s;
}

int main()
{
	CvCapture *capture = cvCaptureFromFile("http://root:DTUUAS@192.168.137.20/axis-cgi/mjpg/video.cgi?resolution=640x480&req_fps=10&.mjpg");
		if(!capture)
		{
			cout<<"fail";
		    return -1;
		}


	long redLineCount, greenLineCount, videoCounts;
	int  temp1=0;//,temp2=0;
	//time_t t1, t2;
	int t=0;
	//double timeDifference;

		IplImage *frame = cvQueryFrame(capture);
		//cout<<cvGetSize(frame).height<<cvGetSize(frame).width;
		flush(cout);
	IplImage* abc = cvCreateImage(cvGetSize(frame), 8 , 3);

	int a[1000][1000], b[1000][1000];
	cvShowImage("Actual Image",abc);
	while(temp1<3)
	{
		cvCopy(frame, abc);
		cvShowImage("camera", frame);
		cvWaitKey(10);
		if(temp1==0)
		{
			detectRed(abc, a);
			redLineCount= count(abc->height, abc->width, a,1);
				detectGreen(abc, a);
				//cout<<"red:";

				//cout<<"green";
				greenLineCount = count(abc->height, abc->width,a, 2);
				//cout<<redLineCount;
				temp1++;
				cvWaitKey(0);

		}
		else if(temp1==1)
			{
				detectRed(abc, b);
				//cout<<"red";
				videoCounts = count(abc->height, abc->width, b, 1);
				if(redLineCount-videoCounts>200)
				{
					//t1=time(NULL);
					temp1++;

				}
				t++;
			}
			else
			{
				detectGreen(abc,b);
				//cout<<"green:";
				videoCounts=count(abc->height, abc->width, b, 2);
				if(greenLineCount-videoCounts>200)
				{
					//t2=time(NULL);
					temp1++;
				}
				//t++;
			}
			//timeDifference = t2-t1;
			frame= cvQueryFrame(capture);
			//t++;
	}
	cout<<t;
	//cout<<redLineCount;
	//cout<<"\n"<<greenLineCount;

	//t1=time(NULL);
	//cout<<t1;
	////////////// to be looped


	//cout<<timeDifference;
	//cvWaitKey(0);
	//t2=time(NULL);
	//cout<<difftime(t2,t1);

	//cvReleaseImage(&abc);
	return 0;
}
