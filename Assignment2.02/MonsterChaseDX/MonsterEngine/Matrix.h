#ifndef GUARD_Matrix_h
#define GUARD_Matrix_h

#include <math.h>
#include "Vector3.h"
#include "Vector4.h"

class Matrix;
typedef __declspec(align(64)) Matrix FastMatrix;

class Matrix
{
public:
	//Default constructor
	Matrix(){};
	//Value based Constructor
	Matrix(
		float i_11, float i_12, float i_13, float i_14,
		float i_21, float i_22, float i_23, float i_24,
		float i_31, float i_32, float i_33, float i_34,
		float i_41, float i_42, float i_43, float i_44) :
		m_11(i_11), m_12(i_12), m_13(i_13), m_14(i_14),
		m_21(i_21), m_22(i_22), m_23(i_23), m_24(i_24),
		m_31(i_31), m_32(i_32), m_33(i_33), m_34(i_34),
		m_41(i_41), m_42(i_42), m_43(i_43), m_44(i_44) {}

	//Copy Constructor
	Matrix(const Matrix & i_other) :
		m_11(i_other.m_11), m_12(i_other.m_12), m_13(i_other.m_13), m_14(i_other.m_14),
		m_21(i_other.m_21), m_22(i_other.m_22), m_23(i_other.m_23), m_24(i_other.m_24),
		m_31(i_other.m_31), m_32(i_other.m_32), m_33(i_other.m_33), m_34(i_other.m_34),
		m_41(i_other.m_41), m_42(i_other.m_42), m_43(i_other.m_43), m_44(i_other.m_44) {}

	//Assignment Operator
	Matrix & operator=(const Matrix & i_other){
		m_11 = i_other.m_11; m_12 = i_other.m_12; m_13 = i_other.m_13; m_14 = i_other.m_14;
		m_21 = i_other.m_21; m_22 = i_other.m_22; m_23 = i_other.m_23; m_24 = i_other.m_24;
		m_31 = i_other.m_31; m_32 = i_other.m_32; m_33 = i_other.m_33; m_34 = i_other.m_34;
		m_41 = i_other.m_41; m_42 = i_other.m_42; m_43 = i_other.m_43; m_44 = i_other.m_44;
		return *this;
	}
	//Acces functions
	float Get(int i_row, int i_col) { return *((&m_11) + i_row * 4 + i_col); }

	//Useful Matrix Initiators
	void SetToIdentity(void);
	void SetToXRotation(float i_RotationRadians);
	void SetToYRotation(float i_RotationRadians);
	void SetToZRotation(float i_RotationRadians);

	void SetToTranslation(float i_transX, float i_transY, float i_transZ);
	void SetToScale(float i_scaleX, float i_scaleY, float i_scaleZ);

	//Useful Matrix Creators
	static Matrix CreateXRotation(float i_RotationRadians);
	static Matrix CreateYRotation(float i_RotationRadians);
	static Matrix CreateZRotation(float i_RotationRadians);

	static Matrix CreateTranslation(float i_transX, float i_transY, float i_transZ);
	static Matrix CreateScale(float i_scaleX, float i_scaleY, float i_scaleZ);

	// Invert this instance
	void Invert(void);
	// Return a matrix that is the inverse of this instance but don't modify this instance
	Matrix GetInverse(void) const;

	// Transpose this instance
	void Transpose(void);
	// return a matrix that is a transpose of this instance but don't modify this instance
	Matrix GetTranspose(void) const;

	// Multiply Matrix * Matrix
	// return *this * i_other
	Matrix operator*(const Matrix & i_other) const;
	Vector4 operator*(const Vector4 & i_other) const;

	// Multiply Vector by Matrix
	// return v * M
	Vector4 MultiplyLeft(const Vector4 & i_Vector) const;
	// return M * v
	Vector4 MultiplyRight(const Vector4 & i_Vector) const;

	// I should probably write this
	bool operator==(const Matrix & i_rhs) const;

	static const FastMatrix Identity;

private:
	float
		// m_<row><column>
		m_11, m_12, m_13, m_14, // row 1
		m_21, m_22, m_23, m_24, // row 2
		m_31, m_32, m_33, m_34, // row 3
		m_41, m_42, m_43, m_44; // row 4

	Matrix Multiply(const Matrix & i_other, Matrix & o_out) const;

	// internal inverse function used by Invert() and GetInverse()
	Matrix & InverseSSE(Matrix & o_out) const;
	Matrix & MultiplySSE(const Matrix & i_other, Matrix & o_out) const;
};

#endif // GUARD_Matrix_h