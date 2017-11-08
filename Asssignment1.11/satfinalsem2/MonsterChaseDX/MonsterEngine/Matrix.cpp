#include "Matrix.h"
#include "Assert.h"

void Matrix::SetToIdentity()
{
	m_11 = 1.0f; 
	m_22 = 1.0f; 
	m_33 = 1.0f; 
	m_44 = 1.0f;
	m_12 = m_13 = m_14 = m_21 = m_23 = m_24 = m_31 = m_32 = m_34 = m_41 = m_42 = m_43 = 0.0f;
}

void Matrix::SetToXRotation(float i_RotationDegrees)
{
	float PI = 3.14159265f;
	m_12 = m_13 = m_14 = m_21 = m_24 = m_31 = m_34 = m_41 = m_42 = m_43 = 0.0f;
	m_11 = m_44 = 1.0f;
	m_22 = cos(i_RotationDegrees*PI / 180);
	m_23 = sin(i_RotationDegrees*PI / 180);
	m_32 = -sin(i_RotationDegrees*PI / 180);
	m_33 = cos(i_RotationDegrees*PI / 180);
}

void Matrix::SetToYRotation(float i_RotationDegrees)
{
	float PI = 3.14159265f;
	m_11 = m_33 = cos(i_RotationDegrees*PI / 180);
	m_12 = m_14 = m_21 = m_23 = m_24 = m_32 = m_34 = m_41 = m_42 = m_43 = 0.0f;
	m_13 = -sin(i_RotationDegrees*PI / 180);
	m_22 = 1.0f;
	m_44 = 1.0f;
	m_31 = sin(i_RotationDegrees*PI / 180);
}

void Matrix::SetToZRotation(float i_RotationDegrees)
{
	float PI = 3.14159265f;
	m_13 = m_14 = m_23 = m_24 = m_31 = m_32 = m_34 = m_41 = m_42 = m_43 = 0.0f;
	m_33 = m_44 = 1.0f;
	m_11 = m_22 = cos(i_RotationDegrees*PI / 180);
	m_12 = m_21 = sin(i_RotationDegrees*PI / 180);
}

