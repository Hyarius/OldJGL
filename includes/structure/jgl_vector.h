#ifndef JGL_VECTOR_H
#define JGL_VECTOR_H

namespace jgl
{
	struct Vector4
	{
		float x;
		float y;
		float z;
		float w;

		Vector4(int p_value);
		Vector4(size_t p_value);
		Vector4(float p_value = -1);
		Vector4(float p_x, float p_y, float p_z, float p_w);
		Vector4(int p_x, int p_y, int p_z, int p_w);
		Vector4(size_t p_x, size_t p_y, size_t p_z, size_t p_w);
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
		float* decompose();
		float distance(Vector4 point);
		Vector4 normalize();
		Vector4 cross(Vector4 other);
		float dot(Vector4 other);
		jgl::String str();
		jgl::String text();
		Vector4 floor();
		Vector4 invert();
	};

	typedef Vector4 Vector3w;

	struct Vector3
	{
		float x;
		float y;
		float z;

		static Vector3 up() { return (Vector3(0, 1, 0)); }
		static Vector3 right() { return (Vector3(0, 0, 1)); }
		static Vector3 front() { return (Vector3(1, 0, 0)); }
		static Vector3 zero() { return (0); }

		Vector3(Vector4 p_other);
		Vector3(int p_value);
		Vector3(size_t p_value);
		Vector3(double p_value);
		Vector3(float p_value = -1);
		Vector3(float p_x, float p_y, float p_z);
		Vector3(int p_x, int p_y, int p_z);
		Vector3(size_t p_x, size_t p_y, size_t p_z);
		Vector3(double p_x, double p_y, double p_z);

		Vector3& operator = (Vector4 p_other);
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
		float* decompose();
		float length();
		float distance(Vector3 point);
		Vector3 normalize();
		Vector3 cross(Vector3 other);
		float dot(Vector3 other);
		jgl::String str();
		jgl::String text();
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
		Vector2(size_t p_value);
		Vector2(double p_value);
		Vector2(float p_value = -1);
		Vector2(float p_x, float p_y);
		Vector2(int p_x, int p_y);
		Vector2(size_t p_x, size_t p_y);
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
		float* decompose();
		float distance(Vector2 point);
		Vector2 cross(Vector2 other);
		Vector2 normalize();
		float dot(Vector2 other);
		jgl::String str();
		jgl::String text();
		Vector2 floor();
		Vector2 ceiling();
		Vector2 invert();
		Vector3 convert(int p_value);
		Vector3 convert(float p_value = 0);
	};
}

std::ostream& operator<<(std::ostream& os, jgl::Vector2 value);

std::ostream& operator<<(std::ostream& os, jgl::Vector3 value);

std::ostream& operator<<(std::ostream& os, jgl::Vector4 value);

#endif
