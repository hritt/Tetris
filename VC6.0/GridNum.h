#if !defined(AFX_GRIDNUM_H__A8FB1D46_B963_4D0B_B664_412813E1F796__INCLUDED_)
#define AFX_GRIDNUM_H__A8FB1D46_B963_4D0B_B664_412813E1F796__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GridNum.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGridNum dialog

class CGridNum : public CDialog
{
// Construction
public:
	CGridNum(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGridNum)
	enum { IDD = IDD_GRID_NUM };
	int		m_nHeight;
	int		m_nWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridNum)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGridNum)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDNUM_H__A8FB1D46_B963_4D0B_B664_412813E1F796__INCLUDED_)
