#ifndef JGL_MATRIX_H
#define JGL_MATRIX_H

namespace jgl
{
	enum class Matrix_type {
		rotation = 0,
		translation = 1,
		scale = 2,
		look_at = 3,
		count
	};

	float degree_to_radian(float degree);

	struct Matrix2x2
	{
		float value[3][3];

		Matrix2x2(float a0 = 1.0F, float a1 = 0.0f,
		float b0 = 0.0f, float b1 = 1.0F)
		{
			value[0][0] = a0; value[1][0] = a1;
			value[0][1] = b0; value[1][1] = b1;
		}
		float determinant();
		Matrix2x2 reverse();
		Matrix2x2 inverse_matrix();
		Matrix2x2 operator * (Matrix2x2 p_matrix)
		{
			int		i;
			int		j;
			Matrix2x2	m = Matrix2x2();

			i = 0;
			while (i < 4)
			{
				j = 0;
				while (j < 4)
				{
					m.value[i][j] = (this->value[0][i] * p_matrix.value[j][0]) +
									(this->value[1][i] * p_matrix.value[j][1]);
					j++;
				}
				i++;
			}
			return (m);
		}
		Vector2 operator * (Vector2 vertex)
		{
			return (Vector2(
				value[0][0] * vertex.x + value[1][0] * vertex.y,
				value[0][1] * vertex.x + value[1][1] * vertex.y
			));
		}
		float* operator[](size_t index)
		{
			if (index > 2)
				return (nullptr);
			return (value[index]);
		}
	};

	struct Matrix3x3
	{
		float value[3][3];

		Matrix3x3(float a0 = 1.0F, float a1 = 0.0f, float a2 = 0.0f,
		float b0 = 0.0f, float b1 = 1.0F, float b2 = 0.0f,
		float c0 = 0.0f, float c1 = 0.0f, float c2 = 1.0F)
		{
			value[0][0] = a0; value[1][0] = a1; value[2][0] = a2;
			value[0][1] = b0; value[1][1] = b1; value[2][1] = b2;
			value[0][2] = c0; value[1][2] = c1; value[2][2] = c2;
		}
		Matrix3x3 reverse();
		float cofactor(int x, int y);
		float determinant();
		Matrix3x3 cofactor_matrix();
		Matrix3x3 adjucate_matrix();
		Matrix3x3 inverse_matrix();
		Matrix3x3 operator * (Matrix3x3 p_matrix)
		{
			int		i;
			int		j;
			Matrix3x3	m = Matrix3x3();

			i = 0;
			while (i < 4)
			{
				j = 0;
				while (j < 4)
				{
					m.value[i][j] = (this->value[0][i] * p_matrix.value[j][0])
					+ (this->value[1][i] * p_matrix.value[j][1])
					+ (this->value[2][i] * p_matrix.value[j][2]);
					j++;
				}
				i++;
			}
			return (m);
		}
		Vector3 operator * (Vector3 vertex)
		{
			return (Vector3(
				value[0][0] * vertex.x + value[1][0] * vertex.y + value[2][0] * vertex.z,
				value[0][1] * vertex.x + value[1][1] * vertex.y + value[2][1] * vertex.z,
				value[0][2] * vertex.x + value[1][2] * vertex.y + value[2][2] * vertex.z
			));
		}
		float* operator[](size_t index)
		{
			if (index > 3)
				return (nullptr);
			return (&(value[index][0]));
		}
	};

	struct Matrix4x4
	{
		float value[4][4];

		static Matrix4x4 matrix_custom_rotation(float angle, Vector3 axis);
		static Matrix4x4 matrix_look_at(Vector3 pos, Vector3 target, Vector3 up_dir);
		static Matrix4x4 matrix_rotation_x(float angle)
		{
			Matrix4x4 result = Matrix4x4();
			float		radian = degree_to_radian(angle);
			result.value[0][0] = 1.0f;result.value[1][0] = 0.0f;       	result.value[2][0] = 0.0f;result.value[3][0] = 0;
			result.value[0][1] = 0.0f;result.value[1][1] = cos(radian); 	result.value[2][1] = sin(radian);	result.value[3][1] = 0;
			result.value[0][2] = 0.0f;result.value[1][2] = -sin(radian); 	result.value[2][2] = cos(radian);	result.value[3][2] = 0;
			result.value[0][3] = 0;result.value[1][3] = 0;result.value[2][3] = 0;result.value[3][3] = 1;
			return (result);
		}
		static Matrix4x4 matrix_rotation_y(float angle)
		{
			Matrix4x4 result = Matrix4x4();
			float		radian = degree_to_radian(angle);

			result.value[0][0] = cos(radian);	result.value[1][0] = 0.0f;result.value[2][0] = -sin(radian);	result.value[3][0] = 0;
			result.value[0][1] = 0.0f;      	result.value[1][1] = 1.0f;result.value[2][1] = 0.0f;result.value[3][1] = 0;
			result.value[0][2] = sin(radian);	result.value[1][2] = 0.0f;result.value[2][2] = cos(radian);	result.value[3][2] = 0;
			result.value[0][3] = 0;result.value[1][3] = 0;result.value[2][3] = 0;result.value[3][3] = 1;
			return (result);
		}
		static Matrix4x4 matrix_rotation_z(float angle)
		{
			Matrix4x4 result = Matrix4x4();
			float		radian = degree_to_radian(angle);

			result.value[0][0] = cos(radian);	result.value[1][0] = sin(radian);	result.value[2][0] = 0.0f;result.value[3][0] = 0;
			result.value[0][1] = -sin(radian);	result.value[1][1] = cos(radian);	result.value[2][1] = 0.0f;result.value[3][1] = 0;
			result.value[0][2] = 0.0f;result.value[1][2] = 0.0f;result.value[2][2] = 1.0f;result.value[3][2] = 0;
			result.value[0][3] = 0;result.value[1][3] = 0;result.value[2][3] = 0;result.value[3][3] = 1;
			return (result);
		}
		void matrix_rotation(float x, float y, float z)
		{
			Matrix4x4 rotx = matrix_rotation_x(x);
			Matrix4x4 roty = matrix_rotation_y(y);
			Matrix4x4 rotz = matrix_rotation_z(z);

			*this = rotx * roty * rotz;
		}
		void matrix_translation(float x, float y, float z)
		{
			value[0][0] = 1.0f;value[1][0] = 0.0f;value[2][0] = 0.0f;value[3][0] = x;
			value[0][1] = 0.0f;value[1][1] = 1.0f;value[2][1] = 0.0f;value[3][1] = y;
			value[0][2] = 0.0f;value[1][2] = 0.0f;value[2][2] = 1.0f;value[3][2] = z;
			value[0][3] = 0;value[1][3] = 0;value[2][3] = 0;value[3][3] = 1;
		}
		void matrix_scale(float x, float y, float z)
		{
			value[0][0] = x;value[1][0] = 0.0f;value[2][0] = 0.0f;value[3][0] = 0.0f;
			value[0][1] = 0.0f;value[1][1] = y; value[2][1] = 0.0f;value[3][1] = 0.0f;
			value[0][2] = 0.0f;value[1][2] = 0.0f;value[2][2] = z;value[3][2] = 0.0f;
			value[0][3] = 0;value[1][3] = 0;value[2][3] = 0;value[3][3] = 1;
		}

