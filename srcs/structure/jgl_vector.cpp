#include "jgl.h"

using namespace std;

Vector3::Vector3(int p_value) :
	x(static_cast<float>(p_value)), y(static_cast<float>(p_value)),
	z(static_cast<float>(p_value)){}

Vector3::Vector3(float p_value) :
	x(p_value), y(p_value), z(p_value){}

Vector3::Vector3(float p_x, float p_y, float p_z) :
	x(p_x), y(p_y), z(p_z){}

Vector3::Vector3(int p_x, int p_y, int p_z) :
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

Vector3		Vector3::operator + (const Vector3& delta){
	return (Vector3(this->x + delta.x, this->y + delta.y, this->z + delta.z));
}

Vector3		Vector3::operator - (const Vector3& delta){
	return (Vector3(this->x - delta.x, this->y - delta.y, this->z - delta.z));
}

Vector3		Vector3::operator * (const Vector3& delta){
	return (Vector3(this->x * delta.x, this->y * delta.y, this->z * delta.z));
}

Vector3		Vector3::operator / (const Vector3& delta){
	return (Vector3(this->x / delta.x, this->y / delta.y, this->z / delta.z));
}

void 		Vector3::operator += (const Vector3& delta){
    this->x += delta.x; this->y += delta.y; this->z += delta.z;
}

void 		Vector3::operator -= (const Vector3& delta){
    this->x -= delta.x; this->y -= delta.y; this->z -= delta.z;
}

void 		Vector3::operator *= (const Vector3& delta){
    this->x *= delta.x; this->y *= delta.y; this->z *= delta.z;
}

void 		Vector3::operator /= (const Vector3& delta){
    this->x /= delta.x; this->y /= delta.y; this->z /= delta.z;
}

bool		Vector3::operator == (const Vector3& delta) const{
	return ((this->x == delta.x && this->y == delta.y && this->z == delta.z) ?
			true : false);
}

bool		Vector3::operator != (const Vector3& delta) const{
	return ((this->x == delta.x && this->y == delta.y && this->z == delta.z) ?
			false : true);
}

bool Vector3::operator < (const Vector3& other) const
{
	if (this->z < other.z)
		return (true);
	if (this->z == other.z && this->y < other.y)
		return (true);
	if (this->z == other.z && this->y == other.y && this->x < other.x)
		return (true);
	return (false);
}

bool Vector3::operator > (const Vector3& other) const
{
	if (this->z < other.z || this->y < other.y || this->x < other.x)
		return (false);
	return (true);
}

float *Vector3::decompose(){
	return (&x);
}

float Vector3::distance(Vector3 &point)
{
	return (sqrt( pow(point.x - this->x, 2.0f)
				+ pow(point.y - this->y, 2.0f)
				+ pow(point.z - this->z, 2.0f)));
}

Vector3		Vector3::normalize()
{
	float		length;

	length = sqrt((this->x * this->x)
				+ (this->y * this->y)
				+ (this->z * this->z));

	return (Vector3(this->x / length, this->y / length, this->z / length));
}

float			Vector3::dot(Vector3 &b)
{
	float		result;

	result = this->x * b.x + this->y * b.y + this->z * b.z;

	return (result);
}

Vector3		Vector3::cross(Vector3 &other) //Produit vectoriel / cross product
{
	Vector3	result = Vector3(
			this->y * other.z - this->z * other.y,
			this->z * other.x - this->x * other.z,
			this->x * other.y - this->y * other.x
		);

	return (result);
}

string Vector3::str()
{
	string result = "(" + to_string(x) + " / " + to_string(y) + " / " + to_string(z) + ")";

	return (result);
}

Vector3 Vector3::floor()
{
	Vector3 result;

	result.x = static_cast<int>(this->x);
	result.y = static_cast<int>(this->y);
	result.z = static_cast<int>(this->z);

	return (result);
}

Vector2::Vector2(int p_value) :
	x(static_cast<float>(p_value)), y(static_cast<float>(p_value)){}

Vector2::Vector2(float p_value) :
	x(p_value), y(p_value){}

Vector2::Vector2(float p_x, float p_y) :
	x(p_x), y(p_y){}

Vector2::Vector2(int p_x, int p_y) :
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

Vector2		Vector2::operator + (const Vector2& delta){
	return (Vector2(this->x + delta.x, this->y + delta.y));
}

Vector2		Vector2::operator - (const Vector2& delta){
	return (Vector2(this->x - delta.x, this->y - delta.y));
}

Vector2		Vector2::operator * (const Vector2& delta){
	return (Vector2(this->x * delta.x, this->y * delta.y));
}

Vector2		Vector2::operator / (const Vector2& delta){
	return (Vector2(this->x / delta.x, this->y / delta.y));
}

void 		Vector2::operator += (const Vector2& delta){
    this->x += delta.x; this->y += delta.y;
}

void 		Vector2::operator -= (const Vector2& delta){
    this->x -= delta.x; this->y -= delta.y;
}

void 		Vector2::operator *= (const Vector2& delta){
    this->x *= delta.x; this->y *= delta.y;
}

void 		Vector2::operator /= (const Vector2& delta){
    this->x /= delta.x; this->y /= delta.y;
}

bool		Vector2::operator == (const Vector2& delta) const
{
	return ((this->x == delta.x && this->y == delta.y) ? true : false);
}

bool		Vector2::operator != (const Vector2& delta) const
{
	return ((this->x == delta.x && this->y == delta.y) ? false : true);
}

bool Vector2::operator < (const Vector2& other) const
{
	if (this->y < other.y)
		return (true);
	if (this->y == other.y && this->x < other.x)
		return (true);
	return (false);
}

bool Vector2::operator > (const Vector2& other) const
{
	if (this->y < other.y || this->x < other.x)
		return (false);
	return (true);
}

float *Vector2::decompose()
{
	return (&x);
}

float Vector2::distance(Vector2 &point)
{
	return (sqrt( pow(point.x - this->x, 2.0f)
				+ pow(point.y - this->y, 2.0f)));
}

Vector2		Vector2::normalize()
{
	float		length;

	length = sqrt((this->x * this->x) + (this->y * this->y));

	return (Vector2(this->x / length, this->y / length));
}

Vector2 Vector2::cross(Vector2 &other)
{
	Vector2 result;

	result = Vector2(-(other.y - this->y), other.x - this->x);

	return (result);
}

float Vector2::dot(Vector2 &other)
{
	float		result;

	result = this->x * other.x + this->y * other.y;

	return (result);
}

string Vector2::str()
{
	string result = "(" + to_string(x) + " / " + to_string(y) + ")";

	return (result);
}

Vector2 Vector2::floor()
{
	Vector2 result;

	result.x = static_cast<int>(this->x);
	result.y = static_cast<int>(this->y);

	return (result);
}
