// E-MARS ver2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "E-MARS ver2.h"
#include "E-MARS ver2Dlg.h"
#include <highgui.h> 
#include <cxcore.h> 
#include <cv.h> 
#include <iostream> 
#include <math.h> 
#include <stdlib.h>
#using <System.dll>
#include "BlobResult.h"  


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

// CEMARSver2Dlg dialog

CEMARSver2Dlg::CEMARSver2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEMARSver2Dlg::IDD, pParent)
	, m_edit_Hmin(0)
	, m_edit_Smin(0)
	, m_edit_Vmin(0)
	, m_edit_Hmax(0)
	, m_edit_Smax(0)
	, m_edit_Vmax(0)
	, m_sendData(_T(""))
	, m_portCom(1)
	, m_edit_brightness(0)
	, m_edit_contrass(1)	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEMARSver2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SBrightness, m_slider_brightness);
	DDX_Control(pDX, IDC_SContrass, m_slider_contrass);
	DDX_Control(pDX, IDC_Pic_capture, m_capture);
	DDX_Control(pDX, IDC_Pic_thresh, m_thresh);
	DDX_Control(pDX, IDC_Hmin, m_slider_Hmin);
	DDX_Control(pDX, IDC_Smin, m_slider_Smin);
	DDX_Control(pDX, IDC_Vmin, m_slider_Vmin);
	DDX_Control(pDX, IDC_Hmax, m_slider_Hmax);
	DDX_Control(pDX, IDC_Smax, m_slider_Smax);
	DDX_Control(pDX, IDC_Vmax, m_slider_Vmax);
	DDX_Text(pDX, IDC_Edit_Hmin, m_edit_Hmin);
	DDX_Text(pDX, IDC_Edit_Smin, m_edit_Smin);
	DDX_Text(pDX, IDC_Edit_Vmin, m_edit_Vmin);
	DDX_Text(pDX, IDC_Edit_Hmax, m_edit_Hmax);
	DDX_Text(pDX, IDC_Edit_Smax, m_edit_Smax);
	DDX_Text(pDX, IDC_Edit_Vmax, m_edit_Vmax);
	DDX_Text(pDX, IDC_SendData, m_sendData);
	DDX_Text(pDX, IDC_dCom, m_portCom);
	DDX_Text(pDX, IDC_Edit_Bright, m_edit_brightness);
	DDX_Text(pDX, IDC_Edit_Contrs, m_edit_contrass);
}

BEGIN_MESSAGE_MAP(CEMARSver2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDStart, &CEMARSver2Dlg::OnBnClickedStart)
	ON_BN_CLICKED(IDExit, &CEMARSver2Dlg::OnBnClickedExit)
	ON_BN_CLICKED(IDConnect, &CEMARSver2Dlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDDisconnect, &CEMARSver2Dlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_Red, &CEMARSver2Dlg::OnBnClickedRed)
	ON_BN_CLICKED(IDC_Green, &CEMARSver2Dlg::OnBnClickedGreen)
	ON_BN_CLICKED(IDC_Blue, &CEMARSver2Dlg::OnBnClickedBlue)
	ON_BN_CLICKED(IDC_Yellow, &CEMARSver2Dlg::OnBnClickedYellow)
	ON_BN_CLICKED(IDC_Orange, &CEMARSver2Dlg::OnBnClickedOrange)
	ON_EN_CHANGE(IDC_Edit_Hmin, &CEMARSver2Dlg::OnEnChangeEditHmin)
	ON_EN_CHANGE(IDC_Edit_Smin, &CEMARSver2Dlg::OnEnChangeEditSmin)
	ON_EN_CHANGE(IDC_Edit_Vmin, &CEMARSver2Dlg::OnEnChangeEditVmin)
	ON_EN_CHANGE(IDC_Edit_Hmax, &CEMARSver2Dlg::OnEnChangeEditHmax)
	ON_EN_CHANGE(IDC_Edit_Smax, &CEMARSver2Dlg::OnEnChangeEditSmax)
	ON_EN_CHANGE(IDC_Edit_Vmax, &CEMARSver2Dlg::OnEnChangeEditVmax)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_Hmin, &CEMARSver2Dlg::OnNMReleasedcaptureHmin)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_Smin, &CEMARSver2Dlg::OnNMReleasedcaptureSmin)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_Vmin, &CEMARSver2Dlg::OnNMReleasedcaptureVmin)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_Hmax, &CEMARSver2Dlg::OnNMReleasedcaptureHmax)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_Smax, &CEMARSver2Dlg::OnNMReleasedcaptureSmax)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_Vmax, &CEMARSver2Dlg::OnNMReleasedcaptureVmax)
	ON_BN_CLICKED(IDC_Trek, &CEMARSver2Dlg::OnBnClickedTrek)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SBrightness, &CEMARSver2Dlg::OnNMReleasedcaptureSbrightness)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SContrass, &CEMARSver2Dlg::OnNMReleasedcaptureScontrass)
	ON_EN_CHANGE(IDC_Edit_Bright, &CEMARSver2Dlg::OnEnChangeEditBright)
	ON_EN_CHANGE(IDC_Edit_Contrs, &CEMARSver2Dlg::OnEnChangeEditContrs)
