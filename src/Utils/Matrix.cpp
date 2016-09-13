/*
 * Matrix1.cpp
 *
 *  Created on: Jul 11, 2014
 *      Author: logan
 */

#include <algorithm>
#include <cstddef>
#include <iostream>
#include "Matrix.h"

Matrix::Matrix(int iRows, int iCols) {
	// TODO Auto-generated constructor stub
	rows = iRows;
	cols = iCols;
	mat = new double *[rows];
	for (int i = 0; i < rows; i++)
		mat[i] = new double[cols];
	//mat = new double[rows][cols]();

}

Matrix::~Matrix() {
	// TODO Auto-generated destructor stub
}

bool Matrix::IsSquare()
{
	return (rows == cols);
}

double &Matrix::operator ()(int iRow, int iCol)
{
	return mat[iRow][iCol];
}


//C# TO C++ CONVERTER TODO TASK: You cannot specify separate 'set' logic for indexers in native C++:
//void Matrix::setdefault(const int &iRow, int iCol, double value)
//{
//	mat[iRow, iCol] = value;
//}

Matrix *Matrix::GetCol(int k)
{
	Matrix *m = new Matrix(rows, 1);
	for (int i = 0; i < rows; i++)
	{
		(*m)(i,0) = mat[i][k];
	}
	return m;
}

void Matrix::SetCol(Matrix *v, int k)
{
	for (int i = 0; i < rows; i++)
	{
		mat[i][k] = (*v)(i,0);
	}
}

void Matrix::MakeLU()
{
	if (!IsSquare())
	{
		throw MException(L"The matrix is not square!");
	}
	L = IdentityMatrix(rows, cols);
	U = Duplicate();

	pi = new int[rows];
	for (int i = 0; i < rows; i++)
	{
		pi[i] = i;
	}

	double p = 0;
	double pom2;
	int k0 = 0;
	int pom1 = 0;

	for (int k = 0; k < cols - 1; k++)
	{
		p = 0;
		for (int i = k; i < rows; i++) // find the row with the biggest pivot
		{
			if (abs((*U)(i,k)) > p)
			{
				p = abs((*U)(i,k));
				k0 = i;
			}
		}
		if (p == 0) // samé nuly ve sloupci
		{
			throw MException(L"The matrix is singular!");
		}

		pom1 = pi[k]; // switch two rows in permutation matrix
		pi[k] = pi[k0];
		pi[k0] = pom1;

		for (int i = 0; i < k; i++)
		{
			pom2 = (*L)(k,i);
			(*L)(k,i) = (*L)(k0,i);
			(*L)(k0,i) = pom2;
		}

		if (k != k0)
		{
			detOfP *= -1;
		}

		for (int i = 0; i < cols; i++) // Switch rows in U
		{
			pom2 = (*U)(k,i);
			(*U)(k,i) = (*U)(k0,i);
			(*U)(k0,i) = pom2;
		}

		for (int i = k + 1; i < rows; i++)
		{
			(*L)(i,k) = (*U)(i,k) / (*U)(k,k);
			for (int j = k; j < cols; j++)
			{
				(*U)(i,j) = (*U)(i,j) - (*L)(i,k) * (*U)(k,j);
			}
		}
	}
}

Matrix *Matrix::SolveWith(Matrix *v)
{
	if (rows != cols)
	{
		throw MException(L"The matrix is not square!");
	}
	if (rows != v->rows)
	{
		throw MException(L"Wrong number of results in solution vector!");
	}
	if (L == NULL)
	{
		MakeLU();
	}

	Matrix *b = new Matrix(rows,cols);
	for (int i = 0; i < rows; i++) // switch two items in "v" due to permutation matrix
	{
		(*b)(pi[i],0) = (*v)(i,0);
	}

	Matrix *z = SubsForth(L,b);
	Matrix *x = SubsBack(U,z);

	return x;
}

Matrix *Matrix::Invert()
{
	if (L == NULL)
	{
		MakeLU();
	}

	Matrix *inv = new Matrix(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		Matrix *Ei = Matrix::ZeroMatrix(rows, 1);
		(*Ei)(pi[pi[i]],0) = 1;
		Matrix *col = SolveWith(Ei);
		inv->SetCol(col, i);
	}
	return inv;
}

double Matrix::Det()
{
	if (L == NULL)
	{
		MakeLU();
	}
	double det = detOfP;
	for (int i = 0; i < rows; i++)
	{
		det *= (*U)(i,i);
	}
	return det;
}

Matrix *Matrix::GetP()
{
	if (L == NULL)
	{
		MakeLU();
	}

	Matrix *matrix = ZeroMatrix(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		(*matrix)(i,pi[i]) = 1;
	}
	return matrix;
}

