// ViewingSystemDoc.cpp : implementation of the CViewingSystemDoc class
//

#include "stdafx.h"
#include "ViewingSystem.h"
#include <math.h>
#include <algorithm>
#include <tuple>
#include <vector>
#include <memory>
#include <fstream>		// Visual studio 2003, 2005
using namespace std;		// Visual studio 2003, 2005

#include <cmath>

#include "ViewingSystemDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CViewingSystemDoc

IMPLEMENT_DYNCREATE(CViewingSystemDoc, CDocument)

BEGIN_MESSAGE_MAP(CViewingSystemDoc, CDocument)
	//{{AFX_MSG_MAP(CViewingSystemDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemDoc construction/destruction

CViewingSystemDoc::CViewingSystemDoc()
{
	// TODO: add one-time construction code here
	m_numberOfVertices = 4;
	m_numberOfFaces = 0;
	shadingType = Shading::FLAT;
	m_vertices = new Vertex[m_numberOfVertices];
	m_faces = 0;

	m_viewingMode = PARALLEL;
	
	m_vertices[0] = Vertex(0, 0, 0);
	m_vertices[1] = Vertex(300, 0, 0);
	m_vertices[2] = Vertex(0, 300, 0);
	m_vertices[3] = Vertex(0, 0, 300);
	
}

CViewingSystemDoc::~CViewingSystemDoc()
{
	delete[] m_vertices;
	delete[] m_faces;
}

BOOL CViewingSystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CViewingSystemDoc serialization

void CViewingSystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemDoc diagnostics

#ifdef _DEBUG
void CViewingSystemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CViewingSystemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemDoc commands

void CViewingSystemDoc::FileOpen(CString filename)
{

	// View로부터 넘어온 파일명으로부터 파일을 연다.
	ifstream fin(filename.AllocSysString());	// Visual studio 2005

	CString check, dump;
	int numberOfVertices, numberOfFaces;

	// 첫 줄의 세 단어를 가져온다.
	// dat파일을 메모장으로 열어 저장된 정보를 확인하기 바람.
	fin >> check.GetBuffer(100) >> dump.GetBuffer(100) >> numberOfVertices;

	if (check == "VERTEX")
	{
		m_numberOfVertices = numberOfVertices + 4;

		// 얻어온 Vertex의 갯수로 배열을 생성
		if (m_vertices == 0){
			m_vertices = new Vertex[numberOfVertices + 4];
		}
		else 
		{
			delete[] m_vertices;
			m_vertices = new Vertex[numberOfVertices + 4];
		}

		double num1, num2, num3;
		// 이어지는 Vertex 정보를 배열에 저장
		for (int i = 0; i < numberOfVertices; i++)
		{
			fin >> num1 >> num2 >> num3;

			m_vertices[i] = Vertex(num1, num2, num3);
		}
		m_vertices[numberOfVertices] = Vertex(0, 0, 0);
		m_vertices[numberOfVertices + 1] = Vertex(300, 0, 0);
		m_vertices[numberOfVertices + 2] = Vertex(0, 300, 0);
		m_vertices[numberOfVertices + 3] = Vertex(0, 0, 300);

		fin >> check.GetBuffer(100) >> dump.GetBuffer(100) >> numberOfFaces;

		if (check == "FACE")
		{
			m_numberOfFaces = numberOfFaces;

			// 얻어온 Face의 갯수로 배열을 생성
			if (m_faces == 0)
				m_faces = new Face[numberOfFaces];
			else 
			{
				delete[] m_faces;
				m_faces = new Face[numberOfFaces];
			}

			int num4, num5, num6;
			// 이어지는 Face 정보를 배열에 저장
			for (int i = 0; i < numberOfFaces; i++)		// Visual studio 6.0, 2003
			//for (int i = 0; i < numberOfFaces; i++)	// Visual studio 2005
			{
				fin >> num4 >> num5 >> num6;

				m_faces[i] = Face(num4, num5, num6);
			}

			// 현재 모델을 그림. default rendering mode = PARALLEL
			Rendering();
		}
	}
}

void CViewingSystemDoc::Transformation(Matrix matrix)
{
	Vertex center = this->CenterVertex();
	for (int i = 0; i < this->m_numberOfVertices; i++) {
		this->m_vertices[i] = (matrix * (this->m_vertices[i] - center)) + center;
	}
	Rendering();
}

double CViewingSystemDoc::perspectiveValue(double x, double center, double z) {
	if (x < center) {
		return z / 25;
	}
	else {
		return -1 * z / 25;
	}
}

