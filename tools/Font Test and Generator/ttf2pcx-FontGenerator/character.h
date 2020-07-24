// character.h : header file


class CCharacter : public CObject
{
public:
	CCharacter();
	~CCharacter();

	void CCharacter::Get(CFont *font, int c, BOOL antialias);

	int GetW() { return w; }
	int GetH() { return h; }
	BOOL GetPixel(int x, int y) { return (p[(y*bw)+x/8] & (0x80>>(x%8))) ? TRUE : FALSE; }

private:
	int w, h, bw;
	unsigned char *p;

	void Destroy();
};