END_MESSAGE_MAP()

// CEMARSver2Dlg message handlers
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
int PORT;

BOOL CEMARSver2Dlg::OnInitDialog()
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
	UpdateData(1);
	m_slider_brightness.SetRange(-80,80);
	m_slider_contrass.SetRange(1,50);
	m_slider_Hmin.SetRange(0,255);
	m_slider_Smin.SetRange(0,255);
	m_slider_Vmin.SetRange(0,255);
	m_slider_Hmax.SetRange(0,255);
	m_slider_Smax.SetRange(0,255);
	m_slider_Vmax.SetRange(0,255);
	m_edit_Hmin=0;
	m_edit_Smin=0;
	m_edit_Vmin=0;
	m_edit_Hmax=0;
	m_edit_Smax=0;
	m_edit_Vmax=0;
	m_edit_brightness=-46;
	m_edit_contrass=7;
	
	UpdateData(FALSE);

	PORT = GetDlgItemInt(IDC_dCom);
	UpdateData(0);

	if(PORT==1)m_sComPort = "Com1";
	else if(PORT==2)m_sComPort = "Com2";
	else if(PORT==3)m_sComPort = "Com3";
	else if(PORT==4)m_sComPort = "Com4";

	m_hCom = CreateFile(m_sComPort, 
		GENERIC_READ | GENERIC_WRITE,
		0, // exclusive access
		NULL, // no security
		OPEN_EXISTING,
		0, // no overlapped I/O
		NULL); // null template 

	m_bPortReady = SetupComm(m_hCom, 128, 128); // set buffer sizes

	m_bPortReady = GetCommState(m_hCom, &m_dcb);
	m_dcb.BaudRate = 9600; //19200;
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

void CEMARSver2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEMARSver2Dlg::OnPaint()
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
HCURSOR CEMARSver2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

////////////////---------------------------\\\\\\\\\\\\\\\\\
///////////////____________________________\\\\\\\\\\\\\\\\\

#define rad2deg (180/(4*atan((double)1)))

long int alpha_r, alpha_g;
double dx1,dy1, dx2,dy2;
long int sdt1, sdt2;
double ax,ay, bx,by, cx,cy, dx,dy;
float xt_1,yt_1, xt_2,yt_2;

void lokal(float xo1,float yo1, float xo2,float yo2, float xt1,float yt1, float xt2,float yt2)
{	//			   R               G                 B               B
	////Penentuan ID 

	//hitung selisih koordinat
	ax=fabs(xt1-xo1);		ay=fabs(yt1-yo1);
	bx=fabs(xt2-xo1);		by=fabs(yt2-yo1);
	cx=fabs(xt1-xo2);		cy=fabs(yt1-yo2);
	dx=fabs(xt2-xo2);		dy=fabs(yt2-yo2);

	if(ax<bx && ay<by)	{ dx1=ax; dy1=ay;	xt_1=xt1; yt_1=yt1;}
	else if(ax>bx && ay>by)	{ dx1=bx; dy1=by;	xt_1=xt2; yt_1=yt2;}

	if(cx<dx && cy<dy)	{ dx2=cx; dy2=cy;	 xt_2=xt1; yt_2=yt1;}
	else if(cx>dx && cy>dy)	{ dx2=dx; dy2=dy;	 xt_2=xt2; yt_2=yt2; }

	sdt1=rad2deg * atan2(dy1,dx1);
	sdt2=rad2deg * atan2(dy2,dx2);

	//Penentuan Kuadran Robot 1
	if(xo1<=xt_1 && yo1>=yt_1)		alpha_r=sdt1;		//kuadran 1
	else if(xo1>=xt_1 && yo1>=yt_1)	alpha_r=180-sdt1;	//kuadran 2
	else if(xo1>=xt_1 && yo1<=yt_1)	alpha_r=sdt1+180;	//kuadran 3
	else if(xo1<=xt_1 && yo1<=yt_1)	alpha_r=360-sdt1;	//kuadran 4	

	//Penentuan Kuadran Robot 2
	if(xo2<=xt_2 && yo2>=yt_2)		alpha_g=sdt2;		//kuadran 1
	else if(xo2>=xt_2 && yo2>=yt_2)	alpha_g=180-sdt2;	//kuadran 2
	else if(xo2>=xt_2 && yo2<=yt_2)	alpha_g=sdt2+180;	//kuadran 3
	else if(xo2<=xt_2 && yo2<=yt_2)	alpha_g=360-sdt2;	//kuadran 4	
}

