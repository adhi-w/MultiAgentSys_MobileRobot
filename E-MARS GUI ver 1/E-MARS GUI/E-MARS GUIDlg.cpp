// E-MARS GUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "E-MARS GUI.h"
#include "E-MARS GUIDlg.h"
#include <highgui.h> 
#include <cxcore.h> 
#include <cv.h> 
#include <iostream> 
#include <stdlib.h>
#using <System.dll>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CEMARSGUIDlg dialog

CEMARSGUIDlg::CEMARSGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEMARSGUIDlg::IDD, pParent)
	, m_edit_smin(0)
	, m_edit_vmin(0)
	, m_edit_h_min(0)
	, m_edit_hmax(0)
	, m_edit_smax(0)
	, m_edit_vmax(0)
	, m_data(_T(""))
	, m_dat_terima(_T(""))
{
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEMARSGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_pic_capture, m_capture);
	DDX_Control(pDX, IDC_pic_thres, m_thresh);


	DDX_Text(pDX, IDC_edit_smin, m_edit_smin);
	DDV_MinMaxInt(pDX, m_edit_smin, 0, 255);
	DDX_Text(pDX, IDC_edit_vmin, m_edit_vmin);
	DDV_MinMaxInt(pDX, m_edit_vmin, 0, 255);
	DDX_Text(pDX, IDC_edit_hmin, m_edit_h_min);
	DDV_MinMaxInt(pDX, m_edit_h_min, 0, 255);

	DDX_Text(pDX, IDC_edit_hmax, m_edit_hmax);
	DDV_MinMaxInt(pDX, m_edit_hmax, 0, 255);
	DDX_Text(pDX, IDC_edit_smax, m_edit_smax);
	DDV_MinMaxInt(pDX, m_edit_smax, 0, 255);
	DDX_Text(pDX, IDC_edit_vmax, m_edit_vmax);
	DDV_MinMaxInt(pDX, m_edit_vmax, 0, 255);

	DDX_Control(pDX, IDC_h_min, m_slider_hmin);
	DDX_Control(pDX, IDC_s_min, m_slider_smin);
	DDX_Control(pDX, IDC_v_min, m_slider_vmin);
	DDX_Control(pDX, IDC_h_max, m_slider_hmax);
	DDX_Control(pDX, IDC_s_max, m_slider_smax);
	DDX_Control(pDX, IDC_v_max, m_slider_vmax);

	DDX_Text(pDX, IDC_data, m_data);
	DDX_Text(pDX, IDC_terima, m_dat_terima);
}

BEGIN_MESSAGE_MAP(CEMARSGUIDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDstart, &CEMARSGUIDlg::OnBnClickedstart)
	ON_BN_CLICKED(IDconnect, &CEMARSGUIDlg::OnBnClickedconnect)
	ON_BN_CLICKED(IDstop, &CEMARSGUIDlg::OnBnClickedstop)
	ON_BN_CLICKED(IDexit, &CEMARSGUIDlg::OnBnClickedexit)
	ON_BN_CLICKED(IDC_red, &CEMARSGUIDlg::OnBnClickedred)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_h_min, &CEMARSGUIDlg::OnNMReleasedcapturehmin)
	ON_EN_CHANGE(IDC_edit_hmin, &CEMARSGUIDlg::OnEnChangeedithmin)
	ON_BN_CLICKED(IDC_green, &CEMARSGUIDlg::OnBnClickedgreen)
	ON_BN_CLICKED(IDC_blue, &CEMARSGUIDlg::OnBnClickedblue)
	ON_BN_CLICKED(IDC_yellow, &CEMARSGUIDlg::OnBnClickedyellow)
	ON_BN_CLICKED(IDC_cyan, &CEMARSGUIDlg::OnBnClickedcyan)
	ON_BN_CLICKED(IDC_magenta, &CEMARSGUIDlg::OnBnClickedmagenta)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_s_min, &CEMARSGUIDlg::OnNMReleasedcapturesmin)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_v_min, &CEMARSGUIDlg::OnNMReleasedcapturevmin)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_h_max, &CEMARSGUIDlg::OnNMReleasedcapturehmax)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_s_max, &CEMARSGUIDlg::OnNMReleasedcapturesmax)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_v_max, &CEMARSGUIDlg::OnNMReleasedcapturevmax)
	ON_EN_CHANGE(IDC_edit_smin, &CEMARSGUIDlg::OnEnChangeeditsmin)
	ON_EN_CHANGE(IDC_edit_vmin, &CEMARSGUIDlg::OnEnChangeeditvmin)
	ON_EN_CHANGE(IDC_edit_hmax, &CEMARSGUIDlg::OnEnChangeedithmax)
	ON_EN_CHANGE(IDC_edit_smax, &CEMARSGUIDlg::OnEnChangeeditsmax)
	ON_EN_CHANGE(IDC_edit_vmax, &CEMARSGUIDlg::OnEnChangeeditvmax)
