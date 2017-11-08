#include "Matrix.h"
#include "Assert.h"


//m_11 = m_12 = m_13 = m_14 = m_21 = m_22 = m_23 = m_24 = m_31 = m_32 = m_33 = m_34 = m_41 = m_42 = m_43 = m_44 = 0.0f;

void Matrix::SetToIdentity()
{
	m_11 = m_22 = m_33 = m_44 = 1.0f;
	m_12 = m_13 = m_14 = m_21 = m_23 = m_24 = m_31 = m_32 = m_34 = m_41 = m_42 = m_43 = 0.0f;
}

void Matrix::SetToXRotation(float i_RotationRadians)
{
	m_12 = m_13 = m_14 = m_21 = m_24 = m_31 = m_34 = m_41 = m_42 = m_43 = 0.0f;
	m_11 = m_44 = 1.0f;
	m_22 = cos(i_RotationRadians);
	m_23 = sin(i_RotationRadians);
	m_32 = -sin(i_RotationRadians);
	m_33 = cos(i_RotationRadians);
}

void Matrix::SetToYRotation(float i_RotationRadians)
{
	m_12 = m_14 = m_21 = m_23 = m_24 = m_32 = m_34 = m_41 = m_42 = m_43 = 0.0f;
	m_22 = m_44 = 1.0f;
	m_11 = m_33 = cos(i_RotationRadians);
	m_13 = -sin(i_RotationRadians);
	m_31 = sin(i_RotationRadians);
}

void Matrix::SetToZRotation(float i_RotationRadians)
{
	m_13 = m_14 = m_23 = m_24 = m_31 = m_32 = m_34 = m_41 = m_42 = m_43 = 0.0f;
	m_33 = m_44 = 1.0f;
	m_11 = m_22 = cos(i_RotationRadians);
	m_12 = m_21 = sin(i_RotationRadians);
}

void Matrix::SetToTranslation(float i_transX, float i_transY, float i_transZ)
{
	m_11 = m_22 = m_33 = m_44 = 1.0f;
	m_12 = m_13 = m_21 = m_23 = m_31 = m_32 = m_41 = m_42 = m_43 = 0.0f;
	m_14 = i_transX;
	m_24 = i_transY;
	m_34 = i_transZ;
}

void Matrix::SetToScale(float i_scaleX, float i_scaleY, float i_scaleZ)
{
	m_44 = 1.0f;
	m_12 = m_13 = m_14 = m_21 = m_23 = m_24 = m_31 = m_32 = m_34 = m_41 = m_42 = m_43 = 0.0f;
	m_11 = i_scaleX;
	m_22 = i_scaleY;
	m_33 = i_scaleZ;
}

Matrix Matrix::CreateXRotation(float i_RotationRadians)
{
	Matrix o_Matrix;

	o_Matrix.m_12 = o_Matrix.m_13 = o_Matrix.m_14 = o_Matrix.m_21 = o_Matrix.m_24 = o_Matrix.m_31 = o_Matrix.m_34 = o_Matrix.m_41 = o_Matrix.m_42 = o_Matrix.m_43 = 0.0f;
	o_Matrix.m_11 = o_Matrix.m_44 = 1.0f;
	o_Matrix.m_22 = cos(i_RotationRadians);
	o_Matrix.m_23 = sin(i_RotationRadians);
	o_Matrix.m_32 = -sin(i_RotationRadians);
	o_Matrix.m_33 = cos(i_RotationRadians);

	return o_Matrix;
}

Matrix Matrix::CreateYRotation(float i_RotationRadians)
{
	Matrix o_Matrix;

	o_Matrix.m_12 = o_Matrix.m_14 = o_Matrix.m_21 = o_Matrix.m_23 = o_Matrix.m_24 = o_Matrix.m_32 = o_Matrix.m_34 = o_Matrix.m_41 = o_Matrix.m_42 = o_Matrix.m_43 = 0.0f;
	o_Matrix.m_22 = o_Matrix.m_44 = 1.0f;
	o_Matrix.m_11 = o_Matrix.m_33 = cos(i_RotationRadians);
	o_Matrix.m_13 = -sin(i_RotationRadians);
	o_Matrix.m_31 = sin(i_RotationRadians);

	return o_Matrix;
}

