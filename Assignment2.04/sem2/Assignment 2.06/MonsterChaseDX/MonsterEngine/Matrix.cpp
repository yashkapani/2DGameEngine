#include "Matrix.h"

Matrix::Matrix()
{
	for (int i = 0; i < 4;i++)
	for (int j = 0; j < 4; j++)
		mat[i][j] = 0; 
}

void Matrix::Identity()
{
	for (int i = 0; i < 4; i++)
		mat[i][i] = 0;
}

void Matrix::Transpose()
{
	float temp[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[i][j] = mat[j][i];
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[i][j] = temp[j][i];
		}
	}
}
void Matrix::Inverse()
{ 
	Matrix temp;
	float det;
	det = (mat[0][0] * mat[1][1] * mat[2][2] * mat[3][3]) + (mat[0][0] * mat[1][2] * mat[2][3] * mat[3][1]) + (mat[0][0] * mat[1][3] * mat[2][1] * mat[3][2]) +
		  (mat[0][1] * mat[1][0] * mat[2][3] * mat[3][2]) + (mat[0][1] * mat[1][2] * mat[2][0] * mat[3][3]) + (mat[0][1] * mat[1][3] * mat[2][3] * mat[3][0]) +
		  (mat[0][2] * mat[1][0] * mat[2][1] * mat[3][3]) + (mat[0][2] * mat[1][1] * mat[2][3] * mat[3][0]) + (mat[0][2] * mat[1][3] * mat[2][1] * mat[3][1]) +
		  (mat[0][3] * mat[1][0] * mat[2][2] * mat[3][1]) + (mat[0][0] * mat[1][2] * mat[2][1] * mat[3][3]) + (mat[0][0] * mat[1][3] * mat[2][2] * mat[3][1]) -
		  (mat[0][0] * mat[1][1] * mat[2][3] * mat[3][2]) + (mat[0][1] * mat[1][2] * mat[2][3] * mat[3][0]) + (mat[0][1] * mat[1][3] * mat[2][0] * mat[3][2]) -
		   (mat[0][1] * mat[1][0] * mat[2][2] * mat[3][3]) + (mat[0][1] * mat[1][2] * mat[2][3] * mat[3][0]) + (mat[0][1] * mat[1][3] * mat[2][0] * mat[3][2]) -
		  (mat[0][2] * mat[1][0] * mat[2][3] * mat[3][1]) + (mat[0][2] * mat[1][1] * mat[2][0] * mat[3][3]) + (mat[0][2] * mat[1][3] * mat[2][1] * mat[3][0]) -
		  (mat[0][3] * mat[1][0] * mat[2][1] * mat[3][2]) + (mat[0][3] * mat[1][1] * mat[2][2] * mat[3][0]) + (mat[0][3] * mat[1][2] * mat[2][0] * mat[3][1]);
		  det = 1.0f / det;
		  temp.mat[0][0] = ((mat[1][1]*mat[2][2]*mat[3][3]) + (mat[1][2]*mat[2][3]*mat[3][1]) + (mat[1][2]*mat[2][1]*mat[3][2]) - (mat[1][1]*mat[2][3]*mat[3][2]) - (mat[1][2]*mat[2][1]*mat[3][3]) - (mat[1][2]*mat[2][2]*mat[3][1])) / det;
		  temp.mat[0][1] = ((mat[0][1]*mat[2][3]*mat[3][2]) + (mat[0][2]*mat[2][1]*mat[3][3]) + (mat[0][3]*mat[2][2]*mat[3][1])  - (mat[0][1]*mat[2][2]*mat[3][3]) - (mat[0][2]*mat[2][3]*mat[3][1]) - (mat[0][3]*mat[2][1]*mat[3][2])) / det;
		  temp.mat[0][2] = ((mat[0][1]*mat[1][2]*mat[3][3]) + (mat[0][2]*mat[1][2]*mat[3][1]) + (mat[0][3]*mat[1][1]*mat[3][2])  - (mat[0][1]*mat[1][2]*mat[3][2]) - (mat[0][2]*mat[1][1]*mat[3][3]) - (mat[0][3]*mat[1][2]*mat[3][1])) / det;
		  temp.mat[0][3] = ((mat[0][1]*mat[1][2]*mat[2][2]) + (mat[0][2]*mat[1][1]*mat[2][3]) + (mat[0][3]*mat[1][2]*mat[2][1])  - (mat[0][1]*mat[1][2]*mat[2][3]) - (mat[0][2]*mat[1][2]*mat[2][1]) - (mat[0][3]*mat[1][1]*mat[2][2])) / det;
		  temp.mat[1][0] = ((mat[1][0]*mat[2][3]*mat[3][2]) + (mat[1][2]*mat[2][0]*mat[3][3]) + (mat[1][2]*mat[2][2]*mat[3][0])  - (mat[1][0]*mat[2][2]*mat[3][3]) - (mat[1][2]*mat[2][3]*mat[3][0]) - (mat[1][2]*mat[2][0]*mat[3][2])) / det;
		  temp.mat[1][1] = ((mat[0][0]*mat[2][2]*mat[3][3]) + (mat[0][2]*mat[2][3]*mat[3][0]) + (mat[0][3]*mat[2][0]*mat[3][2])	  - (mat[0][0]*mat[2][3]*mat[3][2]) - (mat[0][2]*mat[2][0]*mat[3][3]) - (mat[0][3]*mat[2][2]*mat[3][0])) / det;
		  temp.mat[1][2] = ((mat[0][0]*mat[1][2]*mat[3][2]) + (mat[0][2]*mat[1][0]*mat[3][3]) + (mat[0][3]*mat[1][2]*mat[3][0])  - (mat[0][0]*mat[1][2]*mat[3][3]) - (mat[0][2]*mat[1][2]*mat[3][0]) - (mat[0][3]*mat[1][0]*mat[3][2])) / det;
		  temp.mat[1][3] = ((mat[0][0]*mat[1][2]*mat[2][3]) + (mat[0][2]*mat[1][2]*mat[2][0]) + (mat[0][3]*mat[1][0]*mat[2][2])  - (mat[0][0]*mat[1][2]*mat[2][2]) - (mat[0][2]*mat[1][0]*mat[2][3]) - (mat[0][3]*mat[1][2]*mat[2][0])) / det;
		  temp.mat[2][0] = ((mat[1][0]*mat[2][1]*mat[3][3]) + (mat[1][1]*mat[2][3]*mat[3][0]) + (mat[1][2]*mat[2][0]*mat[3][1])  - (mat[1][0]*mat[2][3]*mat[3][1]) - (mat[1][1]*mat[2][0]*mat[3][3]) - (mat[1][2]*mat[2][1]*mat[3][0])) / det;
		  temp.mat[2][1] = ((mat[0][0]*mat[2][3]*mat[3][1]) + (mat[0][1]*mat[2][0]*mat[3][3]) + (mat[0][3]*mat[2][1]*mat[3][0])  - (mat[0][0]*mat[2][1]*mat[3][3]) - (mat[0][1]*mat[2][3]*mat[3][0]) - (mat[0][3]*mat[2][0]*mat[3][1])) / det;
		  temp.mat[2][2] = ((mat[0][0]*mat[1][1]*mat[3][3]) + (mat[0][1]*mat[1][2]*mat[3][0]) + (mat[0][3]*mat[1][0]*mat[3][1])  - (mat[0][0]*mat[1][2]*mat[3][1]) - (mat[0][1]*mat[1][0]*mat[3][3]) - (mat[0][3]*mat[1][1]*mat[3][0])) / det;
		  temp.mat[2][3] = ((mat[0][0]*mat[1][2]*mat[2][1]) + (mat[0][1]*mat[1][0]*mat[2][3]) + (mat[0][3]*mat[1][1]*mat[2][0])  - (mat[0][0]*mat[1][1]*mat[2][3]) - (mat[0][1]*mat[1][2]*mat[2][0]) - (mat[0][3]*mat[1][0]*mat[2][1])) / det;
		  temp.mat[3][0] = ((mat[1][0]*mat[2][2]*mat[3][1]) + (mat[1][1]*mat[2][0]*mat[3][2]) + (mat[1][2]*mat[2][1]*mat[3][0])  - (mat[1][0]*mat[2][1]*mat[3][2]) - (mat[1][1]*mat[2][2]*mat[3][0]) - (mat[1][2]*mat[2][0]*mat[3][1])) / det;
		  temp.mat[3][1] = ((mat[0][0]*mat[2][1]*mat[3][2]) + (mat[0][1]*mat[2][2]*mat[3][0]) + (mat[0][2]*mat[2][0]*mat[3][1])  - (mat[0][0]*mat[2][2]*mat[3][1]) - (mat[0][1]*mat[2][0]*mat[3][2]) - (mat[0][2]*mat[2][1]*mat[3][0])) / det;
		  temp.mat[3][2] = ((mat[0][0]*mat[1][2]*mat[3][1]) + (mat[0][1]*mat[1][0]*mat[3][2]) + (mat[0][2]*mat[1][1]*mat[3][0])  - (mat[0][0]*mat[1][1]*mat[3][2]) - (mat[0][1]*mat[1][2]*mat[3][0]) - (mat[0][2]*mat[1][0]*mat[3][1])) / det;
		  temp.mat[3][3] = ((mat[0][0]*mat[1][1]*mat[2][2]) + (mat[0][1]*mat[1][2]*mat[2][0]) + (mat[0][2]*mat[1][0]*mat[2][1])  - (mat[0][0]*mat[1][2]*mat[2][1]) - (mat[0][1]*mat[1][0]*mat[2][2]) - (mat[0][2]*mat[1][1]*mat[2][0])) / det;
}
void Matrix::RotationArX(float angle_x)
{

	mat[0][0] = 1;
	mat[1][1] = cosf(angle_x);
	mat[2][2] = cosf(angle_x);
	mat[2][1] = sinf(angle_x);
	mat[1][2] = -sinf(angle_x);
}
void Matrix::RotationArY(float angle_y)
{
	mat[0][0] = 1;
	mat[1][1] = cosf(angle_y);
	mat[2][2] = cosf(angle_y);
	mat[2][1] = sinf(angle_y);
	mat[1][2] = -sinf(angle_y);

}
void Matrix::RotationArZ(float angle_z)
{
	mat[0][0] = 1;
	mat[1][1] = cosf(angle_z);
	mat[2][2] = cosf(angle_z);
	mat[2][1] = sinf(angle_z);
	mat[1][2] = -sinf(angle_z);

}

