/**********************************************************
Copyright CarokCo.Inc June 2012
Department of Mechanical and Energy
Mechatronics Engineering
Electronics Engineering Polytechnic Institute of Surabaya

Author	: CarokArmy
Company	: Carok Company
***********************************************************/
#include <stdafx.h>
#include <highgui.h> 
#include <cxcore.h> 
#include <cv.h> 
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
#using <System.dll>
#using <mscorlib.dll>
#include <keycode.h>
#include <sayerror.h>
#include <wsc.h>

#define Port COM1
#define Baud 9600


//using namespace std;
//using namespace System;
//using namespace System::IO;
//using namespace System::IO::Ports;
//using namespace System::Threading;

#define rad2deg (180/(4*atan((double)1)))

//---------------------------SETTING KOMUNIKASI SERIAL----------------
void serial(void)
{	
	int code;
	char buffer[128];

	SioKeyCode(0);	//0 sharewarew version passcode
	SioReset(-1, 1, 1);	//Default inisialisasi
	SioBaud(-1,Baud);
//Inisialisasi Port dan baudrate baru
	code = SioReset(Port, 1024, 1024);
	SioBaud(Port, Baud);
	SioParms(Port,WSC_NoParity, WSC_OneStopBit, WSC_WordLength8);

	if(code<0)
	{
		char temp[80];
		//Tampilkan pesan error
		SioWinError((char *)temp,80);
		printf("ERROR %d : %s\n",code,(LPSTR)temp);
		SioDone(Port);	//Tutup Port
		exit(1);		//Keluar port
	}

		//Set DTR & RTS
		SioDTR(Port,WSC_SET_LINE);
		SioRTS(Port,WSC_SET_LINE);

	//Set Timeout
	SioSetTimeouts(Port, (DWORD)-1, (DWORD)0,(DWORD)0,(DWORD)1, (DWORD)2000);

}
//Cacah Data untuk dikirim

void kirim(int dx, int dy)
{	
	SioPutc(Port,dx/100+48);
	SioPutc(Port,(dx/10)%10+48);
	SioPutc(Port,dx%10+48);
	SioPutc(Port,',');
	
	SioPutc(Port,dy/100+48);
	SioPutc(Port,(dy/10)%10+48);
	SioPutc(Port,dy%10+48);  
}

//----------------------------END of SERIAL-----------------------------------

/*
void kirim(int dx,int dy)
{	
		//---------------INISIALISASI SERIAL-------------------------
	

	serialport->WriteLine(Convert::ToString(dx/100+48));
	serialport->WriteLine(Convert::ToString((dx/10)%10+48));
	serialport->WriteLine(Convert::ToString(dx%10+48));
	
	serialport->WriteLine(",");
	serialport->WriteLine(Convert::ToString(dy/100+48));
	serialport->WriteLine(Convert::ToString((dy/10)%10+48));
	serialport->WriteLine(Convert::ToString(dy%10+48));

}
*/
void hitung(float xo, float yo, float xt, float yt)
{
	long int sudut, magnitude;
	float x;
	float y;
	//hitung selisih koordinat
	x=fabs(xt-xo);
	y=fabs(yt-yo);

	magnitude = sqrt(x*x+y*y);
	sudut=rad2deg * atan2(y,x);

	//Penentuan Kuadran
	if(xo<=xt && yo>=yt)	//kuadran 1
	{	printf("sudut= %d\tmagnitude= %d\n",sudut,magnitude);	
		kirim(sudut,magnitude);
	}

	else if(xo>=xt && yo>=yt)	//kuadran 2
	{	printf("sudut= %d\tmagnitude= %d\n",180-sudut,magnitude);
		kirim(180-sudut,magnitude);
	}

	else if(xo>=xt && yo<=yt)	//kuadran 3
	{	printf("sudut= %d\tmagnitude= %d\n",sudut+180,magnitude);
		kirim(sudut+180,magnitude);
	}

	else if(xo<=xt && yo<=yt)	//kuadran 4	
	{	printf("sudut= %d\tmagnitude= %d\n",360-sudut,magnitude);
		kirim(360-sudut,magnitude);
	}
}


int Hmin_b=100, Smin_b=99, Vmin_b=50;
int Hmax_b=120, Smax_b=255, Vmax_b=255;

int Hmin_h=45, Smin_h=135, Vmin_h=111;
int Hmax_h=56, Smax_h=255, Vmax_h=255;