void CViewingSystemDoc::Rendering()
{
	// DC를 하얀색으로 지우는 함수
	memdc.FillRect(win, &CBrush(RGB(255, 255, 255)));

	// 렌더링 모드에 따른 구현이 필요함

	CPoint center = CPoint(win.Width() / 2, win.Height() / 2);

	CPoint drawingPoint[4];
	Vertex *temp;
	if (m_viewingMode == PARALLEL)
	{
		for (int i = 0; i < m_numberOfFaces; i++)
		{
			drawingPoint[0] = CPoint(int(m_vertices[m_faces[i].v1].x + center.x), int(-1 * m_vertices[m_faces[i].v1].y + center.y));
			drawingPoint[1] = CPoint(int(m_vertices[m_faces[i].v2].x + center.x), int(-1 * m_vertices[m_faces[i].v2].y + center.y));
			drawingPoint[2] = CPoint(int(m_vertices[m_faces[i].v3].x + center.x), int(-1 * m_vertices[m_faces[i].v3].y + center.y));
			drawingPoint[3] = CPoint(int(m_vertices[m_faces[i].v1].x + center.x), int(-1 * m_vertices[m_faces[i].v1].y + center.y));
			memdc.Polyline(drawingPoint, 4);
		}
		temp = new Vertex[m_numberOfVertices - 4];
		for (int i = 0; i < m_numberOfVertices - 4; i++) {
			temp[i] = m_vertices[i] + Vertex(center.x, center.y, 0);
		}
		DrawColor(temp);
		delete[] temp;
	}
	else if (m_viewingMode == PERSPECTIVE)
	{
		for (int i = 0; i < m_numberOfFaces; i++)
		{
			drawingPoint[0] = CPoint(int(m_vertices[m_faces[i].v1].x + center.x + perspectiveValue(m_vertices[m_faces[i].v1].x, CenterVertex().x, m_vertices[m_faces[i].v1].z)), int(-m_vertices[m_faces[i].v1].y + center.y - perspectiveValue(m_vertices[m_faces[i].v1].y, CenterVertex().y, m_vertices[m_faces[i].v1].z)));
			drawingPoint[1] = CPoint(int(m_vertices[m_faces[i].v2].x + center.x + perspectiveValue(m_vertices[m_faces[i].v2].x, CenterVertex().x, m_vertices[m_faces[i].v2].z)), int(-m_vertices[m_faces[i].v2].y + center.y - perspectiveValue(m_vertices[m_faces[i].v2].y, CenterVertex().y, m_vertices[m_faces[i].v2].z)));
			drawingPoint[2] = CPoint(int(m_vertices[m_faces[i].v3].x + center.x + perspectiveValue(m_vertices[m_faces[i].v3].x, CenterVertex().x, m_vertices[m_faces[i].v3].z)), int(-m_vertices[m_faces[i].v3].y + center.y - perspectiveValue(m_vertices[m_faces[i].v3].y, CenterVertex().y, m_vertices[m_faces[i].v3].z)));
			drawingPoint[3] = CPoint(int(m_vertices[m_faces[i].v1].x + center.x + perspectiveValue(m_vertices[m_faces[i].v1].x, CenterVertex().x, m_vertices[m_faces[i].v1].z)), int(-m_vertices[m_faces[i].v1].y + center.y - perspectiveValue(m_vertices[m_faces[i].v1].y, CenterVertex().y, m_vertices[m_faces[i].v1].z)));
			memdc.Polyline(drawingPoint, 4);
		}
	}

	memdc.MoveTo(int(m_vertices[m_numberOfVertices - 4].x + center.x), int(-1 * m_vertices[m_numberOfVertices - 4].y + center.y));
	memdc.LineTo(int(m_vertices[m_numberOfVertices - 3].x + center.x), int(-1 * m_vertices[m_numberOfVertices - 3].y + center.y));
	memdc.TextOutA(int(m_vertices[m_numberOfVertices - 3].x + center.x), int(-1 * m_vertices[m_numberOfVertices - 3].y + center.y - 10), _T("x"));
	memdc.MoveTo(int(m_vertices[m_numberOfVertices - 4].x + center.x), int(-1 * m_vertices[m_numberOfVertices - 4].y + center.y));
	memdc.LineTo(int(m_vertices[m_numberOfVertices - 2].x + center.x), int(-1 * m_vertices[m_numberOfVertices - 2].y + center.y));
	memdc.TextOutA(int(m_vertices[m_numberOfVertices - 2].x + center.x), int(-1 * m_vertices[m_numberOfVertices - 2].y + center.y - 10), _T("y"));
	memdc.MoveTo(int(m_vertices[m_numberOfVertices - 4].x + center.x), int(-1 * m_vertices[m_numberOfVertices - 4].y + center.y));
	memdc.LineTo(int(m_vertices[m_numberOfVertices - 1].x + center.x), int(-1 * m_vertices[m_numberOfVertices - 1].y + center.y));
	memdc.TextOutA(int(m_vertices[m_numberOfVertices - 1].x + center.x), int(-1 * m_vertices[m_numberOfVertices - 1].y + center.y + 10), _T("z"));
}

