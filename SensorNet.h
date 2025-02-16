// SensorNet.h : main header file for the SENSORNET application
//

#if !defined(AFX_SENSORNET_H__63366F94_9AE9_4EB2_B37A_EE08907368F6__INCLUDED_)
#define AFX_SENSORNET_H__63366F94_9AE9_4EB2_B37A_EE08907368F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSensorNetApp:
// See SensorNet.cpp for the implementation of this class
//

class CSensorNetApp : public CWinApp
{
public:
	CSensorNetApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSensorNetApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSensorNetApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENSORNET_H__63366F94_9AE9_4EB2_B37A_EE08907368F6__INCLUDED_)
