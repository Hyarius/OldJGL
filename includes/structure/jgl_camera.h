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

		Vector3 _light_pos;
		Vector3 _light_dir;
		Color _light_color;

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

		void calc_variable();
		void compute_model();
		void compute_view();
		void compute_projection();

	public:
		Camera(Vector3 p_pos = Vector3(), float p_fov = 45, float p_ratio = 4.0f / 3.0f, float p_near = 0.1f, float p_far = 50.0f);

		Vector3 mouse_direction(const jgl::Viewport* p_viewport = nullptr) const;

		void look_at(Vector3 target);
		void rotate_around_point(Vector3 target, float angle, Vector3 axis);
		void rotate(Vector3 delta);
		void move(Vector3 delta);
		void place(Vector3 p_pos);

		void compute() {compute_model(); compute_view(); compute_projection(); bake(); }

		void set_light_position(Vector3 p_light_pos) { _light_pos = p_light_pos; }
		void set_light_direction(Vector3 p_light_dir) { _light_dir = p_light_dir.normalize(); }
		void set_yaw(float p_yaw) { _yaw = p_yaw; }
		void set_pitch(float p_pitch) { _pitch = p_pitch; }
		void set_viewport(Viewport* p_viewport) { _viewport = p_viewport; }
		void set_fov(float p_fov) { _fov = p_fov; }
		void set_vision_range(float p_near, float p_far) { set_near(p_near); set_far(p_far); }
		void set_near(float p_near) { _near = p_near; }
		void set_far(float p_far) { _far = p_far; }

		const Viewport* viewport() const { return (_viewport); }
		const float pitch() const { return (_pitch); }
		const float yaw() const { return (_yaw); }
		float fov() const { return (_fov); }
		float ratio() const { return (_ratio); }
		float view_near() const { return (_near); }
		float view_far() const { return (_far); }
		const Matrix4x4& model() const { return (_model); }
		const Matrix4x4& view() const { return (_view); }
		const Matrix4x4& projection()const { return (_projection); }
		const Matrix4x4& MVP() const { return (_MVP); }
		const Vector3 light_dir() const { return (_light_dir); }
		const Vector3 light_pos() const { return (_light_pos); }
		const Color light_color() const { return (_light_color); }
		const Vector3 pos() const { return (_pos); }
		const Vector3 direction() const { return (_direction); }
		const Vector3 forward() const { return (_forward); }
		const Vector3 right() const { return (_right); }
		const Vector3 up() const { return (_up); }

		void bake() { _MVP = _projection * _view * _model; }
	};
}

std::ostream& operator<<(std::ostream& os, const jgl::Camera camera);
#endif