int Hmin_m=145, Smin_m=111, Vmin_m=66;
int Hmax_m=205, Smax_m=255, Vmax_m=255;

int Hmin_k=22, Smin_k=147, Vmin_k=172;
int Hmax_k=63, Smax_k=255, Vmax_k=255;

CvSize size = cvSize(640,480);	//Ukuran window

//----------------FRAME-----------------------------
IplImage * hsv_frame_b = cvCreateImage(size, IPL_DEPTH_8U, 3);  //Frame konversi ke HSV image warna biru
IplImage* thresholded_b = cvCreateImage(size, IPL_DEPTH_8U, 1);	//Frame	hasil threshold range warna biru

IplImage * hsv_frame_h = cvCreateImage(size, IPL_DEPTH_8U, 3);  //Frame konversi ke HSV image warna hijau
IplImage* thresholded_h = cvCreateImage(size, IPL_DEPTH_8U, 1);	//Frame	hasil threshold range warna hijau

IplImage * hsv_frame_m = cvCreateImage(size, IPL_DEPTH_8U, 3);  //Frame konversi ke HSV image warna merah
IplImage* thresholded_m = cvCreateImage(size, IPL_DEPTH_8U, 1);	//Frame	hasil threshold range warna merah

IplImage * hsv_frame_k = cvCreateImage(size, IPL_DEPTH_8U, 3);  //Frame konversi ke HSV image warna kuning
IplImage* thresholded_k = cvCreateImage(size, IPL_DEPTH_8U, 1);	//Frame	hasil threshold range warna kuning

IplImage* imgScribble = NULL;

void kalibrasi(void)
{	
	int c=cvWaitKey(10);

	switch (c)
	{
	case 'b' :
		cvNamedWindow( "Biru", 1 );
		cvCreateTrackbar( "Hmin", "Biru", &Hmin_b, 255, 0 );
		cvCreateTrackbar( "Smin", "Biru", &Smin_b, 255, 0 );
		cvCreateTrackbar( "Vmin", "Biru", &Vmin_b, 255, 0 ); 

		cvCreateTrackbar( "Hmax", "Biru", &Hmax_b, 255, 0 );
		cvCreateTrackbar( "Smax", "Biru", &Smax_b, 255, 0 );
		cvCreateTrackbar( "Vmax", "Biru", &Vmax_b, 255, 0 ); 
		break;
	case 'h' :
		cvNamedWindow( "Hijau", 1 );
		cvCreateTrackbar( "Hmin", "Hijau", &Hmin_h, 255, 0 );
		cvCreateTrackbar( "Smin", "Hijau", &Smin_h, 255, 0 );
		cvCreateTrackbar( "Vmin", "Hijau", &Vmin_h, 255, 0 ); 

		cvCreateTrackbar( "Hmax", "Hijau", &Hmax_h, 255, 0 );
		cvCreateTrackbar( "Smax", "Hijau", &Smax_h, 255, 0 );
		cvCreateTrackbar( "Vmax", "Hijau", &Vmax_h, 255, 0 ); 
	break;
	case 'm' :
		cvNamedWindow( "Merah", 1 );
		cvCreateTrackbar( "Hmin", "Merah", &Hmin_m, 255, 0 );
		cvCreateTrackbar( "Smin", "Merah", &Smin_m, 255, 0 );
		cvCreateTrackbar( "Vmin", "Merah", &Vmin_m, 255, 0 ); 

		cvCreateTrackbar( "Hmax", "Merah", &Hmax_m, 255, 0 );
		cvCreateTrackbar( "Smax", "Merah", &Smax_m, 255, 0 );
		cvCreateTrackbar( "Vmax", "Merah", &Vmax_m, 255, 0 ); 
	break;
	case 'k' :
		cvNamedWindow( "Kuning", 1 );
		cvCreateTrackbar( "Hmin", "Kuning", &Hmin_k, 255, 0 );
		cvCreateTrackbar( "Smin", "Kuning", &Smin_k, 255, 0 );
		cvCreateTrackbar( "Vmin", "Kuning", &Vmin_k, 255, 0 ); 

		cvCreateTrackbar( "Hmax", "Kuning", &Hmax_k, 255, 0 );
		cvCreateTrackbar( "Smax", "Kuning", &Smax_k, 255, 0 );
		cvCreateTrackbar( "Vmax", "Kuning", &Vmax_k, 255, 0 ); 
	break;
	case 'd' : cvDestroyWindow("Biru"); cvDestroyWindow("Hijau"); 
				cvDestroyWindow("Merah"); cvDestroyWindow("Kuning"); break;
	default: 
		;
	}
}