		Matrix4x4(float a0 = 1.0F, float a1 = 0.0f, float a2 = 0.0f, float a3 = 0.0f,
		float b0 = 0.0f, float b1 = 1.0F, float b2 = 0.0f, float b3 = 0.0f,
		float c0 = 0.0f, float c1 = 0.0f, float c2 = 1.0F, float c3 = 0.0f,
		float d0 = 0.0f, float d1 = 0.0f, float d2 = 0.0f, float d3 = 1.0F)
		{
			value[0][0] = a0;value[1][0] = a1;value[2][0] = a2;value[3][0] = a3;
			value[0][1] = b0;value[1][1] = b1;value[2][1] = b2;value[3][1] = b3;
			value[0][2] = c0;value[1][2] = c1;value[2][2] = c2;value[3][2] = c3;
			value[0][3] = d0;value[1][3] = d1;value[2][3] = d2;value[3][3] = d3;
		}

		Matrix4x4(Matrix_type type, float x, float y, float z)
		{
			if (type == Matrix_type::rotation)
				matrix_rotation(x, y, z);
			else if (type == Matrix_type::translation)
				matrix_translation(x, y, z);
			else if (type == Matrix_type::scale)
				matrix_scale(x, y, z);
			else
				*this = Matrix4x4();
		}
		Matrix4x4(Matrix_type type, Vector3 angle)
		{
			*this = Matrix4x4(type, angle.x, angle.y, angle.z);
		}
		Matrix4x4(Matrix_type type, Vector3 pos, Vector3 target, Vector3 up)
		{
			if (type == Matrix_type::look_at)
				*this = matrix_look_at(pos, target, up);
			else
				*this = Matrix4x4();
		}
		Matrix4x4 reverse();
		float cofactor(int x, int y);
		float determinant();
		Matrix4x4 cofactor_matrix();
		Matrix4x4 adjucate_matrix();
		Matrix4x4 inverse_matrix();
		Matrix4x4 operator * (Matrix4x4 p_matrix)
		{
			int		i;
			int		j;
			Matrix4x4	m = Matrix4x4();

			i = 0;
			while (i < 4)
			{
				j = 0;
				while (j < 4)
				{
					m.value[i][j] = (this->value[0][i] * p_matrix.value[j][0])
					+ (this->value[1][i] * p_matrix.value[j][1])
					+ (this->value[2][i] * p_matrix.value[j][2])
					+ (this->value[3][i] * p_matrix.value[j][3]);
					j++;
				}
				i++;
			}
			return (m);
		}
		Vector3 operator * (Vector3 vertex)
		{
			return (Vector3(
				value[0][0] * vertex.x + value[1][0] * vertex.y + value[2][0] * vertex.z + value[3][0] * value[3][3],
				value[0][1] * vertex.x + value[1][1] * vertex.y + value[2][1] * vertex.z + value[3][1] * value[3][3],
				value[0][2] * vertex.x + value[1][2] * vertex.y + value[2][2] * vertex.z + value[3][2] * value[3][3]
			));
		}
		Vector4 operator * (Vector4 vertex)
		{
			return (Vector4(
				value[0][0] * vertex.x + value[1][0] * vertex.y + value[2][0] * vertex.z + value[3][0] * vertex.w,
				value[0][1] * vertex.x + value[1][1] * vertex.y + value[2][1] * vertex.z + value[3][1] * vertex.w,
				value[0][2] * vertex.x + value[1][2] * vertex.y + value[2][2] * vertex.z + value[3][2] * vertex.w,
				value[3][0] * vertex.x + value[1][3] * vertex.y + value[2][3] * vertex.z + value[3][3] * vertex.w)
			);
		}
		float* operator[](size_t index)
		{
			if (index > 4)
				return (nullptr);
			return (&(value[index][0]));
		}
	};
}
std::ostream& operator<<(std::ostream& os, const jgl::Matrix2x2 data);
std::ostream& operator<<(std::ostream& os, const jgl::Matrix3x3 data);
std::ostream& operator<<(std::ostream& os, const jgl::Matrix4x4 data);

#endif
