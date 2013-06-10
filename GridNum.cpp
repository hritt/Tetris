// GridNum.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "GridNum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridNum dialog


CGridNum::CGridNum(CWnd* pParent /*=NULL*/)
	: CDialog(CGridNum::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGridNum)
	m_nHeight = 15;
	m_nWidth = 8;
	//}}AFX_DATA_INIT
}


void CGridNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridNum)
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nHeight);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGridNum, CDialog)
	//{{AFX_MSG_MAP(CGridNum)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridNum message handlers