Matrix Matrix::CreateZRotation(float i_RotationRadians)
{
	Matrix o_Matrix;

	o_Matrix.m_13 = o_Matrix.m_14 = o_Matrix.m_23 = o_Matrix.m_24 = o_Matrix.m_31 = o_Matrix.m_32 = o_Matrix.m_34 = o_Matrix.m_41 = o_Matrix.m_42 = o_Matrix.m_43 = 0.0f;
	o_Matrix.m_33 = o_Matrix.m_44 = 1.0f;
	o_Matrix.m_11 = o_Matrix.m_22 = cos(i_RotationRadians);
	o_Matrix.m_12 = o_Matrix.m_21 = sin(i_RotationRadians);

	return o_Matrix;
}

Matrix Matrix::CreateTranslation(float i_transX, float i_transY, float i_transZ)
{
	Matrix o_Matrix;

	o_Matrix.m_11 = o_Matrix.m_22 = o_Matrix.m_33 = o_Matrix.m_44 = 1.0f;
	o_Matrix.m_12 = o_Matrix.m_13 = o_Matrix.m_21 = o_Matrix.m_23 = o_Matrix.m_31 = o_Matrix.m_32 = o_Matrix.m_41 = o_Matrix.m_42 = o_Matrix.m_43 = 0.0f;
	o_Matrix.m_14 = i_transX;
	o_Matrix.m_24 = i_transY;
	o_Matrix.m_34 = i_transZ;

	return o_Matrix;
}

Matrix Matrix::CreateScale(float i_scaleX, float i_scaleY, float i_scaleZ)
{
	Matrix o_Matrix;

	o_Matrix.m_44 = 1.0f;
	o_Matrix.m_12 = o_Matrix.m_13 = o_Matrix.m_14 = o_Matrix.m_21 = o_Matrix.m_23 = o_Matrix.m_24 = o_Matrix.m_31 = o_Matrix.m_32 = o_Matrix.m_34 = o_Matrix.m_41 = o_Matrix.m_42 = o_Matrix.m_43 = 0.0f;
	o_Matrix.m_11 = i_scaleX;
	o_Matrix.m_22 = i_scaleY;
	o_Matrix.m_33 = i_scaleZ;

	return o_Matrix;
}

