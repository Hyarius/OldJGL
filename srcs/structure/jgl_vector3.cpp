#include "jgl.h"

namespace jgl
{

	Vector3::Vector3(Vector4 other) :
		x(other.x), y(other.y), z(other.z) {}

	Vector3::Vector3(int p_value) :
		x(static_cast<float>(p_value)), y(static_cast<float>(p_value)),
		z(static_cast<float>(p_value)) {}

	Vector3::Vector3(size_t p_value) :
		x(static_cast<float>(p_value)), y(static_cast<float>(p_value)),
		z(static_cast<float>(p_value)) {}

	Vector3::Vector3(double p_value) :
		x(static_cast<float>(p_value)), y(static_cast<float>(p_value)),
		z(static_cast<float>(p_value)) {}

	Vector3::Vector3(float p_value) :
		x(p_value), y(p_value), z(p_value) {}

	Vector3::Vector3(float p_x, float p_y, float p_z) :
		x(p_x), y(p_y), z(p_z) {}

	Vector3::Vector3(int p_x, int p_y, int p_z) :
		x(static_cast<float>(p_x)), y(static_cast<float>(p_y)),
		z(static_cast<float>(p_z)) {}

	Vector3::Vector3(size_t p_x, size_t p_y, size_t p_z) :
		x(static_cast<float>(p_x)), y(static_cast<float>(p_y)),
		z(static_cast<float>(p_z)) {}

	Vector3::Vector3(double p_x, double p_y, double p_z) :
		x(static_cast<float>(p_x)), y(static_cast<float>(p_y)),
		z(static_cast<float>(p_z)) {}

	Vector3& Vector3::operator = (Vector4 other){
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	Vector3& Vector3::operator = (int p_value) {
		x = static_cast<float>(p_value);
		y = static_cast<float>(p_value);
		z = static_cast<float>(p_value);
		return *this;
	}

	Vector3& Vector3::operator = (float  p_value) {
		x = p_value;
		y = p_value;
		z = p_value;
		return *this;
	}

	Vector3		Vector3::operator + (const Vector3 delta) const {
		return (Vector3(x + delta.x, y + delta.y, z + delta.z));
	}

	Vector3		Vector3::operator - (const Vector3 delta) const {
		return (Vector3(x - delta.x, y - delta.y, z - delta.z));
	}

	Vector3		Vector3::operator * (const Vector3 delta) const {
		return (Vector3(x * delta.x, y * delta.y, z * delta.z));
	}

	Vector3		Vector3::operator / (const Vector3 delta) const {
		return (Vector3(x / delta.x, y / delta.y, z / delta.z));
	}

	void 		Vector3::operator += (const Vector3 delta) {
		x += delta.x; y += delta.y; z += delta.z;
	}

	void 		Vector3::operator -= (const Vector3 delta) {
		x -= delta.x; y -= delta.y; z -= delta.z;
	}

	void 		Vector3::operator *= (const Vector3 delta) {
		x *= delta.x; y *= delta.y; z *= delta.z;
	}

	void 		Vector3::operator /= (const Vector3 delta) {
		x /= delta.x; y /= delta.y; z /= delta.z;
	}

	bool		Vector3::operator == (const Vector3 delta) const {
		return ((x == delta.x && y == delta.y && z == delta.z) ?
			true : false);
	}

	bool		Vector3::operator != (const Vector3 delta) const {
		return ((x == delta.x && y == delta.y && z == delta.z) ?
			false : true);
	}

	bool Vector3::operator < (const Vector3 other) const
	{
		if (z < other.z)
			return (true);
		if (z == other.z && y < other.y)
			return (true);
		if (z == other.z && y == other.y && x < other.x)
			return (true);
		return (false);
	}

	bool Vector3::operator > (const Vector3 other) const
	{
		if (z < other.z || y < other.y || x < other.x)
			return (false);
		return (true);
	}

	const float* Vector3::decompose() const {
		return (&x);
	}
	float Vector3::length() const
	{
		return (sqrt(pow(x, 2.0f)
			+ pow(y, 2.0f)
			+ pow(z, 2.0f)));
	}

	float Vector3::distance(Vector3 point) const
	{
		return (sqrt(pow(point.x - x, 2.0f)
			+ pow(point.y - y, 2.0f)
			+ pow(point.z - z, 2.0f)));
	}

	Vector3		Vector3::normalize() const
	{
		float		length;

		length = sqrt((x * x)
			+ (y * y)
			+ (z * z));

		return (Vector3(x / length, y / length, z / length));
	}

	float			Vector3::dot(Vector3 b) const
	{
		float		result;

		result = x * b.x + y * b.y + z * b.z;

		return (result);
	}

	Vector3		Vector3::cross(Vector3 other) const //Produit vectoriel / cross product
	{
		Vector3	result = Vector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);

		return (result);
	}

	jgl::String Vector3::str() const
	{
		jgl::String result = "(" + jgl::ftoa(x, 3) + " / " + jgl::ftoa(y, 3) + " / " + jgl::ftoa(z, 3) + ")";

		return (result);
	}

	jgl::String Vector3::text() const
	{
		jgl::String result = jgl::ftoa(x, 2) + " " + jgl::ftoa(y, 2) + " " + jgl::ftoa(z, 2);

		return (result);
	}

	Vector3 Vector3::floor() const
	{
		Vector3 result;

		result.x = static_cast<float>(std::floor(x));
		result.y = static_cast<float>(std::floor(y));
		result.z = static_cast<float>(std::floor(z));

		return (result);
	}

	Vector3 Vector3::invert() const
	{
		Vector3 result;

		result.x = x * -1;
		result.y = y * -1;
		result.z = z * -1;

		return (result);
	}

	Vector4 Vector3::convert(int p_value) const
	{
		return (Vector4(x, y, z, (float)p_value));
	}

	Vector4 Vector3::convert(float p_value) const
	{
		return (Vector4(x, y, z, p_value));
	}
}