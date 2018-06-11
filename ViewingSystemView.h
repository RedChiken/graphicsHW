// ViewingSystemView.h : interface of the CViewingSystemView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWINGSYSTEMVIEW_H__3E0F15B0_A739_42CE_8176_C5FDEED76166__INCLUDED_)
#define AFX_VIEWINGSYSTEMVIEW_H__3E0F15B0_A739_42CE_8176_C5FDEED76166__INCLUDED_

#include "ViewingSystemDoc.h"	// Added by ClassView
#include "Coordinate.h"
#include "RayTracing.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CViewingSystemView : public CView
{
protected: // create from serialization only
	CViewingSystemView();
	DECLARE_DYNCREATE(CViewingSystemView)

// Attributes
public:
	CViewingSystemDoc* GetDocument();
	Coordinate* coordinate;
	RayTracing* raytracing;
	bool m_initState;

	CPoint rButtonDownPoint;
	bool isRightButtonDown;

	CPoint buttonDownPoint;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewingSystemView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CViewingSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CViewingSystemView)
	afx_msg void OnFileOpen();
	afx_msg void OnParallel();
	afx_msg void OnPerspective();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnViewingsystemCoordination();
	afx_msg void OnRenderingFlat();
	afx_msg void OnRenderingGouraud();
	afx_msg void OnRenderingPhong();
	afx_msg void OnRenderingLightcoordination();
};

#ifndef _DEBUG  // debug version in ViewingSystemView.cpp
inline CViewingSystemDoc* CViewingSystemView::GetDocument()
   { return (CViewingSystemDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWINGSYSTEMVIEW_H__3E0F15B0_A739_42CE_8176_C5FDEED76166__INCLUDED_)