void Matrix::Invert()
{
	float det = 0;
	det = (m_11*m_22*m_33*m_44) + (m_11*m_23*m_34*m_42) + (m_11*m_24*m_32*m_43)
		+ (m_12*m_21*m_34*m_43) + (m_12*m_23*m_31*m_44) + (m_12*m_24*m_33*m_41)
		+ (m_13*m_21*m_32*m_44) + (m_13*m_22*m_34*m_41) + (m_13*m_24*m_31*m_42)
		+ (m_14*m_21*m_33*m_42) + (m_14*m_22*m_31*m_43) + (m_14*m_23*m_32*m_41)
		- (m_11*m_22*m_34*m_43) - (m_11*m_23*m_32*m_44) - (m_11*m_24*m_33*m_42)
		- (m_12*m_21*m_33*m_44) - (m_12*m_23*m_34*m_41) - (m_12*m_24*m_31*m_43)
		- (m_13*m_21*m_34*m_42) - (m_13*m_22*m_31*m_44) - (m_13*m_24*m_32*m_41)
		- (m_14*m_21*m_32*m_43) - (m_14*m_22*m_33*m_41) - (m_14*m_23*m_31*m_42);


	float
		t11, t12, t13, t14,
		t21, t22, t23, t24,
		t31, t32, t33, t34,
		t41, t42, t43, t44;

	t11 = ((m_22*m_33*m_44) + (m_23*m_34*m_42) + (m_24*m_32*m_43)
		- (m_22*m_34*m_43) - (m_23*m_32*m_44) - (m_24*m_33*m_42)) / det;
	t12 = ((m_12*m_34*m_43) + (m_13*m_32*m_44) + (m_14*m_33*m_42)
		- (m_12*m_33*m_44) - (m_13*m_34*m_42) - (m_14*m_32*m_43)) / det;
	t13 = ((m_12*m_23*m_44) + (m_13*m_24*m_42) + (m_14*m_22*m_43)
		- (m_12*m_24*m_43) - (m_13*m_22*m_44) - (m_14*m_23*m_42)) / det;
	t14 = ((m_12*m_24*m_33) + (m_13*m_22*m_34) + (m_14*m_23*m_32)
		- (m_12*m_23*m_34) - (m_13*m_24*m_32) - (m_14*m_22*m_33)) / det;
	t21 = ((m_21*m_34*m_43) + (m_23*m_31*m_44) + (m_24*m_33*m_41)
		- (m_21*m_33*m_44) - (m_23*m_34*m_41) - (m_24*m_31*m_43)) / det;
	t22 = ((m_11*m_33*m_44) + (m_13*m_34*m_41) + (m_14*m_31*m_43)
		- (m_11*m_34*m_43) - (m_13*m_31*m_44) - (m_14*m_33*m_41)) / det;
	t23 = ((m_11*m_24*m_43) + (m_13*m_21*m_44) + (m_14*m_23*m_41)
		- (m_11*m_23*m_44) - (m_13*m_24*m_41) - (m_14*m_21*m_43)) / det;
	t24 = ((m_11*m_23*m_34) + (m_13*m_24*m_31) + (m_14*m_21*m_33)
		- (m_11*m_24*m_33) - (m_13*m_21*m_34) - (m_14*m_23*m_31)) / det;
	t31 = ((m_21*m_32*m_44) + (m_22*m_34*m_41) + (m_24*m_31*m_42)
		- (m_21*m_34*m_42) - (m_22*m_31*m_44) - (m_24*m_32*m_41)) / det;
	t32 = ((m_11*m_34*m_42) + (m_12*m_31*m_44) + (m_14*m_32*m_41)
		- (m_11*m_32*m_44) - (m_12*m_34*m_41) - (m_14*m_31*m_42)) / det;
	t33 = ((m_11*m_22*m_44) + (m_12*m_24*m_41) + (m_14*m_21*m_42)
		- (m_11*m_24*m_42) - (m_12*m_21*m_44) - (m_14*m_22*m_41)) / det;
	t34 = ((m_11*m_24*m_32) + (m_12*m_21*m_34) + (m_14*m_22*m_31)
		- (m_11*m_22*m_34) - (m_12*m_24*m_31) - (m_14*m_21*m_32)) / det;
	t41 = ((m_21*m_33*m_42) + (m_22*m_31*m_43) + (m_23*m_32*m_41)
		- (m_21*m_32*m_43) - (m_22*m_33*m_41) - (m_23*m_31*m_42)) / det;
	t42 = ((m_11*m_32*m_43) + (m_12*m_33*m_41) + (m_13*m_31*m_42)
		- (m_11*m_33*m_42) - (m_12*m_31*m_43) - (m_13*m_32*m_41)) / det;
	t43 = ((m_11*m_23*m_42) + (m_12*m_21*m_43) + (m_13*m_22*m_41)
		- (m_11*m_22*m_43) - (m_12*m_23*m_41) - (m_13*m_21*m_42)) / det;
	t44 = ((m_11*m_22*m_33) + (m_12*m_23*m_31) + (m_13*m_21*m_32)
		- (m_11*m_23*m_32) - (m_12*m_21*m_33) - (m_13*m_22*m_31)) / det;

	m_11 = t11;
	m_12 = t12;
	m_13 = t13;
	m_14 = t14;
	m_21 = t21;
	m_22 = t22;
	m_23 = t23;
	m_24 = t24;
	m_31 = t31;
	m_32 = t32;
	m_33 = t33;
	m_34 = t34;
	m_41 = t41;
	m_42 = t42;
	m_43 = t43;
	m_44 = t44;
}

