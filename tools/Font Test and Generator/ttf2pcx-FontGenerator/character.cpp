// Character.cpp : implementation file
//

#include "stdafx.h"
#include "ttf2pcx.h"
#include "ttf2pcxdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CCharacter::CCharacter()
{
	w = h = bw = 0;
	p = NULL;
}



CCharacter::~CCharacter()
{	
	Destroy();
}



void CCharacter::Destroy()
{
	w = h = bw = 0;

	if (p) {
		free(p);
		p = NULL;
	}
}



void CCharacter::Get(CFont *font, int c, BOOL antialias)
{
	Destroy();

	CDC cdc;
	cdc.CreateCompatibleDC(NULL);

	CFont *oldfont = cdc.SelectObject(font);

	wchar_t s[2] = { c, 0 };

	CSize size;
	GetTextExtentPoint32W(cdc.m_hDC, s, 1, &size);

	if (antialias) {
		size.cx = (size.cx + 7) & 0xFFF8;
		size.cy = (size.cy + 7) & 0xFFF8;
	}

	CBitmap *bmp = new CBitmap;
	bmp->CreateCompatibleBitmap(&cdc, size.cx*2, size.cy);

	CBitmap *oldbmp = cdc.SelectObject(bmp);

	cdc.FillSolidRect(0, 0, size.cx*2, size.cy, 0);
	cdc.SetTextColor(RGB(255,255,255));
	TextOutW(cdc.m_hDC, 0, 0, s, 1);

	cdc.SelectObject(oldbmp);
	cdc.SelectObject(oldfont);

	BITMAP b;
	bmp->GetBitmap(&b);

	w = b.bmWidth;
	h = b.bmHeight;
	bw = b.bmWidthBytes;

	p = (unsigned char *)malloc(bw*h);
	bmp->GetBitmapBits(bw*h, p);

	delete bmp;

	if (c > ' ') {
		while (w > 1) {
			for (int y=0; y<h; y++)
				if (GetPixel(w-2, y))
					goto done;

			w--;
		}
	}

	done:
	if (antialias)
		w = (w + 7) & 0xFFF8;
}

