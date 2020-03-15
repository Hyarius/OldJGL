#ifndef JGL_MATRIX_H
#define JGL_MATRIX_H

enum class Matrix_type {
	rotation = 0,
	translation = 1,
	scale = 2
};

float degree_to_radius(float degree);

struct Matrix
{
	float value[4][4];

	Matrix matrix_rotation_x(float angle)
	{
		Matrix result = Matrix();
			float		radian = degree_to_radius(angle);
		result.value[0][0] = 1.0f; 			result.value[1][0] = 0.0f;       	result.value[2][0] = 0.0f;			result.value[3][0] = 0;
		result.value[0][1] = 0.0f; 			result.value[1][1] = cos(radian); 	result.value[2][1] = sin(radian);	result.value[3][1] = 0;
		result.value[0][2] = 0.0f; 			result.value[1][2] = -sin(radian); 	result.value[2][2] = cos(radian);	result.value[3][2] = 0;
		result.value[0][3] = 0;				result.value[1][3] = 0;				result.value[2][3] = 0;				result.value[3][3] = 1;
		return (result);
	}
	Matrix matrix_rotation_y(float angle)
	{
		Matrix result = Matrix();
			float		radian = degree_to_radius(angle);

		result.value[0][0] = cos(radian);	result.value[1][0] = 0.0f; 			result.value[2][0] = -sin(radian);	result.value[3][0] = 0;
		result.value[0][1] = 0.0f;      	result.value[1][1] = 1.0f; 			result.value[2][1] = 0.0f;			result.value[3][1] = 0;
		result.value[0][2] = sin(radian);	result.value[1][2] = 0.0f; 			result.value[2][2] = cos(radian);	result.value[3][2] = 0;
		result.value[0][3] = 0;				result.value[1][3] = 0;				result.value[2][3] = 0;				result.value[3][3] = 1;
		return (result);
	}
	Matrix matrix_rotation_z(float angle)
	{
		Matrix result = Matrix();
		float		radian = degree_to_radius(angle);

		result.value[0][0] = cos(radian);	result.value[1][0] = sin(radian);	result.value[2][0] = 0.0f;			result.value[3][0] = 0;
		result.value[0][1] = -sin(radian);	result.value[1][1] = cos(radian);	result.value[2][1] = 0.0f;			result.value[3][1] = 0;
		result.value[0][2] = 0.0f; 			result.value[1][2] = 0.0f; 			result.value[2][2] = 1.0f;			result.value[3][2] = 0;
		result.value[0][3] = 0;				result.value[1][3] = 0;				result.value[2][3] = 0;				result.value[3][3] = 1;
		return (result);
	}
	void matrix_rotation(float x, float y, float z)
	{
		Matrix rotx = matrix_rotation_x(x);
		Matrix roty = matrix_rotation_y(y);
		Matrix rotz = matrix_rotation_z(z);

		*this = rotx * roty * rotz;
	}
	void matrix_translation(float x, float y, float z)
	{
		value[0][0] = 1.0f;			value[1][0] = 0.0f; 			value[2][0] = 0.0f;				value[3][0] = x;
		value[0][1] = 0.0f;			value[1][1] = 1.0f; 			value[2][1] = 0.0f;				value[3][1] = y;
		value[0][2] = 0.0f;			value[1][2] = 0.0f; 			value[2][2] = 1.0f;				value[3][2] = z;
		value[0][3] = 0;			value[1][3] = 0;				value[2][3] = 0;				value[3][3] = 1;
	}
	void matrix_scale(float x, float y, float z)
	{
		value[0][0] = x;			value[1][0] = 0.0f; 			value[2][0] = 0.0f;				value[3][0] = 0.0f;
		value[0][1] = 0.0f;			value[1][1] = y; 				value[2][1] = 0.0f;				value[3][1] = 0.0f;
		value[0][2] = 0.0f;			value[1][2] = 0.0f; 			value[2][2] = z;				value[3][2] = 0.0f;
		value[0][3] = 0;			value[1][3] = 0;				value[2][3] = 0;				value[3][3] = 1;
	}

	Matrix(	float a0 = 1.0F, float a1 = 0.0f, float a2 = 0.0f, float a3 = 0.0f,
			float b0 = 0.0f, float b1 = 1.0F, float b2 = 0.0f, float b3 = 0.0f,
			float c0 = 0.0f, float c1 = 0.0f, float c2 = 1.0F, float c3 = 0.0f,
			float d0 = 0.0f, float d1 = 0.0f, float d2 = 0.0f, float d3 = 1.0F);

	Matrix(Matrix_type type, float x, float y, float z)
	{
		if (type == Matrix_type::rotation)
			matrix_rotation(x, y, z);
		else if (type == Matrix_type::translation)
			matrix_translation(x, y, z);
		else if (type == Matrix_type::scale)
			matrix_scale(x, y, z);
	}
	Matrix(Matrix_type type, Vector3 angle)
	{
		*this = Matrix(type, angle.x, angle.y, angle.z);
	}
	Matrix operator * (Matrix p_matrix);
	Vector3 operator * (Vector3 vertex);
	Vector4 operator * (Vector4 vertex);
	void print();
};

ostream& operator<<(ostream& os, Matrix data);

#endif