Matrix *Matrix::Duplicate()
{
	Matrix *matrix = new Matrix(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			(*matrix)(i,j) = mat[i][j];
		}
	}
	return matrix;
}

Matrix *Matrix::SubsForth(Matrix *A, Matrix *b)
{
	if (A->L == NULL)
	{
		A->MakeLU();
	}
	int n = A->rows;
	Matrix *x = new Matrix(n, 1);

	for (int i = 0; i < n; i++)
	{
		(*x)(i,0) = (*b)(i,0);
		for (int j = 0; j < i; j++)
		{
			(*x)(i,0) -= (*A)(i,j) * (*x)(j,0);
		}
		(*x)(i,0) = (*x)(i,0) / (*A)(i,i);
	}
	return x;
}

Matrix *Matrix::SubsBack(Matrix *A, Matrix *b)
{
	if (A->L == NULL)
	{
		A->MakeLU();
	}
	int n = A->rows;
	Matrix *x = new Matrix(n, 1);

	for (int i = n - 1; i > -1; i--)
	{
		(*x)(i,0) = (*b)(i,0);
		for (int j = n - 1; j > i; j--)
		{
			(*x)(i,0) -= ((*A)(i,j)) * ((*x)(j,0));
		}
		(*x)(i,0) = (*x)(i,0) / (*A)(i,i);
	}
	return x;
}

Matrix *Matrix::ZeroMatrix(int iRows, int iCols)
{
	Matrix *matrix = new Matrix(iRows, iCols);
	for (int i = 0; i < iRows; i++)
	{
		for (int j = 0; j < iCols; j++)
		{
			(*matrix)(i,j) = 0;
		}
	}
	return matrix;
}

Matrix *Matrix::IdentityMatrix(int iRows, int iCols)
{
	Matrix *matrix = ZeroMatrix(iRows, iCols);
	for (int i = 0; i < std::min(iRows, iCols); i++)
	{
		(*matrix)(i,i) = 1;
	}
	return matrix;
}

/*Matrix *Matrix::RandomMatrix(int iRows, int iCols, int dispersion)
{
	Random *random = new Random();
	Matrix *matrix = new Matrix(iRows, iCols);
	for (int i = 0; i < iRows; i++)
	{
		for (int j = 0; j < iCols; j++)
		{
			matrix[i][j] = random->Next(-dispersion, dispersion);
		}
	}
	return matrix;
}*/

/*Matrix *Matrix::Parse(const std::wstring &s)
{
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: string[] rows = Regex.Split(s, "\r\n");
	std::wstring *rows = Regex::Split(s, L"\r\n");
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: string[] nums = rows[0].Split(' ');
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to this .NET String method:
	std::wstring *nums = rows[0].Split(L' ');
	Matrix *matrix = new Matrix(rows->Length, nums->Length);
	try
	{
		for (int i = 0; i < rows->Length; i++)
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to this .NET String method:
			nums = rows[i].Split(L' ');
			for (int j = 0; j < nums->Length; j++)
			{
				matrix[i][j] = static_cast<double>(nums[j]);
			}
		}
	}
	catch (FormatException exc)
	{
		throw MException(L"Wrong input format!");
	}
	return matrix;
}
*/

/*std::wstring Matrix::ToString()
{
	std::wstring s = L"";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			s += std::wstring::Format(L"{0,5:0.00}", mat[i][j]) + std::wstring(L" ");
		}
		s += std::wstring(L"\r\n");
	}
	return s;
}*/

Matrix *Matrix::Transpose(Matrix *m)
{
	Matrix *t = new Matrix(m->cols, m->rows);
	for (int i = 0; i < m->rows; i++)
	{
		for (int j = 0; j < m->cols; j++)
		{
			(*t)(i,j) = (*m)(j,i);
		}
	}
	return t;
}

Matrix *Matrix::Transpose()
{
	Matrix *t = new Matrix(cols, rows);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			(*t)(j,i) = mat[i][j];
		}
	}
	return t;
}

Matrix *Matrix::Power(Matrix *m, int pow)
{
	if (pow == 0)
	{
		return IdentityMatrix(m->rows, m->cols);
	}
	if (pow == 1)
	{
		return m->Duplicate();
	}
	if (pow == -1)
	{
		return m->Invert();
	}

	Matrix *x;
	if (pow < 0)
	{
		x = m->Invert();
		pow *= -1;
	}
	else
	{
		x = m->Duplicate();
	}

	Matrix *ret = IdentityMatrix(m->rows, m->cols);
	while (pow != 0)
	{
		if ((pow & 1) == 1)
		{
			ret = ret->Multiply(x);
		}
		x = x->Multiply(x);
		pow >>= 1;
	}
	return ret;
}