static int x_k=0;		//Asumsi posisi Gawang
static int y_k=200;
long int sdt_ro, sdt_go, sdt_rg, sdt_gr, sdt_rk, sdt_gk, sdt_ok;
long int m_ro, m_go, m_rg, m_gr, m_rk, m_gk, m_ok;

void lokal_target(float xo, float yo, float xt, float yt, char o, char t )
{
 double ax, ay, dx, dy, magnitude;
 long int sdt, px, py, alpha;

 dx=fabs(xt-xo);		dy=fabs(yt-yo);

 magnitude=sqrt(dx*dx + dy*dy);
 sdt=rad2deg * atan2(dy,dx);

 //Penentuan Kuadran (Robot -> Target)
	if(xo<=xt && yo>=yt)		alpha=sdt;		//kuadran 1
	else if(xo>=xt && yo>=yt)	alpha=180-sdt;	//kuadran 2
	else if(xo>=xt && yo<=yt)	alpha=sdt+180;	//kuadran 3
	else if(xo<=xt && yo<=yt)	alpha=360-sdt;	//kuadran 4	

	if(o=='r' && t=='o')	{ sdt_ro=alpha; m_ro=magnitude; }
	else if(o=='g' && t=='o')	{ sdt_go=alpha; m_go=magnitude; }
	else if(o=='r' && t=='g')	{ sdt_rg=alpha; m_rg=magnitude; }
	else if(o=='g' && t=='r')	{ sdt_gr=alpha; m_gr=magnitude; }
	else if(o=='r' && t=='k')	{ sdt_rk=alpha; m_rk=magnitude; }
	else if(o=='g' && t=='k')	{ sdt_gk=alpha; m_gk=magnitude; }
	else if(o=='o' && t=='k')	{ sdt_ok=alpha; m_ok=magnitude; }
}

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

void kirim(char q,int x,int y)
{	
	add(q);	data(x); add(',');data(y);
}

IplImage* ThreshImage(IplImage* image,int hmax, int smax, int vmax, int hmin,int smin, int vmin)
{
	IplImage* HSV = cvCreateImage(cvGetSize(image), 8, 3);
    cvCvtColor(image, HSV, CV_BGR2HSV);

	IplImage* Threshold = cvCreateImage(cvGetSize(image), 8, 1);
	CvScalar hsv_min = cvScalar(hmin, smin, vmin,0);
	CvScalar hsv_max = cvScalar(hmax, smax, vmax,0);
	cvInRangeS(HSV, hsv_min, hsv_max, Threshold); 
	
	//	cvAdaptiveThreshold(Threshold, Threshold, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, 101, 1);

	cvThreshold(Threshold,Threshold,150,255,CV_THRESH_BINARY);
	cvEqualizeHist(Threshold,Threshold);
	cvSmooth(Threshold,Threshold, CV_GAUSSIAN, 9, 9 );	
//	cvErode(Threshold,Threshold,NULL,1);
//	cvCanny(Threshold,Threshold,60,80,3);

	cvReleaseImage(&HSV);
    return Threshold; 
}

int x_r, x_g, x_b, x_y, x_o;
int y_r, y_g, y_b, y_y, y_o;
int x_b1, y_b1;

CvFont font;
char label_b[20], label_r[20], label_g[20], label_y[20], label_o[20];
	
void tulis(char q, int a, int b, int c, int d)
{	
	if(q=='R') { x_r=a, y_r=b; }
	else if(q=='B') { x_b=a, y_b=b, x_b1=c; y_b1=d;}
	else if(q=='G') { x_g=a, y_g=b; }
	else if(q=='Y') { x_y=a, y_y=b; }
	else if(q=='O') { x_o=a, y_o=b; }
}

