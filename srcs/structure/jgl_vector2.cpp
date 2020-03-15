#include "jgl.h"

using namespace std;

Vector2::Vector2(int p_value) :
	x(static_cast<float>(p_value)), y(static_cast<float>(p_value)){}

Vector2::Vector2(double p_value) :
	x(static_cast<float>(p_value)), y(static_cast<float>(p_value)){}

Vector2::Vector2(float p_value) :
	x(p_value), y(p_value){}

Vector2::Vector2(float p_x, float p_y) :
	x(p_x), y(p_y){}

Vector2::Vector2(int p_x, int p_y) :
	x(static_cast<float>(p_x)), y(static_cast<float>(p_y)){}

Vector2::Vector2(double p_x, double p_y) :
	x(static_cast<float>(p_x)), y(static_cast<float>(p_y)){}

Vector2&		Vector2::operator = (int p_value)
{
	x = static_cast<float>(p_value);
	y = static_cast<float>(p_value);
	return *this;
}

Vector2& Vector2::operator = (float  p_value)
{
	x = p_value;
	y = p_value;
	return *this;
}

Vector2		Vector2::operator + (const Vector2 delta){
	return (Vector2(x + delta.x, y + delta.y));
}

Vector2		Vector2::operator - (const Vector2 delta){
	return (Vector2(x - delta.x, y - delta.y));
}

Vector2		Vector2::operator * (const Vector2 delta){
	return (Vector2(x * delta.x, y * delta.y));
}

Vector2		Vector2::operator / (const Vector2 delta){
	return (Vector2(x / delta.x, y / delta.y));
}

void 		Vector2::operator += (const Vector2 delta){
    x += delta.x; y += delta.y;
}

void 		Vector2::operator -= (const Vector2 delta){
    x -= delta.x; y -= delta.y;
}

void 		Vector2::operator *= (const Vector2 delta){
    x *= delta.x; y *= delta.y;
}

void 		Vector2::operator /= (const Vector2 delta){
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

float *Vector2::decompose()
{
	return (&x);
}

float Vector2::distance(Vector2 point)
{
	return (sqrt( pow(point.x - x, 2.0f)
				+ pow(point.y - y, 2.0f)));
}

Vector2		Vector2::normalize()
{
	float		length;

	length = sqrt((x * x) + (y * y));

	return (Vector2(x / length, y / length));
}

Vector2 Vector2::cross(Vector2 other)
{
	Vector2 result;

	result = Vector2(-(other.y - y), other.x - x);

	return (result);
}

float Vector2::dot(Vector2 other)
{
	float		result;

	result = x * other.x + y * other.y;

	return (result);
}

string Vector2::str()
{
	string result = "(" + ftoa(x, 2) + " / " + ftoa(y, 2) + ")";

	return (result);
}

Vector2 Vector2::floor()
{
	Vector2 result;

	result.x = std::floor(x);
	result.y = std::floor(y);

	return (result);
}

Vector2 Vector2::invert()
{
	x *= -1;
	y *= -1;
	return (*this);
}

Vector3 Vector2::convert(int p_value)
{
	return (Vector3(x, y, (float)p_value));
}

Vector3 Vector2::convert(float p_value)
{
	return (Vector3(x, y, p_value));
}
