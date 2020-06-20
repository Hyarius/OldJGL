#include "jgl.h"

namespace jgl
{
	Vector2::Vector2(int p_value) :
		x(static_cast<float>(p_value)), y(static_cast<float>(p_value)) {}

	Vector2::Vector2(size_t p_value) :
		x(static_cast<float>(p_value)), y(static_cast<float>(p_value)) {}

	Vector2::Vector2(double p_value) :
		x(static_cast<float>(p_value)), y(static_cast<float>(p_value)) {}

	Vector2::Vector2(float p_value) :
		x(p_value), y(p_value) {}

	Vector2::Vector2(float p_x, float p_y) :
		x(p_x), y(p_y) {}

	Vector2::Vector2(int p_x, int p_y) :
		x(static_cast<float>(p_x)), y(static_cast<float>(p_y)) {}

	Vector2::Vector2(size_t p_x, size_t p_y) :
		x(static_cast<float>(p_x)), y(static_cast<float>(p_y)) {}

	Vector2::Vector2(double p_x, double p_y) :
		x(static_cast<float>(p_x)), y(static_cast<float>(p_y)) {}

	void Vector2::operator = (int p_value)
	{
		x = static_cast<float>(p_value);
		y = static_cast<float>(p_value);
	}

	void Vector2::operator = (float  p_value)
	{
		x = p_value;
		y = p_value;
	}

	Vector2		Vector2::operator + (const Vector2 delta) const {
		return (Vector2(x + delta.x, y + delta.y));
	}

	Vector2		Vector2::operator - (const Vector2 delta) const {
		return (Vector2(x - delta.x, y - delta.y));
	}

	Vector2		Vector2::operator * (const Vector2 delta) const {
		return (Vector2(x * delta.x, y * delta.y));
	}

	Vector2		Vector2::operator / (const Vector2 delta) const {
		return (Vector2(x / delta.x, y / delta.y));
	}

	void 		Vector2::operator += (const Vector2 delta) {
		x += delta.x; y += delta.y;
	}

	void 		Vector2::operator -= (const Vector2 delta) {
		x -= delta.x; y -= delta.y;
	}

	void 		Vector2::operator *= (const Vector2 delta) {
		x *= delta.x; y *= delta.y;
	}

	void 		Vector2::operator /= (const Vector2 delta) {
		x /= delta.x; y /= delta.y;
	}

	bool		Vector2::operator == (const Vector2 delta) const
	{
		return ((x == delta.x && y == delta.y) ? true : false);
	}

	bool		Vector2::operator != (const Vector2 delta) const
	{
		return ((x == delta.x && y == delta.y) ? false : true);
	}

	bool Vector2::operator < (const Vector2 other) const
	{
		if (y < other.y)
			return (true);
		if (y == other.y && x < other.x)
			return (true);
		return (false);
	}

	bool Vector2::operator > (const Vector2 other) const
	{
		if (y < other.y || x < other.x)
			return (false);
		return (true);
	}

	const float* Vector2::decompose() const
	{
		return (&x);
	}

	float Vector2::distance(Vector2 point) const
	{
		return (sqrt(pow(point.x - x, 2.0f)
			+ pow(point.y - y, 2.0f)));
	}

	Vector2		Vector2::normalize() const
	{
		float		length;

		length = sqrt((x * x) + (y * y));

		return (Vector2(x / length, y / length));
	}

	Vector2 Vector2::cross(Vector2 other) const
	{
		Vector2 result;

		result = Vector2(-(other.y - y), other.x - x);

		return (result);
	}

	float Vector2::dot(Vector2 other) const
	{
		float		result;

		result = x * other.x + y * other.y;

		return (result);
	}

	jgl::String Vector2::str() const
	{
		jgl::String result = "(" + ftoa(x, 2) + " / " + ftoa(y, 2) + ")";

		return (result);
	}

	jgl::String Vector2::text() const
	{
		jgl::String result = ftoa(x, 2) + " " + ftoa(y, 2);

		return (result);
	}

	Vector2 Vector2::floor() const
	{
		Vector2 result;

		result.x = std::floor(x);
		result.y = std::floor(y);

		return (result);
	}

	Vector2 Vector2::ceiling() const
	{
		Vector2 result;

		result.x = std::ceil(x);
		result.y = std::ceil(y);

		return (result);
	}

	Vector2 Vector2::invert() const
	{
		Vector2 result;

		result.x = x * -1;
		result.y = y * -1;

		return (result);
	}

	Vector3 Vector2::convert(int p_value) const
	{
		return (Vector3(x, y, (float)p_value));
	}

	Vector3 Vector2::convert(float p_value) const
	{
		return (Vector3(x, y, p_value));
	}
}