END_MESSAGE_MAP()

// CEMARSGUIDlg message handlers
BOOL     m_bPortReady;
HANDLE   m_hCom;
CString  m_sComPort;
DCB      m_dcb;
COMMTIMEOUTS m_CommTimeouts;
BOOL     bWriteRC;
BOOL     bReadRC;
DWORD iBytesWritten;
DWORD iBytesRead;
char       sBuffer[128];

#define PORT "Com2"

BOOL CEMARSGUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	UpdateData(TRUE);
	m_slider_hmin.SetRange(0,255);
	m_slider_smin.SetRange(0,255);
	m_slider_vmin.SetRange(0,255);
	m_slider_hmax.SetRange(0,255);
	m_slider_smax.SetRange(0,255);
	m_slider_vmax.SetRange(0,255);
	m_edit_h_min=0;
	m_edit_smin=0;
	m_edit_vmin=0;
	m_edit_hmax=0;
	m_edit_smax=0;
	m_edit_vmax=0;
	UpdateData(FALSE);

	m_sComPort = PORT;
	m_hCom = CreateFile(m_sComPort, 
		GENERIC_READ | GENERIC_WRITE,
		0, // exclusive access
		NULL, // no security
		OPEN_EXISTING,
		0, // no overlapped I/O
		NULL); // null template 

	m_bPortReady = SetupComm(m_hCom, 128, 128); // set buffer sizes

	m_bPortReady = GetCommState(m_hCom, &m_dcb);
	m_dcb.BaudRate = 9600;
	m_dcb.ByteSize = 8;
	m_dcb.Parity = NOPARITY;
	m_dcb.StopBits = ONESTOPBIT;
	m_dcb.fAbortOnError = TRUE;

	m_bPortReady = SetCommState(m_hCom, &m_dcb);
	m_bPortReady = GetCommTimeouts (m_hCom, &m_CommTimeouts);

	m_CommTimeouts.ReadIntervalTimeout = 50;
	m_CommTimeouts.ReadTotalTimeoutConstant = 50;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 10;
	m_CommTimeouts.WriteTotalTimeoutConstant = 50;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 10;

	m_bPortReady = SetCommTimeouts (m_hCom, &m_CommTimeouts);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEMARSGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEMARSGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEMARSGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Inisialisasi
bool stop, koneksi;
int flag=0, tanda=0;
int Hmin_b=103, Smin_b=149, Vmin_b=50;
int Hmax_b=120, Smax_b=255, Vmax_b=255;

int Hmin_g=45, Smin_g=135, Vmin_g=111;
int Hmax_g=56, Smax_g=255, Vmax_g=255;

int Hmin_r=124, Smin_r=108, Vmin_r=0;
int Hmax_r=205, Smax_r=255, Vmax_r=255;

int Hmin_y=22, Smin_y=147, Vmin_y=172;
int Hmax_y=63, Smax_y=255, Vmax_y=255;


int h_b=Hmin_b , s_b=Smin_b, v_b=Vmin_b;
int hm_b=Hmax_b, sm_b=Smax_b, vm_b=Vmax_b;

int h_g=Hmin_g , s_g=Smin_g, v_g=Vmin_g;
int hm_g=Hmax_g, sm_g=Smax_g, vm_g=Vmax_g;

int h_r=Hmin_r , s_r=Smin_r, v_r=Vmin_r;
int hm_r=Hmax_r, sm_r=Smax_r, vm_r=Vmax_r;

int h_y=Hmin_y , s_y=Smin_y, v_y=Vmin_y;
int hm_y=Hmax_y, sm_y=Smax_y, vm_y=Vmax_y;

int x_r, x_g, x_b, x_y;	
int y_r, y_g, y_b, y_y;

IplImage* imgLocate = NULL;
CvCapture *capture;

char buff[128];
char ad[10];

