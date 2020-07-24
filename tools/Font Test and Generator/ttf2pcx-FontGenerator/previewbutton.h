// PreviewButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPreviewButton window

class CPreviewButton : public CButton
{
// Construction
public:
	CPreviewButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPreviewButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPreviewButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