Matrix Matrix::GetInverse() const
{
	float det = 0;
	det = (m_11*m_22*m_33*m_44) + (m_11*m_23*m_34*m_42) + (m_11*m_24*m_32*m_43)
		+ (m_12*m_21*m_34*m_43) + (m_12*m_23*m_31*m_44) + (m_12*m_24*m_33*m_41)
		+ (m_13*m_21*m_32*m_44) + (m_13*m_22*m_34*m_41) + (m_13*m_24*m_31*m_42)
		+ (m_14*m_21*m_33*m_42) + (m_14*m_22*m_31*m_43) + (m_14*m_23*m_32*m_41)
		- (m_11*m_22*m_34*m_43) - (m_11*m_23*m_32*m_44) - (m_11*m_24*m_33*m_42)
		- (m_12*m_21*m_33*m_44) - (m_12*m_23*m_34*m_41) - (m_12*m_24*m_31*m_43)
		- (m_13*m_21*m_34*m_42) - (m_13*m_22*m_31*m_44) - (m_13*m_24*m_32*m_41)
		- (m_14*m_21*m_32*m_43) - (m_14*m_22*m_33*m_41) - (m_14*m_23*m_31*m_42);



	float
		t11, t12, t13, t14,
		t21, t22, t23, t24,
		t31, t32, t33, t34,
		t41, t42, t43, t44;

	t11 = ((m_22*m_33*m_44) + (m_23*m_34*m_42) + (m_24*m_32*m_43)
		- (m_22*m_34*m_43) - (m_23*m_32*m_44) - (m_24*m_33*m_42)) / det;
	t12 = ((m_12*m_34*m_43) + (m_13*m_32*m_44) + (m_14*m_33*m_42)
		- (m_12*m_33*m_44) - (m_13*m_34*m_42) - (m_14*m_32*m_43)) / det;
	t13 = ((m_12*m_23*m_44) + (m_13*m_24*m_42) + (m_14*m_22*m_43)
		- (m_12*m_24*m_43) - (m_13*m_22*m_44) - (m_14*m_23*m_42)) / det;
	t14 = ((m_12*m_24*m_33) + (m_13*m_22*m_34) + (m_14*m_23*m_32)
		- (m_12*m_23*m_34) - (m_13*m_24*m_32) - (m_14*m_22*m_33)) / det;
	t21 = ((m_21*m_34*m_43) + (m_23*m_31*m_44) + (m_24*m_33*m_41)
		- (m_21*m_33*m_44) - (m_23*m_34*m_41) - (m_24*m_31*m_43)) / det;
	t22 = ((m_11*m_33*m_44) + (m_13*m_34*m_41) + (m_14*m_31*m_43)
		- (m_11*m_34*m_43) - (m_13*m_31*m_44) - (m_14*m_33*m_41)) / det;
	t23 = ((m_11*m_24*m_43) + (m_13*m_21*m_44) + (m_14*m_23*m_41)
		- (m_11*m_23*m_44) - (m_13*m_24*m_41) - (m_14*m_21*m_43)) / det;
	t24 = ((m_11*m_23*m_34) + (m_13*m_24*m_31) + (m_14*m_21*m_33)
		- (m_11*m_24*m_33) - (m_13*m_21*m_34) - (m_14*m_23*m_31)) / det;
	t31 = ((m_21*m_32*m_44) + (m_22*m_34*m_41) + (m_24*m_31*m_42)
		- (m_21*m_34*m_42) - (m_22*m_31*m_44) - (m_24*m_32*m_41)) / det;
	t32 = ((m_11*m_34*m_42) + (m_12*m_31*m_44) + (m_14*m_32*m_41)
		- (m_11*m_32*m_44) - (m_12*m_34*m_41) - (m_14*m_31*m_42)) / det;
	t33 = ((m_11*m_22*m_44) + (m_12*m_24*m_41) + (m_14*m_21*m_42)
		- (m_11*m_24*m_42) - (m_12*m_21*m_44) - (m_14*m_22*m_41)) / det;
	t34 = ((m_11*m_24*m_32) + (m_12*m_21*m_34) + (m_14*m_22*m_31)
		- (m_11*m_22*m_34) - (m_12*m_24*m_31) - (m_14*m_21*m_32)) / det;
	t41 = ((m_21*m_33*m_42) + (m_22*m_31*m_43) + (m_23*m_32*m_41)
		- (m_21*m_32*m_43) - (m_22*m_33*m_41) - (m_23*m_31*m_42)) / det;
	t42 = ((m_11*m_32*m_43) + (m_12*m_33*m_41) + (m_13*m_31*m_42)
		- (m_11*m_33*m_42) - (m_12*m_31*m_43) - (m_13*m_32*m_41)) / det;
	t43 = ((m_11*m_23*m_42) + (m_12*m_21*m_43) + (m_13*m_22*m_41)
		- (m_11*m_22*m_43) - (m_12*m_23*m_41) - (m_13*m_21*m_42)) / det;
	t44 = ((m_11*m_22*m_33) + (m_12*m_23*m_31) + (m_13*m_21*m_32)
		- (m_11*m_23*m_32) - (m_12*m_21*m_33) - (m_13*m_22*m_31)) / det;

	Matrix o_Matrix(t11, t12, t13, t14,
		t21, t22, t23, t24,
		t31, t32, t33, t34,
		t41, t42, t43, t44);
	return o_Matrix;
}

