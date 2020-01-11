#ifndef JGL_MATRIX_H
#define JGL_MATRIX_H

enum X_ROTATE { X };
enum Y_ROTATE { Y };
enum Z_ROTATE { Z };
enum ROTATION { R };
enum TRANSLATION { T };
enum SCALE { S };
enum PERSPECTIVE { P };
enum IDENTITY { I };

struct Matrix
{
	float value[4][4];

	Matrix();
	Matrix(float a0, float a1, float a2, float a3, float b0, float b1, float b2, float b3, float c0, float c1, float c2, float c3,
					float d0, float d1, float d2, float d3);
	Matrix(X_ROTATE, float angle);
	Matrix(Y_ROTATE, float angle);
	Matrix(Z_ROTATE, float angle);
	Matrix(ROTATION, float x, float y, float z);
	Matrix(TRANSLATION, float t_x, float t_y, float t_z);
	Matrix(SCALE, float t_x, float t_y, float t_z);
	Matrix operator * (Matrix p_Matrix);
	Vector3 operator * (Vector3 vertex);
	void print();
};

ostream& operator<<(ostream& os, Matrix data);

#endif