void add(char z)
{	
	sprintf(ad,"%c",z);
	bWriteRC = WriteFile(m_hCom,ad,1,&iBytesWritten,NULL);
}

void data(int x)
{	
	if(x>=100)
	{	sprintf(buff,"%d",x);
		bWriteRC = WriteFile(m_hCom,buff,3,&iBytesWritten,NULL);
	}	
	else if(x>=10)
	{	sprintf(buff,"0%d",x);
		bWriteRC = WriteFile(m_hCom,buff,3,&iBytesWritten,NULL);
	}	
	else
	{	sprintf(buff,"00%d",x);
		bWriteRC = WriteFile(m_hCom,buff,3,&iBytesWritten,NULL);
	}	
}

void kirim(char q, int x)
{	
	add(q);	data(x); 
}


void CEMARSGUIDlg::OnBnClickedstart()
{	
	// TODO: Add your control notification handler code here
	cvNamedWindow( "camera", CV_WINDOW_AUTOSIZE );	
	cvNamedWindow( "thresh", CV_WINDOW_AUTOSIZE );		

	HWND hWnd1 = (HWND) cvGetWindowHandle("camera");
	HWND hParent1 = ::GetParent(hWnd1);
	::SetParent(hWnd1, GetDlgItem(IDC_pic_capture)->m_hWnd);
	::ShowWindow(hParent1, SW_HIDE);

	HWND hWnd2 = (HWND) cvGetWindowHandle("thresh");
	HWND hParent2 = ::GetParent(hWnd2);
	::SetParent(hWnd2, GetDlgItem(IDC_pic_thres)->m_hWnd);
	::ShowWindow(hParent2, SW_HIDE);


	capture=cvCaptureFromCAM(0);
	cvResizeWindow("camera",640,480);
	cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH,640);
	cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT,480);

		
	
	stop=false;	
	while(!stop) 
	{ 
	if( !cvGrabFrame( capture )) break;
	IplImage* streaming = cvRetrieveFrame(capture);
	cvFlip(streaming,streaming,-1);
	streaming->origin=0;

	IplImage* frame = cvCreateImage( cvSize(streaming->width/1.46,streaming->height/1.46),
					  streaming->depth,
					  streaming->nChannels );
	cvResize(streaming,frame,CV_INTER_NN); 

	if(imgLocate == NULL)
	{
		imgLocate = cvCreateImage(cvGetSize(frame),8,3);
	}

	//--------------Inisialisasi----------
	CvSize size = cvGetSize(frame);	//Ukuran window
	
	IplImage* hsv_frame_r = cvCreateImage(size, IPL_DEPTH_8U, 3);  //Frame konversi ke HSV image warna biru
	IplImage* hsv_frame_g = cvCreateImage(size, IPL_DEPTH_8U, 3);  //Frame konversi ke HSV image warna biru
	IplImage* hsv_frame_b = cvCreateImage(size, IPL_DEPTH_8U, 3);  //Frame konversi ke HSV image warna biru
	IplImage* hsv_frame_y = cvCreateImage(size, IPL_DEPTH_8U, 3);  //Frame konversi ke HSV image warna biru

	//----------------FRAME-----------------------------
	IplImage* thresholded_r = cvCreateImage(size, IPL_DEPTH_8U, 1);	//Frame	hasil threshold range warna biru
	IplImage* thresholded_g = cvCreateImage(size, IPL_DEPTH_8U, 1);	//Frame	hasil threshold range warna biru
	IplImage* thresholded_b = cvCreateImage(size, IPL_DEPTH_8U, 1);	//Frame	hasil threshold range warna biru
	IplImage* thresholded_y = cvCreateImage(size, IPL_DEPTH_8U, 1);	//Frame	hasil threshold range warna biru
	
//-------------KALIBRASI------------//
	switch(flag)
	{
	case 1:	h_r=GetDlgItemInt(IDC_edit_hmin);	hm_r=GetDlgItemInt(IDC_edit_hmax);
			s_r=GetDlgItemInt(IDC_edit_smin);	sm_r=GetDlgItemInt(IDC_edit_smax);
			v_r=GetDlgItemInt(IDC_edit_vmin);	vm_r=GetDlgItemInt(IDC_edit_vmax); break;
	case 2: h_g=GetDlgItemInt(IDC_edit_hmin);	hm_g=GetDlgItemInt(IDC_edit_hmax);
			s_g=GetDlgItemInt(IDC_edit_smin);	sm_g=GetDlgItemInt(IDC_edit_smax);
			v_g=GetDlgItemInt(IDC_edit_vmin);	vm_g=GetDlgItemInt(IDC_edit_vmax); break;
	case 3: h_b=GetDlgItemInt(IDC_edit_hmin);	hm_b=GetDlgItemInt(IDC_edit_hmax);
			s_b=GetDlgItemInt(IDC_edit_smin);	sm_b=GetDlgItemInt(IDC_edit_smax);
			v_b=GetDlgItemInt(IDC_edit_vmin);	vm_b=GetDlgItemInt(IDC_edit_vmax); break;
	case 4: h_y=GetDlgItemInt(IDC_edit_hmin);	hm_y=GetDlgItemInt(IDC_edit_hmax);
			s_y=GetDlgItemInt(IDC_edit_smin);	sm_y=GetDlgItemInt(IDC_edit_smax);
			v_y=GetDlgItemInt(IDC_edit_vmin);	vm_y=GetDlgItemInt(IDC_edit_vmax); break;
	}
	
	//----------------------------Warna Merah------------------------------------
	CvScalar hsv_min_r = cvScalar(h_r, s_r, v_r, 0); //Nilai min H,S,V utk merah
	CvScalar hsv_max_r = cvScalar(hm_r, sm_r, vm_r, 0);  //Nilai max H,S,V utk merah

	//----------------------------Warna Hijau------------------------------------
	CvScalar hsv_min_g = cvScalar(h_g, s_g, v_g, 0); //Nilai min H,S,V utk hijau
	CvScalar hsv_max_g = cvScalar(hm_g, sm_g, vm_g, 0);  //Nilai max H,S,V utk hijau

	//----------------------------Warna Biru------------------------------------
	CvScalar hsv_min_b = cvScalar(h_b, s_b, v_b, 0); //Nilai min H,S,V utk biru
	CvScalar hsv_max_b = cvScalar(hm_b, sm_b, vm_b, 0);  //Nilai max H,S,V utk biru
	
	//----------------------------Warna Kuning------------------------------------
	CvScalar hsv_min_y = cvScalar(h_y, s_y, v_y, 0); //Nilai min H,S,V utk kuning
	CvScalar hsv_max_y = cvScalar(hm_y, sm_y, vm_y, 0);  //Nilai max H,S,V utk kuning

		
		// Konversi warna ke HSV
		cvCvtColor(frame, hsv_frame_r, CV_BGR2HSV);
		cvCvtColor(frame, hsv_frame_g, CV_BGR2HSV);
		cvCvtColor(frame, hsv_frame_b, CV_BGR2HSV);
		cvCvtColor(frame, hsv_frame_y, CV_BGR2HSV);

		// Filter warna sesuai range. 
		cvInRangeS(hsv_frame_r, hsv_min_r, hsv_max_r, thresholded_r);
		cvInRangeS(hsv_frame_g, hsv_min_g, hsv_max_g, thresholded_g);
		cvInRangeS(hsv_frame_b, hsv_min_b, hsv_max_b, thresholded_b);
		cvInRangeS(hsv_frame_y, hsv_min_y, hsv_max_y, thresholded_y);
		
		// Memory untuk akumulasi Hough Transform 
		CvMemStorage* storage_r = cvCreateMemStorage(0);
		CvMemStorage* storage_g = cvCreateMemStorage(0);
		CvMemStorage* storage_b = cvCreateMemStorage(0);
		CvMemStorage* storage_y = cvCreateMemStorage(0);
		
		// Smooth gambar untuk memudahkan hough transform 
		cvSmooth( thresholded_r, thresholded_r, CV_GAUSSIAN, 9, 9 );
		cvSmooth( thresholded_g, thresholded_g, CV_GAUSSIAN, 9, 9 );
		cvSmooth( thresholded_b, thresholded_b, CV_GAUSSIAN, 9, 9 );
		cvSmooth( thresholded_y, thresholded_y, CV_GAUSSIAN, 9, 9 );

		////Inisialisasi buffer tulisan
		CvFont font;
		char label_r[20], label_g[20], label_b[20],label_y[20];
		cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, .8, .8, 0, 1, 8);

		//----------------------Cari Lingkaran warna Merah---------
		CvSeq* circles_r = cvHoughCircles(thresholded_r, storage_r, CV_HOUGH_GRADIENT, 2,
							thresholded_r->height/4, 10, 10, 0, 40);

		static int posX_r = 0;
		static int posY_r = 0;

		for (int i = 0; i < circles_r->total; i++) 
		{ 
			float* p = (float*)cvGetSeqElem( circles_r, 1 ); 
			cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),3, CV_RGB(0,255,0), -1, 8, 0 ); 
			cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );

			//menahan pergerakan lintasan merah
		
			int lastX_r = posX_r;
			int lastY_r = posY_r;
		
			posX_r = p[0];
			posY_r = p[1];

			//-------------perhitungan garis merah--------------------
			if(lastX_r>0 && lastY_r>0 && posX_r>0 && posY_r>0)
			{
				//Gambar garis merah
				cvLine(imgLocate, cvPoint(posX_r,posY_r), cvPoint(lastX_r,lastY_r),cvScalar(255,0,0),5);
				//Inisial Untuk Merah
				sprintf(label_r,"Red (%d,%d)",posX_r,posY_r);
				cvPutText(frame, label_r, cvPoint(posX_r+10,posY_r+10),&font,CV_RGB(31,244,43));
			}
			x_r=posX_r;	y_r=posY_r;
		}
 
		//----------------------Cari Lingkaran warna Hijau
		CvSeq* circles_g = cvHoughCircles(thresholded_g, storage_g, CV_HOUGH_GRADIENT, 2,
							thresholded_g->height/4, 100, 50, 20, 400);
		
				static int posX_g = 0;
				static int posY_g = 0;

			for (int i = 0; i < circles_g->total;i++ ) 
			{ 
				float* p = (float*)cvGetSeqElem( circles_g, 1 ); 
				cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),3, CV_RGB(0,0,255), -1, 8, 0 ); 
				cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );

				//menahan pergerakan lintasan hijau
		
				int lastX_g = posX_g;
				int lastY_g = posY_g;
		
				posX_g = p[0];
				posY_g = p[1];

				//-------------perhitungan garis hijau--------------------
				if(lastX_g>0 && lastY_g>0 && posX_g>0 && posY_g>0)
				{
					//Gambar garis hijau
					cvLine(imgLocate, cvPoint(posX_g,posY_g), cvPoint(lastX_g,lastY_g),cvScalar(255,0,0),5);
					//Inisial Untuk hijau
					sprintf(label_g,"Green (%d,%d)",posX_g,posY_g);
					cvPutText(frame, label_g, cvPoint(posX_g+10,posY_g+10),&font,CV_RGB(248,42,30));
				}
				x_g=posX_g;	y_g=posY_g;
			}

			//----------------------Cari Lingkaran warna Biru
		CvSeq* circles_b = cvHoughCircles(thresholded_b, storage_b, CV_HOUGH_GRADIENT, 2,
							thresholded_b->height/4, 10, 10, 0, 40);
		
				static int posX_b = 0;
				static int posY_b = 0;

			for (int i = 0; i < circles_b->total;i++ ) 
			{ 
				float* p = (float*)cvGetSeqElem( circles_b, 1 ); 
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
					cvLine(imgLocate, cvPoint(posX_b,posY_b), cvPoint(lastX_b,lastY_b),cvScalar(255,0,0),5);
					//Inisial Untuk Biru
					sprintf(label_b,"Blue (%d,%d)",posX_b,posY_b);
					cvPutText(frame, label_b, cvPoint(posX_b+10,posY_b+10),&font,CV_RGB(10,248,30));
				}
				x_b=posX_b;	y_b=posY_b;
			}

		////----------------------Cari Lingkaran warna Kuning
		//CvSeq* circles_y = cvHoughCircles(thresholded_y, storage_y, CV_HOUGH_GRADIENT, 2,
		//					thresholded_y->height/8, 1, 3, 0, 50);

		//		static int posX_y = 0;
		//		static int posY_y = 0;

		//	for (int i = 0; i < circles_y->total;i++ ) 
		//	{ 
		//		float* p = (float*)cvGetSeqElem( circles_y, 1 ); 
		//		cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),3, CV_RGB(0,255,0), -1, 8, 0 ); 
		//		cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );

		//		//menahan pergerakan lintasan kuning
		//
		//		int lastX_y = posX_y;
		//		int lastY_y = posY_y;
		//
		//		posX_y = p[0];
		//		posY_y = p[1];

		//		//-------------perhitungan garis kuning--------------------
		//		if(lastX_y>0 && lastY_y>0 && posX_y>0 && posY_y>0)
		//		{
		//			//Gambar garis kuning
		//			cvLine(imgLocate, cvPoint(posX_y,posY_y), cvPoint(lastX_y,lastY_y),cvScalar(255,0,0),5);
		//			//Inisial Untuk kuning
		//			sprintf(label_y,"Kuning (%d,%d)",posX_y,posY_y);
		//			cvPutText(frame, label_y, cvPoint(posX_y+10,posY_y+10),&font,CV_RGB(10,248,30));
		//		}
		//		x_y=posX_y;	y_y=posY_y;
		//	}
	
		//cvAdd(frame, imgLocate, frame);
		cvShowImage( "camera", frame );
		switch(tanda)
		{
		case 1:	cvShowImage( "thresh", thresholded_r );  break;// Hasil streaming setelah diFilter		
		case 2:	cvShowImage( "thresh", thresholded_g );  break;	
		case 3: cvShowImage( "thresh", thresholded_b );  break;
		case 4: cvShowImage( "thresh", thresholded_y );  break;
		}
		//cvSaveImage("image.bmp",frame);
	//	cvResizeWindow("thresh",640,480);
		cvReleaseMemStorage(&storage_r);
		cvReleaseMemStorage(&storage_g);
		cvReleaseMemStorage(&storage_b);
		cvReleaseMemStorage(&storage_y);

					
		cvReleaseImage(&frame);
		cvReleaseImage(&thresholded_r);
		cvReleaseImage(&thresholded_g);
		cvReleaseImage(&thresholded_b);
		cvReleaseImage(&thresholded_y);
		streaming=NULL;	
		cvWaitKey(1);

