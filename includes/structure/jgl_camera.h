#ifndef JGL_CAMERA_H
#define JGL_CAMERA_H

class c_camera
{
private:
	c_viewport *viewport;

	Matrix	model;
	Matrix	view;
	Matrix	projection;

	float		pitch;
	float		yaw;
public:
	c_camera();
};

#endif
