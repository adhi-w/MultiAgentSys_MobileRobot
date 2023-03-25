// E-MARS GUIDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CEMARSGUIDlg dialog
class CEMARSGUIDlg : public CDialog
{
// Construction
public:
	CEMARSGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EMARSGUI_DIALOG };

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
	afx_msg void OnBnClickedCancel2();
	CStatic m_capture;
	CStatic m_thresh;
	afx_msg void OnBnClickedstart();
	afx_msg void OnBnClickedconnect();
	afx_msg void OnBnClickedstop();
	afx_msg void OnBnClickedexit();
	afx_msg void OnBnClickedred();
	int m_slider_h_min;
	CString m_edit_hmin;
	CSliderCtrl m_slider_hmin;
	int m_edit_smin;
	int m_edit_vmin;
	afx_msg void OnNMReleasedcapturehmin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeedithmin();
	int m_edit_h_min;
	afx_msg void OnBnClickedgreen();
	afx_msg void OnBnClickedblue();
	afx_msg void OnBnClickedyellow();
	afx_msg void OnBnClickedcyan();
	afx_msg void OnBnClickedmagenta();
	CSliderCtrl m_slider_smin;
	CSliderCtrl m_slider_vmin;
	CSliderCtrl m_slider_hmax;
	CSliderCtrl m_slider_smax;
	CSliderCtrl m_slider_vmax;
	int m_edit_hmax;
	int m_edit_smax;
	int m_edit_vmax;
	afx_msg void OnNMReleasedcapturesmin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcapturevmin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcapturehmax(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcapturesmax(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcapturevmax(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeeditsmin();
	afx_msg void OnEnChangeeditvmin();
	afx_msg void OnEnChangeedithmax();
	afx_msg void OnEnChangeeditsmax();
	afx_msg void OnEnChangeeditvmax();
	CString m_data;
	CString m_dat_terima;
};
