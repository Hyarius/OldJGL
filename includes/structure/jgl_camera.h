#ifndef JGL_CAMERA_H
#define JGL_CAMERA_H

namespace jgl
{
	class Camera
	{
	protected:
		Viewport* _viewport;

		Matrix _model;
		Matrix _view;
		Matrix _projection;
		Matrix _MVP;
		Matrix _MVP_pos;

		Vector3 _dir_light;

		Vector3 _pos;
		Vector3 _forward;
		Vector3 _right;
		Vector3 _up;

		float _fov;
		float _near;
		float _far;
		float _pitch;
		float _yaw;

	public:
		Camera(Vector3 p_pos = Vector3(), float p_fov = 45, float p_near = 0.01f, float p_far = 50.0f);

		void look_at(Vector3 target);
		void rotate_around_point(Vector3 point, Vector3 angle);
		void rotate(float pitch, float yaw);
		void move(Vector3 delta);
		void place(Vector3 p_pos);

		void actualize();
		void compute_model();
		void compute_view();
		void compute_projection();
		void compute() { actualize(); compute_model(); compute_view(); compute_projection(); bake(); }

		void set_viewport(Viewport* p_viewport) { _viewport = p_viewport; }
		void set_yaw(float p_yaw) { _yaw = p_yaw; }
		void set_pitch(float p_pitch) { _pitch = p_pitch; }
		void set_fov(float p_fov) { _fov = p_fov; }
		void set_vision_range(float p_near, float p_far) { set_near(p_near); set_far(p_far); }
		void set_near(float p_near) { _near = p_near; }
		void set_far(float p_far) { _far = p_far; }

		Viewport* viewport() { return (_viewport); }
		float fov() { return (_fov); }
		float view_near() { return (_near); }
		float view_far() { return (_far); }
		float yaw() { return (_yaw); }
		float pitch() { return (_pitch); }
		Matrix model() { return (_model); }
		Matrix view() { return (_view); }
		Matrix projection() { return (_projection); }
		void bake() { _MVP = _projection * _view * _model; }
		Matrix& MVP() { return (_MVP); }
		Vector3 dir_light() { return (_dir_light); }
		Vector3 pos() { return (_pos); }
		Vector3 forward() { return (_forward); }
		Vector3 right() { return (_right); }
		Vector3 up() { return (_up); }
	};
}
#endif
