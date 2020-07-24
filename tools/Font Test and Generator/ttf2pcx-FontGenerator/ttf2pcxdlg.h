// ttf2pcxdlg.h : header file
//

#include "previewbutton.h"
#include "character.h"

/////////////////////////////////////////////////////////////////////////////
// Cttf2pcxDlg dialog

class Cttf2pcxDlg : public CDialog
{
// Construction
public:
	Cttf2pcxDlg(CWnd* pParent = NULL);	// standard constructor
	~Cttf2pcxDlg();

	CFont *GetFont(BOOL big = FALSE);
	void SaveChars(FILE *f, BOOL antialias);

	CCharacter *chars;

	int minchar, maxchar;

// Dialog Data
	//{{AFX_DATA(Cttf2pcxDlg)
	enum { IDD = IDD_TTF2PCX_DIALOG };
	CPreviewButton	m_preview;
	CEdit	m_mincolortext;
	CEdit	m_maxcolortext;
	CComboBox	m_stylelist;
	CComboBox	m_sizelist;
	CComboBox	m_fontlist;
	CString	m_font;
	CString	m_size;
	CString	m_style;
	int		m_maxcolor;
	int		m_mincolor;
	int		m_outputmode;
	CString	m_minchar;
	CString	m_maxchar;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cttf2pcxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(Cttf2pcxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExport();
	afx_msg void OnAntialiased();
	afx_msg void OnMonochrome();
	afx_msg void OnQuit();
	afx_msg void OnChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