//----------SERIAL--------------
	
		if(!koneksi)
		{	UpdateData(1);
			m_data.Format(L"Koneksi Terputus....Silahkan Tekan Tombol Connect");
			UpdateData(0);		
		}
		else 
		{	UpdateData(1);	
			m_data.Format(L"R(%d, %d), B(%d,%d)",x_r,y_r, x_b,y_b); 
		
			m_dat_terima.Format(_T("%c",terima));
			UpdateData(0); 

		//---------KIRIM SERIAL-----------
		kirim('R',x_r);	add(13);	kirim('r',y_r); add(13);
		kirim('B',x_b);	add(13);	kirim('b',y_b); add(13);	

		}
	}	
}

void CEMARSGUIDlg::OnBnClickedconnect()
{
	// TODO: Add your control notification handler code here
	koneksi=true;	
}

void CEMARSGUIDlg::OnBnClickedstop()
{
	// TODO: Add your control notification handler code here
	koneksi=false;	
}

void CEMARSGUIDlg::OnBnClickedexit()
{
	// TODO: Add your control notification handler code here
	stop =true;
	cvReleaseCapture(&capture);
	OnOK();	
	CDialog::OnCancel();
}

void CEMARSGUIDlg::OnBnClickedred()
{	
	// TODO: Add your control notification handler code here
	flag=1; tanda=1; UpdateData(1);	
	m_slider_hmin.SetPos(h_r); m_edit_h_min=h_r;
	m_slider_smin.SetPos(s_r); m_edit_smin=s_r;
	m_slider_vmin.SetPos(v_r); m_edit_vmin=v_r;
	m_slider_hmax.SetPos(hm_r); m_edit_hmax=hm_r;
	m_slider_smax.SetPos(sm_r); m_edit_smax=sm_r;
	m_slider_vmax.SetPos(vm_r); m_edit_vmax=vm_r;
			UpdateData(0);
}

