#include "jgl.h"

namespace jgl
{
	Camera::Camera(Vector3 p_pos, float p_fov, float p_ratio, float p_near, float p_far)
	{
		_pitch = 0;
		_yaw = 0;
		_direction = Vector3(0, 0, 1);
		_pos = p_pos;
		_forward = Vector3(0, 0, 1);
		_right = Vector3(1, 0, 0);
		_up = Vector3(0, 1, 0);

		_dir_light = Vector3(0.0f, -1.0f, 0.0f);
		_dir_light = _dir_light.normalize();

		_fov = p_fov;
		_ratio = p_ratio;
		_near = p_near;
		_far = p_far;

		compute();
	}

	void Camera::calc_variable()
	{
		_yaw = radian_to_degree(atan2(_direction.z, -_direction.x)) - 90;
		_pitch = radian_to_degree(atan2(_direction.y, sqrt(pow(_direction.x, 2) + pow(_direction.z, 2))));
		_pitch = clamp_float(-89.0f, _pitch, 89.0f);
		_right = Vector3(_view[0][0], _view[1][0], _view[2][0]);
		_up = Vector3(_view[0][1], _view[1][1], _view[2][1]);
		_forward = Vector3(_view[0][2], _view[1][2], _view[2][2]);
	}


	void Camera::look_at(Vector3 target)
	{
		_direction = (target - _pos).normalize();
		calc_variable();
		compute();
	}

	void Camera::rotate_around_point(Vector3 target, float angle, Vector3 axis)
	{
		Vector3 tmp;
		Matrix4x4 rotation = jgl::Matrix4x4::matrix_custom_rotation(angle, axis);

		tmp = _pos - target;
		tmp = rotation * tmp;
		_pos = tmp + target;
		calc_variable();
		compute();
	}


	jgl::Vector3 Camera::mouse_direction()
	{
		float mouseX = g_mouse->pos.x / (g_application->size().x / 2) - 1.0f;
		float mouseY = 1.0f - g_mouse->pos.y / (g_application->size().y / 2);

		jgl::Vector4 screen_pos = jgl::Vector4(mouseX, mouseY, -1.0f, 1.0f);
		jgl::Matrix4x4 inv_proj = projection().inverse_matrix();
		jgl::Matrix4x4 inv_view = view().inverse_matrix();

		jgl::Vector4 ray_eye = inv_proj * screen_pos;
		ray_eye.z = -1;
		ray_eye.w = 0;

		Vector4 dir = inv_view * ray_eye;
		Vector3 result = dir.normalize();
		return (result);
	}

	void Camera::rotate(Vector3 delta)
	{
		Matrix4x4 rotation(Matrix_type::rotation, delta.x, delta.y, delta.z);

		_direction = rotation * _direction;
		calc_variable();
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
		_model = Matrix4x4();
	}

	void Camera::compute_view()
	{ 
		_view = Matrix4x4::matrix_look_at(_pos, _pos + _direction, _up);
		calc_variable();
	}

	void Camera::compute_projection()
	{
		float		r;
		float		t;

		_projection = Matrix4x4();
		r = 1.0f / (tan(degree_to_radian(_fov / 2.0f)));
		t = 1.0f / (tan(degree_to_radian(_fov / 2.0f))) / _ratio;
		_projection.value[0][0] = t;
		_projection.value[1][1] = r;
		_projection.value[2][2] = -_far / (_far - _near);
		_projection.value[2][3] = -1.0;
		_projection.value[3][2] = -(2 * _far * _near) / (_far - _near);
		_projection.value[3][3] = 0;
	}
}