void tracking(IplImage* image, IplImage* image2,char z)
{	
	CBlobResult blobs;    
	CBlob *currentBlob;   
	CvPoint pt1, pt2;  
	CvRect cvRect;  
	int midX[30],midY[30];
	char label[20];

	cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, .8, .8, 0, 1, 8);

	// Detect the white blobs from the black background  
            blobs = CBlobResult( image, NULL, 0 );    
      
            // Exclude white blobs smaller than the given value (10)    
            // The bigger the last parameter, the bigger the blobs need    
            // to be for inclusion    
            blobs.Filter( blobs,B_EXCLUDE,CBlobGetArea(),B_LESS,10 ); 
			      
            // Attach a bounding rectangle for each blob discovered  
            int num_blobs = blobs.GetNumBlobs();  
      
            for ( int i = 0; i < num_blobs; i++ )    
            {                 
                currentBlob = blobs.GetBlob( i );               
                cvRect = currentBlob->GetBoundingBox();  
      
                pt1.x = cvRect.x;  
                pt1.y = cvRect.y;  
                pt2.x = cvRect.x + cvRect.width;  
                pt2.y = cvRect.y + cvRect.height;  

				midX[i]=cvRect.width*0.5+pt1.x;
				midY[i]=cvRect.height*0.5+pt1.y;

                // Attach bounding rect to blob in orginal video input  
                cvRectangle( image2, pt1, pt2, cvScalar(255, 0, 0, 0),1, 8,0 );
				
				cvCircle( image2, cvPoint(midX[i],midY[i]),3, CV_RGB(0,255,0), -1, 8, 0 );
				sprintf(label,"%c.%d",z,i);
				cvPutText(image2, label, cvPoint(midX[i],midY[i]),&font,CV_RGB(0,255,0));
			}	

			tulis(z,midX[0],midY[0],midX[1],midY[1]);
}

bool tutup, koneksi;
int flag=0, tanda=0;

/*	Lapangan LAb jj208
int Hmin_r=156, Smin_r=111, Vmin_r=74;		//127, 75, 93
int Hmax_r=255, Smax_r=255, Vmax_r=255;		//205
int Hmin_b=95, Smin_b=95, Vmin_b=71;
int Hmax_b=140, Smax_b=255, Vmax_b=255;
int Hmin_g=49, Smin_g=38, Vmin_g=76;
int Hmax_g=78, Smax_g=255, Vmax_g=255;
int Hmin_y=15, Smin_y=133, Vmin_y=88;
int Hmax_y=63, Smax_y=255, Vmax_y=255;
int Hmin_o=151, Smin_o=109, Vmin_o=198;		
int Hmax_o=255, Smax_o=255, Vmax_o=255;		
*/

int Hmin_r=150, Smin_r=50, Vmin_r=144;		//127, 75, 93
int Hmax_r=157, Smax_r=255, Vmax_r=255;		//205
int Hmin_b=72, Smin_b=122, Vmin_b=125;
int Hmax_b=137, Smax_b=255, Vmax_b=255;
int Hmin_g=48, Smin_g=17, Vmin_g=133;
int Hmax_g=76, Smax_g=255, Vmax_g=255;
int Hmin_y=15, Smin_y=133, Vmin_y=88;
int Hmax_y=63, Smax_y=255, Vmax_y=255;
int Hmin_o=0, Smin_o=147, Vmin_o=111;		
int Hmax_o=49, Smax_o=255, Vmax_o=255;		

int h_r=Hmin_r , s_r=Smin_r, v_r=Vmin_r;
int hm_r=Hmax_r, sm_r=Smax_r, vm_r=Vmax_r;

int h_b=Hmin_b , s_b=Smin_b, v_b=Vmin_b;
int hm_b=Hmax_b, sm_b=Smax_b, vm_b=Vmax_b;
int h_g=Hmin_g , s_g=Smin_g, v_g=Vmin_g;
int hm_g=Hmax_g, sm_g=Smax_g, vm_g=Vmax_g;
int h_y=Hmin_y , s_y=Smin_y, v_y=Vmin_y;
int hm_y=Hmax_y, sm_y=Smax_y, vm_y=Vmax_y;
int h_o=Hmin_o , s_o=Smin_o, v_o=Vmin_o;
int hm_o=Hmax_o, sm_o=Smax_o, vm_o=Vmax_o;

int br, cn; float cnt;

CvCapture *capture;
IplImage* imgScribble = NULL;
FILE *save;