void CEMARSGUIDlg::OnBnClickedgreen()
{
	// TODO: Add your control notification handler code here
	flag=2;	tanda=2; UpdateData(1);	
	m_slider_hmin.SetPos(h_g); m_edit_h_min=h_g;
	m_slider_smin.SetPos(s_g); m_edit_smin=s_g;
	m_slider_vmin.SetPos(v_g); m_edit_vmin=v_g;
	m_slider_hmax.SetPos(hm_g); m_edit_hmax=hm_g;
	m_slider_smax.SetPos(sm_g); m_edit_smax=sm_g;
	m_slider_vmax.SetPos(vm_g); m_edit_vmax=vm_g;
			UpdateData(0);
}

void CEMARSGUIDlg::OnBnClickedblue()
{
	// TODO: Add your control notification handler code here
	flag=3; tanda=3; UpdateData(1);	
	m_slider_hmin.SetPos(h_b); m_edit_h_min=h_b;
	m_slider_smin.SetPos(s_b); m_edit_smin=s_b;
	m_slider_vmin.SetPos(v_b); m_edit_vmin=v_b;
	m_slider_hmax.SetPos(hm_b); m_edit_hmax=hm_b;
	m_slider_smax.SetPos(sm_b); m_edit_smax=sm_b;
	m_slider_vmax.SetPos(vm_b); m_edit_vmax=vm_b;
			UpdateData(0);
}

