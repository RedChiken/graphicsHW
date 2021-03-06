// Coordinate.cpp: 구현 파일
//

#include "stdafx.h"
#include "ViewingSystem.h"
#include "Coordinate.h"
#include "afxdialogex.h"


// Coordinate 대화 상자

IMPLEMENT_DYNAMIC(Coordinate, CDialogEx)

Coordinate::Coordinate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
}

Coordinate::~Coordinate()
{
}

void Coordinate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Coordinate, CDialogEx)
	ON_BN_CLICKED(IDOK, &Coordinate::OnBnClickedOk)
END_MESSAGE_MAP()


// Coordinate 메시지 처리기
void Coordinate::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_EDIT2, eye_x);
	GetDlgItemText(IDC_EDIT3, eye_y);
	GetDlgItemText(IDC_EDIT4, eye_z);
	GetDlgItemText(IDC_EDIT5, target_x);
	GetDlgItemText(IDC_EDIT6, target_y);
	GetDlgItemText(IDC_EDIT7, target_z);
	GetDlgItemText(IDC_EDIT8, vup_x);
	GetDlgItemText(IDC_EDIT9, vup_y);
	GetDlgItemText(IDC_EDIT10, vup_z);
	Vertex eye(atof(eye_x), atof(eye_y), atof(eye_z));
	Vertex lookat(atof(target_x), atof(target_y), atof(target_z));
	Vertex vup(atof(vup_x), atof(vup_y), atof(vup_z));
	document->MoveCoordination(eye, lookat, vup);
	CDialogEx::OnOK();
}
