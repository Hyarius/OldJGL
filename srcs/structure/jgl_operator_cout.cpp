#include "jgl.h"

ostream& operator<<(ostream& os, const Color& value)
{
	os << "(r : " << to_string(value.r) << " / g : " << to_string(value.g) << " / b : " << to_string(value.b) << " / a : " << to_string(value.a) << ")";
	return os;
}

ostream& operator<<(ostream& os, const Vector2& value)
{
	os << "(" << ftoa(value.x, 3) << " / " << ftoa(value.y, 3) << ")";
	return os;
}

ostream& operator<<(ostream& os, const Vector3& value)
{
	os << "(" << ftoa(value.x, 3) << " / " << ftoa(value.y, 3) << " / " << ftoa(value.z, 3) << ")";
	return os;
}

ostream& operator<<(ostream& os, t_mouse& mouse)
{
	string left = (mouse.get_button(mouse_button::left) == mouse_state::up ? "Up" : (mouse.get_button(mouse_button::left) == mouse_state::down ? "Down" : "Null" ));
	string middle = (mouse.get_button(mouse_button::middle) == mouse_state::up ? "Up" : (mouse.get_button(mouse_button::middle) == mouse_state::down ? "Down" : "Null" ));
	string right = (mouse.get_button(mouse_button::right) == mouse_state::up ? "Up" : (mouse.get_button(mouse_button::right) == mouse_state::down ? "Down" : "Null" ));
	os << "Left : " << left << "\n" << "Middle : " << middle << "\n" << "Right : " << right;
	return os;
}

ostream& operator<<(ostream& os, t_mouse *mouse)
{
	string left = (mouse->get_button(mouse_button::left) == mouse_state::up ? "Up" : (mouse->get_button(mouse_button::left) == mouse_state::down ? "Down" : "Null" ));
	string middle = (mouse->get_button(mouse_button::middle) == mouse_state::up ? "Up" : (mouse->get_button(mouse_button::middle) == mouse_state::down ? "Down" : "Null" ));
	string right = (mouse->get_button(mouse_button::right) == mouse_state::up ? "Up" : (mouse->get_button(mouse_button::right) == mouse_state::down ? "Down" : "Null" ));
	os << "Left : " << left << "\n" << "Middle : " << middle << "\n" << "Right : " << right;
	return os;
}
