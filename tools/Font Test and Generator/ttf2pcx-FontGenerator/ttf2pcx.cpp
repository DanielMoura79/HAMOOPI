// ttf2pcx.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ttf2pcx.h"
#include "ttf2pcxdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cttf2pcxApp

BEGIN_MESSAGE_MAP(Cttf2pcxApp, CWinApp)
	//{{AFX_MSG_MAP(Cttf2pcxApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cttf2pcxApp construction

Cttf2pcxApp::Cttf2pcxApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only Cttf2pcxApp object

Cttf2pcxApp theApp;

/////////////////////////////////////////////////////////////////////////////
// Cttf2pcxApp initialization

BOOL Cttf2pcxApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	Cttf2pcxDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
