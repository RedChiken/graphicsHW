// RayTracing.cpp: 구현 파일
//

#include "stdafx.h"
#include "ViewingSystem.h"
#include "RayTracing.h"
#include "afxdialogex.h"


// RayTracing 대화 상자

IMPLEMENT_DYNAMIC(RayTracing, CDialogEx)

RayTracing::RayTracing(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

RayTracing::~RayTracing()
{
}

void RayTracing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, x);
	DDX_Control(pDX, IDC_EDIT2, y);
	DDX_Control(pDX, IDC_EDIT3, z);
	DDX_Control(pDX, IDC_SLIDER1, ambientSlide);
	DDX_Control(pDX, IDC_SLIDER2, diffuseSlide);
	DDX_Control(pDX, IDC_SLIDER3, SpecularSlide);
	DDX_Control(pDX, IDC_SLIDER4, TransparentSlide);
	DDX_Control(pDX, IDC_EDIT4, ambientValue);
	DDX_Control(pDX, IDC_EDIT5, diffuseValue);
	DDX_Control(pDX, IDC_EDIT6, specularValue);
	DDX_Control(pDX, IDC_EDIT7, transparentValue);
}


BEGIN_MESSAGE_MAP(RayTracing, CDialogEx)
	ON_BN_CLICKED(IDOK, &RayTracing::OnBnClickedOk)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &RayTracing::OnNMReleasedcaptureAmbientSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, &RayTracing::OnNMReleasedcaptureDiffuseSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER3, &RayTracing::OnNMReleasedcaptureSpecularSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER4, &RayTracing::OnNMReleasedcaptureTransparentSlider)
END_MESSAGE_MAP()


// RayTracing 메시지 처리기


void RayTracing::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void RayTracing::OnNMReleasedcaptureAmbientSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void RayTracing::OnNMReleasedcaptureDiffuseSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void RayTracing::OnNMReleasedcaptureSpecularSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void RayTracing::OnNMReleasedcaptureTransparentSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

//TODO: need to get event until moving theme