void CEMARSGUIDlg::OnBnClickedyellow()
{
	// TODO: Add your control notification handler code here
	flag=4; tanda=4; UpdateData(1);	
	m_slider_hmin.SetPos(h_y); m_edit_h_min=h_y;
	m_slider_smin.SetPos(s_y); m_edit_smin=s_y;
	m_slider_vmin.SetPos(v_y); m_edit_vmin=v_y;
	m_slider_hmax.SetPos(hm_y); m_edit_hmax=hm_y;
	m_slider_smax.SetPos(sm_y); m_edit_smax=sm_y;
	m_slider_vmax.SetPos(vm_y); m_edit_vmax=vm_y;
			UpdateData(0);
}

void CEMARSGUIDlg::OnBnClickedcyan()
{
	// TODO: Add your control notification handler code here
	flag=5; tanda=5; UpdateData(1);	
	m_slider_hmin.SetPos(h_r); m_edit_h_min=h_r;
	m_slider_smin.SetPos(s_r); m_edit_smin=s_r;
	m_slider_vmin.SetPos(v_r); m_edit_vmin=v_r;
	m_slider_hmax.SetPos(hm_r); m_edit_hmax=hm_r;
	m_slider_smax.SetPos(sm_r); m_edit_smax=sm_r;
	m_slider_vmax.SetPos(vm_r); m_edit_vmax=vm_r;
			UpdateData(0);
}

