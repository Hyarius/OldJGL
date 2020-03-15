#include "jgl.h"

using namespace std;

Vector3::Vector3(int p_value) :
	x(static_cast<float>(p_value)), y(static_cast<float>(p_value)),
	z(static_cast<float>(p_value)){}

Vector3::Vector3(double p_value) :
	x(static_cast<float>(p_value)), y(static_cast<float>(p_value)),
	z(static_cast<float>(p_value)){}

Vector3::Vector3(float p_value) :
	x(p_value), y(p_value), z(p_value){}

Vector3::Vector3(float p_x, float p_y, float p_z) :
	x(p_x), y(p_y), z(p_z){}

Vector3::Vector3(int p_x, int p_y, int p_z) :
	x(static_cast<float>(p_x)), y(static_cast<float>(p_y)),
	z(static_cast<float>(p_z)){}

Vector3::Vector3(double p_x, double p_y, double p_z) :
	x(static_cast<float>(p_x)), y(static_cast<float>(p_y)),
	z(static_cast<float>(p_z)){}

Vector3&		Vector3::operator = (int p_value) {
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

Vector3		Vector3::operator + (const Vector3 delta){
	return (Vector3(x + delta.x, y + delta.y, z + delta.z));
}

Vector3		Vector3::operator - (const Vector3 delta){
	return (Vector3(x - delta.x, y - delta.y, z - delta.z));
}

Vector3		Vector3::operator * (const Vector3 delta){
	return (Vector3(x * delta.x, y * delta.y, z * delta.z));
}

Vector3		Vector3::operator / (const Vector3 delta){
	return (Vector3(x / delta.x, y / delta.y, z / delta.z));
}

void 		Vector3::operator += (const Vector3 delta){
    x += delta.x; y += delta.y; z += delta.z;
}

void 		Vector3::operator -= (const Vector3 delta){
    x -= delta.x; y -= delta.y; z -= delta.z;
}

void 		Vector3::operator *= (const Vector3 delta){
    x *= delta.x; y *= delta.y; z *= delta.z;
}

void 		Vector3::operator /= (const Vector3 delta){
    x /= delta.x; y /= delta.y; z /= delta.z;
}

bool		Vector3::operator == (const Vector3 delta) const{
	return ((x == delta.x && y == delta.y && z == delta.z) ?
			true : false);
}

bool		Vector3::operator != (const Vector3 delta) const{
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

float *Vector3::decompose(){
	return (&x);
}

float Vector3::distance(Vector3 point)
{
	return (sqrt( pow(point.x - x, 2.0f)
				+ pow(point.y - y, 2.0f)
				+ pow(point.z - z, 2.0f)));
}

Vector3		Vector3::normalize()
{
	float		length;

	length = sqrt((x * x)
				+ (y * y)
				+ (z * z));

	return (Vector3(x / length, y / length, z / length));
}

float			Vector3::dot(Vector3 b)
{
	float		result;

	result = x * b.x + y * b.y + z * b.z;

	return (result);
}

Vector3		Vector3::cross(Vector3 other) //Produit vectoriel / cross product
{
	Vector3	result = Vector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);

	return (result);
}

string Vector3::str()
{
	string result = "(" + ftoa(x, 2) + " / " + ftoa(y, 2) + " / " + ftoa(z, 2) + ")";

	return (result);
}

Vector3 Vector3::floor()
{
	Vector3 result;

	result.x = static_cast<float>(std::floor(x));
	result.y = static_cast<float>(std::floor(y));
	result.z = static_cast<float>(std::floor(z));

	return (result);
}

Vector3 Vector3::invert()
{
	x *= -1;
	y *= -1;
	z *= -1;
	return (*this);
}

Vector4 Vector3::convert(int p_value)
{
	return (Vector4(x, y, z, (float)p_value));
}

Vector4 Vector3::convert(float p_value)
{
	return (Vector4(x, y, z, p_value));
}
