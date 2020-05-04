#include "jgl.h"

std::ostream& operator<<(std::ostream& os, jgl::Color& value)
{
	os << "(r : " << std::to_string(value.r) << " / g : " << std::to_string(value.g) << " / b : " << std::to_string(value.b) << " / a : " << std::to_string(value.a) << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Vector2& value)
{
	os << value.str();
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Vector3& value)
{
	os << value.str();
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Vector4& value)
{
	os << value.str();
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Pixel& value)
{
	os << "(" << jgl::ftoa(value.x, 3) << " / " << jgl::ftoa(value.y, 3) << " / " << jgl::ftoa(value.z, 3) << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Mouse& mouse)
{
	jgl::String left = (mouse.get_button(jgl::mouse_button::left) == jgl::mouse_state::up ? "Up" : (mouse.get_button(jgl::mouse_button::left) == jgl::mouse_state::down ? "Down" : "Null"));
	jgl::String middle = (mouse.get_button(jgl::mouse_button::middle) == jgl::mouse_state::up ? "Up" : (mouse.get_button(jgl::mouse_button::middle) == jgl::mouse_state::down ? "Down" : "Null"));
	jgl::String right = (mouse.get_button(jgl::mouse_button::right) == jgl::mouse_state::up ? "Up" : (mouse.get_button(jgl::mouse_button::right) == jgl::mouse_state::down ? "Down" : "Null"));
	os << "Left : " << left << "\n" << "Middle : " << middle << "\n" << "Right : " << right;
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Mouse* mouse)
{
	jgl::String left = (mouse->get_button(jgl::mouse_button::left) == jgl::mouse_state::up ? "Up" : (mouse->get_button(jgl::mouse_button::left) == jgl::mouse_state::down ? "Down" : "Null"));
	jgl::String middle = (mouse->get_button(jgl::mouse_button::middle) == jgl::mouse_state::up ? "Up" : (mouse->get_button(jgl::mouse_button::middle) == jgl::mouse_state::down ? "Down" : "Null"));
	jgl::String right = (mouse->get_button(jgl::mouse_button::right) == jgl::mouse_state::up ? "Up" : (mouse->get_button(jgl::mouse_button::right) == jgl::mouse_state::down ? "Down" : "Null"));
	os << "Left : " << left << "\n" << "Middle : " << middle << "\n" << "Right : " << right;
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Matrix& data)
{
	os << "--------------------------------------------------------------" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j != 0)
				os << " - ";
			os << "[" << jgl::ftoa(data.value[j][i], 3) << "]";
		}
		os << std::endl;
	}
	os << "--------------------------------------------------------------" << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Line3D& value)
{
	os << "(" << value.a << " / " << value.b << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Triangle3D& value)
{
	os << "(" << value.a << " / " << value.b << " / " << value.c << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Glyph& value)
{
	os << value.content();
	return os;
}

std::ostream& operator<<(std::ostream& os, const jgl::Glyph& value)
{
	os << value.content();
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::String value)
{
	for (size_t i = 0; i < value.size(); i++)
	{
		os << value[i];
	}
	return os;
}