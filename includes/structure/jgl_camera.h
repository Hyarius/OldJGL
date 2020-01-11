#ifndef JGL_CAMERA_H
#define JGL_CAMERA_H

class c_camera
{
private:
	c_viewport *_viewport;

	Matrix _model;
	Matrix _view;
	Matrix _projection;

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
	c_camera(Vector3 p_pos = Vector3(), float p_pitch = 0.0f, float p_yaw = 0.0f);

	void look_at(Vector3 target);
	void rotate(float pitch, float yaw);
	void move(Vector3 delta);
	void place(Vector3 p_pos);

	void compute_axis();
	void compute_model();
	void compute_view();
	void compute_projection();
	void compute(){compute_axis();compute_model();compute_view();compute_projection();}

	void set_viewport(c_viewport *p_viewport){_viewport = p_viewport;}
	void set_yaw(float p_yaw){_yaw = p_yaw;}
	void set_pitch(float p_pitch){_pitch = p_pitch;}
	void set_fov(float p_fov){_fov = p_fov;}
	void set_vision_range(float p_near, float p_far){set_near(p_near);set_far(p_far);}
	void set_near(float p_near){_near = p_near;}
	void set_far(float p_far){_far = p_far;}

	c_viewport *viewport(){return (_viewport);}
	float fov(){return (_fov);}
	float near(){return (_near);}
	float far(){return (_far);}
	float yaw(){return (_yaw);}
	float pitch(){return (_pitch);}
	Matrix model(){return (_model);}
	Matrix view(){return (_view);}
	Matrix projection(){return (_projection);}
	Matrix MVP(){compute();return (_projection * _view * _model);}
	Vector3 pos(){return (_pos);}
	Vector3 forward(){return (_forward);}
	Vector3 right(){return (_right);}
	Vector3 up(){return (_up);}
};

#endif
