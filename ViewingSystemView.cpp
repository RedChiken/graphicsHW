// ViewingSystemView.cpp : implementation of the CViewingSystemView class
//

#include "stdafx.h"
#include "ViewingSystem.h"
#include <string>
#include <memory>

#include "ViewingSystemDoc.h"
#include "ViewingSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemView

IMPLEMENT_DYNCREATE(CViewingSystemView, CView)

BEGIN_MESSAGE_MAP(CViewingSystemView, CView)
	//{{AFX_MSG_MAP(CViewingSystemView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_PARALLEL, OnParallel)
	ON_COMMAND(ID_PERSPECTIVE, OnPerspective)
	//}}AFX_MSG_MAP
	// Standard printing commands
	//다른 이벤트들도 매크로 추가
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
//	ON_WM_ACTIVATE()
ON_WM_MOUSEMOVE()
ON_WM_MOUSEWHEEL()
ON_WM_LBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_COMMAND(ID_VIEWINGSYSTEM_COORDINATION, &CViewingSystemView::OnViewingsystemCoordination)
ON_COMMAND(ID_RENDERING_FLAT, &CViewingSystemView::OnRenderingFlat)
ON_COMMAND(ID_RENDERING_GOURAUD, &CViewingSystemView::OnRenderingGouraud)
ON_COMMAND(ID_RENDERING_PHONG, &CViewingSystemView::OnRenderingPhong)
ON_COMMAND(ID_RENDERING_LIGHTCOORDINATION, &CViewingSystemView::OnRenderingLightcoordination)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemView construction/destruction

CViewingSystemView::CViewingSystemView()
{
	// TODO: add construction code here

	m_initState = true;

	rButtonDownPoint = CPoint(0, 0);
	isRightButtonDown = false;
	this->coordinate = new Coordinate();
	this->raytracing = new RayTracing();
}

CViewingSystemView::~CViewingSystemView()
{
	delete(this->coordinate);
	delete(this->raytracing);
}

BOOL CViewingSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemView drawing