void Matrix::Transpose()
{
	float
		t11, t12, t13, t14,
		t21, t22, t23, t24,
		t31, t32, t33, t34,
		t41, t42, t43, t44;

	t11 = m_11;
	t12 = m_21;
	t13 = m_31;
	t14 = m_41;
	t21 = m_12;
	t22 = m_22;
	t23 = m_32;
	t24 = m_42;
	t31 = m_13;
	t32 = m_23;
	t33 = m_33;
	t34 = m_43;
	t41 = m_14;
	t42 = m_24;
	t43 = m_34;
	t44 = m_44;

	m_11 = t11;
	m_12 = t12;
	m_13 = t13;
	m_14 = t14;
	m_21 = t21;
	m_22 = t22;
	m_23 = t23;
	m_24 = t24;
	m_31 = t31;
	m_32 = t32;
	m_33 = t33;
	m_34 = t34;
	m_41 = t41;
	m_42 = t42;
	m_43 = t43;
	m_44 = t44;
}

Matrix Matrix::GetTranspose() const
{
	float
		t11, t12, t13, t14,
		t21, t22, t23, t24,
		t31, t32, t33, t34,
		t41, t42, t43, t44;

	t11 = m_11;
	t12 = m_21;
	t13 = m_31;
	t14 = m_41;
	t21 = m_12;
	t22 = m_22;
	t23 = m_32;
	t24 = m_42;
	t31 = m_13;
	t32 = m_23;
	t33 = m_33;
	t34 = m_43;
	t41 = m_14;
	t42 = m_24;
	t43 = m_32;
	t44 = m_44;

	Matrix o_Matrix(t11, t12, t13, t14,
		t21, t22, t23, t24,
		t31, t32, t33, t34,
		t41, t42, t43, t44);

	return o_Matrix;
}