void CEMARSver2Dlg::OnBnClickedStart()
{
	// TODO: Add your control notification handler code here
	cvNamedWindow( "camera", CV_WINDOW_AUTOSIZE );	
	cvNamedWindow( "thresh", CV_WINDOW_AUTOSIZE );	

	HWND hWnd1 = (HWND) cvGetWindowHandle("camera");
	HWND hParent1 = ::GetParent(hWnd1);
	::SetParent(hWnd1, GetDlgItem(IDC_Pic_capture)->m_hWnd);
	::ShowWindow(hParent1, SW_HIDE);

	HWND hWnd2 = (HWND) cvGetWindowHandle("thresh");
	HWND hParent2 = ::GetParent(hWnd2);
	::SetParent(hWnd2, GetDlgItem(IDC_Pic_thresh)->m_hWnd);
	::ShowWindow(hParent2, SW_HIDE);
	
	capture=cvCaptureFromCAM(1);
	cvResizeWindow("camera",800,600);//320,270
	cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH,600);
	cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT,480);

	
	save=fopen("Data.txt","w");

	while(!tutup){
	//Mat* streaming = cvCaptureFromFile("http://192.168.0.10");
	if( !cvGrabFrame( capture )) break;
	IplImage* streaming = cvRetrieveFrame(capture);
	cvFlip(streaming,streaming, 1);
	cvFlip(streaming,streaming, 1);
	streaming->origin=0;

	br=GetDlgItemInt(IDC_Edit_Bright);	
	cn=GetDlgItemInt(IDC_Edit_Contrs);	
	cnt=0.1*cn;

	cvAddS(streaming,cvScalar(br,br,br),streaming);
	cvScale(streaming,streaming,cnt);

	//IplImage* frame = cvCreateImage( cvSize(streaming->width/1,streaming->height/1), //1.46//1.4
	//				  streaming->depth,
	//				  streaming->nChannels );
	//cvResize(streaming,frame,CV_INTER_NN); 
	
	if(imgScribble == NULL)
		{	imgScribble = cvCreateImage(cvGetSize(streaming),8,3);	}

	IplImage *imgThresh_r;
	IplImage *imgThresh_g;
	IplImage *imgThresh_b;
	IplImage *imgThresh_y;
	IplImage *imgThresh_o;
	
	//--------copy streaming-------
	IplImage *cpstreaming;
	cpstreaming = cvCloneImage(streaming);
	//-------------KALIBRASI------------//
	switch(flag)
	{
	case 1:	h_r=GetDlgItemInt(IDC_Edit_Hmin);	hm_r=GetDlgItemInt(IDC_Edit_Hmax);
			s_r=GetDlgItemInt(IDC_Edit_Smin);	sm_r=GetDlgItemInt(IDC_Edit_Smax);
			v_r=GetDlgItemInt(IDC_Edit_Vmin);	vm_r=GetDlgItemInt(IDC_Edit_Vmax); break;
	case 2: h_g=GetDlgItemInt(IDC_Edit_Hmin);	hm_g=GetDlgItemInt(IDC_Edit_Hmax);
			s_g=GetDlgItemInt(IDC_Edit_Smin);	sm_g=GetDlgItemInt(IDC_Edit_Smax);
			v_g=GetDlgItemInt(IDC_Edit_Vmin);	vm_g=GetDlgItemInt(IDC_Edit_Vmax); break;
	case 3: h_b=GetDlgItemInt(IDC_Edit_Hmin);	hm_b=GetDlgItemInt(IDC_Edit_Hmax);
			s_b=GetDlgItemInt(IDC_Edit_Smin);	sm_b=GetDlgItemInt(IDC_Edit_Smax);
			v_b=GetDlgItemInt(IDC_Edit_Vmin);	vm_b=GetDlgItemInt(IDC_Edit_Vmax); break;
	case 4: h_y=GetDlgItemInt(IDC_Edit_Hmin);	hm_y=GetDlgItemInt(IDC_Edit_Hmax);
			s_y=GetDlgItemInt(IDC_Edit_Smin);	sm_y=GetDlgItemInt(IDC_Edit_Smax);
			v_y=GetDlgItemInt(IDC_Edit_Vmin);	vm_y=GetDlgItemInt(IDC_Edit_Vmax); break;
	case 5: h_o=GetDlgItemInt(IDC_Edit_Hmin);	hm_o=GetDlgItemInt(IDC_Edit_Hmax);
			s_o=GetDlgItemInt(IDC_Edit_Smin);	sm_o=GetDlgItemInt(IDC_Edit_Smax);
			v_o=GetDlgItemInt(IDC_Edit_Vmin);	vm_o=GetDlgItemInt(IDC_Edit_Vmax); break;
	}


		/*	imgThresh_r = ThreshImage( streaming,hm_r,sm_r,vm_r, h_r,s_r,v_r );
			tracking(imgThresh_r, streaming,'R');
	
			imgThresh_b = ThreshImage( streaming,hm_b,sm_b,vm_b, h_b,s_b,v_b );
			tracking(imgThresh_b, streaming,'B'); 
			

			imgThresh_g = ThreshImage( streaming,hm_g,sm_g,vm_g, h_g,s_g,v_g );
			tracking(imgThresh_g, streaming,'G');*/

		//	imgThresh_y = ThreshImage( streaming,hm_y,sm_y,vm_y, h_y,s_y,v_y );
		//	tracking(imgThresh_y, streaming,'Y');

			imgThresh_o = ThreshImage( streaming,hm_o,sm_o,vm_o, h_o,s_o,v_o );
			tracking(imgThresh_o, streaming,'O');


			lokal(x_r,y_r,x_g,y_g,x_b,y_b,x_b1,y_b1);

			/*sprintf(label_b,"%d.B(%d,%d)",0,x_b,y_b);
			cvPutText(streaming, label_b, cvPoint(10,20),&font,CV_RGB(255,0,0));*/

			/*sprintf(label_r,"%d.R(%d,%d)",0,x_r,y_r);
			cvPutText(streaming, label_r, cvPoint(10,40),&font,CV_RGB(255,0,0));

			sprintf(label_r,"%d.R(%d,%d)",1,x_r1,y_r1);
			cvPutText(streaming, label_r, cvPoint(10,60),&font,CV_RGB(255,0,0));*/
		
//-----------------------------
		int rt, gt, sr, sg; 

		lokal_target(x_r,y_r,x_o,y_o,'r','o');	//Red->Orange
		lokal_target(x_g,y_g,x_o,y_o,'g','o');	//Green->Orange

		lokal_target(x_r,y_r,x_g,y_g,'r','g');	//Red->Green
		lokal_target(x_g,y_g,x_r,y_r,'g','r');		//Green->Red

		//lokal_target(x_r,y_r,x_k,y_k,'r','k');	//Red->Goal
		//lokal_target(x_g,y_g,x_k,y_k,'g','k');	//Green->Goal

		lokal_target(x_r,y_r,622,252,'r','k');	//Red->Goal
		lokal_target(x_g,y_g,622,252,'g','k');	//Green->Goal
		lokal_target(x_o,y_o,622,252,'o','k');	//Orange->Goal

////////-----------------//------------------------//----------//////////
///Formation Spring---Kejar2an
	//	if(m_ro <= m_go){	rt=m_ro; sr=sdt_ro; gt=m_gr; sg=sdt_gr; }
	//	else {	rt=m_rg; sr=sdt_rg; gt=m_go; sg=sdt_go;}

// Warna garis leader/follower
		int rr1,gg1,bb1, rr2,gg2,bb2;

		if(m_ro <= m_go) { rr1=20; gg1=128; bb1=80;  rr2=20; gg2=255; bb2=0;}
		else {  rr1=20; gg1=255; bb1=0;  rr2=20; gg2=128; bb2=80; }

		cvLine(cpstreaming,cvPoint(x_o,y_o), cvPoint(x_r,y_r),cvScalar(bb1,gg1,rr1),2);
		cvLine(cpstreaming,cvPoint(x_o,y_o), cvPoint(x_g,y_g),cvScalar(bb2,gg2,rr2),2);
		cvLine(cpstreaming,cvPoint(x_r,y_r), cvPoint(x_g,y_g),cvScalar(20,255,0),2);
//-----------------------------
		static int posX_r = 0;  static int posX_g = 0;  static int posX_y = 0;  static int posX_o = 0;
		static int posY_r = 0;  static int posY_g = 0;	static int posY_y = 0;  static int posY_o = 0;

		int lastX_r=posX_r;		int lastX_g=posX_g;		int lastX_y=posX_y;  int lastX_o=posX_o;
		int lastY_r=posY_r;		int lastY_g=posY_g;		int lastY_y=posY_y;  int lastY_o=posY_o;
		
		posX_r=x_r; posY_r=y_r;		posX_g=x_g; posY_g=y_g;		
		posX_y=x_y; posY_y=y_y;		posX_o=x_o; posY_o=y_o;

		int j,l;

		if(x_r<=5 || y_r<=5 ) j=1; else j=0;
		if(x_g<=5 || y_g<=5)  l=1; else l=0;

		if(!koneksi)
		{	UpdateData(1);
			m_sendData.Format(L"Koneksi Terputus....Silahkan Tekan Tombol Connect");
			add('o'); add(13);
			
			UpdateData(0);		
		}
		else 
		{	UpdateData(1);
			//m_sendData.Format(L"R(%d, %d), G(%d,%d), <R%d,<G%d ",sr,rt, sg,gt, alpha_r, alpha_g);
			m_sendData.Format(L"R(%d, %d), G(%d,%d), O(%d,%d), <R%d,<G%d ",sdt_ro,m_ro, sdt_go,m_go, x_o,y_o, alpha_r, alpha_g);
			UpdateData(0);
			//---------KIRIM SERIAL-----------	
			
			kirim('z',j,l); add(13);

			kirim('!',alpha_r,alpha_g);	add(13);
			kirim('R',sdt_ro,m_ro);	add(13);
			kirim('G',sdt_go,m_go);	add(13);
			kirim('r',sdt_rg,m_rg);	add(13);
			kirim('g',sdt_gr,m_gr);	add(13);

			
			kirim('K',sdt_rk,m_rk);	add(13);
			kirim('k',sdt_gk,m_gk);	add(13);
			kirim('@',sdt_ok,m_ok); add(13);
			
		//	kirim('R',sr,rt);	add(13);
		//	kirim('G',sg,gt);	add(13);
		//	kirim('r',sdt_rk,m_rk);	add(13);
		//	kirim('g',sdt_gk,m_gk);	add(13);

			///////------------------Garis Trek--------------//////////////
			//	if(lastX_r>0 && lastY_r>0 && posX_r>0 && posY_r>0)
			//{
			////	Gambar garis merah
			//	cvLine(imgScribble, cvPoint(posX_r,posY_r), cvPoint(lastX_r,lastY_r),cvScalar(0,0,255),2);
			//}
			//	if(lastX_g>0 && lastY_g>0 && posX_g>0 && posY_g>0)
			//{
			////	Gambar garis Hijau
			//	cvLine(imgScribble, cvPoint(posX_g,posY_g), cvPoint(lastX_g,lastY_g),cvScalar(0,255,0),2);
			//}
				if(lastX_o>0 && lastY_o>0 && posX_o>0 && posY_o>0)
			{
			//	Gambar garis orange
				cvLine(imgScribble, cvPoint(posX_o,posY_o), cvPoint(lastX_o,lastY_o),cvScalar(0,255,255),2);
			}
			/*{
			//	Gambar garis kuning
				cvLine(imgScribble, cvPoint(posX_y,posY_y), cvPoint(lastX_y,lastY_y),cvScalar(0,255,255),2);
			}*/
			///----------//////////////////-////////----------------////////

			fprintf(save,"%d\t%d\t%d\t  %d\t%d\t%d\t  %d\t%d\t  %d\t%d\t\%d\t%d\n",lastX_r,lastY_r,alpha_r, lastX_g,lastY_g,alpha_g, lastX_o,lastY_o, sdt_ro,sdt_go, sdt_rg,sdt_gr);
		}

		cvShowImage( "camera", streaming);
		cvAdd(streaming, imgScribble,streaming); 

		switch(tanda)
	{
		case 1:	cvShowImage( "thresh", imgThresh_r );  break;// Hasil streaming setelah diFilter		
		case 2:	cvShowImage( "thresh", imgThresh_g );  break;	
		case 3: cvShowImage( "thresh", imgThresh_b );  break;
		case 4: cvShowImage( "thresh", imgThresh_y );  break;
		case 5: cvShowImage( "thresh", imgThresh_o );  break; 
		case 6: cvShowImage( "thresh", streaming   );  
				cvShowImage( "camera", cpstreaming );  break;
	}
						
	cvWaitKey(5);
	
	//cvReleaseImage( &imgThresh_r );
	//cvReleaseImage( &imgThresh_g );
	//cvReleaseImage( &imgThresh_b );
	////cvReleaseImage( &imgThresh_y );
	cvReleaseImage( &imgThresh_o );
	cvReleaseImage( &cpstreaming);
		
	}
	cvReleaseCapture( &capture );
	fclose(save);
}

