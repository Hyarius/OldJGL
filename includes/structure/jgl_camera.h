#ifndef JGL_CAMERA_H
#define JGL_CAMERA_H

namespace jgl
{
	class Camera
	{
	protected:
		Viewport* _viewport;

		Matrix4x4 _model;
		Matrix4x4 _view;
		Matrix4x4 _projection;
		Matrix4x4 _MVP;
		Matrix4x4 _MVP_pos;

		Vector3 _dir_light;

		Vector3 _pos;
		float _yaw;
		float _pitch;
		Vector3 _direction;

		Vector3 _forward;
		Vector3 _right;
		Vector3 _up;

		float _ratio;
		float _fov;
		float _near;
		float _far;

	public:
		Camera(Vector3 p_pos = Vector3(), float p_fov = 45, float p_ratio = 4.0f / 3.0f, float p_near = 0.01f, float p_far = 50.0f);

		Vector3 mouse_direction();

		void look_at(Vector3 target);
		void rotate_around_point(Vector3 target, float angle, Vector3 axis);
		void rotate(Vector3 delta);
		void move(Vector3 delta);
		void place(Vector3 p_pos);

		void calc_variable();
		void compute_model();
		void compute_view();
		void compute_projection();
		void compute() {compute_model(); compute_view(); compute_projection(); bake(); }

		void set_yaw(float p_yaw) { _yaw = p_yaw; }
		void set_pitch(float p_pitch) { _pitch = p_pitch; }
		void set_viewport(Viewport* p_viewport) { _viewport = p_viewport; }
		void set_fov(float p_fov) { _fov = p_fov; }
		void set_vision_range(float p_near, float p_far) { set_near(p_near); set_far(p_far); }
		void set_near(float p_near) { _near = p_near; }
		void set_far(float p_far) { _far = p_far; }

		Viewport* viewport() { return (_viewport); }
		float pitch() { return (_pitch); }
		float yaw() { return (_yaw); }
		float fov() { return (_fov); }
		float ratio() { return (_ratio); }
		float view_near() { return (_near); }
		float view_far() { return (_far); }
		Matrix4x4 model() { return (_model); }
		Matrix4x4 view() { return (_view); }
		Matrix4x4 projection() { return (_projection); }
		void bake() { _MVP = _projection * _view * _model; }
		Matrix4x4& MVP() { return (_MVP); }
		Vector3 dir_light() { return (_dir_light); }
		Vector3 pos() { return (_pos); }
		Vector3 direction() { return (_direction); }
		Vector3 forward() { return (_forward); }
		Vector3 right() { return (_right); }
		Vector3 up() { return (_up); }
	};
}

std::ostream& operator<<(std::ostream& os, jgl::Camera camera);
#endif
