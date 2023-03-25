/**********************************************************
Copyright CarokCo.Inc 2011-2012
Department of Mechanics and Energy
Mechatronics Engineering
Electronics Engineering Polytechnic Institute of Surabaya

Author	: CarokArmy
Company	: Carok Company
***********************************************************/
#include <stdio.h>
#include <stdafx.h>
#include <stdlib.h>
#include <conio.h>
#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <windows.h>
#include <keycode.h>
#include <sayerror.h>
#include <wsc.h>

#define rad2deg (180/(4*atan((double)1)))

#define Port COM1
#define Baud 9600

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

//---------------------------PERHITUNGAN SUDUT & SELISIH KOORDINAT------------

void Hitung(float xo, float yo, float xt, float yt)
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


//--------------------------KONVERSI RGB KE HSV---------------------------
IplImage* GetThresholdedImage_Yellow(IplImage* img) // Untuk Warna Kuning
{
	//konversi ke HSV image
	IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8 ,3);
	cvCvtColor(img,imgHSV,CV_BGR2HSV);
	IplImage* imgThreshed = cvCreateImage(cvGetSize(img),8,1);
	cvInRangeS(imgHSV, cvScalar(10,100,95), cvScalar(30,255,255),imgThreshed);	//Kuning		0,100,100 -> 30,255,255

	cvReleaseImage(&imgHSV);
	return imgThreshed;
}

IplImage* GetThresholdedImage_Blue(IplImage* img_b) // Untuk Warna Biru
{	
	CvMemStorage* storage = cvCreateMemStorage(0);
	//konversi ke HSV image
	IplImage* imgHSV_b = cvCreateImage(cvGetSize(img_b), 8 ,3);
	cvCvtColor(img_b,imgHSV_b,CV_BGR2HSV);
	cvSmooth( imgHSV_b, imgHSV_b, CV_GAUSSIAN, 5, 5 );
	IplImage* imgThreshed_b = cvCreateImage(cvGetSize(img_b),8,1);
	cvInRangeS(imgHSV_b, cvScalar(100,75,50), cvScalar(120,255,255),imgThreshed_b);	//Biru	  96,140,40 -> 234,161,117
		
	cvReleaseImage(&imgHSV_b);
	return imgThreshed_b;
}

IplImage* GetThresholdedImage_Green(IplImage* img_h) // Untuk Warna Hijau
{
	//konversi ke HSV image
	IplImage* imgHSV_h = cvCreateImage(cvGetSize(img_h), 8 ,3);
	cvCvtColor(img_h,imgHSV_h,CV_BGR2HSV);
	IplImage* imgThreshed_h = cvCreateImage(cvGetSize(img_h),8,1);
	cvInRangeS(imgHSV_h,  cvScalar(45,75,50), cvScalar(75,255,255),imgThreshed_h);	//Hijau

	cvReleaseImage(&imgHSV_h);
	return imgThreshed_h;
}

IplImage* GetThresholdedImage_Red(IplImage* img_m) // Untuk Warna Merah
{
	//konversi ke HSV image
	IplImage* imgHSV_m = cvCreateImage(cvGetSize(img_m), 8 ,3);
	cvCvtColor(img_m,imgHSV_m,CV_BGR2HSV);
	IplImage* imgThreshed_m = cvCreateImage(cvGetSize(img_m),8,1);
	cvInRangeS(imgHSV_m,  cvScalar(0,175,50), cvScalar(15,255,252),imgThreshed_m);	//Merah

	cvReleaseImage(&imgHSV_m);
	return imgThreshed_m;
}

/*
IplImage* Ling_biru(IplImage* xbiru)
{		
	//	IplImage* tbiru = GetThresholdedImage_Blue(xbiru);
		IplImage* gray = cvCreateImage( cvGetSize(xbiru), 8, 1 );
        CvMemStorage* storage = cvCreateMemStorage(0);
        cvCvtColor( xbiru, gray, CV_BGR2GRAY );
        cvSmooth( gray, gray, CV_GAUSSIAN, 9, 9 ); // smooth it, otherwise a lot of false circles may be detected
        CvSeq* circles = cvHoughCircles( gray, storage, CV_HOUGH_GRADIENT, 2, gray->height/4, 200, 100 );
        int i;
        for( i = 0; i < circles->total; i++ )
        {
             float* p = (float*)cvGetSeqElem( circles, i );
             cvCircle( xbiru, cvPoint(cvRound(p[0]),cvRound(p[1])), 3, CV_RGB(0,255,0), -1, 8, 0 );
             cvCircle( xbiru, cvPoint(cvRound(p[0]),cvRound(p[1])), cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );
        }
		return gray;
}*/
//-----------------------------------------------------------------------------------------------

 //Menampilkan video
