#include <stdafx.h>
#include <highgui.h> 
#include <cxcore.h> 
#include <cv.h> 
#include <stdio.h> 
#include <iostream> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include <math.h> 
#include <float.h> 
#include <limits.h> 
#include <time.h> 
#include <ctype.h> 
#include <fstream>

int hmin=100, smin=99, vmin=50;
int hmax=120, smax=255, vmax=255;

void kalibrasi()
{	int c=cvWaitKey(10);
	int show_hist=0;
	switch (c)
	{
	case 'a' :
		show_hist = 1;
		cvNamedWindow( "Slider", 1 );
		cvCreateTrackbar( "Hmin", "Slider", &hmin, 256, 0 );
		cvCreateTrackbar( "Sin", "Slider", &smin, 256, 0 );
		cvCreateTrackbar( "Vmin", "Slider", &vmin, 256, 0 ); 
		break;
	case 'b' :
		cvNamedWindow( "Slider", 1 );
		cvCreateTrackbar( "Hmax", "Slider", &hmax, 256, 0 );
		cvCreateTrackbar( "Smax", "Slider", &smax, 256, 0 );
		cvCreateTrackbar( "Vmax", "Slider", &vmax, 256, 0 ); 
	break;
	case 'd' : cvDestroyWindow("Slider"); break;
	default: 
		;
	}
}

int main(int argc, char* argv[]) 
{ 
CvSize size = cvSize(640,480); 
CvCapture* capture = cvCaptureFromCAM( 0 ); //Change to -1,1 or 2 if 0 does not work 
	if( !capture ) 
		{ 
			fprintf( stderr, "ERROR: capture is NULL \n" ); 
			getchar(); 
			return -1; 
		}
// Create a window in which the captured images will be presented 
cvNamedWindow( "Camera", CV_WINDOW_AUTOSIZE ); 
cvNamedWindow( "HSV", CV_WINDOW_AUTOSIZE ); 
cvNamedWindow( "EdgeDetection", CV_WINDOW_AUTOSIZE );

// Detect a red/orange ball 

IplImage * hsv_frame = cvCreateImage(size, IPL_DEPTH_8U, 3);
A
//CvMat *thresholded = cvCreateMat(size.height, size.width, CV_8UC1);
IplImage* thresholded = cvCreateImage(size, IPL_DEPTH_8U, 1);
IplImage* canny = cvCreateImage(size, IPL_DEPTH_8U, 1);

while( 1 ) 
{ 
// Get one frame
IplImage* frame = cvQueryFrame( capture );
	if( !frame ) 
	{ 
		fprintf( stderr, "ERROR: frame is null...\n" ); 
		getchar(); break;
	}
		cvFlip(frame,frame,1);
		frame->origin=0;

	kalibrasi();
	int h=hmin, s=smin, v=vmin;
	int hm=hmax, sm=smax, vm=vmax;

CvScalar hsv_min = cvScalar(h, s, v, 0); 
CvScalar hsv_max = cvScalar(hm, sm, vm, 0);

// Covert color space to HSV as it is much easier to filter colors in the HSV color-space.
cvCvtColor(frame, hsv_frame, CV_BGR2HSV); 

// Filter out colors which are out of range. 
cvInRangeS(hsv_frame, hsv_min, hsv_max, thresholded);

// Memory for hough circles 
CvMemStorage* storage = cvCreateMemStorage(0);
 
// hough detector works better with some smoothing of the image 
cvSmooth( thresholded, thresholded, CV_GAUSSIAN, 9, 9 );
cvCanny(thresholded, canny,200,220,3);
 
CvSeq* circles = cvHoughCircles(canny, storage, CV_HOUGH_GRADIENT, 2,
				canny->height/4, 100, 50, 10, 400);
	for (int i = 0; i < circles->total; i++) 
	{ 
		float* p = (float*)cvGetSeqElem( circles, i ); 
		printf("Ball! x=%f y=%f r=%f\n\r",p[0],p[1],p[2] );
		cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),3, CV_RGB(0,255,0), -1, 8, 0 ); 
		cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );
	//	 CvPoint center = cvPoint(cvRound(p[0]),cvRound(p[1]));
	 //    CvScalar val = cvGet2D(thresholded, center.y, center.x);
	  //   if (val.val[0] < 1) continue;
       //      cvCircle(frame,  center, 3,             CV_RGB(0,255,0), -1, CV_AA, 0);
        //     cvCircle(frame,  center, cvRound(p[2]), CV_RGB(255,0,0),  3, CV_AA, 0);
          //   cvCircle(thresholded, center, 3,             CV_RGB(0,255,0), -1, CV_AA, 0);
          //   cvCircle(thresholded, center, cvRound(p[2]), CV_RGB(255,0,0),  3, CV_AA, 0);
	}
cvShowImage( "Camera", frame ); // Original stream with detected ball overlay 
cvShowImage( "HSV", hsv_frame); // Original stream in the HSV color space 
cvShowImage( "After Color Filtering", thresholded ); // The stream after color filtering
cvShowImage( "EdgeDetection", canny ); 
cvReleaseMemStorage(&storage);


if( (cvWaitKey(10) & 255) == 27 ) break;
}
// Release the capture device housekeeping
cvReleaseCapture( &capture ); 
cvDestroyWindow( "mywindow" ); 
return 0;
 
}