void CEMARSver2Dlg::OnBnClickedExit()
{
	// TODO: Add your control notification handler code here
	tutup=true;
	cvReleaseCapture(&capture);
	OnCancel();

}

void CEMARSver2Dlg::OnBnClickedConnect()
{
	// TODO: Add your control notification handler code here
	koneksi=true;
}

void CEMARSver2Dlg::OnBnClickedDisconnect()
{
	// TODO: Add your control notification handler code here
	koneksi=false;
}

void CEMARSver2Dlg::OnBnClickedRed()
{
	// TODO: Add your control notification handler code here
	flag=1; tanda=1; UpdateData(1);	
	m_slider_Hmin.SetPos(h_r); m_edit_Hmin=h_r;
	m_slider_Smin.SetPos(s_r); m_edit_Smin=s_r;
	m_slider_Vmin.SetPos(v_r); m_edit_Vmin=v_r;
	m_slider_Hmax.SetPos(hm_r); m_edit_Hmax=hm_r;
	m_slider_Smax.SetPos(sm_r); m_edit_Smax=sm_r;
	m_slider_Vmax.SetPos(vm_r); m_edit_Vmax=vm_r;
			UpdateData(0);
}

void CEMARSver2Dlg::OnBnClickedGreen()
{
	// TODO: Add your control notification handler code here
	flag=2;	tanda=2; UpdateData(1);	
	m_slider_Hmin.SetPos(h_g); m_edit_Hmin=h_g;
	m_slider_Smin.SetPos(s_g); m_edit_Smin=s_g;
	m_slider_Vmin.SetPos(v_g); m_edit_Vmin=v_g;
	m_slider_Hmax.SetPos(hm_g); m_edit_Hmax=hm_g;
	m_slider_Smax.SetPos(sm_g); m_edit_Smax=sm_g;
	m_slider_Vmax.SetPos(vm_g); m_edit_Vmax=vm_g;
			UpdateData(0);
}