//--------------------------------------------------------------------
//----------------------------------MAIN Program---------------------
int main(int argc, char* argv[]) 
{	/*
	SerialPort^ serialport=gcnew SerialPort("COM1");
	serialport->BaudRate = 9600;
	serialport->Parity = Parity::None;
	serialport->DataBits = 8;
	serialport->StopBits = StopBits::One;
	serialport->Handshake = Handshake::None;
	serialport->ReadTimeout = 500;
	serialport->WriteTimeout = 500;
	serialport->Open();
*/
	serial();

	CvCapture* capture = cvCaptureFromCAM( 0 ); //Ganti -1,1 / 2 utk pilihan device  
	if( !capture ) 
		{ 
			fprintf( stderr, "ERROR: capture is NULL \n" ); 
			getchar(); 
			return -1; 
		}
// Membuat tampilan window
cvNamedWindow( "Camera", CV_WINDOW_AUTOSIZE ); cvMoveWindow("Camera",680,5);
cvNamedWindow( "HSV", CV_WINDOW_AUTOSIZE );		cvMoveWindow("HSV",5,320);
cvNamedWindow( "Thresh", CV_WINDOW_AUTOSIZE );	cvMoveWindow("Thresh",680,480); //cvResizeWindow("Thresh",480,320);

while( 1 ) 
{ 
// Pindahkan hasil capture kamera ke frame
IplImage* frame = cvQueryFrame( capture );
	if( !frame ) 
	{ 
		fprintf( stderr, "ERROR: frame is null...\n" ); 
		getchar(); break;
	}
		cvFlip(frame,frame,1);
		frame->origin=0;

		if(imgScribble == NULL)
		{
			imgScribble = cvCreateImage(cvGetSize(frame),8,3);
		}

//------------------------KALIBRASI---------------------
		kalibrasi();

int h_b=Hmin_b , s_b=Smin_b, v_b=Vmin_b;
int hm_b=Hmax_b, sm_b=Smax_b, vm_b=Vmax_b;

int h_h=Hmin_h , s_h=Smin_h, v_h=Vmin_h;
int hm_h=Hmax_h, sm_h=Smax_h, vm_h=Vmax_h;

int h_m=Hmin_m , s_m=Smin_m, v_m=Vmin_m;
int hm_m=Hmax_m, sm_m=Smax_m, vm_m=Vmax_m;

int h_k=Hmin_k , s_k=Smin_k, v_k=Vmin_k;
int hm_k=Hmax_k, sm_k=Smax_k, vm_k=Vmax_k;

//------------------Warna Biru------------------------------------
CvScalar hsv_min_b = cvScalar(h_b, s_b, v_b, 0); //Nilai min H,S,V utk biru
CvScalar hsv_max_b = cvScalar(hm_b, sm_b, vm_b, 0);  //Nilai max H,S,V utk biru

//----------------------------Warna Hijau------------------------------------
CvScalar hsv_min_h = cvScalar(h_h, s_h, v_h, 0); //Nilai min H,S,V utk hijau
CvScalar hsv_max_h = cvScalar(hm_h, sm_h, vm_h, 0);  //Nilai max H,S,V utk hijau

//----------------------------Warna Merah------------------------------------
CvScalar hsv_min_m = cvScalar(h_m, s_m, v_m, 0); //Nilai min H,S,V utk merah
CvScalar hsv_max_m = cvScalar(hm_m, sm_m, vm_m, 0);  //Nilai max H,S,V utk merah

//----------------------------Warna Kuning------------------------------------
CvScalar hsv_min_k = cvScalar(h_k, s_k, v_k, 0); //Nilai min H,S,V utk kuning
CvScalar hsv_max_k = cvScalar(hm_k, sm_k, vm_k, 0);  //Nilai max H,S,V utk kuning

// Konversi warna ke HSV
cvCvtColor(frame, hsv_frame_b, CV_BGR2HSV);
cvCvtColor(frame, hsv_frame_h, CV_BGR2HSV);
cvCvtColor(frame, hsv_frame_m, CV_BGR2HSV);
cvCvtColor(frame, hsv_frame_k, CV_BGR2HSV); 

// Filter warna sesuai range. 
cvInRangeS(hsv_frame_b, hsv_min_b, hsv_max_b, thresholded_b);
cvInRangeS(hsv_frame_h, hsv_min_h, hsv_max_h, thresholded_h);
cvInRangeS(hsv_frame_m, hsv_min_m, hsv_max_m, thresholded_m);
cvInRangeS(hsv_frame_k, hsv_min_k, hsv_max_k, thresholded_k);

// Memory untuk akumulasi Hough Transform 
CvMemStorage* storage_b = cvCreateMemStorage(0);
CvMemStorage* storage_h = cvCreateMemStorage(0);
CvMemStorage* storage_m = cvCreateMemStorage(0);
CvMemStorage* storage_k = cvCreateMemStorage(0);
 
// Smooth gambar untuk memudahkan hough transform 
cvSmooth( thresholded_b, thresholded_b, CV_GAUSSIAN, 9, 9 );
cvSmooth( thresholded_h, thresholded_h, CV_GAUSSIAN, 9, 9 );
cvSmooth( thresholded_m, thresholded_m, CV_GAUSSIAN, 9, 9 );
cvSmooth( thresholded_k, thresholded_k, CV_GAUSSIAN, 9, 9 );

//Inisialisasi buffer tulisan
CvFont font;
char label_b[20], label_h[20], label_m[20],label_k[20];
cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, .8, .8, 0, 1, 8);
 
//----------------------Cari Lingkaran warna Biru
CvSeq* circles_b = cvHoughCircles(thresholded_b, storage_b, CV_HOUGH_GRADIENT, 2,
				thresholded_b->height/4, 100, 50, 20, 400);
		
		static int posX_b = 0;
		static int posY_b = 0;

	for (int i = 0; i < circles_b->total;i++ ) 
	{ 
		float* p = (float*)cvGetSeqElem( circles_b, 1 ); 
		//printf("Ball B! x=%.1f y=%.1f r=%.2f\n\r",p[0],p[1],p[2] );
		cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),3, CV_RGB(0,255,0), -1, 8, 0 ); 
		cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );

		//menahan pergerakan lintasan biru
		
		int lastX_b = posX_b;
		int lastY_b = posY_b;
		
		posX_b = p[0];
		posY_b = p[1];

		//-------------perhitungan garis biru--------------------
		if(lastX_b>0 && lastY_b>0 && posX_b>0 && posY_b>0)
		{
			//Gambar garis biru
			cvLine(imgScribble, cvPoint(posX_b,posY_b), cvPoint(lastX_b,lastY_b),cvScalar(255,0,0),5);
			//Inisial Untuk Biru
			sprintf(label_b,"Leader (%d,%d)",posX_b,posY_b);
			cvPutText(frame, label_b, cvPoint(posX_b+10,posY_b+10),&font,CV_RGB(10,248,30));
		}
	}

