#include "jgl.h"

Matrix::Matrix(
	float a0, float a1, float a2, float a3,
	float b0, float b1, float b2, float b3,
	float c0, float c1, float c2, float c3,
	float d0, float d1, float d2, float d3)
{
	value[0][0] = a0;			value[0][1] = a1;				value[0][2] = a2;				value[0][3] = a3;
	value[1][0] = b0;			value[1][1] = b1;				value[1][2] = b2;				value[1][3] = b3;
	value[2][0] = c0;			value[2][1] = c1;				value[2][2] = c2;				value[2][3] = c3;
	value[2][0] = d0;			value[2][1] = d1;				value[2][2] = d2;				value[3][3] = d3;
}

Matrix::Matrix(X_ROTATE, float angle)
{
	float		radian = degree_to_radius(angle);
	value[0][0] = 1.0f; 		value[0][1] = 0.0f;       		value[0][2] = 0.0f;				value[0][3] = 0;
	value[1][0] = 0.0f; 		value[1][1] = cos(radian); 		value[1][2] = -sin(radian);		value[1][3] = 0;
	value[2][0] = 0.0f; 		value[2][1] = sin(radian); 		value[2][2] = cos(radian);		value[2][3] = 0;
	value[3][0] = 0;			value[3][1] = 0;				value[3][2] = 0;				value[3][3] = 1;
}

Matrix::Matrix(Y_ROTATE, float angle)
{
	float		radian = degree_to_radius(angle);

	value[0][0] = cos(radian);	value[0][1] = 0.0f; 			value[0][2] = -sin(radian);		value[0][3] = 0;
	value[1][0] = 0.0f;      	value[1][1] = 1.0f; 			value[1][2] = 0.0f;				value[1][3] = 0;
	value[2][0] = sin(radian);	value[2][1] = 0.0f; 			value[2][2] = cos(radian);		value[2][3] = 0;
	value[3][0] = 0;			value[3][1] = 0;				value[3][2] = 0;				value[3][3] = 1;
}

Matrix::Matrix(Z_ROTATE, float angle)
{
	float		radian = degree_to_radius(angle);

	value[0][0] = cos(radian);	value[0][1] = sin(radian);		value[0][2] = 0.0f;				value[0][3] = 0;
	value[1][0] = -sin(radian);	value[1][1] = cos(radian);		value[1][2] = 0.0f;				value[1][3] = 0;
	value[2][0] = 0.0f; 		value[2][1] = 0.0f; 			value[2][2] = 1.0f;				value[2][3] = 0;
	value[3][0] = 0;			value[3][1] = 0;				value[3][2] = 0;				value[3][3] = 1;
}

Matrix::Matrix(ROTATION, float x, float y, float z)
{
	Matrix rotx = Matrix(X, x);
	Matrix roty = Matrix(Y, y);
	Matrix rotz = Matrix(Z, z);

	Matrix result = (rotx * roty * rotz);

	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			value[i][j] = result.value[i][j];
			j++;
		}
		i++;
	}
}

Matrix::Matrix(TRANSLATION, float t_x, float t_y, float t_z)
{
	value[0][0] = 1.0f;			value[0][1] = 0.0f; 			value[0][2] = 0.0f;				value[0][3] = t_x;
	value[1][0] = 0.0f;			value[1][1] = 1.0f; 			value[1][2] = 0.0f;				value[1][3] = t_y;
	value[2][0] = 0.0f;			value[2][1] = 0.0f; 			value[2][2] = 1.0f;				value[2][3] = t_z;
	value[3][0] = 0;			value[3][1] = 0;				value[3][2] = 0;				value[3][3] = 1;
}

Matrix::Matrix(SCALE, float t_x, float t_y, float t_z)
{
	value[0][0] = t_x;			value[0][1] = 0.0f; 			value[0][2] = 0.0f;				value[0][3] = 0.0f;
	value[1][0] = 0.0f;			value[1][1] = t_y; 				value[1][2] = 0.0f;				value[1][3] = 0.0f;
	value[2][0] = 0.0f;			value[2][1] = 0.0f; 			value[2][2] = t_z;				value[2][3] = 0.0f;
	value[3][0] = 0;			value[3][1] = 0;				value[3][2] = 0;				value[3][3] = 1;
}

Matrix			Matrix::operator * (Matrix p_Matrix)
{
	int		i;
	int		j;
	Matrix	m = Matrix(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.value[i][j] = (value[i][0] * p_Matrix.value[0][j]) +
					(value[i][1] * p_Matrix.value[1][j]) +
					(value[i][2] * p_Matrix.value[2][j]) +
					(value[i][3] * p_Matrix.value[3][j]);
			j++;
		}
		i++;
	}
	return (m);
}

Vector3		Matrix::operator * (Vector3 vertex)
{
	float		result[3];

	result[0] = value[0][0] * vertex.x + value[0][1] * vertex.y + value[0][2] * vertex.z + value[0][3] + value[0][3];
	result[1] = value[1][0] * vertex.x + value[1][1] * vertex.y + value[1][2] * vertex.z + value[1][3] + value[1][3];
	result[2] = value[2][0] * vertex.x + value[2][1] * vertex.y + value[2][2] * vertex.z + value[2][3] + value[2][3];

	return (Vector3(result[0], result[1], result[2]));
}
