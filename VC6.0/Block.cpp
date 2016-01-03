// Block.cpp: implementation of the CBlock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenGL.h"
#include "Block.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBlock::CBlock()
{

}

CBlock::~CBlock()
{

}

void CBlock::BlockMake(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, int p4x, int p4y)
{
	p1.x=p1x;
	p1.y=p1y;
	p2.x=p2x;
	p2.y=p2y;
	p3.x=p3x;
	p3.y=p3y;
	p4.x=p4x;
	p4.y=p4y;
}
