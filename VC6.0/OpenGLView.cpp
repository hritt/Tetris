// OpenGLView.cpp : implementation of the COpenGLView class
//

#include "stdafx.h"
#include "OpenGL.h"

#include "OpenGLDoc.h"
#include "OpenGLView.h"

#include "GridNum.h"
#include "Block.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	//{{AFX_MSG_MAP(COpenGLView)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CHAR()
	ON_WM_TIMER()
	ON_COMMAND(ID_GRID_NUM, OnGridNum)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_AGAIN, OnAgain)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLView construction/destruction

COpenGLView::COpenGLView()
{
	// TODO: add construction code here
	srand( (unsigned)time( NULL ) );
	i=rand()%7;
	j=rand()%4;
	x=0;
	y=square.height-4;
	isOld=true;
	stop=false;
}

COpenGLView::~COpenGLView()
{
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style|=(WS_CLIPSIBLINGS|WS_CLIPCHILDREN);

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView drawing

void COpenGLView::OnDraw(CDC* pDC)
{
	COpenGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	glClearColor(0.6,0.9,0.8,0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	square.DisplayAll();//��ʾ����û�����ķ���

	//��ʾ��ǰ�ƶ����ķ���
	square.Display(x+square.block[i][j].p1.x,y+square.block[i][j].p1.y);
	square.Display(x+square.block[i][j].p2.x,y+square.block[i][j].p2.y);
	square.Display(x+square.block[i][j].p3.x,y+square.block[i][j].p3.y);
	square.Display(x+square.block[i][j].p4.x,y+square.block[i][j].p4.y);

	DisplayGrid();//��ʾ����

//	glFlush();// ǿ��OpenGL�����ͼ����
	SwapBuffers(m_hDC);// ˫�������Ľ���

	DisplayScore();//��ʾ�ɼ�
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView printing

BOOL COpenGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView diagnostics

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLDoc* COpenGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLDoc)));
	return (COpenGLDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenGLView message handlers

void COpenGLView::SetOpenGLPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = 
	{	
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // �汾��
		PFD_DRAW_TO_WINDOW   |          // ֧�ִ���
		PFD_SUPPORT_OPENGL |            // ֧��OpenGL
		PFD_DOUBLEBUFFER,               // ֧��˫����
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24λ��ɫ
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // ��alpha����
		0,                              // ����shiftλ
		0,                              // ��accumulation����
		0, 0, 0, 0,                     // ���Ե�accumλ
		32,                             // 32λzbuffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	CClientDC *pDC = new CClientDC(this);
	m_hDC = pDC->GetSafeHdc();  
	int pf = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, pf, &pfd); // �������ظ�ʽ
}

void COpenGLView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	SetOpenGLPixelFormat();  
	m_hRC = wglCreateContext( m_hDC ); 
	wglMakeCurrent( m_hDC, m_hRC ); // ����m_hDC��m_hRC
	SetTimer(1, 600, NULL);//��ʱ��ID;ʱ����,��λΪ����;�ص�����,�趨ΪNULL��Ҳ����ʹ��ϵͳĬ��

	// TODO: Add your specialized code here and/or call the base class
	
}

void COpenGLView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	wglDeleteContext(m_hRC);
	
}

void COpenGLView::OnSize(UINT nType, int cx, int cy) //��֤OpenGL�Ĵ�������ͼ��Сһ��
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	glViewport(0,0,cx-150,cy);
	
}

