// E-MARS ver2Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CEMARSver2Dlg dialog
class CEMARSver2Dlg : public CDialog
{
// Construction
public:
	CEMARSver2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EMARSVER2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CStatic m_capture;
	afx_msg void OnBnClickedCancel();
	CStatic m_thresh;
	CButton m_start;
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider_Hmin;
	CSliderCtrl m_slider_Smin;
	CSliderCtrl m_slider_Vmin;
	CSliderCtrl m_slider_Hmax;
	CSliderCtrl m_slider_Smax;
	CSliderCtrl m_slider_Vmax;
	afx_msg void OnBnClickedRed();
	afx_msg void OnBnClickedGreen();
	afx_msg void OnBnClickedBlue();
	afx_msg void OnBnClickedYellow();
	afx_msg void OnBnClickedOrange();
	afx_msg void OnEnChangeEditHmin();
	afx_msg void OnEnChangeEditSmin();
	afx_msg void OnEnChangeEditVmin();
	afx_msg void OnEnChangeEditHmax();
	afx_msg void OnEnChangeEditSmax();
	afx_msg void OnEnChangeEditVmax();
	int m_edit_Hmin;
	int m_edit_Smin;
	int m_edit_Vmin;
	int m_edit_Hmax;
	int m_edit_Smax;
	int m_edit_Vmax;
	afx_msg void OnNMReleasedcaptureHmin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSmin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureVmin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureHmax(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSmax(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureVmax(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_portComm;
	CString m_sendData;
	int m_portCom;
	afx_msg void OnBnClickedTrek();
	int m_brightness;
	int m_Brightness;
	int m_Contrass;
	int m_edit_brightness;
	float m_edit_contrass;
	afx_msg void OnNMReleasedcaptureSbrightness(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureScontrass(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider_brightness;
	CSliderCtrl m_slider_contrass;
	afx_msg void OnEnChangeEditContrass();
	afx_msg void OnEnChangeEditBrightness();
	afx_msg void OnEnChangeEditBright();
	afx_msg void OnEnChangeEditContrs();
};
