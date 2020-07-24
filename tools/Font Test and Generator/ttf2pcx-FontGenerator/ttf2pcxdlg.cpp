// ttf2pcxdlg.cpp : implementation file
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
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cttf2pcxDlg dialog

Cttf2pcxDlg::Cttf2pcxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cttf2pcxDlg::IDD, pParent)
{
	chars = new CCharacter[65536];

	//{{AFX_DATA_INIT(Cttf2pcxDlg)
	m_font = _T("Times New Roman");
	m_size = _T("12");
	m_style = _T("Regular");
	m_maxcolor = 254;
	m_mincolor = 1;
	m_outputmode = 0;
	m_minchar = _T("0x20");
	m_maxchar = _T("0x7F");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

Cttf2pcxDlg::~Cttf2pcxDlg()
{
	delete [] chars;
}

void Cttf2pcxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cttf2pcxDlg)
	DDX_Control(pDX, IDC_PREVIEW, m_preview);
	DDX_Control(pDX, IDC_MINCOLOR, m_mincolortext);
	DDX_Control(pDX, IDC_MAXCOLOR, m_maxcolortext);
	DDX_Control(pDX, IDC_STYLELIST, m_stylelist);
	DDX_Control(pDX, IDC_SIZELIST, m_sizelist);
	DDX_Control(pDX, IDC_FONTLIST, m_fontlist);
	DDX_CBString(pDX, IDC_FONTLIST, m_font);
	DDX_CBString(pDX, IDC_SIZELIST, m_size);
	DDX_CBString(pDX, IDC_STYLELIST, m_style);
	DDX_Text(pDX, IDC_MAXCOLOR, m_maxcolor);
	DDV_MinMaxInt(pDX, m_maxcolor, 1, 254);
	DDX_Text(pDX, IDC_MINCOLOR, m_mincolor);
	DDV_MinMaxInt(pDX, m_mincolor, 1, 254);
	DDX_Radio(pDX, IDC_MONOCHROME, m_outputmode);
	DDX_Text(pDX, IDC_MINCHAR, m_minchar);

	if (pDX->m_bSaveAndValidate) {
		minchar = strtol(m_minchar, NULL, 0);

		if ((minchar <= 0) || (minchar > 65535)) {
			AfxMessageBox("Starting character must be in range 1-65535");
			pDX->Fail();
		}
	}

	DDX_Text(pDX, IDC_MAXCHAR, m_maxchar);

	if (pDX->m_bSaveAndValidate) {
		maxchar = strtol(m_maxchar, NULL, 0);

		if ((maxchar <= 0) || (maxchar > 65535)) {
			AfxMessageBox("End character must be in range 1-65535");
			pDX->Fail();
		}

		if (maxchar < minchar) {
			AfxMessageBox("Start character greater than end character, you stupid fool...");
			pDX->Fail();
		}
	}

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cttf2pcxDlg, CDialog)
	//{{AFX_MSG_MAP(Cttf2pcxDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	ON_BN_CLICKED(IDC_ANTIALIASED, OnAntialiased)
	ON_BN_CLICKED(IDC_MONOCHROME, OnMonochrome)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_CBN_SELCHANGE(IDC_FONTLIST, OnChange)
	ON_CBN_SELCHANGE(IDC_STYLELIST, OnChange)
	ON_CBN_SELCHANGE(IDC_SIZELIST, OnChange)
	ON_CBN_EDITCHANGE(IDC_FONTLIST, OnChange)
	ON_CBN_EDITCHANGE(IDC_STYLELIST, OnChange)
	ON_CBN_EDITCHANGE(IDC_SIZELIST, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cttf2pcxDlg message handlers


int CALLBACK enumfontproc(const LOGFONT *lpelfe, const TEXTMETRICA *lpntme, unsigned long FontType,     long lParam)
{
	CComboBox *combo = (CComboBox *)lParam;

	if (combo->FindStringExact(-1, lpelfe->lfFaceName) == CB_ERR)
		combo->AddString(lpelfe->lfFaceName);

	return 1;
}


BOOL Cttf2pcxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	SetIcon(m_hIcon, TRUE);                 // Set big icon
	SetIcon(m_hIcon, FALSE);                // Set small icon

	LOGFONT lf;

	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfFaceName[0] = 0;
	lf.lfPitchAndFamily = 0;

	CClientDC cdc(this);

	EnumFontFamiliesEx(cdc.m_hAttribDC, &lf, enumfontproc, (DWORD)&m_fontlist, 0);

	m_fontlist.SelectString(-1, "Times New Roman");

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void Cttf2pcxDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cttf2pcxDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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


HCURSOR Cttf2pcxDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


#define FONT_SIZE       (maxchar - minchar + 1)


void iputw(int w, FILE *f)
{
   int b1, b2;

   b1 = (w & 0xff00) >> 8;
   b2 = w & 0x00ff;

   putc(b2, f);
   putc(b1, f);
}


void save_pcx(unsigned char *b, int bw, int bh, FILE *f, BOOL antialias, int minc, int maxc)
{
   int c, d;
   int x, y;
   int runcount;
   char runchar;
   char ch;

   putc(10, f);                /* manufacturer */
   putc(5, f);                 /* version */
   putc(1, f);                 /* run length encoding  */
   putc(8, f);                 /* 8 bits per pixel */
   iputw(0, f);                /* xmin */
   iputw(0, f);                /* ymin */
   iputw(bw-1, f);             /* xmax */
   iputw(bh-1, f);             /* ymax */
   iputw(320, f);              /* HDpi */
   iputw(200, f);              /* VDpi */
   for (c=0; c<16; c++) {
      putc(c, f);
      putc(c, f);
      putc(c, f);
   }
   putc(0, f);                 /* reserved */
   putc(1, f);                 /* one color plane */
   iputw(bw, f);               /* number of bytes per scanline */
   iputw(1, f);                /* color pallete */
   iputw(bw, f);               /* hscreen size */
   iputw(bh, f);               /* vscreen size */
   for (c=0; c<54; c++)        /* filler */
      putc(0, f);

   for (y=0; y<bh; y++) {      /* for each scanline... */
      runcount = 0;
      runchar = 0;
      for (x=0; x<bw; x++) {   /* for each pixel... */
	     ch = b[x+y*bw];
	     if (runcount==0) {
		runcount = 1;
		runchar = ch;
	     }
	     else {
		if ((ch != runchar) || (runcount >= 0x3f)) {
		   if ((runcount > 1) || ((runchar & 0xC0) == 0xC0))
			  putc(0xC0 | runcount, f);
		   putc(runchar,f);
		   runcount = 1;
		   runchar = ch;
		}
		else
		   runcount++;
	     }
      }
      if ((runcount > 1) || ((runchar & 0xC0) == 0xC0))
	     putc(0xC0 | runcount, f);
      putc(runchar,f);
   }

   putc(12,f);                 /* 256 color pallete flag */

   putc(255, f);
   putc(0, f);
   putc(255, f);

   if (antialias) {
      for (c=1; c<255; c++) {
		 if ((c == minc) && (c == maxc)) {
		putc(128, f);
			putc(128, f);
			putc(128, f);
		 }
		 else if ((c >= minc) && (c <= maxc)) {
			d = (c-minc)*255/(maxc-minc);
		putc(d, f);
			putc(d, f);
			putc(d, f);
		 }
		 else if ((c >= maxc) && (c <= minc)) {
			d = (c-maxc)*255/(minc-maxc);
		putc(d, f);
			putc(d, f);
			putc(d, f);
		 }
		 else {
		putc(0, f);
			putc(255, f);
			putc(255, f);
		 }
	  }
   }
   else {
	  putc(255, f);
	  putc(255, f);
	  putc(255, f);

      for (c=2; c<255; c++) {
	 putc(0, f);
	 putc(255, f);
	 putc(255, f);
	  }
   }

   putc(255, f);
   putc(255, f);
   putc(0, f);
}


void Cttf2pcxDlg::SaveChars(FILE *f, BOOL antialias)
{
	int w, h, bw, bh, c;
	unsigned char *b;

	w = 0;
	h = 0;

	for (c=0; c<FONT_SIZE; c++) {
		if (chars[c].GetW() > w)
			w = chars[c].GetW();
		if (chars[c].GetH() > h)
			h = chars[c].GetH();
	}

	if (antialias) {
		w /= 8;
		h /= 8;
	}

	w = (w+16) & 0xFFF0;
	h = (h+16) & 0xFFF0;

	bw = 1+w*16;
	bh = 1+h*((FONT_SIZE+15)/16);
	b = (unsigned char *)malloc(bw*bh);
	memset(b, 255, bw*bh);

	int scale = (antialias ? 8 : 1);

	for (c=0; c<FONT_SIZE; c++) {
		int x = 1+w*(c&15);
		int y = 1+h*(c/16);


		for (int _y=0; _y<chars[c].GetH()/scale; _y++) {
			for (int _x=0; _x<chars[c].GetW()/scale; _x++) {
				int col;

				if (antialias) {
					col = 0;
					for (int xx=0; xx<8; xx++)
						for (int yy=0; yy<8; yy++)
							if (chars[c].GetPixel(_x*8+xx, _y*8+yy))
								col++;

					if (col)
						col = m_mincolor + (m_maxcolor - m_mincolor) * col / 64;
				}
				else {
					col = chars[c].GetPixel(_x, _y) ? 1 : 0;
				}

				b[(_y+y)*bw+_x+x] = col;
			}
		}
	}

	save_pcx(b, bw, bh, f, antialias, m_mincolor, m_maxcolor);
	free(b);
}


void Cttf2pcxDlg::OnExport() 
{
	if (UpdateData()) {
		CFileDialog dlg(FALSE, "pcx", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					    "PCX Files (*.pcx)|*.pcx|All Files (*.*)|*.*||");

		dlg.m_ofn.lpstrTitle = "Export Font";

		if (dlg.DoModal() == IDOK) {
			CWaitCursor wc;

			CFont *font = GetFont((m_outputmode > 0));

			for (int c=minchar; c<=maxchar; c++)
				chars[c-minchar].Get(font, c, (m_outputmode > 0));

			delete font;

			FILE *f = fopen(dlg.GetPathName(), "wb");
			if (!f) {
				AfxMessageBox("Error opening " + dlg.GetPathName());
				return;
			}

			SaveChars(f, (m_outputmode > 0));
			fclose(f);
		}
	}
}


void Cttf2pcxDlg::OnAntialiased() 
{
	m_maxcolortext.EnableWindow(TRUE);
	m_mincolortext.EnableWindow(TRUE); 
}


void Cttf2pcxDlg::OnMonochrome() 
{
	m_maxcolortext.EnableWindow(FALSE);
	m_mincolortext.EnableWindow(FALSE); 
}


void Cttf2pcxDlg::OnQuit() 
{
	OnCancel();
}


CFont *Cttf2pcxDlg::GetFont(BOOL big)
{
	CString size;
	m_sizelist.GetWindowText(size);

	CString fontname;
	m_fontlist.GetWindowText(fontname);

	CString style;
	m_stylelist.GetWindowText(style);

	BOOL bold = (style.Find("Bold") >= 0);
	BOOL italic = (style.Find("Italic") >= 0);

	LOGFONT lf = {
		atoi(size) * (big ? 80 : 10),
		0,
		0,
		0,
		bold ? 700 : 400,
		italic,
		FALSE,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
	};

	strcpy(lf.lfFaceName, fontname.GetBuffer(0));

	CFont *font = new CFont;
	font->CreatePointFontIndirect(&lf, NULL);

	return font;
}


void Cttf2pcxDlg::OnChange() 
{
	m_preview.Invalidate();
}

