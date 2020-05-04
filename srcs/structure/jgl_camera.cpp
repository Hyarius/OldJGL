#include "jgl.h"

namespace jgl
{
	Camera::Camera(Vector3 p_pos, float p_fov, float p_near, float p_far)
	{
		_pitch = 0;
		_yaw = 0;
		_pos = p_pos;

		_dir_light = Vector3(0.0f, -1.0f, 0.0f);
		_dir_light = _dir_light.normalize();

		_fov = p_fov;
		_near = p_near;
		_far = p_far;

		compute();
	}

	void Camera::actualize()
	{
		float tmp_pitch = degree_to_radian(_pitch);
		float tmp_yaw = degree_to_radian(_yaw);
		Vector3	xaxis;
		Vector3	yaxis;
		Vector3	zaxis;

		zaxis = Vector3(
			cos(tmp_pitch) * sin(tmp_yaw),
			sin(tmp_pitch),
			cos(tmp_pitch) * cos(tmp_yaw)).normalize();
		xaxis = Vector3(
			sin(tmp_yaw - 3.14f / 2.0f), 0.0f,
			cos(tmp_yaw - 3.14f / 2.0f)).normalize();
		yaxis = (xaxis.cross(zaxis)).normalize();
		_forward = zaxis;
		_right = xaxis;
		_up = yaxis;
	}

	void Camera::look_at(Vector3 target)
	{
		Vector3	r;

		r = (_pos - target).normalize();
		_yaw = radian_to_degree(atan2(r.z, -r.x)) - 90;
		_pitch = radian_to_degree(atan2(r.y, sqrt(pow(r.x, 2) + pow(r.z, 2))));
		_pitch = clamp_float(-89.0f, _pitch, 89.0f);
		compute();
	}

	void Camera::rotate_around_point(Vector3 target, Vector3 delta)
	{
		Vector3 tmp;
		Matrix rotation;

		rotation = Matrix(Matrix_type::rotation, delta.x, delta.y, delta.z);

		tmp = _pos - target;
		tmp = rotation * tmp;
		_pos = tmp + target;
		compute();
	}

	void Camera::rotate(float p_pitch, float p_yaw)
	{
		_yaw += p_pitch;
		_pitch += p_yaw;
		_pitch = clamp_float(-89.0f, _pitch, 89.0f);
		compute();
	}

	void Camera::move(Vector3 delta)
	{
		_pos += delta;

		compute();
	}

	void Camera::place(Vector3 p_pos)
	{
		_pos = p_pos;

		compute();
	}

	void Camera::compute_model()
	{
		_model = Matrix();
	}

	void Camera::compute_view()
	{
		_view = Matrix();
		_view.value[0][0] = _right.x;
		_view.value[1][0] = _right.y;
		_view.value[2][0] = _right.z;
		_view.value[3][0] = -(_right.dot(_pos / 2));
		_view.value[0][1] = _up.x;
		_view.value[1][1] = _up.y;
		_view.value[2][1] = _up.z;
		_view.value[3][1] = -(_up.dot(_pos / 2));
		_view.value[0][2] = _forward.x;
		_view.value[1][2] = _forward.y;
		_view.value[2][2] = _forward.z;
		_view.value[3][2] = -(_forward.dot(_pos / 2));
		_view.value[0][3] = 0;
		_view.value[1][3] = 0;
		_view.value[2][3] = 0;
		_view.value[3][3] = 1;
	}

	void Camera::compute_projection()
	{
		float		r;
		float		t;

		_projection = Matrix();
		r = 1.0f / (tan(degree_to_radian(_fov / 2.0f)));
		t = 1.0f / (tan(degree_to_radian(_fov / 2.0f))) / (g_application->size().x / g_application->size().y);
		_projection.value[0][0] = t;
		_projection.value[1][1] = r;
		_projection.value[2][2] = -_far / (_far - _near);
		_projection.value[2][3] = -1.0;
		_projection.value[3][2] = -(2 * _far * _near) / (_far - _near);
		_projection.value[3][3] = 0;
	}
}
