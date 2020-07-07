#include "jgl.h"

namespace jgl
{
	Matrix2x2 Matrix2x2::reverse() const
	{
		Matrix2x2 result;

		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 2; j++)
			{
				result.value[i][j] = value[j][i];
			}
		return (result);
	}
	float Matrix2x2::determinant() const
	{
		return (value[0][0] * value[1][1] - value[1][0] * value[0][1]);
	}
	Matrix2x2 Matrix2x2::inverse_matrix() const
	{
		float tmp = determinant();
		return (Matrix2x2(
			value[1][1] / tmp, -(value[1][0] / tmp),
			-(value[0][1] / tmp), value[0][0] / tmp
		));
	}

	Matrix3x3 Matrix3x3::reverse() const
	{
		Matrix3x3 result;

		for (size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 3; j++)
			{
				result.value[i][j] = value[j][i];
			}
		return (result);
	}
	float Matrix3x3::cofactor(int x, int y) const
	{
		float tmp_value[4]{1, 1, 1, 1};

		size_t index = 0;

		for (size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 3; j++)
			{
				if (i != x && j != y)
				{
					tmp_value[index] = value[i][j];
					index++;
				}
			}
		Matrix2x2 tmp_matrix(tmp_value[0], tmp_value[1], tmp_value[2], tmp_value[3]);
		return (tmp_matrix.determinant());
	}
	Matrix3x3 Matrix3x3::cofactor_matrix() const
	{
		Matrix3x3 result = Matrix3x3(
			+cofactor(0, 0), -cofactor(1, 0), +cofactor(2, 0),
			-cofactor(0, 1), +cofactor(1, 1), -cofactor(2, 1),
			+cofactor(0, 2), -cofactor(1, 2), +cofactor(2, 2)
		);

		return (result);
	}
	Matrix3x3 Matrix3x3::adjucate_matrix() const
	{
		return (cofactor_matrix().reverse());
	}
	float Matrix3x3::determinant() const
	{
		return (value[0][0] * cofactor(0, 0) - value[1][0] * cofactor(1, 0) + value[2][0] * cofactor(2, 0));
	}
	Matrix3x3 Matrix3x3::inverse_matrix() const
	{
		Matrix3x3 tmp = adjucate_matrix();
		Matrix3x3 result = Matrix3x3();
		float deter = determinant();

		if (deter != 0)
		{
			for (size_t i = 0; i < 3; i++)
				for (size_t j = 0; j < 3; j++)
				{
					result.value[i][j] = tmp.value[i][j] / deter;
				}
		}
		return (result);

		return (result);
	}

	Matrix4x4 Matrix4x4::matrix_custom_rotation(float angle, Vector3 axis)
	{
		axis = axis.normalize();
		float u = axis.x;
		float v = axis.y;
		float w = axis.z;
		float len = axis.length();
		float root_len = sqrt(len);
		float theta = degree_to_radian(angle);
		float cos_theta = std::cos(theta);
		float sin_theta = std::sin(theta);

		float a0 = pow(u, 2) + (pow(v, 2) + pow(w, 2)) * cos_theta;
		float a1 = u * v * (1 - cos_theta) - w * root_len * sin_theta;
		float a2 = u * w * (1 - cos_theta) + v * root_len * sin_theta;
		float a3 = 0;

		float b0 = v * u * (1 - cos_theta) + w * root_len * sin_theta;
		float b1 = pow(v, 2) + (pow(u, 2) + pow(w, 2)) * cos_theta;
		float b2 = v * w * (1 - cos_theta) - u * root_len * sin_theta;
		float b3 = 0;

		float c0 = u * w * (1 - cos_theta) - v * root_len * sin_theta;
		float c1 = v * w * (1 - cos_theta) + u * root_len * sin_theta;
		float c2 = pow(w, 2) + (pow(u, 2) + pow(v, 2)) * cos_theta;
		float c3 = 0;

		float d0 = 0;
		float d1 = 0;
		float d2 = 0;
		float d3 = 1;

		Matrix4x4 result(
			a0, a1, a2, a3,
			b0, b1, b2, b3,
			c0, c1, c2, c3,
			d0, d1, d2, d3
		);

		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 3; j++)
				result[i][j] /= len;

		return (result);
	}
	Matrix4x4 Matrix4x4::matrix_look_at(Vector3 pos, Vector3 target, Vector3 up_dir, float angle)
	{
		Matrix4x4 result;


		Vector3 forward = (pos - target).normalize();
		Vector3 up = Vector3::up();
		if (forward.dot(up) == 1 || forward.dot(up) == -1)
			up = Vector3::front();
		Vector3 right = (up.cross(forward)).normalize();
		right = Matrix4x4::matrix_rotation_y(angle) * right;
		up = (forward.cross(right)).normalize();

		result.value[0][0] = right.x;
		result.value[1][0] = right.y;
		result.value[2][0] = right.z;
		result.value[3][0] = -(right.dot(pos) / 2);
		result.value[0][1] = up.x;
		result.value[1][1] = up.y;
		result.value[2][1] = up.z;
		result.value[3][1] = -(up.dot(pos) / 2);
		result.value[0][2] = forward.x;
		result.value[1][2] = forward.y;
		result.value[2][2] = forward.z;
		result.value[3][2] = -(forward.dot(pos) / 2);
		result.value[0][3] = 0;
		result.value[1][3] = 0;
		result.value[2][3] = 0;
		result.value[3][3] = 1;

		return (result);
	}
	Matrix4x4 Matrix4x4::reverse() const
	{
		Matrix4x4 result;

		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++)
			{
				result.value[i][j] = value[j][i];
			}
		return (result);
	}
	float Matrix4x4::cofactor(int x, int y) const
	{
		float tmp_value[9]{ 1, 1, 1, 1, 1, 1, 1, 1, 1 };

		size_t index = 0;

		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++)
			{
				if (i != x && j != y)
				{
					tmp_value[index] = value[i][j];
					index++;
				}
			}
		Matrix3x3 tmp_matrix(
			tmp_value[0], tmp_value[1], tmp_value[2],
			tmp_value[3], tmp_value[4], tmp_value[5],
			tmp_value[6], tmp_value[7], tmp_value[8]
		);
		float result = tmp_matrix.determinant();
		return (result);
	}
	Matrix4x4 Matrix4x4::cofactor_matrix() const
	{
		Matrix4x4 result = Matrix4x4(
			+cofactor(0, 0), -cofactor(1, 0), +cofactor(2, 0), -cofactor(3, 0),
			-cofactor(0, 1), +cofactor(1, 1), -cofactor(2, 1), +cofactor(3, 1),
			+cofactor(0, 2), -cofactor(1, 2), +cofactor(2, 2), -cofactor(3, 2),
			-cofactor(0, 3), +cofactor(1, 3), -cofactor(2, 3), +cofactor(3, 3)
		);

		return (result);
	}
	Matrix4x4 Matrix4x4::adjucate_matrix() const
	{
		return (cofactor_matrix().reverse());
	}
	float Matrix4x4::determinant() const
	{
		return (value[0][0] * cofactor(0, 0) - value[1][0] * cofactor(1, 0) + value[2][0] * cofactor(2, 0) - value[3][0] * cofactor(3, 0));
	}
	Matrix4x4 Matrix4x4::inverse_matrix() const
	{
		Matrix4x4 tmp = adjucate_matrix();
		Matrix4x4 result = Matrix4x4();
		float deter = determinant();

		if (deter != 0)
		{
			for (size_t i = 0; i < 4; i++)
				for (size_t j = 0; j < 4; j++)
				{
					result.value[i][j] = tmp.value[i][j] / deter;
				}
		}
		return (result);
	}
}