void Matrix::Translation(float trans_x, float trans_y, float trans_z)
{
	for (int i = 0; i < 4; i++)
		mat[i][i] = 0;

	mat[0][3] = trans_x;
	mat[1][3] = trans_y;
	mat[2][3] = trans_z;
}

void Matrix::Translation(Vector3 i_trans)
{
	for (int i = 0; i < 4; i++)
		mat[i][i] = 0;

	mat[0][3] = i_trans.X();
	mat[1][3] = i_trans.X();
	mat[2][3] = i_trans.Z();
}

Matrix Matrix::operator * (Matrix i_mat)
{ 
	Matrix temp;
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
	for (int k = 0; k < 4; k++)
		temp.mat[i][j] += mat[i][k] * i_mat.mat[k][j];
	return temp;
}

Vector4 Matrix::operator * (Vector4 i_mat)
{
	
	float t[4], t2[4];
	t[0] = i_mat.X();
	t[1] = i_mat.Y();
	t[2] = i_mat.Z();
	t[3] = i_mat.W();
	
	for (int i = 0; i < 3; i++)
	{
		t2[0] += mat[0][i] * t[i];
		t2[1] += mat[1][i] * t[i];
		t2[2] += mat[2][i] * t[i];
		t2[3] += mat[3][i] * t[i];
	}
	Vector4 temp(t2[0], t2[1], t2[2], t2[3]);
	return temp;
}

