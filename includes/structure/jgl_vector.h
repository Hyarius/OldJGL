#ifndef JGL_VECTOR_H
#define JGL_VECTOR_H

using namespace std;

struct Vector4
{
	float x;
	float y;
	float z;
	float w;

	Vector4(int p_value);
	Vector4(double p_value);
	Vector4(float p_value = -1);
	Vector4(float p_x, float p_y, float p_z, float p_w);
	Vector4(int p_x, int p_y, int p_z, int p_w);
	Vector4(double p_x, double p_y, double p_z, double p_w);

	Vector4& operator = (int p_value);
	Vector4& operator = (float p_value);

	Vector4 operator + (const Vector4 delta);
	Vector4 operator - (const Vector4 delta);
	Vector4 operator * (const Vector4 delta);
	Vector4 operator / (const Vector4 delta);
	void operator += (const Vector4 delta);
	void operator -= (const Vector4 delta);
	void operator *= (const Vector4 delta);
	void operator /= (const Vector4 delta);
	bool operator == (const Vector4 delta) const;
	bool operator != (const Vector4 delta) const;
	bool operator < (const Vector4 other) const;
	bool operator > (const Vector4 other) const;
	float *decompose();
	float distance(Vector4 point);
	Vector4 normalize();
	Vector4 cross(Vector4 other);
	float dot(Vector4 other);
	string str();
	Vector4 floor();
	Vector4 invert();
};

typedef Vector4 Vector3w;

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3(int p_value);
	Vector3(double p_value);
	Vector3(float p_value = -1);
	Vector3(float p_x, float p_y, float p_z);
	Vector3(int p_x, int p_y, int p_z);
	Vector3(double p_x, double p_y, double p_z);

	Vector3& operator = (int p_value);
	Vector3& operator = (float  p_value);

	Vector3 operator + (const Vector3 delta);
	Vector3 operator - (const Vector3 delta);
	Vector3 operator * (const Vector3 delta);
	Vector3 operator / (const Vector3 delta);
	void operator += (const Vector3 delta);
	void operator -= (const Vector3 delta);
	void operator *= (const Vector3 delta);
	void operator /= (const Vector3 delta);
	bool operator == (const Vector3 delta) const;
	bool operator != (const Vector3 delta) const;
	bool operator < (const Vector3 other) const;
	bool operator > (const Vector3 other) const;
	float *decompose();
	float distance(Vector3 point);
	Vector3 normalize();
	Vector3 cross(Vector3 other);
	float dot(Vector3 other);
	string str();
	Vector3 floor();
	Vector3 invert();
	Vector4 convert(int p_value);
	Vector4 convert(float p_value = 0);
};

struct Vector2
{
	float x;
	float y;

	Vector2(int p_value);
	Vector2(double p_value);
	Vector2(float p_value = -1);
	Vector2(float p_x, float p_y);
	Vector2(int p_x, int p_y);
	Vector2(double p_x, double p_y);

	Vector2& operator = (int p_value);
	Vector2& operator = (float  p_value);

	Vector2 operator + (const Vector2 delta);
	Vector2	operator - (const Vector2 delta);
	Vector2	operator * (const Vector2 delta);
	Vector2	operator / (const Vector2 delta);
	void operator += (const Vector2 delta);
	void operator -= (const Vector2 delta);
	void operator *= (const Vector2 delta);
	void operator /= (const Vector2 delta);
	bool operator == (const Vector2 delta) const;
	bool operator != (const Vector2 delta) const;
	bool operator < (const Vector2 other) const;
	bool operator > (const Vector2 other) const;
	float *decompose();
	float distance(Vector2 point);
	Vector2 cross(Vector2 other);
	Vector2 normalize();
	float dot(Vector2 other);
	string str();
	Vector2 floor();
	Vector2 invert();
	Vector3 convert(int p_value);
	Vector3 convert(float p_value = 0);
};

ostream& operator<<(ostream& os, Vector2 value);

ostream& operator<<(ostream& os, Vector3 value);

ostream& operator<<(ostream& os, Vector4 value);

#endif