int main()
{	
	serial();		//Memanggil Routine Serial Komunikasi

	CvCapture* capture=0;
	capture = cvCaptureFromCAM(0);
	
	cvNamedWindow("video");
	cvMoveWindow("video", 10, 10);
	
	cvNamedWindow("thresh");
	cvMoveWindow("thresh", 680, 10);
	
	IplImage* imgScribble = NULL;

	while(true)
	{
		IplImage* frame = 0;
		frame = cvQueryFrame(capture);

		if(!frame)	break;

		cvFlip(frame,frame,1);
		frame->origin=0;

		if(imgScribble == NULL)
		{
			imgScribble = cvCreateImage(cvGetSize(frame),8,3);
		}


//----------------------Untuk Warna Kuning----------------------		
		//Tahan warna kuning threshold
		IplImage* imgYellowThresh = GetThresholdedImage_Yellow(frame);

		//Kalkulasi pergerakan Warna Kuning
		CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
		cvMoments(imgYellowThresh, moments, 1);

		//Nilai Aktual pergerakan 
		double moment10 = cvGetSpatialMoment(moments, 1, 0);
		double moment01 = cvGetSpatialMoment(moments, 0, 1);
		double area = cvGetCentralMoment(moments, 0, 0);

		//menahan pergerakan lintasan bola
		static int posX = 0;
		static int posY = 0;

		int lastX = posX;
		int lastY = posY;
		
		posX = moment10/area;
		posY = moment01/area;

//------------------------------untuk Warna Biru-------------------------
			//Tahan warna Biru threshold
		IplImage* imgBlueThresh = GetThresholdedImage_Blue(frame);

		//Kalkulasi pergerakan Warna Biru
		CvMoments *moments_b = (CvMoments*)malloc(sizeof(CvMoments));
		cvMoments(imgBlueThresh, moments_b, 1);

		//Nilai Aktual pergerakan 
		double moment10_b = cvGetSpatialMoment(moments_b, 1, 0);
		double moment01_b = cvGetSpatialMoment(moments_b, 0, 1);
		double area_b = cvGetCentralMoment(moments_b, 0, 0);

		//menahan pergerakan lintasan bola
		static int posX_b = 0;
		static int posY_b = 0;

		int lastX_b = posX_b;
		int lastY_b = posY_b;
		
		posX_b = moment10_b/area_b;
		posY_b = moment01_b/area_b;

//------------------------------untuk Warna Hijau-------------------------
			//Tahan warna Hijau threshold
		IplImage* imgGreenThresh = GetThresholdedImage_Green(frame);

		//Kalkulasi pergerakan Warna Hijau
		CvMoments *moments_h = (CvMoments*)malloc(sizeof(CvMoments));
		cvMoments(imgGreenThresh, moments_h, 1);

		//Nilai Aktual pergerakan 
		double moment10_h = cvGetSpatialMoment(moments_h, 1, 0);
		double moment01_h = cvGetSpatialMoment(moments_h, 0, 1);
		double area_h = cvGetCentralMoment(moments_h, 0, 0);

		//menahan pergerakan lintasan bola
		static int posX_h = 0;
		static int posY_h = 0;

		int lastX_h = posX_h;
		int lastY_h = posY_h;
		
		posX_h = moment10_h/area_h;
		posY_h = moment01_h/area_h;

//------------------------------untuk Warna Merah-------------------------
			//Tahan warna Merah threshold
		IplImage* imgRedThresh = GetThresholdedImage_Red(frame);

		//Kalkulasi pergerakan Warna Merah
		CvMoments *moments_m = (CvMoments*)malloc(sizeof(CvMoments));
		cvMoments(imgRedThresh, moments_m, 1);

		//Nilai Aktual pergerakan 
		double moment10_m = cvGetSpatialMoment(moments_m, 1, 0);
		double moment01_m = cvGetSpatialMoment(moments_m, 0, 1);
		double area_m = cvGetCentralMoment(moments_m, 0, 0);

		//menahan pergerakan lintasan bola
		static int posX_m = 0;
		static int posY_m = 0;

		int lastX_m = posX_m;
		int lastY_m = posY_m;
		
		posX_m = moment10_m/area_m;
		posY_m = moment01_m/area_m;

//--------------------------------Tampilkan Koordinat--------------------

	//	printf("posisi K(%d,%d)\t& B(%d,%d)\t& H(%d,%d)\t& M(%d,%d)\n",posX,posY,posX_b,posY_b,posX_h,posY_h,posX_m,posY_m);
		//---------perhitungan garis Kuning---------------------
//		if(lastX>0 && lastY>0 && posX>0 && posY>0)
//		{
			//Gambar garis kuning
//			cvLine(imgScribble, cvPoint(posX,posY), cvPoint(lastX,lastY),cvScalar(0,255,255),5);
//		}

		//-------------perhitungan garis biru--------------------
		if(lastX_b>0 && lastY_b>0 && posX_b>0 && posY_b>0)
		{
			//Gambar garis biru
			cvLine(imgScribble, cvPoint(posX_b,posY_b), cvPoint(lastX_b,lastY_b),cvScalar(255,0,0),5);
		}
/*
		//-------------perhitungan garis hijau--------------------
		if(lastX_h>0 && lastY_h>0 && posX_h>0 && posY_h>0)
		{
			//Gambar garis hijau
			cvLine(imgScribble, cvPoint(posX_h,posY_h), cvPoint(lastX_h,lastY_h),cvScalar(0,255,0),5);
		}
		
		//-------------perhitungan garis merah--------------------
		if(lastX_m>0 && lastY_m>0 && posX_m>0 && posY_m>0)
		{
			//Gambar garis merah
			cvLine(imgScribble, cvPoint(posX_m,posY_m), cvPoint(lastX_m,lastY_m),cvScalar(0,0,255),5);
		}
	
*/	
//--------------------------------Penanda koordinat----------------------------
		CvFont font;
		char label[20],label_b[20], label_h[20], label_m[20];
		cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, .8, .8, 0, 1, 8);

		//Inisial Untuk Kuning
//		sprintf(label,"kuning (%d,%d)",posX,posY);
//		cvPutText(frame, label, cvPoint(posX+10,posY+10),&font,CV_RGB(255,255,255));
//		cvRectangle(frame, cvPoint(posX-20,posY-20),cvPoint(posX+5,posY+5),CV_RGB(255,0,0),1,8,0);

		//Inisial Untuk Biru
//		sprintf(label_b,"biru (%d,%d)",posX_b,posY_b);
//		cvPutText(frame, label_b, cvPoint(posX_b+10,posY_b+10),&font,CV_RGB(125,148,119));
//		cvRectangle(frame, cvPoint(posX_b-20,posY_b-20),cvPoint(posX_b+5,posY_b+5),CV_RGB(255,255,0),1,8,0);

		//Inisial Untuk Hijau
		sprintf(label_h,"hijau (%d,%d)",posX_h,posY_h);
		cvPutText(frame, label_h, cvPoint(posX_h+10,posY_h+10),&font,CV_RGB(231,94,43));
		cvRectangle(frame, cvPoint(posX_h-20,posY_h-20),cvPoint(posX_h+5,posY_h+5),CV_RGB(0,255,255),1,8,0);
/*
		//Inisial Untuk Merah
		sprintf(label_m,"merah (%d,%d)",posX_m,posY_m);
		cvPutText(frame, label_m, cvPoint(posX_m+10,posY_m+10),&font,CV_RGB(89,165,243));
		cvRectangle(frame, cvPoint(posX_m-20,posY_m-20),cvPoint(posX_m+5,posY_m+5),CV_RGB(0,255,0),1,8,0);
*/

		//panggil routine sudut & magnitude
//		Hitung(posX_b,posY_b,posX,posY);		//biru->lokasi robot		kuning->tujuan
		
		

		//memasukkan gmbr scribble dan frame
		cvAdd(frame, imgScribble, frame);
//		cvShowImage("thresh",imgYellowThresh);
//		cvShowImage("thresh",imgBlueThresh);
		cvShowImage("thresh",imgGreenThresh);
//		cvShowImage("thresh",imgRedThresh);
		cvShowImage("video",frame);
		//cvResizeWindow("video",480,320);
		//cvResizeWindow("thresh",480,320);

		int c = cvWaitKey(10);
		if(c!=-1)	break;

		cvReleaseImage(&imgYellowThresh);
		cvReleaseImage(&imgBlueThresh);
		cvReleaseImage(&imgGreenThresh);
		cvReleaseImage(&imgRedThresh);
		delete moments, moments_b, moments_h, moments_m;	

		//----------------KIRIM DATA KE SERIAL------------
	
//		SioPutc(Port,'K');	kirim(posX,posY);	SioPutc(Port,32);
		SioPutc(Port,'B');	kirim(posX_b,posY_b);
		printf("B(%d, %d)\n",posX_b,posY_b);
		SioPutc(Port,13);
/*	
				
		SioPutc(Port,'B');
		Hitung(posX_b,posY_b,posX,posY);	//Biru ke target(kuning)
*/
	//	SioPuts(Port,(LPSTR)label,16);
	}
	
	SioTxClear(Port);		//Clear Transmit buffer
	SioDone(Port);			//Tutup Port

	cvReleaseCapture(&capture);
	return 0;
}

  