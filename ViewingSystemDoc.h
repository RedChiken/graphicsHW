// ViewingSystemDoc.h : interface of the CViewingSystemDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWINGSYSTEMDOC_H__C9D36D04_6DB8_4D69_8C1A_1DD2C175A75B__INCLUDED_)
#define AFX_VIEWINGSYSTEMDOC_H__C9D36D04_6DB8_4D69_8C1A_1DD2C175A75B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Matrix.h"
#include <tuple>
#define		PARALLEL	0
#define		PERSPECTIVE	1

enum class Shading {
	FLAT, GOURAUD, PHONG
};

class CViewingSystemDoc : public CDocument
{
protected: // create from serialization only
	CViewingSystemDoc();
	DECLARE_DYNCREATE(CViewingSystemDoc)

// Attributes
public:
	Shading shadingType;
	Vertex *m_vertices;		// Object�� Vertex ������ �����ϴ� �迭
	Face *m_faces;			// Object�� Face ������ �����ϴ� �迭
	int m_numberOfVertices;	// Object�� �� Vertex ����
	int m_numberOfFaces;	// Object�� �� Face ����

	Vertex m_eye;			// ����
	Vertex m_lookAt;		// �ٶ󺸴°�
	Vertex m_up;			// ������ ����

	CRect win;

	CDC memdc;				// �׸��� �׸��� �� (DC)

	int m_viewingMode;		// Parallel, Perspective ������ ���� ����
	const int Z_LIMIT = 20000;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewingSystemDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	Vertex CenterVertex();						// ���� ������ �߽� vertex�� ���ϴ� �Լ�
	Vertex CrossProduct(Vertex a, Vertex b);	// �� Vertex�� ������ ���ϴ� �Լ�
	double DotProduct(Vertex a, Vertex b);		// �� Vertex�� ������ ���ϴ� �Լ�
	void DrawColor(Vertex *temp);
	bool Intersection(Vertex * temp, Face& gace, const int& x, const int& y, double& intp_z);
	void Flat(const std::tuple<int, int, int>& tuple);
	void Gouraud(const std::tuple<int, int, int>& tuple);
	void Phong(const std::tuple<int, int, int>& tuple);
	Vertex Normalization(Vertex vertex);		// Vertex�� ����ȭ ��Ű�� �Լ�
	Matrix InverseMatrix(Vertex& a, Vertex& b, Vertex& c);

	double Determinant(const Matrix & matrix);

	void Transformation(Matrix matrix);
	double perspectiveValue(double x, double center, double z);
	void MoveCoordination(Vertex& eye, Vertex& LookAt, Vertex& up);
	void Rendering();							// ���� ���� �׸��� �Լ�
	void FileOpen(CString filename);			// ������ Object������ �о���� �Լ�
	virtual ~CViewingSystemDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CViewingSystemDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWINGSYSTEMDOC_H__C9D36D04_6DB8_4D69_8C1A_1DD2C175A75B__INCLUDED_)
