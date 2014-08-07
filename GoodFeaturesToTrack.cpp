// GoodFeaturesToTrack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// The standard OpenCV headers
#include <cv.h>
#include <highgui.h>

// The main function
int main()
{
	// Load a color image, and convert it into grayscale
	IplImage* img = cvLoadImage("goal_arena.jpg");
	IplImage* imgGrayscale = cvCreateImage(cvGetSize(img), 8, 1);
	cvCvtColor(img, imgGrayscale, CV_BGR2GRAY);

	// Create temporary images required by cvGoodFeaturesToTrack
	IplImage* imgTemp = cvCreateImage(cvGetSize(img), 32, 1);
	IplImage* imgEigen = cvCreateImage(cvGetSize(img), 32, 1);

	// Create the array
	int count = 100;
	CvPoint2D32f* corners = new CvPoint2D32f[count];

	// Find corners
	cvGoodFeaturesToTrack(imgGrayscale, imgEigen, imgTemp, corners, &count, 0.1, 20);

	// Mark these corners on the original image
	for(int i=0;i<count;i++)
	{
		cvLine(img, cvPoint(corners[i].x, corners[i].y), cvPoint(corners[i].x, corners[i].y), CV_RGB(255,0,0), 5);
	}

	// Display it
	cvNamedWindow("Original");
	cvShowImage("Original", img);

	// Print the number of corners
	printf("Count: %d\n", count);

	cvWaitKey(0);
}