void CViewingSystemView::OnDraw(CDC* pDC)
{
	CViewingSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (m_initState)
	{
		GetClientRect(&pDoc->win);

		CBitmap bmp;
		bmp.CreateBitmap(pDoc->win.Width(), pDoc->win.Width(), 1, 0x20, NULL);
		pDoc->memdc.CreateCompatibleDC(pDC);
		pDoc->memdc.SelectObject(bmp);
		pDoc->memdc.ExtFloodFill(0, 0, RGB(255, 255, 255), FLOODFILLBORDER);

		m_initState = false;
	}
	pDC->BitBlt(pDoc->win.left, pDoc->win.top, pDoc->win.Width(), pDoc->win.Height(), &pDoc->memdc, 0, 0, SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemView printing

BOOL CViewingSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CViewingSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CViewingSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemView diagnostics

#ifdef _DEBUG
void CViewingSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CViewingSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CViewingSystemDoc* CViewingSystemView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CViewingSystemDoc)));
	return (CViewingSystemDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemView message handlers

void CViewingSystemView::OnFileOpen()
{
	// TODO: Add your command handler code here
	CViewingSystemDoc* pDoc = GetDocument();

	char szFilter[] = "Image (*.dat) |*.dat| All Files(*.*)|*.*||";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if (dlg.DoModal() == IDOK)
		pDoc->FileOpen(dlg.GetPathName());

	Invalidate();
}

void CViewingSystemView::OnParallel()
{
	GetDocument()->m_viewingMode = PARALLEL;
	GetDocument()->Rendering();

}

void CViewingSystemView::OnPerspective()
{
	GetDocument()->m_viewingMode = PERSPECTIVE;
	GetDocument()->Rendering();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// 시점 변경에 대한 구현이 필요
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


//void CViewingSystemView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
//{
//	CView::OnActivate(nState, pWndOther, bMinimized);
//
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//}


void CViewingSystemView::OnMouseMove(UINT nFlags, CPoint point)
{
	Matrix mat;
	
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON){
		//translate
		if ((nFlags & MK_CONTROL) == MK_CONTROL) {
			//x axis
			Matrix m;
			m.m[3] = point.x - this->buttonDownPoint.x;
			mat = mat * m;
		}
		if ((nFlags & MK_SHIFT) == MK_SHIFT) {
			//y axis
			Matrix m;
			m.m[7] = -point.y + this->buttonDownPoint.y;
			mat = mat * m;
		}
		if ((nFlags & MK_MBUTTON) == MK_MBUTTON) {
			//작동 확인 불가
			//z axis
			Matrix m;
			m.m[11] = -20;
			mat = mat * m;
		}
		if (((nFlags & MK_CONTROL) != MK_CONTROL) 
			&& ((nFlags & MK_MBUTTON) != MK_MBUTTON)
			&& ((nFlags & MK_SHIFT) != MK_SHIFT)) {
		//else{
			//all
			Matrix m;
			m.m[3] = point.x - this->buttonDownPoint.x;
			m.m[7] = -point.y + this->buttonDownPoint.y;
			//m.m[11] = -5;
			mat = mat * m;
		}
	}
	if ((nFlags & MK_RBUTTON) == MK_RBUTTON) {
		//rotation
		if ((nFlags & MK_CONTROL) == MK_CONTROL) {
			//x axis
			Matrix xaxis;
			double rad = (3.141592 * (point.x - this->buttonDownPoint.x)) 
				/ (GetDocument()->win.Width());
			xaxis.m[5] *= cos(rad);
			xaxis.m[6] = sin(rad);
			xaxis.m[9] = -sin(rad);
			xaxis.m[10] *= cos(rad);
			mat = mat * xaxis;
		}
		if ((nFlags & MK_SHIFT) == MK_SHIFT) {
			//이거 뭐 받아야 할까?
			//y axis
			Matrix yaxis;
			double rad = (3.141592 * (point.y - this->buttonDownPoint.y))
				/ (GetDocument()->win.Width());
			yaxis.m[0] *= cos(rad);
			yaxis.m[2] = sin(rad);
			yaxis.m[8] = -sin(rad);
			yaxis.m[10] *= cos(rad);
			mat = mat * yaxis;
		}
		if ((nFlags & MK_MBUTTON) == MK_MBUTTON) {
			//z axis
			Matrix zaxis;
			double zmove = ((point.y - this->buttonDownPoint.y)
				* (point.y - this->buttonDownPoint.y))
				+ ((point.x - this->buttonDownPoint.x)
				* (point.x - this->buttonDownPoint.x));
			double rad = (3.141592 * (zmove)) / (GetDocument()->win.Width());
			zaxis.m[0] *= cos(rad);
			zaxis.m[1] = sin(rad);
			zaxis.m[4] = -sin(rad);
			zaxis.m[5] *= cos(rad);
			mat = mat * zaxis;
		}
		if (((nFlags & MK_CONTROL) != MK_CONTROL)
			&& ((nFlags & MK_MBUTTON) != MK_MBUTTON)
			&& ((nFlags & MK_SHIFT) != MK_SHIFT)) {
			//all
			Matrix x, y, z;
			double xrad = (3.141592 * (point.x - this->buttonDownPoint.x))
				/ (GetDocument()->win.Width());
			double yrad = (3.141592 * (point.y - this->buttonDownPoint.y))
				/ (GetDocument()->win.Width());
			double zmove = ((point.y - this->buttonDownPoint.y)
				* (point.y - this->buttonDownPoint.y))
				+ ((point.x - this->buttonDownPoint.x)
					* (point.x - this->buttonDownPoint.x));
			double zrad = (3.141592 * (zmove)) / (GetDocument()->win.Width());
			x.m[5] *= cos(xrad);
			x.m[6] = sin(xrad);
			x.m[9] = -sin(xrad);
			x.m[10] *= cos(xrad);
			y.m[0] *= cos(yrad);
			y.m[2] = sin(yrad);
			y.m[8] = -sin(yrad);
			y.m[10] *= cos(yrad);
			z.m[0] *= cos(zrad);
			z.m[1] = sin(zrad);
			z.m[4] = -sin(zrad);
			z.m[5] *= cos(zrad);
			mat = mat * x;
			mat = mat * y;
			mat = mat * z;
		}
	}
	GetDocument()->Transformation(mat);
	this->buttonDownPoint = point;
	Invalidate(false);
	CView::OnMouseMove(nFlags, point);
}


BOOL CViewingSystemView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	Matrix mat;
	if ((nFlags & MK_CONTROL) == MK_CONTROL) {
		mat.m[0] = 1 + static_cast<double>(zDelta) / 1000;
	}
	if ((nFlags & MK_SHIFT) == MK_SHIFT) {
		mat.m[5] = 1 + static_cast<double>(zDelta) / 1000;
	}
	if ((nFlags & MK_MBUTTON) == MK_MBUTTON) {
		mat.m[10] = 1 + static_cast<double>(zDelta) / 1000;
	}
	if (((nFlags & MK_CONTROL) != MK_CONTROL)
		&& ((nFlags & MK_MBUTTON) != MK_MBUTTON)
		&& ((nFlags & MK_SHIFT) != MK_SHIFT)) {
		mat.m[0] = 1 + static_cast<double>(zDelta) / 1000;
		mat.m[5] = 1 + static_cast<double>(zDelta) / 1000;
		mat.m[10] = 1 + static_cast<double>(zDelta) / 1000;
	}
	GetDocument()->Transformation(mat);
	this->buttonDownPoint = pt;
	Invalidate(false);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CViewingSystemView::OnLButtonDown(UINT nFlags, CPoint point)
{
	this->buttonDownPoint = point;
	CView::OnLButtonDown(nFlags, point);
}


void CViewingSystemView::OnRButtonDown(UINT nFlags, CPoint point)
{
	this->buttonDownPoint = point;
	CView::OnRButtonDown(nFlags, point);
}


void CViewingSystemView::OnViewingsystemCoordination()
{
	coordinate->document = this->GetDocument();
	coordinate->DoModal();
}


void CViewingSystemView::OnRenderingFlat()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	GetDocument()->shadingType = Shading::FLAT;
	GetDocument()->Rendering();
}


void CViewingSystemView::OnRenderingGouraud()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	GetDocument()->shadingType = Shading::GOURAUD;
	GetDocument()->Rendering();
}


void CViewingSystemView::OnRenderingPhong()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	GetDocument()->shadingType = Shading::PHONG;
	GetDocument()->Rendering();
}


void CViewingSystemView::OnRenderingLightcoordination()
{
	raytracing->document = this->GetDocument();
	raytracing->DoModal();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