BOOL COpenGLView::OnEraseBkgnd(CDC* pDC) //����OnEraseBkgnd() ʹ����ͼ�ػ�ʱ�����ػ汳���������ػ�ʱ��ͼ��������˸
{
	// TODO: Add your message handler code here and/or call default
	
//	return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

void COpenGLView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar){
	case 'a'://����
		if(!( square.IsEdge(square.block[i][j],x-1,y)||square.IsDown(square.block[i][j],x-1,y) ))
			x--;
		break;
	case 'd'://����
	case 'D':
//	case char(25):
//	case VK_LEFT:
		if(!( square.IsEdge(square.block[i][j],x+1,y)||square.IsDown(square.block[i][j],x+1,y) ))
			x++;
		break;
	case 'w':{//����
		int newj=(j+1)%4;
		CBlock newb=square.block[i][newj];//case�ﲻ�����������������{}������
		if(!(square.IsEdge(newb,x,y)||square.IsDown(newb,x,y)))
			j=newj;
		break;}
	case 's'://���¼���һ��
		if(!(square.IsDown(square.block[i][j],x,y-1))&&y>0)
			y--;
		break;
	}
	Invalidate();
	
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void COpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) //ʵ���÷����������
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar){
	case VK_LEFT:
		OnChar('a',nRepCnt,nFlags);
		break;
	case VK_RIGHT:
		OnChar('d',nRepCnt,nFlags);
		break;
	case VK_UP:
		OnChar('w',nRepCnt,nFlags);
		break;
	case VK_DOWN:
		OnChar('s',nRepCnt,nFlags);
		break;
	}
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void COpenGLView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if(y<=0||square.IsDown(square.block[i][j],x,y-1)){//ֱ�����������еķ�����ߵ��ײ�
		isOld=false;
	}
	if(isOld){
		y--;
	}else{
		//��ԭ���ƶ����ķ���̶�
		square.m_square[x+square.block[i][j].p1.x][y+square.block[i][j].p1.y]=true;
		square.m_square[x+square.block[i][j].p2.x][y+square.block[i][j].p2.y]=true;
		square.m_square[x+square.block[i][j].p3.x][y+square.block[i][j].p3.y]=true;
		square.m_square[x+square.block[i][j].p4.x][y+square.block[i][j].p4.y]=true;
		
		//��һ����ʱ���� //�޸ķ���
		int r=0;//�˴�����������
		for(int k=y;k<y+4;k++){
			bool tmp=true;
			for(int m=0;m<square.width;m++){
				if(square.m_square[m][k]==false){
					tmp=false;
					break;
				}
			}
			if(tmp==true){
				square.DeleteRow(k);
				r++; k--; y--;
			}
		}
		switch(r){
			case 1:square.m_grade+=1;  break;
			case 2:square.m_grade+=3;  break;
			case 3:square.m_grade+=6;  break;
			case 4:square.m_grade+=10; break;
		}
				
		if(square.Fail()){
			KillTimer(1);
//			AfxMessageBox("ʤ���˱��ҳ��£�\nӢ������������!");
			MessageBox("ʤ���˱��ҳ��£�\nӢ������������!","���",MB_OK);
			return ;
		}
		if(square.Success()){
			KillTimer(1);
			MessageBox("Success,you hava eliminated 50 rows!","��ϲ",MB_OK);
			return ;
		}

		//�����µ��ƶ��ķ���
		srand( (unsigned)time( NULL ) );
		i=rand()%7;
		j=rand()%4;
		x=0;
		y=square.height-4;
		isOld=true;
	}

	Invalidate();

	CView::OnTimer(nIDEvent);
}

void COpenGLView::DisplayScore()
{
	CString s;
	s.Format("made by hritt");
	TextOut(m_hDC,310,40,s,s.GetLength());
	s.Format("�÷�:%d",square.m_grade);
	TextOut(m_hDC,330,80,s,s.GetLength());
}

void COpenGLView::DisplayGrid()
{
	glColor3f(0.3,0.4,0.5);

	int i,j;
	for(i=1;i<square.width+2;i++){//����8��
		glBegin(GL_LINES);
		glVertex2f(i*2.0/(square.width+2)-1, 2.0/(square.height+2)-1 );
		glVertex2f(i*2.0/(square.width+2)-1, 1-2.0/(square.height+2) );
		glEnd();
	}
	for(j=1;j<square.height+2;j++){//����15��
		glBegin(GL_LINES);
		glVertex2f(2.0/(square.width+2)-1, j*2.0/(square.height+2)-1);
		glVertex2f(1-2.0/(square.width+2), j*2.0/(square.height+2)-1);
		glEnd();
	}
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex2f(2.0/(square.width+2)-1, (square.height-3)*2.0/(square.height+2)-1);
	glVertex2f(1-2.0/(square.width+2), (square.height-3)*2.0/(square.height+2)-1);
	glEnd();
}

void COpenGLView::OnGridNum() 
{
	OnStop();
	CGridNum dlg;
	if(IDOK==dlg.DoModal()){
		if(dlg.m_nHeight<=0||dlg.m_nWidth<=0||dlg.m_nHeight>50||dlg.m_nWidth>50){
			MessageBox("�����ĸ������ɲ���Ŷ!");
			OnStop();
			return;
		}
		square.m_grade=0;
		square.ChangeSize(dlg.m_nWidth,dlg.m_nHeight);
	}
	OnStop();
}

void COpenGLView::OnStop() 
{
	// TODO: Add your command handler code here
	if(false==stop){
		KillTimer(1);
		stop=true;
	}
	else{
		SetTimer(1, 600, NULL);
		stop=false;
	}
}

void COpenGLView::OnAgain() 
{
	// TODO: Add your command handler code here	
	square.m_grade=0;
	square.ChangeSize(square.width,square.height);
	isOld=true;
//	stop=false;
	
	srand( (unsigned)time( NULL ) );
	i=rand()%7;
	j=rand()%4;
	x=0;
	y=square.height-3;
	
	SetTimer(1, 600, NULL);
}


