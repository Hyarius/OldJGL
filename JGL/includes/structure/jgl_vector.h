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
		Vector4(uint32_t p_value);
		Vector4(float p_value = -1);
		Vector4(float p_x, float p_y, float p_z, float p_w);
		Vector4(int p_x, int p_y, int p_z, int p_w);
		Vector4(uint32_t p_x, uint32_t p_y, uint32_t p_z, uint32_t p_w);
		Vector4(double p_x, double p_y, double p_z, double p_w);

		void operator = (int p_value);
		void operator = (float p_value);

		Vector4 operator + (const Vector4 delta) const;
		Vector4 operator - (const Vector4 delta) const;
		Vector4 operator * (const Vector4 delta) const;
		Vector4 operator / (const Vector4 delta) const;
		Vector4 operator % (const Vector4 delta) const;
		void operator += (const Vector4 delta);
		void operator -= (const Vector4 delta);
		void operator *= (const Vector4 delta);
		void operator /= (const Vector4 delta);
		bool operator == (const Vector4 delta) const;
		bool operator != (const Vector4 delta) const;
		bool operator < (const Vector4 other) const;
		bool operator > (const Vector4 other) const;
		const float* decompose() const;
		float distance(Vector4 point) const;
		Vector4 normalize() const;
		Vector4 cross(Vector4 other) const;
		float dot(Vector4 other) const;
		jgl::String str() const;
		jgl::String text() const;
		Vector4 floor() const;
		Vector4 round() const;
		Vector4 invert() const;

		friend std::ostream& operator<<(std::ostream& os, const jgl::Vector4 value)
		{
			os << value.str();
			return os;
		}
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
		Vector3(struct Vector2 p_other);
		Vector3(int p_value);
		Vector3(uint32_t p_value);
		Vector3(double p_value);
		Vector3(float p_value = -1);
		Vector3(float p_x, float p_y, float p_z);
		Vector3(int p_x, int p_y, int p_z);
		Vector3(uint32_t p_x, uint32_t p_y, uint32_t p_z);
		Vector3(double p_x, double p_y, double p_z);

		void operator = (Vector4 p_other);
		void operator = (int p_value);
		void operator = (float  p_value);

		Vector3 operator + (const Vector3 delta) const;
		Vector3 operator - (const Vector3 delta) const;
		Vector3 operator * (const Vector3 delta) const;
		Vector3 operator / (const Vector3 delta) const;
		Vector3 operator % (const Vector3 delta) const;
		void operator += (const Vector3 delta);
		void operator -= (const Vector3 delta);
		void operator *= (const Vector3 delta);
		void operator /= (const Vector3 delta);
		bool operator == (const Vector3 delta) const;
		bool operator != (const Vector3 delta) const;
		bool operator < (const Vector3 other) const;
		bool operator > (const Vector3 other) const;
		const float* decompose() const;
		float length() const;
		float distance(Vector3 point) const;
		Vector3 normalize() const;
		Vector3 cross(Vector3 other) const;
		float dot(Vector3 other) const;
		jgl::String str() const;
		jgl::String text() const;
		float angle(Vector3 other);
		Vector3 floor() const;
		Vector3 round() const;
		Vector3 invert() const;
		Vector4 convert(int p_value) const;
		Vector4 convert(float p_value = 0) const;

		friend std::ostream& operator<<(std::ostream& os, const jgl::Vector3 value)
		{
			os << value.str();
			return os;
		}
	};

	struct Vector2
	{
		float x;
		float y;

		Vector2(int p_value);
		Vector2(uint32_t p_value);
		Vector2(double p_value);
		Vector2(float p_value = -1);
		Vector2(float p_x, float p_y);
		Vector2(int p_x, int p_y);
		Vector2(uint32_t p_x, uint32_t p_y);
		Vector2(double p_x, double p_y);

		void operator = (int p_value);
		void operator = (float  p_value);

		Vector2 operator + (const Vector2 delta) const;
		Vector2	operator - (const Vector2 delta) const;
		Vector2	operator * (const Vector2 delta) const;
		Vector2	operator / (const Vector2 delta) const;
		Vector2 operator % (const Vector2 delta) const;
		void operator += (const Vector2 delta);
		void operator -= (const Vector2 delta);
		void operator *= (const Vector2 delta);
		void operator /= (const Vector2 delta);
		bool operator == (const Vector2 delta) const;
		bool operator != (const Vector2 delta) const;
		bool operator < (const Vector2 other) const;
		bool operator > (const Vector2 other) const;
		const float* decompose() const;
		float distance(Vector2 point) const;
		Vector2 cross(Vector2 other) const;
		Vector2 normalize() const;
		float dot(Vector2 other) const;
		jgl::String str() const;
		jgl::String text() const;
		float angle(Vector2 other);
		Vector2 floor() const;
		Vector2 ceiling() const;
		Vector2 round() const;
		Vector2 invert() const;
		Vector3 convert(int p_value) const;
		Vector3 convert(float p_value = 0) const;
		Vector2 rotate(Vector2 center, float angle);

		friend std::ostream& operator<<(std::ostream& os, const jgl::Vector2 value)
		{
			os << value.str();
			return os;
		}
	};
}

#endif
