// E-MARS ver2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CEMARSver2App:
// See E-MARS ver2.cpp for the implementation of this class
//

class CEMARSver2App : public CWinApp
{
public:
	CEMARSver2App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CEMARSver2App theApp;