Vertex CViewingSystemDoc::Normalization(const Vertex vertex)
{
	double dis = sqrt(pow(vertex.x, 2.0) + pow(vertex.y, 2.0) + pow(vertex.z, 2.0));

	return Vertex(vertex.x/dis, vertex.y/dis, vertex.z/dis);
}

double CViewingSystemDoc::DotProduct(Vertex a, Vertex b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vertex CViewingSystemDoc::CenterVertex()
{
	Vertex ret(0, 0, 0);
	for (int i = 0; i < m_numberOfVertices - 4; i++) {
		ret = ret + (m_vertices[i] / (m_numberOfVertices - 4));
	}
	return ret;
}

Vertex CViewingSystemDoc::CrossProduct(Vertex a, Vertex b)
{
	return Vertex(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

void CViewingSystemDoc::MoveCoordination(Vertex& eye, Vertex& LookAt, Vertex& vup)
{
	Vertex vrp = eye;
	Vertex vpn = LookAt - eye;
	Vertex norm_vup = Normalization(Normalization(vup) - Normalization(vpn) * DotProduct(Normalization(vpn), Normalization(vup)));
	Vertex center = this->CenterVertex();
	Matrix Inv = this->InverseMatrix(vrp, norm_vup, Normalization(vpn)) * (3 * center.size() / vpn.size());
	this->Transformation(Inv);
}

Matrix CViewingSystemDoc::InverseMatrix(Vertex & a, Vertex & b, Vertex & c)
{
	Matrix mat, inv;
	Vertex Norm_a = Normalization(CrossProduct(c, b)),
		Norm_b = Normalization(b), 
		Norm_c = Normalization(c);
	double score_a = a / Norm_a, score_b = b / Norm_b, score_c = c / Norm_c;
	mat.m[0] = Norm_a.x;
	mat.m[1] = Norm_a.y;
	mat.m[2] = Norm_a.z;
	mat.m[3] = Norm_a.h;
	mat.m[4] = Norm_b.x;
	mat.m[5] = Norm_b.y;
	mat.m[6] = Norm_b.z;
	mat.m[7] = Norm_b.h;
	mat.m[8] = Norm_c.x;
	mat.m[9] = Norm_c.y;
	mat.m[10] = Norm_c.z;
	mat.m[11] = Norm_c.h;
	double det = Determinant(mat);
	inv.m[0] = mat.m[5] * (mat.m[10] * mat.m[15] - mat.m[11] * mat.m[14])
		- mat.m[6] * (mat.m[9] * mat.m[15] - mat.m[11] * mat.m[13])
		+ mat.m[7] * (mat.m[9] * mat.m[14] - mat.m[10] * mat.m[13]);
	inv.m[1] = mat.m[4] * (mat.m[10] * mat.m[15] - mat.m[11] * mat.m[14])
		- mat.m[6] * (mat.m[8] * mat.m[15] - mat.m[11] * mat.m[12])
		+ mat.m[7] * (mat.m[8] * mat.m[14] - mat.m[10] * mat.m[12]);
	inv.m[2] = mat.m[4] * (mat.m[9] * mat.m[15] - mat.m[11] * mat.m[13])
		- mat.m[5] * (mat.m[8] * mat.m[15] - mat.m[11] * mat.m[12])
		+ mat.m[7] * (mat.m[8] * mat.m[13] - mat.m[9] * mat.m[12]);
	inv.m[3] = mat.m[4] * (mat.m[9] * mat.m[14] - mat.m[10] * mat.m[13])
		- mat.m[5] * (mat.m[8] * mat.m[14] - mat.m[10] * mat.m[12])
		+ mat.m[6] * (mat.m[8] * mat.m[13] - mat.m[9] * mat.m[12]);
	inv.m[4] = mat.m[1] * (mat.m[10] * mat.m[15] - mat.m[11] * mat.m[14])
		- mat.m[2] * (mat.m[9] * mat.m[15] - mat.m[11] * mat.m[13])
		+ mat.m[3] * (mat.m[9] * mat.m[14] - mat.m[10] * mat.m[13]);
	inv.m[5] = mat.m[0] * (mat.m[10] * mat.m[15] - mat.m[11] * mat.m[14])
		- mat.m[2] * (mat.m[8] * mat.m[15] - mat.m[11] * mat.m[12])
		+ mat.m[3] * (mat.m[8] * mat.m[14] - mat.m[10] * mat.m[12]);
	inv.m[6] = mat.m[0] * (mat.m[9] * mat.m[15] - mat.m[11] * mat.m[13])
		- mat.m[1] * (mat.m[8] * mat.m[15] - mat.m[11] * mat.m[12])
		+ mat.m[3] * (mat.m[8] * mat.m[13] - mat.m[9] * mat.m[12]);
	inv.m[7] = mat.m[0] * (mat.m[9] * mat.m[14] - mat.m[10] * mat.m[13])
		- mat.m[1] * (mat.m[8] * mat.m[14] - mat.m[10] * mat.m[12])
		+ mat.m[2] * (mat.m[8] * mat.m[13] - mat.m[9] * mat.m[12]);
	inv.m[8] = mat.m[1] * (mat.m[6] * mat.m[15] - mat.m[7] * mat.m[14])
		- mat.m[2] * (mat.m[5] * mat.m[15] - mat.m[7] * mat.m[13])
		+ mat.m[3] * (mat.m[5] * mat.m[14] - mat.m[6] * mat.m[13]);
	inv.m[9] = mat.m[0] * (mat.m[6] * mat.m[15] - mat.m[7] * mat.m[14])
		- mat.m[2] * (mat.m[4] * mat.m[15] - mat.m[7] * mat.m[12])
		+ mat.m[3] * (mat.m[4] * mat.m[14] - mat.m[6] * mat.m[12]);
	inv.m[10] = mat.m[0] * (mat.m[5] * mat.m[15] - mat.m[7] * mat.m[13])
		- mat.m[1] * (mat.m[4] * mat.m[15] - mat.m[7] * mat.m[12])
		+ mat.m[3] * (mat.m[4] * mat.m[13] - mat.m[5] * mat.m[12]);
	inv.m[11] = mat.m[0] * (mat.m[5] * mat.m[14] - mat.m[6] * mat.m[13])
		- mat.m[1] * (mat.m[4] * mat.m[14] - mat.m[6] * mat.m[12])
		+ mat.m[2] * (mat.m[4] * mat.m[13] - mat.m[5] * mat.m[12]);
	inv.m[12] = mat.m[1] * (mat.m[6] * mat.m[11] - mat.m[7] * mat.m[10])
		- mat.m[2] * (mat.m[5] * mat.m[11] - mat.m[7] * mat.m[9])
		+ mat.m[3] * (mat.m[5] * mat.m[10] - mat.m[6] * mat.m[9]);
	inv.m[13] = mat.m[0] * (mat.m[6] * mat.m[11] - mat.m[7] * mat.m[10])
		- mat.m[2] * (mat.m[4] * mat.m[11] - mat.m[7] * mat.m[8])
		+ mat.m[3] * (mat.m[4] * mat.m[10] - mat.m[6] * mat.m[8]);
	inv.m[14] = mat.m[0] * (mat.m[5] * mat.m[11] - mat.m[7] * mat.m[9])
		- mat.m[1] * (mat.m[4] * mat.m[7] - mat.m[7] * mat.m[8])
		+ mat.m[3] * (mat.m[4] * mat.m[9] - mat.m[5] * mat.m[8]);
	inv.m[15] = mat.m[0] * (mat.m[5] * mat.m[10] - mat.m[6] * mat.m[9])
		- mat.m[1] * (mat.m[4] * mat.m[10] - mat.m[6] * mat.m[8])
		+ mat.m[2] * (mat.m[4] * mat.m[9] - mat.m[5] * mat.m[8]);
	inv = inv / det;
	return inv;
}

double CViewingSystemDoc::Determinant(const Matrix& matrix) {
	return matrix.m[0] * (matrix.m[5] * (matrix.m[10] * matrix.m[15] - matrix.m[11] * matrix.m[14])
					- matrix.m[6] * (matrix.m[9] * matrix.m[15] - matrix.m[11] * matrix.m[13])
					+ matrix.m[7] * (matrix.m[9] * matrix.m[14] - matrix.m[10] * matrix.m[13])) 
		- matrix.m[1] * (matrix.m[4] * (matrix.m[10] * matrix.m[15] - matrix.m[11] * matrix.m[14])
						- matrix.m[6] * (matrix.m[8] * matrix.m[15] - matrix.m[11] * matrix.m[12])
						+ matrix.m[7] * (matrix.m[8] * matrix.m[14] - matrix.m[10] * matrix.m[12]))
		+ matrix.m[2] * (matrix.m[4] * (matrix.m[9] * matrix.m[15] - matrix.m[11] * matrix.m[13])
						- matrix.m[5] * (matrix.m[8] * matrix.m[15] - matrix.m[11] * matrix.m[12])
						+ matrix.m[7] * (matrix.m[8] * matrix.m[13] - matrix.m[9] * matrix.m[12]))
		- matrix.m[3] * (matrix.m[4] * (matrix.m[9] * matrix.m[14] - matrix.m[10] * matrix.m[13])
						- matrix.m[5] * (matrix.m[8] * matrix.m[14] - matrix.m[10] * matrix.m[12])
						+ matrix.m[6] * (matrix.m[8] * matrix.m[13] - matrix.m[9] * matrix.m[12]));
}

void CViewingSystemDoc::DrawColor(Vertex *temp) {
	int x_max = 0, x_min = win.Width(), y_max = 0, y_min = win.Height();
	for (int i = 0; i < m_numberOfVertices - 4; i++) {
		if (temp[i].x > x_max) {
			x_max = static_cast<int>(temp[i].x + 1);
		}
		if (temp[i].x < x_min) {
			x_min = static_cast<int>(temp[i].x);
		}
		if (temp[i].y > y_max) {
			y_max = static_cast<int>(temp[i].y + 1);
		}
		if (temp[i].y < y_min) {
			y_min = static_cast<int>(temp[i].y);
		}
	}
	vector<std::tuple<int, int, int>> pixel_info;
	for (int i = x_min; i < x_max; i++) {
		for (int j = y_min; j < y_max; j++) {
			double max_z = DBL_MAX;
			int max_z_index = -1;
			for (int k = 0; k < m_numberOfFaces; k++) {
				double intp_z = DBL_MAX;
				if (Intersection(temp, m_faces[k], i, j, intp_z)) {
					if (intp_z < max_z) {
						max_z = intp_z;
						max_z_index = k;
					}
				}
			}
			
			if (max_z_index > -1) {
				pixel_info.push_back(make_tuple(i, j, max_z_index));
			}
		}
	}
	

	switch (this->shadingType) {
	case Shading::FLAT:
		for (const auto& tuple : pixel_info) {
			Flat(tuple);
		}
		break;
	case Shading::GOURAUD:
		for (const auto& tuple : pixel_info) {
			Gouraud(tuple);
		}
		break;
	case Shading::PHONG:

		break;
	}
}

bool CViewingSystemDoc::Intersection(Vertex * temp, Face& face, const int& x, const int& y, double& intp_z) {
	double a = 0, b = 0;
	Vertex vec1 = temp[face.v2] - temp[face.v1];
	Vertex vec2 = temp[face.v3] - temp[face.v1];
	Vertex p = Vertex(x, y, 0) - temp[face.v1];
	a = (p.x * vec2.y - p.y * vec2.x) / (vec1.x * vec2.y - vec2.x * vec1.y);
	b = (p.x * vec1.y - p.y * vec1.x) / (vec2.x * vec1.y - vec1.x * vec2.y);
	if (((a >= 0) && (a <= 1)) && ((b >= 0) && (b <= 1)) && (((a + b) >= 0) && ((a + b) <= 1))) {
		Vertex norm = Normalization(CrossProduct(vec1, vec2));
		face.Norm = norm;
		if ((norm.z < 0.00000001) && (norm.z > -0.00000001)) {
			return false;
		}
		intp_z = temp[face.v1].z
			- ((x - temp[face.v1].x) * norm.x
				+ (y - temp[face.v1].y) * norm.y) / norm.z;
		return true;
	}
	else {
		return false;
	}
}

void CViewingSystemDoc::Flat(const tuple<int, int, int>& tuple)
{
	int x = std::get<0>(tuple);
	int y = std::get<1>(tuple);
	int face_index = std::get<2>(tuple);
	Vertex ray(win.Width() / 2 - x, win.Height() / 2 - y, -500);
	double angle = DotProduct(Normalization(m_faces[face_index].Norm), Normalization(ray));
	//if(memdc.GetPixel(x, win.Height() - y) == RGB(255, 255, 255))
	memdc.SetPixel(x, win.Height() - y, m_faces[face_index].getRealColor(angle));
}

void CViewingSystemDoc::Gouraud(const tuple<int, int, int>& tuple)
{
	int x = std::get<0>(tuple);
	int y = std::get<1>(tuple);
	int face_index = std::get<2>(tuple);
	Vertex vertex[3];
	int color[3];
	
}

void CViewingSystemDoc::Phong(const tuple<int, int, int>& tuple)
{
}
