#include "jgl.h"

namespace jgl
{
	Vector4::Vector4(int p_value) :
		x(static_cast<float>(p_value)), y(static_cast<float>(p_value)),
		z(static_cast<float>(p_value)), w(static_cast<float>(p_value)) {}

	Vector4::Vector4(size_t p_value) :
		x(static_cast<float>(p_value)), y(static_cast<float>(p_value)),
		z(static_cast<float>(p_value)), w(static_cast<float>(p_value)) {}

	Vector4::Vector4(float p_value) :
		x(p_value), y(p_value), z(p_value), w(p_value) {}

	Vector4::Vector4(float p_x, float p_y, float p_z, float p_w) :
		x(p_x), y(p_y), z(p_z), w(p_w) {}

	Vector4::Vector4(int p_x, int p_y, int p_z, int p_w) :
		x(static_cast<float>(p_x)), y(static_cast<float>(p_y)),
		z(static_cast<float>(p_z)), w(static_cast<float>(p_w)) {}

	Vector4::Vector4(size_t p_x, size_t p_y, size_t p_z, size_t p_w) :
		x(static_cast<float>(p_x)), y(static_cast<float>(p_y)),
		z(static_cast<float>(p_z)), w(static_cast<float>(p_w)) {}

	Vector4::Vector4(double p_x, double p_y, double p_z, double p_w) :
		x(static_cast<float>(p_x)), y(static_cast<float>(p_y)),
		z(static_cast<float>(p_z)), w(static_cast<float>(p_w)) {}

	void Vector4::operator = (int p_value) {
		x = static_cast<float>(p_value);
		y = static_cast<float>(p_value);
		z = static_cast<float>(p_value);
		w = static_cast<float>(1);
	}

	void Vector4::operator = (float  p_value) {
		x = p_value;
		y = p_value;
		z = p_value;
		w = 1;
	}

	Vector4		Vector4::operator + (const Vector4 delta) const {
		return (Vector4(x + delta.x, y + delta.y, z + delta.z, 1.0f));
	}

	Vector4		Vector4::operator - (const Vector4 delta) const {
		return (Vector4(x - delta.x, y - delta.y, z - delta.z, 1.0f));
	}

	Vector4		Vector4::operator * (const Vector4 delta) const {
		return (Vector4(x * delta.x, y * delta.y, z * delta.z, 1.0f));
	}

	Vector4		Vector4::operator / (const Vector4 delta) const {
		return (Vector4(x / delta.x, y / delta.y, z / delta.z, 1.0f));
	}

	Vector4		Vector4::operator % (const Vector4 delta) const {
		return (Vector4(
			static_cast<int>(x) % static_cast<int>(delta.x),
			static_cast<int>(y) % static_cast<int>(delta.y),
			static_cast<int>(z) % static_cast<int>(delta.z),
			static_cast<int>(w) % static_cast<int>(delta.w)));
	}

	void 		Vector4::operator += (const Vector4 delta) {
		x += delta.x; y += delta.y; z += delta.z;
	}

	void 		Vector4::operator -= (const Vector4 delta) {
		x -= delta.x; y -= delta.y; z -= delta.z;
	}

	void 		Vector4::operator *= (const Vector4 delta) {
		x *= delta.x; y *= delta.y; z *= delta.z;
	}

	void 		Vector4::operator /= (const Vector4 delta) {
		x /= delta.x; y /= delta.y; z /= delta.z;
	}

	bool		Vector4::operator == (const Vector4 delta) const {
		return ((x == delta.x && y == delta.y && z == delta.z) ?
			true : false);
	}

	bool		Vector4::operator != (const Vector4 delta) const {
		return ((x == delta.x && y == delta.y && z == delta.z) ?
			false : true);
	}

	bool Vector4::operator < (const Vector4 other) const
	{
		if (z < other.z)
			return (true);
		if (z == other.z && y < other.y)
			return (true);
		if (z == other.z && y == other.y && x < other.x)
			return (true);
		return (false);
	}

	bool Vector4::operator > (const Vector4 other) const
	{
		if (z < other.z || y < other.y || x < other.x)
			return (false);
		return (true);
	}

	const float* Vector4::decompose() const {
		return (&x);
	}

	float Vector4::distance(Vector4 point) const
	{
		return (sqrt(pow(point.x - x, 2.0f)
			+ pow(point.y - y, 2.0f)
			+ pow(point.z - z, 2.0f)
		));
	}

	Vector4		Vector4::normalize() const
	{
		float		length;

		length = sqrt((x * x)
			+ (y * y)
			+ (z * z));

		return (Vector4(x / length, y / length, z / length, 1.0f));
	}

	float			Vector4::dot(Vector4 b) const
	{
		float		result;

		result = x * b.x + y * b.y + z * b.z;

		return (result);
	}

	Vector4		Vector4::cross(Vector4 other) const //Produit vectoriel / cross product
	{
		Vector4	result = Vector4(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x,
			1.0f
		);

		return (result);
	}

	jgl::String Vector4::str() const
	{
		jgl::String result = "(" + ftoa(x, 2) + " / " + ftoa(y, 2) + " / " + ftoa(z, 2) + " / " + ftoa(w, 2) + ")";

		return (result);
	}

	jgl::String Vector4::text() const
	{
		jgl::String result = ftoa(x, 2) + ";" + ftoa(y, 2) + ";" + ftoa(z, 2) + ";" + ftoa(w, 2);

		return (result);
	}

	Vector4 Vector4::floor() const
	{
		Vector4 result;

		result.x = std::floor(x);
		result.y = std::floor(y);
		result.z = std::floor(z);
		result.w = std::floor(w);

		return (result);
	}

	Vector4 Vector4::round() const
	{
		Vector4 result;

		result.x = std::round(x);
		result.y = std::round(y);
		result.z = std::round(z);
		result.w = std::round(w);

		return (result);
	}

	Vector4 Vector4::invert() const
	{
		Vector4 result;

		result.x = x * -1;
		result.y = y * -1;
		result.z = z * -1;
		result.w = w * -1;

		return (result);
	}
}