void Matrix::SetToTranslation(float i_transX, float i_transY, float i_transZ)
{
	m_11 = 1.0f;
	m_22 = 1.0f;
	m_33 = 1.0f;
	m_44 = 1.0f;
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

Matrix Matrix::CreateXRotation(float i_RotationDegrees)
{
	Matrix Op_Mat;
	float PI = 3.14159265f;
	Op_Mat.m_12 = Op_Mat.m_13 = Op_Mat.m_14 = Op_Mat.m_21 = Op_Mat.m_24 = Op_Mat.m_31 = Op_Mat.m_34 = Op_Mat.m_41 = Op_Mat.m_42 = Op_Mat.m_43 = 0.0f;
	Op_Mat.m_11 = Op_Mat.m_44 = 1.0f;
	Op_Mat.m_22 = cos(i_RotationDegrees*PI / 180);
	Op_Mat.m_23 = -sin(i_RotationDegrees*PI / 180);
	Op_Mat.m_32 = sin(i_RotationDegrees*PI / 180);
	Op_Mat.m_33 = cos(i_RotationDegrees*PI / 180);

	return Op_Mat;
}

Matrix Matrix::CreateYRotation(float i_RotationDegrees)
{
	Matrix Op_Mat;
	float PI = 3.14159265f;
	Op_Mat.m_12 = Op_Mat.m_14 = Op_Mat.m_21 = Op_Mat.m_23 = Op_Mat.m_24 = Op_Mat.m_32 = Op_Mat.m_34 = Op_Mat.m_41 = Op_Mat.m_42 = Op_Mat.m_43 = 0.0f;
	Op_Mat.m_22 = Op_Mat.m_44 = 1.0f;
	Op_Mat.m_11 = Op_Mat.m_33 = cos(i_RotationDegrees*PI / 180);
	Op_Mat.m_13 = sin(i_RotationDegrees*PI / 180);
	Op_Mat.m_31 = -sin(i_RotationDegrees*PI / 180);

	return Op_Mat;
}

Matrix Matrix::CreateZRotation(float i_RotationDegrees)
{
	Matrix Op_Mat;
	float PI = 3.14159265f;
	Op_Mat.m_13 = Op_Mat.m_14 = Op_Mat.m_23 = Op_Mat.m_24 = Op_Mat.m_31 = Op_Mat.m_32 = Op_Mat.m_34 = Op_Mat.m_41 = Op_Mat.m_42 = Op_Mat.m_43 = 0.0f;
	Op_Mat.m_33 = Op_Mat.m_44 = 1.0f;
	Op_Mat.m_11 = Op_Mat.m_22 = cos(i_RotationDegrees*PI / 180);
	Op_Mat.m_12 = sin(i_RotationDegrees*PI / 180);
	Op_Mat.m_21 = -sin(i_RotationDegrees*PI / 180);

	return Op_Mat;
}

Matrix Matrix::CreateTransformationToWorld(Vector3 i_LocalCoords, Matrix i_Rot)
{
	Matrix m_Translation = Matrix::CreateTranslation(i_LocalCoords.X(), i_LocalCoords.Y(), i_LocalCoords.Z());
	return (m_Translation*i_Rot);
}

Matrix Matrix::CreateTransformationToLocal(Vector3 i_LocalCoords, Matrix i_Rot)
{
	Matrix m_Translation = Matrix::CreateTranslation(i_LocalCoords.X(), i_LocalCoords.Y(), i_LocalCoords.Z());
	Matrix o_Mat = m_Translation*i_Rot;
	o_Mat.Invert();
	return o_Mat;
}

Matrix Matrix::CreateTranslation(float i_transX, float i_transY, float i_transZ)
{
	Matrix Op_Mat;

	Op_Mat.m_11 = Op_Mat.m_22 = Op_Mat.m_33 = Op_Mat.m_44 = 1.0f;
	Op_Mat.m_12 = Op_Mat.m_13 = Op_Mat.m_21 = Op_Mat.m_23 = Op_Mat.m_31 = Op_Mat.m_32 = Op_Mat.m_41 = Op_Mat.m_42 = Op_Mat.m_43 = 0.0f;
	Op_Mat.m_14 = i_transX;
	Op_Mat.m_24 = i_transY;
	Op_Mat.m_34 = i_transZ;

	return Op_Mat;
}

Matrix Matrix::CreateScale(float i_scaleX, float i_scaleY, float i_scaleZ)
{
	Matrix Op_Mat;

	Op_Mat.m_44 = 1.0f;
	Op_Mat.m_12 = Op_Mat.m_13 = Op_Mat.m_14 = Op_Mat.m_21 = Op_Mat.m_23 = Op_Mat.m_24 = Op_Mat.m_31 = Op_Mat.m_32 = Op_Mat.m_34 = Op_Mat.m_41 = Op_Mat.m_42 = Op_Mat.m_43 = 0.0f;
	Op_Mat.m_11 = i_scaleX;
	Op_Mat.m_22 = i_scaleY;
	Op_Mat.m_33 = i_scaleZ;

	return Op_Mat;
}

void Matrix::Invert()
{
	float d_mat = 0;
	d_mat = (m_11*m_22*m_33*m_44) + (m_11*m_23*m_34*m_42) + (m_11*m_24*m_32*m_43)
		+ (m_12*m_21*m_34*m_43) + (m_12*m_23*m_31*m_44) + (m_12*m_24*m_33*m_41)
		+ (m_13*m_21*m_32*m_44) + (m_13*m_22*m_34*m_41) + (m_13*m_24*m_31*m_42)
		+ (m_14*m_21*m_33*m_42) + (m_14*m_22*m_31*m_43) + (m_14*m_23*m_32*m_41)
		- (m_11*m_22*m_34*m_43) - (m_11*m_23*m_32*m_44) - (m_11*m_24*m_33*m_42)
		- (m_12*m_21*m_33*m_44) - (m_12*m_23*m_34*m_41) - (m_12*m_24*m_31*m_43)
		- (m_13*m_21*m_34*m_42) - (m_13*m_22*m_31*m_44) - (m_13*m_24*m_32*m_41)
		- (m_14*m_21*m_32*m_43) - (m_14*m_22*m_33*m_41) - (m_14*m_23*m_31*m_42);

	MessagedAssert(d_mat, "Check Inverse"); 

	float
		t11, t12, t13, t14,
		t21, t22, t23, t24,
		t31, t32, t33, t34,
		t41, t42, t43, t44;

	t11 = ((m_22*m_33*m_44) + (m_23*m_34*m_42) + (m_24*m_32*m_43)
		- (m_22*m_34*m_43) - (m_23*m_32*m_44) - (m_24*m_33*m_42)) / d_mat;
	t12 = ((m_12*m_34*m_43) + (m_13*m_32*m_44) + (m_14*m_33*m_42)
		- (m_12*m_33*m_44) - (m_13*m_34*m_42) - (m_14*m_32*m_43)) / d_mat;
	t13 = ((m_12*m_23*m_44) + (m_13*m_24*m_42) + (m_14*m_22*m_43)
		- (m_12*m_24*m_43) - (m_13*m_22*m_44) - (m_14*m_23*m_42)) / d_mat;
	t14 = ((m_12*m_24*m_33) + (m_13*m_22*m_34) + (m_14*m_23*m_32)
		- (m_12*m_23*m_34) - (m_13*m_24*m_32) - (m_14*m_22*m_33)) / d_mat;
	t21 = ((m_21*m_34*m_43) + (m_23*m_31*m_44) + (m_24*m_33*m_41)
		- (m_21*m_33*m_44) - (m_23*m_34*m_41) - (m_24*m_31*m_43)) / d_mat;
	t22 = ((m_11*m_33*m_44) + (m_13*m_34*m_41) + (m_14*m_31*m_43)
		- (m_11*m_34*m_43) - (m_13*m_31*m_44) - (m_14*m_33*m_41)) / d_mat;
	t23 = ((m_11*m_24*m_43) + (m_13*m_21*m_44) + (m_14*m_23*m_41)
		- (m_11*m_23*m_44) - (m_13*m_24*m_41) - (m_14*m_21*m_43)) / d_mat;
	t24 = ((m_11*m_23*m_34) + (m_13*m_24*m_31) + (m_14*m_21*m_33)
		- (m_11*m_24*m_33) - (m_13*m_21*m_34) - (m_14*m_23*m_31)) / d_mat;
	t31 = ((m_21*m_32*m_44) + (m_22*m_34*m_41) + (m_24*m_31*m_42)
		- (m_21*m_34*m_42) - (m_22*m_31*m_44) - (m_24*m_32*m_41)) / d_mat;
	t32 = ((m_11*m_34*m_42) + (m_12*m_31*m_44) + (m_14*m_32*m_41)
		- (m_11*m_32*m_44) - (m_12*m_34*m_41) - (m_14*m_31*m_42)) / d_mat;
	t33 = ((m_11*m_22*m_44) + (m_12*m_24*m_41) + (m_14*m_21*m_42)
		- (m_11*m_24*m_42) - (m_12*m_21*m_44) - (m_14*m_22*m_41)) / d_mat;
	t34 = ((m_11*m_24*m_32) + (m_12*m_21*m_34) + (m_14*m_22*m_31)
		- (m_11*m_22*m_34) - (m_12*m_24*m_31) - (m_14*m_21*m_32)) / d_mat;
	t41 = ((m_21*m_33*m_42) + (m_22*m_31*m_43) + (m_23*m_32*m_41)
		- (m_21*m_32*m_43) - (m_22*m_33*m_41) - (m_23*m_31*m_42)) / d_mat;
	t42 = ((m_11*m_32*m_43) + (m_12*m_33*m_41) + (m_13*m_31*m_42)
		- (m_11*m_33*m_42) - (m_12*m_31*m_43) - (m_13*m_32*m_41)) / d_mat;
	t43 = ((m_11*m_23*m_42) + (m_12*m_21*m_43) + (m_13*m_22*m_41)
		- (m_11*m_22*m_43) - (m_12*m_23*m_41) - (m_13*m_21*m_42)) / d_mat;
	t44 = ((m_11*m_22*m_33) + (m_12*m_23*m_31) + (m_13*m_21*m_32)
		- (m_11*m_23*m_32) - (m_12*m_21*m_33) - (m_13*m_22*m_31)) / d_mat;

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
	float d_mat = 0;
	d_mat = (m_11*m_22*m_33*m_44) + (m_11*m_23*m_34*m_42) + (m_11*m_24*m_32*m_43)
		+ (m_12*m_21*m_34*m_43) + (m_12*m_23*m_31*m_44) + (m_12*m_24*m_33*m_41)
		+ (m_13*m_21*m_32*m_44) + (m_13*m_22*m_34*m_41) + (m_13*m_24*m_31*m_42)
		+ (m_14*m_21*m_33*m_42) + (m_14*m_22*m_31*m_43) + (m_14*m_23*m_32*m_41)
		- (m_11*m_22*m_34*m_43) - (m_11*m_23*m_32*m_44) - (m_11*m_24*m_33*m_42)
		- (m_12*m_21*m_33*m_44) - (m_12*m_23*m_34*m_41) - (m_12*m_24*m_31*m_43)
		- (m_13*m_21*m_34*m_42) - (m_13*m_22*m_31*m_44) - (m_13*m_24*m_32*m_41)
		- (m_14*m_21*m_32*m_43) - (m_14*m_22*m_33*m_41) - (m_14*m_23*m_31*m_42);

	MessagedAssert(d_mat, "check inverse"); 

	float
		t11, t12, t13, t14,
		t21, t22, t23, t24,
		t31, t32, t33, t34,
		t41, t42, t43, t44;

	t11 = ((m_22*m_33*m_44) + (m_23*m_34*m_42) + (m_24*m_32*m_43)
		- (m_22*m_34*m_43) - (m_23*m_32*m_44) - (m_24*m_33*m_42)) / d_mat;
	t12 = ((m_12*m_34*m_43) + (m_13*m_32*m_44) + (m_14*m_33*m_42)
		- (m_12*m_33*m_44) - (m_13*m_34*m_42) - (m_14*m_32*m_43)) / d_mat;
	t13 = ((m_12*m_23*m_44) + (m_13*m_24*m_42) + (m_14*m_22*m_43)
		- (m_12*m_24*m_43) - (m_13*m_22*m_44) - (m_14*m_23*m_42)) / d_mat;
	t14 = ((m_12*m_24*m_33) + (m_13*m_22*m_34) + (m_14*m_23*m_32)
		- (m_12*m_23*m_34) - (m_13*m_24*m_32) - (m_14*m_22*m_33)) / d_mat;
	t21 = ((m_21*m_34*m_43) + (m_23*m_31*m_44) + (m_24*m_33*m_41)
		- (m_21*m_33*m_44) - (m_23*m_34*m_41) - (m_24*m_31*m_43)) / d_mat;
	t22 = ((m_11*m_33*m_44) + (m_13*m_34*m_41) + (m_14*m_31*m_43)
		- (m_11*m_34*m_43) - (m_13*m_31*m_44) - (m_14*m_33*m_41)) / d_mat;
	t23 = ((m_11*m_24*m_43) + (m_13*m_21*m_44) + (m_14*m_23*m_41)
		- (m_11*m_23*m_44) - (m_13*m_24*m_41) - (m_14*m_21*m_43)) / d_mat;
	t24 = ((m_11*m_23*m_34) + (m_13*m_24*m_31) + (m_14*m_21*m_33)
		- (m_11*m_24*m_33) - (m_13*m_21*m_34) - (m_14*m_23*m_31)) / d_mat;
	t31 = ((m_21*m_32*m_44) + (m_22*m_34*m_41) + (m_24*m_31*m_42)
		- (m_21*m_34*m_42) - (m_22*m_31*m_44) - (m_24*m_32*m_41)) / d_mat;
	t32 = ((m_11*m_34*m_42) + (m_12*m_31*m_44) + (m_14*m_32*m_41)
		- (m_11*m_32*m_44) - (m_12*m_34*m_41) - (m_14*m_31*m_42)) / d_mat;
	t33 = ((m_11*m_22*m_44) + (m_12*m_24*m_41) + (m_14*m_21*m_42)
		- (m_11*m_24*m_42) - (m_12*m_21*m_44) - (m_14*m_22*m_41)) / d_mat;
	t34 = ((m_11*m_24*m_32) + (m_12*m_21*m_34) + (m_14*m_22*m_31)
		- (m_11*m_22*m_34) - (m_12*m_24*m_31) - (m_14*m_21*m_32)) / d_mat;
	t41 = ((m_21*m_33*m_42) + (m_22*m_31*m_43) + (m_23*m_32*m_41)
		- (m_21*m_32*m_43) - (m_22*m_33*m_41) - (m_23*m_31*m_42)) / d_mat;
	t42 = ((m_11*m_32*m_43) + (m_12*m_33*m_41) + (m_13*m_31*m_42)
		- (m_11*m_33*m_42) - (m_12*m_31*m_43) - (m_13*m_32*m_41)) / d_mat;
	t43 = ((m_11*m_23*m_42) + (m_12*m_21*m_43) + (m_13*m_22*m_41)
		- (m_11*m_22*m_43) - (m_12*m_23*m_41) - (m_13*m_21*m_42)) / d_mat;
	t44 = ((m_11*m_22*m_33) + (m_12*m_23*m_31) + (m_13*m_21*m_32)
		- (m_11*m_23*m_32) - (m_12*m_21*m_33) - (m_13*m_22*m_31)) / d_mat;

	Matrix Op_Mat(t11, t12, t13, t14,
		t21, t22, t23, t24,
		t31, t32, t33, t34,
		t41, t42, t43, t44);
	return Op_Mat;
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
	float t_11, t_12, t_13, t_14,t_21, t_22, t_23, t_24,t_31, t_32, t_33, t_34,	t_41, t_42, t_43, t_44;

	t_11 = m_11;
	t_12 = m_21;
	t_13 = m_31;
	t_14 = m_41;
	t_21 = m_12;
	t_22 = m_22;
	t_23 = m_32;
	t_24 = m_42;
	t_31 = m_13;
	t_32 = m_23;
	t_33 = m_33;
	t_34 = m_43;
	t_41 = m_14;
	t_42 = m_24;
	t_43 = m_32;
	t_44 = m_44;

	Matrix Op_Mat(t_11, t_12, t_13, t_14,
		t_21, t_22, t_23, t_24,
		t_31, t_32, t_33, t_34,
		t_41, t_42, t_43, t_44);

	return Op_Mat;
}

Matrix Matrix::operator*(const Matrix & i_other) const
{
	float t_11, t_12, t_13, t_14,t_21, t_22, t_23, t_24,t_31, t_32, t_33, t_34,	t_41, t_42, t_43, t_44;

	t_11 = (m_11*i_other.m_11) + (m_12*i_other.m_21) + (m_13*i_other.m_31) + (m_14*i_other.m_41);
	t_12 = (m_11*i_other.m_12) + (m_12*i_other.m_22) + (m_13*i_other.m_32) + (m_14*i_other.m_42);
	t_13 = (m_11*i_other.m_13) + (m_12*i_other.m_23) + (m_13*i_other.m_33) + (m_14*i_other.m_43);
	t_14 = (m_11*i_other.m_14) + (m_12*i_other.m_24) + (m_13*i_other.m_34) + (m_14*i_other.m_44);
	t_21 = (m_21*i_other.m_11) + (m_22*i_other.m_21) + (m_23*i_other.m_31) + (m_24*i_other.m_41);
	t_22 = (m_21*i_other.m_12) + (m_22*i_other.m_22) + (m_23*i_other.m_32) + (m_24*i_other.m_42);
	t_23 = (m_21*i_other.m_13) + (m_22*i_other.m_23) + (m_23*i_other.m_33) + (m_24*i_other.m_43);
	t_24 = (m_21*i_other.m_14) + (m_22*i_other.m_24) + (m_23*i_other.m_34) + (m_24*i_other.m_44);
	t_31 = (m_31*i_other.m_11) + (m_32*i_other.m_21) + (m_33*i_other.m_31) + (m_34*i_other.m_41);
	t_32 = (m_31*i_other.m_12) + (m_32*i_other.m_22) + (m_33*i_other.m_32) + (m_34*i_other.m_42);
	t_33 = (m_31*i_other.m_13) + (m_32*i_other.m_23) + (m_33*i_other.m_33) + (m_34*i_other.m_43);
	t_34 = (m_31*i_other.m_14) + (m_32*i_other.m_24) + (m_33*i_other.m_34) + (m_34*i_other.m_44);
	t_41 = (m_41*i_other.m_11) + (m_42*i_other.m_21) + (m_43*i_other.m_31) + (m_44*i_other.m_41);
	t_42 = (m_41*i_other.m_12) + (m_42*i_other.m_22) + (m_43*i_other.m_32) + (m_44*i_other.m_42);
	t_43 = (m_41*i_other.m_13) + (m_42*i_other.m_23) + (m_43*i_other.m_33) + (m_44*i_other.m_43);
	t_44 = (m_41*i_other.m_14) + (m_42*i_other.m_24) + (m_43*i_other.m_34) + (m_44*i_other.m_44);

	Matrix Op_Mat(t_11, t_12, t_13, t_14, t_21, t_22, t_23, t_24, t_31, t_32, t_33, t_34, t_41, t_42, t_43, t_44);

	return Op_Mat;

}
Vector4 Matrix::operator*(const Vector4 & i_Vector)const
{
	float
		v_11,
		v_21,
		v_31,
		v_41; // Treating Vector 4 as a column vector

	v_11 = i_Vector.X();
	v_21 = i_Vector.Y();
	v_31 = i_Vector.Z();
	v_41 = i_Vector.W();

	return Vector4((m_11*v_11 + m_12*v_21 + m_13*v_31 + m_14*v_41), (m_21*v_11 + m_22*v_21 + m_23*v_31 + m_24*v_41), (m_31*v_11 + m_32*v_21 + m_33*v_31 + m_34*v_41), (m_41*v_11 + m_42*v_21 + m_43*v_31 + m_44*v_41));
}

Vector4 Matrix::MultiplyRight(const Vector4 & i_Vector) const
{
	float
		mr_11,mr_21,mr_31,mr_41; // Treating Vector 4 as a column vector

	mr_11 = i_Vector.X();
	mr_21 = i_Vector.Y();
	mr_31 = i_Vector.Z();
	mr_41 = i_Vector.W();

	return Vector4((m_11*mr_11 + m_12*mr_21 + m_13*mr_31 + m_14*mr_41), (m_21*mr_11 + m_22*mr_21 + m_23*mr_31 + m_24*mr_41), (m_31*mr_11 + m_32*mr_21 + m_33*mr_31 + m_34*mr_41), (m_41*mr_11 + m_42*mr_21 + m_43*mr_31 + m_44*mr_41));

}

Vector4 Matrix::MultiplyLeft(const Vector4 & i_Vector) const
{
	float ml_11,ml_12,ml_13,ml_14; // Treating Vector 4 as a row vector

	ml_11 = i_Vector.X();
	ml_12 = i_Vector.Y();
	ml_13 = i_Vector.Z();
	ml_14 = i_Vector.W();

	return Vector4((ml_11*m_11 + ml_12*m_21 + ml_13*m_31 + ml_14*m_41), (ml_11*m_12 + ml_12*m_22 + ml_13*m_32 + ml_14*m_42), (ml_11*m_13 + ml_12*m_23 + ml_13*m_33 + ml_14*m_43), (ml_11*m_14 + ml_12*m_24 + ml_13*m_34 + ml_14*m_44));
}

bool Matrix::operator==(const Matrix & i_rhs) const
{
	if (m_11 == i_rhs.m_11 && m_12 == i_rhs.m_12 && m_13 == i_rhs.m_13 && m_14 == i_rhs.m_14 &&
		m_21 == i_rhs.m_21 && m_22 == i_rhs.m_22 &&	m_23 == i_rhs.m_23 && m_24 == i_rhs.m_24 &&
		m_31 == i_rhs.m_31 && m_32 == i_rhs.m_32 && m_33 == i_rhs.m_33 && m_34 == i_rhs.m_34 &&
		m_41 == i_rhs.m_41 && m_42 == i_rhs.m_42 &&	m_43 == i_rhs.m_43 && m_44 == i_rhs.m_44)
		return true;
	else
		return false;
}