void Matrix::SafeAplusBintoC(Matrix *A, int xa, int ya, Matrix *B, int xb, int yb, Matrix *C, int size)
{
	for (int i = 0; i < size; i++) // rows
	{
		for (int j = 0; j < size; j++) // cols
		{
			(*C)(i,j) = 0;
			if (xa + j < A->cols && ya + i < A->rows)
			{
				(*C)(i,j) += (*A)(ya + i,xa + j);
			}
			if (xb + j < B->cols && yb + i < B->rows)
			{
				(*C)(i,j) += (*B)(yb + i,xb + j);
			}
		}
	}
}

void Matrix::SafeAminusBintoC(Matrix *A, int xa, int ya, Matrix *B, int xb, int yb, Matrix *C, int size)
{
	for (int i = 0; i < size; i++) // rows
	{
		for (int j = 0; j < size; j++) // cols
		{
			(*C)(i,j) = 0;
			if (xa + j < A->cols && ya + i < A->rows)
			{
				(*C)(i,j) += (*A)(ya + i,xa + j);
			}
			if (xb + j < B->cols && yb + i < B->rows)
			{
				(*C)(i,j) -= (*B)(yb + i,xb + j);
			}
		}
	}
}

void Matrix::SafeACopytoC(Matrix *A, int xa, int ya, Matrix *C, int size)
{
	for (int i = 0; i < size; i++) // rows
	{
		for (int j = 0; j < size; j++) // cols
		{
			(*C)(i,j) = 0;
			if (xa + j < A->cols && ya + i < A->rows)
			{
				(*C)(i,j) += (*A)(ya + i,xa + j);
			}
		}
	}
}

void Matrix::AplusBintoC(Matrix *A, int xa, int ya, Matrix *B, int xb, int yb, Matrix *C, int size)
{
	for (int i = 0; i < size; i++) // rows
	{
		for (int j = 0; j < size; j++)
		{
			(*C)(i,j) = (*A)(ya + i,xa + j) + (*B)(yb + i,xb + j);
		}
	}
}

void Matrix::AminusBintoC(Matrix *A, int xa, int ya, Matrix *B, int xb, int yb, Matrix *C, int size)
{
	for (int i = 0; i < size; i++) // rows
	{
		for (int j = 0; j < size; j++)
		{
			(*C)(i,j) = (*A)(ya + i,xa + j) - (*B)(yb + i,xb + j);
		}
	}
}

void Matrix::ACopytoC(Matrix *A, int xa, int ya, Matrix *C, int size)
{
	for (int i = 0; i < size; i++) // rows
	{
		for (int j = 0; j < size; j++)
		{
			(*C)(i,j) = (*A)(ya + i,xa + j);
		}
	}
}

