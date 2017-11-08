#include "Matrix.h" 
#include "Assert.h"

class MatrixUnitTest
{

	void unitTest(){
	

		Matrix Mat1 = Matrix(1, 2, 3, 4,
			1, 2, 3, 4,
			1, 2, 3, 4,
			4, 5, 6, 7);
		Matrix Mat2 = Matrix(1, 2, 3, 4,
			5, 6, 7, 8,
			1, 2, 3, 4,
			4, 5, 6, 7);

		Vector4 Vec41 = Vector4(5, 6, 7, 8);
		Vector4 Vec42 = Mat1*Vec41;
		Vector4 Vec43 = Vector4(70, 70, 70, 148);
		MessagedAssert(Vec42 == Vec43, "Matrix * Vector 4 failed");
		Mat1.SetToIdentity();
		Matrix identity = Matrix(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		MessagedAssert(Mat1 == identity, "SetToIdentity failed");
		Mat1.SetToScale(3, 4, 1);
		MessagedAssert(Mat1 == Matrix(3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), "Set to Scale failed");
		Mat1 = Matrix(1, 2, 3, 4,
			1, 2, 3, 4,
			1, 2, 3, 4,
			4, 5, 6, 7);
		Matrix Mat3 = Mat1 * Mat2;
		MessagedAssert(Mat3 == Matrix(30, 40, 50, 60, 30, 40, 50, 60, 30, 40, 50, 60, 63, 85, 107, 129), "Matrix Multiplication failed");
		Mat3 = Matrix(4, 0, 0, 0,
			0, 0, 2, 0,
			0, 1, 2, 0,
			1, 0, 0, 1);
		Mat3.Invert();
		MessagedAssert(Mat3 == Matrix(0.25, 0, 0, 0, 0, -1, 1, 0, 0, 0.5, 0, 0, -0.25, 0, 0, 1), "Invert failed");

		Mat1.Transpose();
		MessagedAssert(Mat1 == Matrix(1, 1, 1, 4, 2, 2, 2, 5, 3, 3, 3, 6, 4, 4, 4, 7), "Transpose failed");

		Mat1.SetToXRotation(90);
		Mat2.Transpose();

	}
};