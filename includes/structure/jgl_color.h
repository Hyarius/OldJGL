#ifndef JGL_COLOR_H
#define JGL_COLOR_H

#define CALC(value) ((value % 256) / 255.0f)

struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color();
	Color(float p_r, float p_g, float p_b, float p_a = 1.0f);
	Color(unsigned char p_r, unsigned char p_g, unsigned char p_b, unsigned char p_a = 255);

	float *decompose();

	Color operator + (const Color& delta);

};

ostream& operator<<(ostream& os, Color value);

#endif
