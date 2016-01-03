// OpenGLView.h : interface of the COpenGLView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLVIEW_H__DAC1B809_BA5C_4364_8C5D_DD2D4B184C4A__INCLUDED_)
#define AFX_OPENGLVIEW_H__DAC1B809_BA5C_4364_8C5D_DD2D4B184C4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Square.h"

class COpenGLView : public CView
{
public:
	HDC    m_hDC;//һ���豸�����ľ��������OpenGL�����ɵ����߳���ȷ�����豸HDC�ϻ��� 
	HGLRC  m_hRC;//OpenGL��Ⱦ�����ĵĹ�������Ϊ�����̵߳���Ⱦ�����ĵľ��

protected: // create from serialization only
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)

// Attributes
public:
	COpenGLDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	//��ǰѡ��ķ�������
	int i;//0-6,7����״
	int j;//0-3,4�ֱ仯

	int x;//��ǰ����
	int y;
	
	bool stop;//��ͣ/��ʼ

	bool isOld;//�Ƿ����ƶ����ķ���

	CSquare square;
	void SetOpenGLPixelFormat();
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COpenGLView)
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnGridNum();
	afx_msg void OnStop();
	afx_msg void OnAgain();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DisplayGrid();
	void DisplayScore();
};

#ifndef _DEBUG  // debug version in OpenGLView.cpp
inline COpenGLDoc* COpenGLView::GetDocument()
   { return (COpenGLDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGLVIEW_H__DAC1B809_BA5C_4364_8C5D_DD2D4B184C4A__INCLUDED_)
