#include <math.h>
#include "Vector3.h"
#include "Vector4.h"

class Matrix
{
public:
	float mat[4][4];

	Matrix();
	 void RotationArX(float angle_x);
    void RotationArY(float angle_y);
    void RotationArZ(float angle_z);
    void Identity();
   	void Translation(Vector3 i_trans);
	void Translation(float trans_x, float trans_y, float trans_z);
	void Transpose();
	void Inverse();
	Matrix operator*(Matrix i_mat);
	Vector3 operator*(Vector3 i_mat);
	Vector4 operator*(Vector4 i_mat);
};