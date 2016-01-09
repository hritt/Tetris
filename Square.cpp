// Square.cpp: implementation of the CSquare class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenGL.h"
#include "Square.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSquare::CSquare()
{
	width=8,height=15;//默认大小
	m_grade=0;
	int i,j;

	m_square=new bool *[width];
	for(i=0;i<width;i++)
		m_square[i]=new bool [height];
	for(i=0;i<width;i++)
		for(j=0;j<height;j++)
			m_square[i][j]=false;
	
	//这里要注意这些形状位子的定义！！
	block[0][0].BlockMake(0,0,1,0,0,1,1,1);
	block[0][1].BlockMake(0,0,1,0,0,1,1,1);
	block[0][2].BlockMake(0,0,1,0,0,1,1,1);/////■■
	block[0][3].BlockMake(0,0,1,0,0,1,1,1);/////■■

	block[1][0].BlockMake(0,0,1,0,2,0,3,0);/////■
	block[1][1].BlockMake(1,0,1,1,1,2,1,3);/////■
	block[1][2].BlockMake(0,0,1,0,2,0,3,0);/////■
	block[1][3].BlockMake(1,0,1,1,1,2,1,3);/////■

	block[2][0].BlockMake(0,0,1,0,2,0,0,1);
	block[2][1].BlockMake(1,0,2,0,2,1,2,2);
	block[2][2].BlockMake(2,0,0,1,1,1,2,1);/////■
	block[2][3].BlockMake(0,0,0,1,0,2,1,2);/////■■■

	block[3][0].BlockMake(0,0,1,0,2,0,2,1);
	block[3][1].BlockMake(2,0,2,1,1,2,2,2);
	block[3][2].BlockMake(0,0,0,1,1,1,2,1);/////    ■
	block[3][3].BlockMake(0,0,1,0,0,1,0,2);/////■■■

	block[4][0].BlockMake(0,0,1,0,2,0,1,1);
	block[4][1].BlockMake(2,0,1,1,2,1,2,2);
	block[4][2].BlockMake(1,0,0,1,1,1,2,1);/////  ■
	block[4][3].BlockMake(0,0,0,1,1,1,0,2);/////■■■

	block[5][0].BlockMake(0,0,1,0,1,1,2,1);
	block[5][1].BlockMake(1,0,0,1,1,1,0,2);
	block[5][2].BlockMake(0,0,1,0,1,1,2,1);/////  ■■
	block[5][3].BlockMake(1,0,0,1,1,1,0,2);/////■■
	
	block[6][0].BlockMake(1,0,2,0,0,1,1,1);
	block[6][1].BlockMake(0,0,0,1,1,1,1,2);
	block[6][2].BlockMake(1,0,2,0,0,1,1,1);/////■■
	block[6][3].BlockMake(0,0,0,1,1,1,1,2);/////  ■■
}

CSquare::~CSquare()
{
	int i;
	for(i=0;i<this->width;i++)
		delete [] m_square[i];
	delete [] m_square;
}

void CSquare::Display(int x,int y)
{
	glColor3f(0.6,0.7,0.8);

	glBegin(GL_POLYGON);
	glVertex2d((x+1)*2.0/(width+2)-1,(y+1)*2.0/(height+2)-1);
	glVertex2d((x+1)*2.0/(width+2)-1,(y+2)*2.0/(height+2)-1);
	glVertex2d((x+2)*2.0/(width+2)-1,(y+2)*2.0/(height+2)-1);
	glVertex2d((x+2)*2.0/(width+2)-1,(y+1)*2.0/(height+2)-1);
	glEnd();
}

void CSquare::DisplayAll()
{
	for(int i=0;i<width;i++)
		for(int j=0;j<height;j++)
			if(m_square[i][j]==TRUE)
				Display(i,j);
}

void CSquare::ChangeSize(int width,int height)
{
	int i,j;
	for(i=0;i<this->width;i++)
		delete [] m_square[i];
	delete [] m_square;

	this->width=width;
	this->height=height;

	m_square=new bool *[width];
	for(i=0;i<width;i++)
		m_square[i]=new bool [height];
	for(i=0;i<width;i++)
		for(j=0;j<height;j++)
			m_square[i][j]=false;
}

bool CSquare::Success()
{
	if(m_grade>=50)
		return true;
	else
		return false;
}

bool CSquare::Fail()
{
	for(int i=0;i<width;i++){
		if(m_square[i][height-4]==true)
			return true;
	}
	return false;
}

void CSquare::DeleteRow(int k)
{
	for(int j=k;j<=height-4;j++)
		for(int i=0;i<width;i++)
			m_square[i][j]=m_square[i][j+1];
}

//翻转时，是否出两边边界
bool CSquare::IsEdge(CBlock b,int x,int y)//b为变化后的四方块
{
	if(x+b.p1.x<0||x+b.p1.x>width-1||
	   x+b.p2.x<0||x+b.p2.x>width-1||
	   x+b.p3.x<0||x+b.p3.x>width-1||
	   x+b.p4.x<0||x+b.p4.x>width-1)
	   return true;
	return false;
}

//翻转时，底部已有方块会不会影响到
bool CSquare::IsDown(CBlock b,int x,int y)//b为变化后的四方块
{
	if(m_square[x+b.p1.x][y+b.p1.y]==true||
	   m_square[x+b.p2.x][y+b.p2.y]==true||
	   m_square[x+b.p3.x][y+b.p3.y]==true||
	   m_square[x+b.p4.x][y+b.p4.y]==true)
		return true;
	return false;
}