void CEMARSver2Dlg::OnBnClickedBlue()
{
	// TODO: Add your control notification handler code here
	flag=3; tanda=3; UpdateData(1);	
	m_slider_Hmin.SetPos(h_b); m_edit_Hmin=h_b;
	m_slider_Smin.SetPos(s_b); m_edit_Smin=s_b;
	m_slider_Vmin.SetPos(v_b); m_edit_Vmin=v_b;
	m_slider_Hmax.SetPos(hm_b); m_edit_Hmax=hm_b;
	m_slider_Smax.SetPos(sm_b); m_edit_Smax=sm_b;
	m_slider_Vmax.SetPos(vm_b); m_edit_Vmax=vm_b;
			UpdateData(0);
}

void CEMARSver2Dlg::OnBnClickedYellow()
{
	// TODO: Add your control notification handler code here
	flag=4; tanda=4; UpdateData(1);	
	m_slider_Hmin.SetPos(h_y); m_edit_Hmin=h_y;
	m_slider_Smin.SetPos(s_y); m_edit_Smin=s_y;
	m_slider_Vmin.SetPos(v_y); m_edit_Vmin=v_y;
	m_slider_Hmax.SetPos(hm_y); m_edit_Hmax=hm_y;
	m_slider_Smax.SetPos(sm_y); m_edit_Smax=sm_y;
	m_slider_Vmax.SetPos(vm_y); m_edit_Vmax=vm_y;
			UpdateData(0);
}

