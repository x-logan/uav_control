/*
 * Matrix1.h
 *
 *  Created on: Jul 11, 2014
 *      Author: logan
 */
#include <string.h>

#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {
public:
	Matrix(int iRows, int iCols); // Matrix Class constructor
	virtual ~Matrix();
	int rows;
	int cols;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: public double[,] mat;
	double **mat;
	Matrix *L;
	Matrix *U;
	bool IsSquare();
	double &operator ()(int iRow, int iCol); // Access this matrix as a 2D array
	//const double operator ()(int iRow, int iCol); // Access this matrix as a 2D array
	Matrix *GetCol(int k);
	void SetCol(Matrix *v, int k);
	void MakeLU(); // Function for LU decomposition
	Matrix *SolveWith(Matrix *v); // Function solves Ax = v in confirmity with solution vector "v"
	Matrix *Invert(); // Function returns the inverted matrix
	double Det(); // Function for determinant
	Matrix *GetP(); // Function returns permutation matrix "P" due to permutation vector "pi"
	Matrix *Duplicate(); // Function returns the copy of this matrix
	static Matrix *SubsForth(Matrix *A, Matrix *b); // Function solves Ax = b for A as a lower triangular matrix
	static Matrix *SubsBack(Matrix *A, Matrix *b); // Function solves Ax = b for A as an upper triangular matrix
	static Matrix *ZeroMatrix(int iRows, int iCols); // Function generates the zero matrix
	static Matrix *IdentityMatrix(int iRows, int iCols); // Function generates the identity matrix
	//static Matrix *RandomMatrix(int iRows, int iCols, int dispersion); // Function generates the zero matrix
	//static Matrix *Parse(const std::wstring &s); // Function parses the matrix from string
	//virtual std::wstring ToString() override; // Function returns matrix as a string
	static Matrix *Transpose(Matrix *m); // Matrix transpose
	Matrix *Transpose(); // Matrix transpose
	static Matrix *Power(Matrix *m, int pow); // Power matrix to exponent
	static Matrix *StupidMultiply(Matrix *m1, Matrix *m2); // Stupid matrix multiplication
	Matrix *operator - ();
	Matrix *operator + (Matrix *m2);
	Matrix *operator - (Matrix *m2);
	Matrix *operator * (Matrix *m2);

	//static Matrix *operator - (Matrix m);
	//static Matrix *operator + (Matrix *m2);
	//Matrix *operator - (Matrix *m2);
	Matrix *operator * (double n);
	Matrix *Multiply(Matrix *m1); // Multiplication

private:
	int *pi;
	double detOfP;
	static void SafeAplusBintoC(Matrix *A, int xa, int ya, Matrix *B, int xb, int yb, Matrix *C, int size);
	static void SafeAminusBintoC(Matrix *A, int xa, int ya, Matrix *B, int xb, int yb, Matrix *C, int size);
	static void SafeACopytoC(Matrix *A, int xa, int ya, Matrix *C, int size);
	static void AplusBintoC(Matrix *A, int xa, int ya, Matrix *B, int xb, int yb, Matrix *C, int size);
	static void AminusBintoC(Matrix *A, int xa, int ya, Matrix *B, int xb, int yb, Matrix *C, int size);
	static void ACopytoC(Matrix *A, int xa, int ya, Matrix *C, int size);
	static Matrix *StrassenMultiply(Matrix *A, Matrix *B); // Smart matrix multiplication
	// function for square matrix 2^N x 2^N
	//static void StrassenMultiplyRun(Matrix *A, Matrix *B, Matrix *C, int l, Matrix f[][]); // A * B into C, level of recursion, matrix field
	static Matrix *Multiply(double n, Matrix *m); // Multiplication by constant n
	static Matrix *Multiply(Matrix *m1, Matrix *m2); // Multiplication

	static Matrix *Add(Matrix *m1, Matrix *m2); // Sčítání matic
	void InitializeInstanceFields();

};

//  The class for exceptions
class MException
{
public:

	MException(const wchar_t* Message);
};

#endif /* MATRIX_H_ */
