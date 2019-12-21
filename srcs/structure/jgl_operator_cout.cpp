#include "jgl.h"

ostream& operator<<(ostream& os, const Color& value)
{
	os << "(r : " << to_string(value.r) << " / g : " << to_string(value.g) << " / b : " << to_string(value.b) << " / a : " << to_string(value.a) << ")";
	return os;
}

ostream& operator<<(ostream& os, const Vector2& value)
{
	os << "(" << to_string(value.x) << " / " << to_string(value.y) << ")";
	return os;
}

ostream& operator<<(ostream& os, const Vector3& value)
{
	os << "(" << to_string(value.x) << " / " << to_string(value.y) << " / " << to_string(value.z) << ")";
	return os;
}
