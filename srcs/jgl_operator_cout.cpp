#include "jgl.h"

ostream& operator<<(ostream& os, Color value)
{
	os << "(r : " << to_string(value.r) << " / g : " << to_string(value.g) << " / b : " << to_string(value.b) << " / a : " << to_string(value.a) << ")";
	return os;
}

ostream& operator<<(ostream& os, Vector2 value)
{
	os << value.str();
	return os;
}

ostream& operator<<(ostream& os, Vector3 value)
{
	os << value.str();
	return os;
}

ostream& operator<<(ostream& os, Vector4 value)
{
	os << value.str();
	return os;
}

ostream& operator<<(ostream& os, Pixel value)
{
	os << "(" << ftoa(value.x, 3) << " / " << ftoa(value.y, 3) << " / " << ftoa(value.z, 3) << ")";
	return os;
}

ostream& operator<<(ostream& os, Mouse mouse)
{
	string left = (mouse.get_button(mouse_button::left) == mouse_state::up ? "Up" : (mouse.get_button(mouse_button::left) == mouse_state::down ? "Down" : "Null" ));
	string middle = (mouse.get_button(mouse_button::middle) == mouse_state::up ? "Up" : (mouse.get_button(mouse_button::middle) == mouse_state::down ? "Down" : "Null" ));
	string right = (mouse.get_button(mouse_button::right) == mouse_state::up ? "Up" : (mouse.get_button(mouse_button::right) == mouse_state::down ? "Down" : "Null" ));
	os << "Left : " << left << "\n" << "Middle : " << middle << "\n" << "Right : " << right;
	return os;
}

ostream& operator<<(ostream& os, Mouse *mouse)
{
	string left = (mouse->get_button(mouse_button::left) == mouse_state::up ? "Up" : (mouse->get_button(mouse_button::left) == mouse_state::down ? "Down" : "Null" ));
	string middle = (mouse->get_button(mouse_button::middle) == mouse_state::up ? "Up" : (mouse->get_button(mouse_button::middle) == mouse_state::down ? "Down" : "Null" ));
	string right = (mouse->get_button(mouse_button::right) == mouse_state::up ? "Up" : (mouse->get_button(mouse_button::right) == mouse_state::down ? "Down" : "Null" ));
	os << "Left : " << left << "\n" << "Middle : " << middle << "\n" << "Right : " << right;
	return os;
}

ostream& operator<<(ostream& os, Matrix data)
{
	os << "--------------------------------------------------------------" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j != 0)
				os << " - ";
			os << "[" << ftoa(data.value[j][i], 3) << "]";
		}
		os << endl;
	}
	os << "--------------------------------------------------------------" << endl;
	return os;
}

ostream& operator<<(ostream& os, Line3D value)
{
	os << "(" << value.a << " / " << value.b << ")";
	return os;
}

ostream& operator<<(ostream& os, Triangle3D value)
{
	os << "(" << value.a << " / " << value.b << " / " << value.c << ")";
	return os;
}
