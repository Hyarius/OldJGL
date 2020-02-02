#include "jgl.h"

using namespace std;

Vector4::Vector4(int p_value) :
	x(static_cast<float>(p_value)), y(static_cast<float>(p_value)),
	z(static_cast<float>(p_value)), w(static_cast<float>(p_value)){}

Vector4::Vector4(float p_value) :
	x(p_value), y(p_value), z(p_value), w(p_value){}

Vector4::Vector4(float p_x, float p_y, float p_z, float p_w) :
	x(p_x), y(p_y), z(p_z), w(p_w){}

Vector4::Vector4(int p_x, int p_y, int p_z, int p_w) :
	x(static_cast<float>(p_x)), y(static_cast<float>(p_y)),
	z(static_cast<float>(p_z)), w(static_cast<float>(p_w)){}

Vector4::Vector4(double p_x, double p_y, double p_z, double p_w) :
	x(static_cast<float>(p_x)), y(static_cast<float>(p_y)),
	z(static_cast<float>(p_z)), w(static_cast<float>(p_w)){}

Vector4&		Vector4::operator = (int p_value) {
	x = static_cast<float>(p_value);
	y = static_cast<float>(p_value);
	z = static_cast<float>(p_value);
	w = static_cast<float>(1);
	return *this;
}

Vector4& Vector4::operator = (float  p_value) {
	x = p_value;
	y = p_value;
	z = p_value;
	w = 1;
	return *this;
}

Vector4		Vector4::operator + (const Vector4& delta){
	return (Vector4(x + delta.x, y + delta.y, z + delta.z, 1.0f));
}

Vector4		Vector4::operator - (const Vector4& delta){
	return (Vector4(x - delta.x, y - delta.y, z - delta.z, 1.0f));
}

Vector4		Vector4::operator * (const Vector4& delta){
	return (Vector4(x * delta.x, y * delta.y, z * delta.z, 1.0f));
}

Vector4		Vector4::operator / (const Vector4& delta){
	return (Vector4(x / delta.x, y / delta.y, z / delta.z, 1.0f));
}

void 		Vector4::operator += (const Vector4& delta){
    x += delta.x; y += delta.y; z += delta.z;
}

void 		Vector4::operator -= (const Vector4& delta){
    x -= delta.x; y -= delta.y; z -= delta.z;
}

void 		Vector4::operator *= (const Vector4& delta){
    x *= delta.x; y *= delta.y; z *= delta.z;
}

void 		Vector4::operator /= (const Vector4& delta){
    x /= delta.x; y /= delta.y; z /= delta.z;
}

bool		Vector4::operator == (const Vector4& delta) const{
	return ((x == delta.x && y == delta.y && z == delta.z) ?
			true : false);
}

bool		Vector4::operator != (const Vector4& delta) const{
	return ((x == delta.x && y == delta.y && z == delta.z) ?
			false : true);
}

bool Vector4::operator < (const Vector4& other) const
{
	if (z < other.z)
		return (true);
	if (z == other.z && y < other.y)
		return (true);
	if (z == other.z && y == other.y && x < other.x)
		return (true);
	return (false);
}

bool Vector4::operator > (const Vector4& other) const
{
	if (z < other.z || y < other.y || x < other.x)
		return (false);
	return (true);
}

float *Vector4::decompose(){
	return (&x);
}

float Vector4::distance(Vector4 &point)
{
	return (sqrt( pow(point.x - x, 2.0f)
				+ pow(point.y - y, 2.0f)
				+ pow(point.z - z, 2.0f)
				));
}

Vector4		Vector4::normalize()
{
	float		length;

	length = sqrt((x * x)
				+ (y * y)
				+ (z * z));

	return (Vector4(x / length, y / length, z / length, 1.0f));
}

float			Vector4::dot(Vector4 &b)
{
	float		result;

	result = x * b.x + y * b.y + z * b.z;

	return (result);
}

Vector4		Vector4::cross(Vector4 &other) //Produit vectoriel / cross product
{
	Vector4	result = Vector4(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x,
			1.0f
		);

	return (result);
}

string Vector4::str()
{
	string result = "(" + to_string(x) + " / " + to_string(y) + " / " + to_string(z) + " / " + to_string(w) + ")";

	return (result);
}

Vector4 Vector4::floor()
{
	Vector4 result;

	result.x = static_cast<int>(x);
	result.y = static_cast<int>(y);
	result.z = static_cast<int>(z);
	result.w = static_cast<int>(w);

	return (result);
}

Vector4 Vector4::invert()
{
	x *= -1;
	y *= -1;
	z *= -1;
	w *= -1;
	return (*this);
}