/*Matrix *Matrix::StrassenMultiply(Matrix *A, Matrix *B)
{
	if (A->cols != B->rows)
	{
		throw MException(L"Wrong dimension of matrix!");
	}

	Matrix *R;

	int msize = std::max(std::max(A->rows, A->cols), std::max(B->rows, B->cols));

	if (msize < 32)
	{
		R = ZeroMatrix(A->rows, B->cols);
		for (int i = 0; i < R->rows; i++)
		{
			for (int j = 0; j < R->cols; j++)
			{
				for (int k = 0; k < A->cols; k++)
				{
					R[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		return R;
	}

	int size = 1;
	int n = 0;
	while (msize > size)
	{
		size *= 2;
		n++;
	};
	int h = size / 2;


	Matrix mField[n][9];

	/*
	 *  8x8, 8x8, 8x8, ...
	 *  4x4, 4x4, 4x4, ...
	 *  2x2, 2x2, 2x2, ...
	 *  . . .
	 *

	int z;
	for (int i = 0; i < n - 4; i++) // rows
	{
		z = static_cast<int>(pow(2, n - i - 1));
		for (int j = 0; j < 9; j++)
		{
			mField[i][j] = new Matrix(z, z);
		}
	}

	SafeAplusBintoC(A, 0, 0, A, h, h, mField[0][0], h);
	SafeAplusBintoC(B, 0, 0, B, h, h, mField[0][1], h);
	StrassenMultiplyRun(mField[0][0], mField[0][1], mField[0][1 + 1], 1, mField); // (A11 + A22) * (B11 + B22);

	SafeAplusBintoC(A, 0, h, A, h, h, mField[0][0], h);
	SafeACopytoC(B, 0, 0, mField[0][1], h);
	StrassenMultiplyRun(mField[0][0], mField[0][1], mField[0][1 + 2], 1, mField); // (A21 + A22) * B11;

	SafeACopytoC(A, 0, 0, mField[0][0], h);
	SafeAminusBintoC(B, h, 0, B, h, h, mField[0][1], h);
	StrassenMultiplyRun(mField[0][0], mField[0][1], mField[0][1 + 3], 1, mField); //A11 * (B12 - B22);

	SafeACopytoC(A, h, h, mField[0][0], h);
	SafeAminusBintoC(B, 0, h, B, 0, 0, mField[0][1], h);
	StrassenMultiplyRun(mField[0][0], mField[0][1], mField[0][1 + 4], 1, mField); //A22 * (B21 - B11);

	SafeAplusBintoC(A, 0, 0, A, h, 0, mField[0][0], h);
	SafeACopytoC(B, h, h, mField[0][1], h);
	StrassenMultiplyRun(mField[0][0], mField[0][1], mField[0][1 + 5], 1, mField); //(A11 + A12) * B22;

	SafeAminusBintoC(A, 0, h, A, 0, 0, mField[0][0], h);
	SafeAplusBintoC(B, 0, 0, B, h, 0, mField[0][1], h);
	StrassenMultiplyRun(mField[0][0], mField[0][1], mField[0][1 + 6], 1, mField); //(A21 - A11) * (B11 + B12);

	SafeAminusBintoC(A, h, 0, A, h, h, mField[0][0], h);
	SafeAplusBintoC(B, 0, h, B, h, h, mField[0][1], h);
	StrassenMultiplyRun(mField[0][0], mField[0][1], mField[0][1 + 7], 1, mField); // (A12 - A22) * (B21 + B22);

	R = new Matrix(A->rows, B->cols); // result

	/// C11
	for (int i = 0; i < std::min(h, R->rows); i++) // rows
	{
		for (int j = 0; j < std::min(h, R->cols); j++) // cols
		{
			R[i][j] = mField[0][1 + 1][i, j] + mField[0][1 + 4][i, j] - mField[0][1 + 5][i, j] + mField[0][1 + 7][i, j];
		}
	}

	/// C12
	for (int i = 0; i < std::min(h, R->rows); i++) // rows
	{
		for (int j = h; j < std::min(2*h, R->cols); j++) // cols
		{
			R[i][j] = mField[0][1 + 3][i, j - h] + mField[0][1 + 5][i, j - h];
		}
	}

	/// C21
	for (int i = h; i < std::min(2*h, R->rows); i++) // rows
	{
		for (int j = 0; j < std::min(h, R->cols); j++) // cols
		{
			R[i][j] = mField[0][1 + 2][i - h, j] + mField[0][1 + 4][i - h, j];
		}
	}

	/// C22
	for (int i = h; i < std::min(2 * h, R->rows); i++) // rows
	{
		for (int j = h; j < std::min(2 * h, R->cols); j++) // cols
		{
			R[i][j] = mField[0][1 + 1][i - h, j - h] - mField[0][1 + 2][i - h, j - h] + mField[0][1 + 3][i - h, j - h] + mField[0][1 + 6][i - h, j - h];
		}
	}

	return R;
}*

/*void Matrix::StrassenMultiplyRun(Matrix *A, Matrix *B, Matrix *C, int l, Matrix f[][])
{
	int size = A->rows;
	int h = size / 2;

	if (size < 32)
	{
		for (int i = 0; i < C->rows; i++)
		{
			for (int j = 0; j < C->cols; j++)
			{
				C[i][j] = 0;
				for (int k = 0; k < A->cols; k++)
				{
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		return;
	}

	AplusBintoC(A, 0, 0, A, h, h, f[l][0], h);
	AplusBintoC(B, 0, 0, B, h, h, f[l][1], h);
	StrassenMultiplyRun(f[l][0], f[l][1], f[l][1 + 1], l + 1, f); // (A11 + A22) * (B11 + B22);

	AplusBintoC(A, 0, h, A, h, h, f[l][0], h);
	ACopytoC(B, 0, 0, f[l][1], h);
	StrassenMultiplyRun(f[l][0], f[l][1], f[l][1 + 2], l + 1, f); // (A21 + A22) * B11;

	ACopytoC(A, 0, 0, f[l][0], h);
	AminusBintoC(B, h, 0, B, h, h, f[l][1], h);
	StrassenMultiplyRun(f[l][0], f[l][1], f[l][1 + 3], l + 1, f); //A11 * (B12 - B22);

	ACopytoC(A, h, h, f[l][0], h);
	AminusBintoC(B, 0, h, B, 0, 0, f[l][1], h);
	StrassenMultiplyRun(f[l][0], f[l][1], f[l][1 + 4], l + 1, f); //A22 * (B21 - B11);

	AplusBintoC(A, 0, 0, A, h, 0, f[l][0], h);
	ACopytoC(B, h, h, f[l][1], h);
	StrassenMultiplyRun(f[l][0], f[l][1], f[l][1 + 5], l + 1, f); //(A11 + A12) * B22;

	AminusBintoC(A, 0, h, A, 0, 0, f[l][0], h);
	AplusBintoC(B, 0, 0, B, h, 0, f[l][1], h);
	StrassenMultiplyRun(f[l][0], f[l][1], f[l][1 + 6], l + 1, f); //(A21 - A11) * (B11 + B12);

	AminusBintoC(A, h, 0, A, h, h, f[l][0], h);
	AplusBintoC(B, 0, h, B, h, h, f[l][1], h);
	StrassenMultiplyRun(f[l][0], f[l][1], f[l][1 + 7], l + 1, f); // (A12 - A22) * (B21 + B22);

	/// C11
	for (int i = 0; i < h; i++) // rows
	{
		for (int j = 0; j < h; j++) // cols
		{
			C[i][j] = f[l][1 + 1][i, j] + f[l][1 + 4][i, j] - f[l][1 + 5][i, j] + f[l][1 + 7][i, j];
		}
	}

	/// C12
	for (int i = 0; i < h; i++) // rows
	{
		for (int j = h; j < size; j++) // cols
		{
			C[i][j] = f[l][1 + 3][i, j - h] + f[l][1 + 5][i, j - h];
		}
	}

	/// C21
	for (int i = h; i < size; i++) // rows
	{
		for (int j = 0; j < h; j++) // cols
		{
			C[i][j] = f[l][1 + 2][i - h, j] + f[l][1 + 4][i - h, j];
		}
	}

	/// C22
	for (int i = h; i < size; i++) // rows
	{
		for (int j = h; j < size; j++) // cols
		{
			C[i][j] = f[l][1 + 1][i - h, j - h] - f[l][1 + 2][i - h, j - h] + f[l][1 + 3][i - h, j - h] + f[l][1 + 6][i - h, j - h];
		}
	}
}*/

