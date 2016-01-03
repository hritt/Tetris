// Square.h: interface for the CSquare class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQUARE_H__D61E04C7_ED8D_4FDC_B8EC_B572536B32DD__INCLUDED_)
#define AFX_SQUARE_H__D61E04C7_ED8D_4FDC_B8EC_B572536B32DD__INCLUDED_

#include "Block.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSquare  
{
public:
	CBlock block[7][4];
	int width;
	int height;
	int m_grade;
	bool **m_square;
	
	CSquare();
	virtual ~CSquare();

	void ChangeSize(int width,int height);
	void DisplayAll();
	void Display(int x,int y);
	bool IsEdge(CBlock b,int x,int y);
	bool IsDown(CBlock b,int x,int y);
	void DeleteRow(int j);
	bool Fail();
	bool Success();
	
};

#endif // !defined(AFX_SQUARE_H__D61E04C7_ED8D_4FDC_B8EC_B572536B32DD__INCLUDED_)
