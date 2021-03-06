#pragma once

#include "Matrix.h"
#include "ViewingSystemDoc.h"
// Coordinate 대화 상자

class Coordinate : public CDialogEx
{
	DECLARE_DYNAMIC(Coordinate)

public:
	Coordinate(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Coordinate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString eye_x;
	CString eye_y;
	CString eye_z;
	CString target_x;
	CString target_y;
	CString target_z;
	CString vup_x;
	CString vup_y;
	CString vup_z;
	CViewingSystemDoc* document;
	afx_msg void OnBnClickedOk();
};