void CEMARSGUIDlg::OnBnClickedmagenta()
{
	// TODO: Add your control notification handler code here
	flag=6; tanda=6; UpdateData(1);	
	m_slider_hmin.SetPos(h_r); m_edit_h_min=h_r;
	m_slider_smin.SetPos(s_r); m_edit_smin=s_r;
	m_slider_vmin.SetPos(v_r); m_edit_vmin=v_r;
	m_slider_hmax.SetPos(hm_r); m_edit_hmax=hm_r;
	m_slider_smax.SetPos(sm_r); m_edit_smax=sm_r;
	m_slider_vmax.SetPos(vm_r); m_edit_vmax=vm_r;
			UpdateData(0);
}

void CEMARSGUIDlg::OnNMReleasedcapturehmin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_h_min=m_slider_hmin.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSGUIDlg::OnNMReleasedcapturesmin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_smin=m_slider_smin.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSGUIDlg::OnNMReleasedcapturevmin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_vmin=m_slider_vmin.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSGUIDlg::OnNMReleasedcapturehmax(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_hmax=m_slider_hmax.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSGUIDlg::OnNMReleasedcapturesmax(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_smax=m_slider_smax.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSGUIDlg::OnNMReleasedcapturevmax(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_vmax=m_slider_vmax.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSGUIDlg::OnEnChangeedithmin()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_edit_hmin);
	UpdateData(1);
	m_slider_hmin.SetPos(k);
	UpdateData(0);
}


void CEMARSGUIDlg::OnEnChangeeditsmin()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_edit_smin);
	UpdateData(1);
	m_slider_smin.SetPos(k);
	UpdateData(0);
}

void CEMARSGUIDlg::OnEnChangeeditvmin()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_edit_vmin);
	UpdateData(1);
	m_slider_vmin.SetPos(k);
	UpdateData(0);
}

void CEMARSGUIDlg::OnEnChangeedithmax()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_edit_hmax);
	UpdateData(1);
	m_slider_hmax.SetPos(k);
	UpdateData(0);
}

void CEMARSGUIDlg::OnEnChangeeditsmax()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_edit_smax);
	UpdateData(1);
	m_slider_smax.SetPos(k);
	UpdateData(0);
}

void CEMARSGUIDlg::OnEnChangeeditvmax()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_edit_vmax);
	UpdateData(1);
	m_slider_vmax.SetPos(k);
	UpdateData(0);
}
