// Matrix.h: interface for the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__E2559E10_6977_4DBC_B101_DCBA0C07C86A__INCLUDED_)
#define AFX_MATRIX_H__E2559E10_6977_4DBC_B101_DCBA0C07C86A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <math.h>
#include <random>
#include <time.h>
#endif // _MSC_VER > 1000

struct Vertex
{
	double x;
	double y;
	double z;
	double h;
	double normal_vec[3];
	int color[3];

	Vertex() : Vertex(0, 0, 0)
	{
	}
	
	Vertex(double v1, double v2, double v3, double vh = 1.0)
	{
		x = v1;
		y = v2;
		z = v3;
		h = vh;
		//TODO: check and write it
		
		color[0] = rand() % 256;
		color[1] = rand() % 256;
		color[2] = rand() % 256;
	}

	Vertex operator+(Vertex vertex)
	{
		return Vertex(x + vertex.x, y + vertex.y, z + vertex.z);
	}

	Vertex operator-(Vertex vertex)
	{
		return Vertex(x - vertex.x, y - vertex.y, z - vertex.z);
	}

	Vertex operator*(int number)
	{
		return Vertex(x * number, y * number, z * number);
	}

	Vertex operator*(double number)
	{
		return Vertex(x * number, y * number, z * number);
	}

	Vertex operator/(double number)
	{
		return Vertex(x / number, y / number, z / number);
	}
	
	double operator/(Vertex a) {
		return (x * x + y * y + z * z) / (a.x * a.x + a.y * a.y + a.z * a.z);
	}

	double size() {
		return sqrt(x * x + y * y + z * z);
	}

	Vertex colorVector(const int& i) {
		return Vertex(x, y, color[i]);
	}
};

struct Face
{
	int v1;
	int v2;
	int v3;
	double Norm[3];
	//need color;
	int rgb[3] = { rand() * 255, rand() * 255 , rand() * 255 };
	Face()
	{
	}

	Face(int f1, int f2, int f3)
	{
		v1 = f1;
		v2 = f2;
		v3 = f3;
	}

	Face(const Face& f) {
		v1 = f.v1;
		v2 = f.v2;
		v3 = f.v3;
	}
};

class Matrix  
{
public:
	Matrix();
	virtual ~Matrix();

	double m[16];

	void operator=(Matrix b);
	Matrix operator+(Matrix b);
	Matrix operator-(Matrix b);
	Matrix operator*(Matrix b);
	Vertex operator*(Vertex b);
	Matrix operator*(double d);
	Matrix operator/(const double d);

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//                             Matrix Class 사용법
//
//	Matrix A, B, C, D, temp;		// 기본 생성자로 4*4의 크기를 갖는 단위 행렬을 생성한다.
//	for (int i = 0; i < 16; i++)	// B, C 행렬에 원하는 값을 대입
//	{
//		B.m[i] = i;
//		C.m[i] = i * 2;
//	}
//
//	A = B * C;		// B와 C 행렬의 곱셈의 결과가 A에 저장된다.
//	A = B * C * D;	// B, C, D 행려의 곱셈의 결과가 A에 저장된다.
//
//	Vertex r, v;
//
//	// 4*4 행렬과 Vertex v의 곱셈의 결과가 Vertex r에 저장된다.
//	r = B * v;
//	
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
};

#endif // !defined(AFX_MATRIX_H__E2559E10_6977_4DBC_B101_DCBA0C07C86A__INCLUDED_)