Matrix Matrix::operator*(const Matrix & i_other) const
{
	float
		t11, t12, t13, t14,
		t21, t22, t23, t24,
		t31, t32, t33, t34,
		t41, t42, t43, t44;

	t11 = (m_11*i_other.m_11) + (m_12*i_other.m_21) + (m_13*i_other.m_31) + (m_14*i_other.m_41);
	t12 = (m_11*i_other.m_12) + (m_12*i_other.m_22) + (m_13*i_other.m_32) + (m_14*i_other.m_42);
	t13 = (m_11*i_other.m_13) + (m_12*i_other.m_23) + (m_13*i_other.m_33) + (m_14*i_other.m_43);
	t14 = (m_11*i_other.m_14) + (m_12*i_other.m_24) + (m_13*i_other.m_34) + (m_14*i_other.m_44);
	t21 = (m_21*i_other.m_11) + (m_22*i_other.m_21) + (m_23*i_other.m_31) + (m_24*i_other.m_41);
	t22 = (m_21*i_other.m_12) + (m_22*i_other.m_22) + (m_23*i_other.m_32) + (m_24*i_other.m_42);
	t23 = (m_21*i_other.m_13) + (m_22*i_other.m_23) + (m_23*i_other.m_33) + (m_24*i_other.m_43);
	t24 = (m_21*i_other.m_14) + (m_22*i_other.m_24) + (m_23*i_other.m_34) + (m_24*i_other.m_44);
	t31 = (m_31*i_other.m_11) + (m_32*i_other.m_21) + (m_33*i_other.m_31) + (m_34*i_other.m_41);
	t32 = (m_31*i_other.m_12) + (m_32*i_other.m_22) + (m_33*i_other.m_32) + (m_34*i_other.m_42);
	t33 = (m_31*i_other.m_13) + (m_32*i_other.m_23) + (m_33*i_other.m_33) + (m_34*i_other.m_43);
	t34 = (m_31*i_other.m_14) + (m_32*i_other.m_24) + (m_33*i_other.m_34) + (m_34*i_other.m_44);
	t41 = (m_41*i_other.m_11) + (m_42*i_other.m_21) + (m_43*i_other.m_31) + (m_44*i_other.m_41);
	t42 = (m_41*i_other.m_12) + (m_42*i_other.m_22) + (m_43*i_other.m_32) + (m_44*i_other.m_42);
	t43 = (m_41*i_other.m_13) + (m_42*i_other.m_23) + (m_43*i_other.m_33) + (m_44*i_other.m_43);
	t44 = (m_41*i_other.m_14) + (m_42*i_other.m_24) + (m_43*i_other.m_34) + (m_44*i_other.m_44);

	Matrix o_Matrix(t11, t12, t13, t14,
		t21, t22, t23, t24,
		t31, t32, t33, t34,
		t41, t42, t43, t44);

	return o_Matrix;

}
Vector4 Matrix::operator*(const Vector4 & i_Vector)const
{
	float
		v11,
		v21,
		v31,
		v41; // Treating Vector 4 as a column vector

	v11 = i_Vector.X();
	v21 = i_Vector.Y();
	v31 = i_Vector.Z();
	v41 = i_Vector.W();

	return Vector4((m_11*v11 + m_12*v21 + m_13*v31 + m_14*v41), (m_21*v11 + m_22*v21 + m_23*v31 + m_24*v41), (m_31*v11 + m_32*v21 + m_33*v31 + m_34*v41), (m_41*v11 + m_42*v21 + m_43*v31 + m_44*v41));
}

Vector4 Matrix::MultiplyRight(const Vector4 & i_Vector) const
{
	float
		v11,
		v21,
		v31,
		v41; // Treating Vector 4 as a column vector

	v11 = i_Vector.X();
	v21 = i_Vector.Y();
	v31 = i_Vector.Z();
	v41 = i_Vector.W();

	return Vector4((m_11*v11 + m_12*v21 + m_13*v31 + m_14*v41), (m_21*v11 + m_22*v21 + m_23*v31 + m_24*v41), (m_31*v11 + m_32*v21 + m_33*v31 + m_34*v41), (m_41*v11 + m_42*v21 + m_43*v31 + m_44*v41));

}

Vector4 Matrix::MultiplyLeft(const Vector4 & i_Vector) const
{
	float
		v11,
		v12,
		v13,
		v14; // Treating Vector 4 as a row vector

	v11 = i_Vector.X();
	v12 = i_Vector.Y();
	v13 = i_Vector.Z();
	v14 = i_Vector.W();

	return Vector4((v11*m_11 + v12*m_21 + v13*m_31 + v14*m_41), (v11*m_12 + v12*m_22 + v13*m_32 + v14*m_42), (v11*m_13 + v12*m_23 + v13*m_33 + v14*m_43), (v11*m_14 + v12*m_24 + v13*m_34 + v14*m_44));
}

bool Matrix::operator==(const Matrix & i_rhs) const
{
	if (m_11 == i_rhs.m_11 &&
		m_12 == i_rhs.m_12 &&
		m_13 == i_rhs.m_13 &&
		m_14 == i_rhs.m_14 &&
		m_21 == i_rhs.m_21 &&
		m_22 == i_rhs.m_22 &&
		m_23 == i_rhs.m_23 &&
		m_24 == i_rhs.m_24 &&
		m_31 == i_rhs.m_31 &&
		m_32 == i_rhs.m_32 &&
		m_33 == i_rhs.m_33 &&
		m_34 == i_rhs.m_34 &&
		m_41 == i_rhs.m_41 &&
		m_42 == i_rhs.m_42 &&
		m_43 == i_rhs.m_43 &&
		m_44 == i_rhs.m_44)
		return true;
	else
		return false;
}

//Matrix Matrix::Multiply(const Matrix & i_other, Matrix & o_out) const
//{
//
//}