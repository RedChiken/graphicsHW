#pragma once

#include "ViewingSystemDoc.h"
// RayTracing 대화 상자

class RayTracing : public CDialogEx
{
	DECLARE_DYNAMIC(RayTracing)

public:
	RayTracing(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~RayTracing();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit x;
	CEdit y;
	CEdit z;
	CSliderCtrl ambientSlide;
	CSliderCtrl diffuseSlide;
	CSliderCtrl SpecularSlide;
	CSliderCtrl TransparentSlide;
	CEdit ambientValue;
	CEdit diffuseValue;
	CEdit specularValue;
	CEdit transparentValue;
	CViewingSystemDoc* document;
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMReleasedcaptureAmbientSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureDiffuseSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSpecularSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureTransparentSlider(NMHDR *pNMHDR, LRESULT *pResult);
};