Matrix *Matrix::Multiply(Matrix *m1, Matrix *m2)
{
	if (m1->cols != m2->rows)
	{
		throw MException(L"Wrong dimensions of matrix!");
	}

	Matrix *result = ZeroMatrix(m1->rows, m2->cols);
	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->cols; j++)
		{
			for (int k = 0; k < m1->cols; k++)
			{
				result->operator ()(i,j) += m1->operator ()(i,k) * m2->operator ()(k,j);
			}
		}
	}
	return result;
}

Matrix *Matrix::Multiply(Matrix *m1)
{
	return Multiply(this,m1);
}

Matrix *Matrix::Multiply(double n, Matrix *m)
{
	Matrix *r = new Matrix(m->rows, m->cols);
	for (int i = 0; i < m->rows; i++)
	{
		for (int j = 0; j < m->cols; j++)
		{
			r->operator ()(i,j) = m->operator ()(i,j) * n;
		}
	}
	return r;
}

Matrix *Matrix::Add(Matrix *m1, Matrix *m2)
{
	if (m1->rows != m2->rows || m1->cols != m2->cols)
	{
		throw MException(L"Matrices must have the same dimensions!");
	}
	Matrix *r = new Matrix(m1->rows, m1->cols);
	for (int i = 0; i < r->rows; i++)
	{
		for (int j = 0; j < r->cols; j++)
		{
			r->operator ()(i,j) = m1->operator ()(i,j) + m2->operator ()(i,j);
		}
	}

	return r;
}

Matrix *Matrix::operator -()
{
	return Matrix::Multiply(-1, this);
}

Matrix *Matrix::operator + (Matrix *m2)
{
	return Matrix::Add(this, m2);
}

Matrix *Matrix::operator - (Matrix *m2)
{
	return Matrix::Add(this, Matrix::Multiply(-1, m2));
}

Matrix *Matrix::operator * (Matrix *m2)
{
	return Matrix::Multiply(this, m2);
}

Matrix *Matrix::operator * (double n)
{
	return Matrix::Multiply(n, this);
}

void Matrix::InitializeInstanceFields()
{
	rows = 0;
	cols = 0;
	detOfP = 1;
}

MException::MException(const wchar_t* Message)
{
}




