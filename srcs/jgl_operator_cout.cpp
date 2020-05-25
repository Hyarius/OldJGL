#include "jgl.h"

std::ostream& operator<<(std::ostream& os, jgl::Color& value)
{
	os << "(r : " << std::to_string(value.r) << " / g : " << std::to_string(value.g) << " / b : " << std::to_string(value.b) << " / a : " << std::to_string(value.a) << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Vector2 value)
{
	os << value.str();
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Vector3 value)
{
	os << value.str();
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Vector4 value)
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

std::ostream& operator<<(std::ostream& os, jgl::Matrix2x2 data)
{
	os << jgl::normalize_string("", '-', 6 * 2 + (3 * 1)) << std::endl;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (j != 0)
				os << " - ";
			os << "[" << jgl::normalize_float(data.value[j][i], 4, ' ', 4) << "]";
		}
		os << std::endl;
	}
	os << jgl::normalize_string("", '-', 6 * 2 + (3 * 1)) << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Matrix3x3 data)
{
	os << jgl::normalize_string("", '-', 6 * 3 + (3 * 2)) << std::endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j != 0)
				os << " - ";
			os << "[" << jgl::normalize_float(data.value[j][i], 4, ' ', 4) << "]";
		}
		os << std::endl;
	}
	os << jgl::normalize_string("", '-', 6 * 3 + (3 * 2)) << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, jgl::Matrix4x4 data)
{
	os << jgl::normalize_string("", '-', 6 * 4 + 9) << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j != 0)
				os << " - ";
			os << "[" << jgl::normalize_float(data.value[j][i], 4, ' ', 4) << "]";
		}
		os << std::endl;
	}
	os << jgl::normalize_string("", '-', 6 * 4 + 9) << std::endl;
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

std::ostream& operator<<(std::ostream& os, jgl::Camera camera)
{
	std::cout << "Camera pos : " << camera.pos() << std::endl;
	std::cout << "Camera forward : " << camera.forward() << std::endl;
	std::cout << "Camera right : " << camera.right() << std::endl;
	std::cout << "Camera up : " << camera.up() << std::endl;
	std::cout << "Camera direction : " << camera.direction() << std::endl;
	std::cout << "Camera Model matrix : " << std::endl << camera.model() << std::endl;
	std::cout << "Camera View matrix : " << std::endl << camera.view() << std::endl;
	std::cout << "Camera Projection matrix : " << std::endl << camera.projection() << std::endl;
	std::cout << "Camera MVP matrix : " << std::endl << camera.MVP() << std::endl;

	return os;
}