void CEMARSver2Dlg::OnBnClickedOrange()
{
	// TODO: Add your control notification handler code here
	flag=5; tanda=5; UpdateData(1);	
	m_slider_Hmin.SetPos(h_o); m_edit_Hmin=h_o;
	m_slider_Smin.SetPos(s_o); m_edit_Smin=s_o;
	m_slider_Vmin.SetPos(v_o); m_edit_Vmin=v_o;
	m_slider_Hmax.SetPos(hm_o); m_edit_Hmax=hm_o;
	m_slider_Smax.SetPos(sm_o); m_edit_Smax=sm_o;
	m_slider_Vmax.SetPos(vm_o); m_edit_Vmax=vm_o;
			UpdateData(0);
}

void CEMARSver2Dlg::OnBnClickedTrek()
{
	// TODO: Add your control notification handler code here
	tanda=6;
}

void CEMARSver2Dlg::OnEnChangeEditHmin()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_Edit_Hmin);
	UpdateData(1);
	m_slider_Hmin.SetPos(k);
	UpdateData(0);
}

void CEMARSver2Dlg::OnEnChangeEditSmin()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_Edit_Smin);
	UpdateData(1);
	m_slider_Smin.SetPos(k);
	UpdateData(0);
}

void CEMARSver2Dlg::OnEnChangeEditVmin()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_Edit_Vmin);
	UpdateData(1);
	m_slider_Vmin.SetPos(k);
	UpdateData(0);
}

void CEMARSver2Dlg::OnEnChangeEditHmax()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_Edit_Hmax);
	UpdateData(1);
	m_slider_Hmax.SetPos(k);
	UpdateData(0);
}

void CEMARSver2Dlg::OnEnChangeEditSmax()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_Edit_Smax);
	UpdateData(1);
	m_slider_Smax.SetPos(k);
	UpdateData(0);
}

void CEMARSver2Dlg::OnEnChangeEditVmax()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_Edit_Vmax);
	UpdateData(1);
	m_slider_Vmax.SetPos(k);
	UpdateData(0);
}

void CEMARSver2Dlg::OnEnChangeEditBright()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_Edit_Bright);
	UpdateData(1);
	m_slider_brightness.SetPos(k);
	UpdateData(0);
}

void CEMARSver2Dlg::OnEnChangeEditContrs()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int k=GetDlgItemInt(IDC_Edit_Contrs);
	UpdateData(1);
	m_slider_contrass.SetPos(k);
	UpdateData(0);
}


void CEMARSver2Dlg::OnNMReleasedcaptureHmin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_Hmin=m_slider_Hmin.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSver2Dlg::OnNMReleasedcaptureSmin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_Smin=m_slider_Smin.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSver2Dlg::OnNMReleasedcaptureVmin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_Vmin=m_slider_Vmin.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSver2Dlg::OnNMReleasedcaptureHmax(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_Hmax=m_slider_Hmax.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSver2Dlg::OnNMReleasedcaptureSmax(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_Smax=m_slider_Smax.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSver2Dlg::OnNMReleasedcaptureVmax(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_Vmax=m_slider_Vmax.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSver2Dlg::OnNMReleasedcaptureSbrightness(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_brightness=m_slider_brightness.GetPos();
	UpdateData(0);
	*pResult = 0;
}

void CEMARSver2Dlg::OnNMReleasedcaptureScontrass(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	m_edit_contrass=m_slider_contrass.GetPos();
	UpdateData(0);
	*pResult = 0;
}
