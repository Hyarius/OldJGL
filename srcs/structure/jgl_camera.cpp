#include "jgl.h"

c_camera::c_camera(Vector3 p_pos, float p_pitch, float p_yaw)
{
	_pos = p_pos;

	_fov = 70.0f;
	_near = 0.01f;
	_far = 50.0f;
	_pitch = p_pitch;
	_yaw = p_yaw;

	_forward = Vector3(1, 0, 0);
	_right = Vector3(0, 0, 1);
	_up = Vector3(0, 1, 0);

	compute();
}

void c_camera::look_at(Vector3 target)
{
	Vector3	result;

	result = (_pos - target).normalize();
	_yaw = radius_to_degree(atan2(result.z, -result.x)) - 90;
	_pitch = radius_to_degree(atan2(result.y,
				sqrt(result.x * result.x + result.z * result.z)));
	_pitch = clamp_float(-89, _pitch, 89);
	compute_axis();
}

void c_camera::rotate(float pitch, float yaw)
{
	_pitch = clamp_float(-89.0f, _pitch + pitch, 89.0f);
	_yaw += yaw;
	if (_yaw < 0)
		_yaw += 360;
	if (_yaw > 360)
		_yaw -= 360;
	compute_axis();
}

void c_camera::move(Vector3 delta)
{
	_pos += delta;

	compute();
}

void c_camera::place(Vector3 p_pos)
{
	_pos = p_pos;

	compute();
}

void c_camera::compute_axis()
{
	float tmp_yaw = degree_to_radius(_yaw);
	float tmp_pitch = degree_to_radius(_pitch);

	_right = (Vector3(cos(tmp_pitch) * sin(tmp_yaw), sin(tmp_pitch), cos(tmp_pitch) * cos(tmp_yaw)) ).normalize();
	_forward = (Vector3( sin(tmp_yaw - 3.14f / 2.0f), 0.0f, cos(tmp_yaw - 3.14f / 2.0f))).normalize();
	_up = ((_forward).cross(_right)).normalize();
}

void c_camera::compute_model()
{
	_model = Matrix();
	_model.value[0][3] = _pos.x;
	_model.value[1][3] = _pos.y;
	_model.value[2][3] = _pos.z;
}

void c_camera::compute_view()
{
	_view = Matrix();
	_view.value[0][0] = _right.x;
	_view.value[1][0] = _right.y;
	_view.value[2][0] = _right.z;
	_view.value[3][0] = -(_right.dot(_pos));
	_view.value[0][1] = _up.x;
	_view.value[1][1] = _up.y;
	_view.value[2][1] = _up.z;
	_view.value[3][1] = -(_up.dot(_pos));
	_view.value[0][2] = _forward.x;
	_view.value[1][2] = _forward.y;
	_view.value[2][2] = _forward.z;
	_view.value[3][2] = -(_forward.dot(_pos));
}
void c_camera::compute_projection()
{
	float		n;
	float		r;
	float		f;
	float		t;

	_projection = Matrix();
	r = 1.0 / (tan(degree_to_radius(_fov / 2.0)));
	t = 1.0 / (tan(degree_to_radius(_fov / 2.0))) / (4.0 / 3.0);
	_projection.value[0][0] = t;
	_projection.value[1][1] = r;
	_projection.value[2][2] = _far / (_far - _near);
	_projection.value[2][3] = 1.0;
	_projection.value[3][2] = -(2 * _far * _near) / (_far - _near);
}
