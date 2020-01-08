#include "jgl.h"

using namespace std;

Pixel::Pixel(int p_value) :
	x(static_cast<float>(p_value)), y(static_cast<float>(p_value)),
	z(static_cast<float>(p_value)){}

Pixel::Pixel(Vector2 p_value) :
	x(static_cast<float>(p_value.x)), y(static_cast<float>(p_value.y)),
	z(static_cast<float>(-1.0f)){}

Pixel::Pixel(float p_value) :
	x(p_value), y(p_value), z(p_value){}

Pixel::Pixel(float p_x, float p_y, float p_z) :
	x(p_x), y(p_y), z(p_z){}

Pixel::Pixel(int p_x, int p_y, int p_z) :
	x(static_cast<float>(p_x)), y(static_cast<float>(p_y)),
	z(static_cast<float>(p_z)){}

Pixel&		Pixel::operator = (int p_value) {
	x = static_cast<float>(p_value);
	y = static_cast<float>(p_value);
	z = static_cast<float>(p_value);
	return *this;
}

Pixel& Pixel::operator = (float  p_value) {
	x = p_value;
	y = p_value;
	z = p_value;
	return *this;
}

Pixel& Pixel::operator = (Vector2 p_value)
{
	x = p_value.x;
	y = p_value.y;
	z = -1.0f;
	return *this;
}

Pixel		Pixel::operator + (const Pixel& delta){
	return (Pixel(this->x + delta.x, this->y + delta.y, this->z + delta.z));
}

Pixel		Pixel::operator - (const Pixel& delta){
	return (Pixel(this->x - delta.x, this->y - delta.y, this->z - delta.z));
}

Pixel		Pixel::operator * (const Pixel& delta){
	return (Pixel(this->x * delta.x, this->y * delta.y, this->z * delta.z));
}

Pixel		Pixel::operator / (const Pixel& delta){
	return (Pixel(this->x / delta.x, this->y / delta.y, this->z / delta.z));
}

void 		Pixel::operator += (const Pixel& delta){
    this->x += delta.x; this->y += delta.y; this->z += delta.z;
}

void 		Pixel::operator -= (const Pixel& delta){
    this->x -= delta.x; this->y -= delta.y; this->z -= delta.z;
}

void 		Pixel::operator *= (const Pixel& delta){
    this->x *= delta.x; this->y *= delta.y; this->z *= delta.z;
}

void 		Pixel::operator /= (const Pixel& delta){
    this->x /= delta.x; this->y /= delta.y; this->z /= delta.z;
}

bool		Pixel::operator == (const Pixel& delta) const{
	return ((this->x == delta.x && this->y == delta.y && this->z == delta.z) ?
			true : false);
}

bool		Pixel::operator != (const Pixel& delta) const{
	return ((this->x == delta.x && this->y == delta.y && this->z == delta.z) ?
			false : true);
}

bool Pixel::operator < (const Pixel& other) const
{
	if (this->z < other.z)
		return (true);
	if (this->z == other.z && this->y < other.y)
		return (true);
	if (this->z == other.z && this->y == other.y && this->x < other.x)
		return (true);
	return (false);
}

bool Pixel::operator > (const Pixel& other) const
{
	if (this->z < other.z || this->y < other.y || this->x < other.x)
		return (false);
	return (true);
}

float *Pixel::decompose(){
	return (&x);
}

float Pixel::distance(Pixel &point)
{
	return (sqrt( pow(point.x - this->x, 2.0f)
				+ pow(point.y - this->y, 2.0f)
				+ pow(point.z - this->z, 2.0f)));
}

Pixel		Pixel::normalize()
{
	float		length;

	length = sqrt((this->x * this->x)
				+ (this->y * this->y)
				+ (this->z * this->z));

	return (Pixel(this->x / length, this->y / length, this->z / length));
}

float			Pixel::dot(Pixel &b)
{
	float		result;

	result = this->x * b.x + this->y * b.y + this->z * b.z;

	return (result);
}

Pixel		Pixel::cross(Pixel &other) //Produit vectoriel / cross product
{
	Pixel	result = Pixel(
			this->y * other.z - this->z * other.y,
			this->z * other.x - this->x * other.z,
			this->x * other.y - this->y * other.x
		);

	return (result);
}

string Pixel::str()
{
	string result = "(" + to_string(x) + " / " + to_string(y) + " / " + to_string(z) + ")";

	return (result);
}

Pixel Pixel::floor()
{
	Pixel result;

	result.x = static_cast<int>(this->x);
	result.y = static_cast<int>(this->y);
	result.z = static_cast<int>(this->z);

	return (result);
}
