#include "jgl.h"

c_camera::c_camera(Vector3 p_pos, float p_fov, float p_near, float p_far)
{
	_pos = p_pos;

	_fov = p_fov;
	_near = p_near;
	_far = p_far;

	_forward = Vector3(1, 0, 0);
	_right = Vector3(0, 0, 1);
	_up = Vector3(0, 1, 0);

	compute();
}

void c_camera::look_at(Vector3 target)
{
	_forward = (_pos - target).normalize();    // The "forward" vector.
	_right = ((Vector3(0, 1, 0)).cross(_forward)).normalize();// The "right" vector.
	_up = ((_forward).cross(_right)).normalize();
	compute_view();
}

void c_camera::rotate_around_point(Vector3 target, Vector3 delta)
{
	Matrix translate;
	Matrix axis_mat;
	Matrix inv_axis_mat;
	Matrix rotation;
	Matrix inv_translate;
	int			i;

	translate = Matrix( T, target - _pos);
	inv_translate = Matrix( T, (target - _pos).invert());
	rotation = Matrix( R, delta.x, delta.y, delta.z);

	_pos = inv_translate * _pos;
	_pos = rotation * _pos;
	_pos = translate * _pos;
	_forward = rotation * _forward;
	_right = rotation * _right;
	_up = rotation * _up;
}

void c_camera::rotate(float pitch, float yaw)
{

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

void c_camera::compute_model()
{
	_model = Matrix();
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
	_view.value[0][3] = 0;
	_view.value[1][3] = 0;
	_view.value[2][3] = 0;
	_view.value[3][3] = 1;
}

void c_camera::compute_projection()
{
	float		n;
	float		r;
	float		f;
	float		t;

	_projection = Matrix();
	r = 1.0 / (tan(degree_to_radius(_fov / 2.0f)));
	t = 1.0 / (tan(degree_to_radius(_fov / 2.0f))) / (4.0 / 3.0);
	_projection.value[0][0] = t;
	_projection.value[1][1] = r;
	_projection.value[2][2] = -_far / (_far - _near);
	_projection.value[2][3] = -1.0;
	_projection.value[3][2] = -(2 * _far * _near) / (_far - _near);
	_projection.value[3][3] = 0;
}