//----------------------Cari Lingkaran warna Hijau
CvSeq* circles_h = cvHoughCircles(thresholded_h, storage_h, CV_HOUGH_GRADIENT, 2,
				thresholded_h->height/4, 100, 50, 10, 400);

		static int posX_h = 0;
		static int posY_h = 0;

	for (int i = 0; i < circles_h->total; i++) 
	{ 
		float* p = (float*)cvGetSeqElem( circles_h, 1 ); 
	//	printf("Ball H! x=%.1f y=%.1f r=%.2f\n\r",p[0],p[1],p[2] );
		cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),3, CV_RGB(0,255,0), -1, 8, 0 ); 
		cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );

		//menahan pergerakan lintasan hijau
		
		int lastX_h = posX_h;
		int lastY_h = posY_h;
		
		posX_h = p[0];
		posY_h = p[1];

		//-------------perhitungan garis hijau--------------------
		if(lastX_h>0 && lastY_h>0 && posX_h>0 && posY_h>0)
		{
			//Gambar garis hijau
			cvLine(imgScribble, cvPoint(posX_h,posY_h), cvPoint(lastX_h,lastY_h),cvScalar(0,128,128),5);
			//Inisial Untuk Hijau
			sprintf(label_h,"Follower 1 (%d,%d)",posX_h,posY_h);
			cvPutText(frame, label_h, cvPoint(posX_h+10,posY_h+10),&font,CV_RGB(11,94,243));
		}
	}

