// Block.h: interface for the CBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOCK_H__A581214D_2EB7_4EB2_A87B_3CCF8ECF3D14__INCLUDED_)
#define AFX_BLOCK_H__A581214D_2EB7_4EB2_A87B_3CCF8ECF3D14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBlock  
{
public:
	void BlockMake(int p1x,int p1y,int p2x,int p2y,int p3x,int p3y,int p4x,int p4y);
	CBlock();
	virtual ~CBlock();

	CPoint p1;
	CPoint p2;
	CPoint p3;
	CPoint p4;
};

#endif // !defined(AFX_BLOCK_H__A581214D_2EB7_4EB2_A87B_3CCF8ECF3D14__INCLUDED_)