//----------------------Cari Lingkaran warna Merah
CvSeq* circles_m = cvHoughCircles(thresholded_m, storage_m, CV_HOUGH_GRADIENT, 2,
				thresholded_m->height/4, 100, 50, 10, 400);

		static int posX_m = 0;
		static int posY_m = 0;

	for (int i = 0; i < circles_m->total; i++) 
	{ 
		float* p = (float*)cvGetSeqElem( circles_m, 1 ); 
	//	printf("Ball M! x=%.1f y=%.1f r=%.2f\n\r",p[0],p[1],p[2] );
		cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),3, CV_RGB(0,255,0), -1, 8, 0 ); 
		cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );

		//menahan pergerakan lintasan merah
		
		int lastX_m = posX_m;
		int lastY_m = posY_m;
		
		posX_m = p[0];
		posY_m = p[1];

		//-------------perhitungan garis merah--------------------
		if(lastX_m>0 && lastY_m>0 && posX_m>0 && posY_m>0)
		{
			//Gambar garis merah
			cvLine(imgScribble, cvPoint(posX_m,posY_m), cvPoint(lastX_m,lastY_m),cvScalar(255,0,0),5);
			//Inisial Untuk Merah
			sprintf(label_m,"Follower 2 (%d,%d)",posX_m,posY_m);
			cvPutText(frame, label_m, cvPoint(posX_m+10,posY_m+10),&font,CV_RGB(31,244,43));
		}
	}

//----------------------Cari Lingkaran warna Kuning
CvSeq* circles_k = cvHoughCircles(thresholded_k, storage_k, CV_HOUGH_GRADIENT, 2,
				thresholded_k->height/4, 100, 50, 10, 400);

		static int posX_k = 0;
		static int posY_k = 0;

	for (int i = 0; i < circles_k->total; i++) 
	{ 
		float* p = (float*)cvGetSeqElem( circles_k, 1 ); 
	//	printf("Ball K! x=%.1f y=%.1f r=%.2f\n\r",p[0],p[1],p[2] );
		cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),3, CV_RGB(0,255,0), -1, 8, 0 ); 
		cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );

		//menahan pergerakan lintasan kuning
		
		int lastX_k = posX_k;
		int lastY_k = posY_k;
		
		posX_k = p[0];
		posY_k = p[1];

		//-------------perhitungan garis kuning--------------------
		if(lastX_k>0 && lastY_k>0 && posX_k>0 && posY_k>0)
		{
			//Gambar garis kuning
			cvLine(imgScribble, cvPoint(posX_k,posY_k), cvPoint(lastX_k,lastY_k),cvScalar(255,0,0),5);
			//Inisial Untuk Kuning
			sprintf(label_k,"Target (%d,%d)",posX_k,posY_k);
			cvPutText(frame, label_k, cvPoint(posX_k+10,posY_k+10),&font,CV_RGB(231,14,23));
	
			//serialport->WriteLine(Convert::ToString(posX_k));
		}
	}	
	
//cvAdd(frame, imgScribble, frame);
cvShowImage( "Camera", frame ); // Hasil capture kamera
cvShowImage( "HSV", hsv_frame_b); // Hasil konversi ke HSV
cvShowImage( "HSV", hsv_frame_h);
cvShowImage( "HSV", hsv_frame_m);
cvShowImage( "HSV", hsv_frame_k);;

//cvResizeWindow("Thresh",480,320);
//cvShowImage( "Thresh", thresholded_b ); // Hasil streaming setelah diFilter
//cvShowImage( "Thresh", thresholded_h );

cvShowImage( "Thresh", thresholded_m );
cvShowImage( "Thresh", thresholded_k );

cvReleaseMemStorage(&storage_b);
cvReleaseMemStorage(&storage_h);
cvReleaseMemStorage(&storage_m);
cvReleaseMemStorage(&storage_k);

hitung(posX_b,posY_b,posX_h,posY_h);
SioPutc(Port,13);

if( (cvWaitKey(10) & 255) == 27 ) break;
}
//Tutup device serial
//serialport->Close();

	SioTxClear(Port);		//Clear Transmit buffer
	SioDone(Port);			//Tutup Port

// Tutup Capture device
cvReleaseCapture( &capture ); 
cvDestroyWindow( "window" ); 
return 0;
 
} 