#include "jgl.h"

std::ostream& operator<<(std::ostream& os, const jgl::Color value)
{
	os << "(r : " << std::to_string(value.r) << " / g : " << std::to_string(value.g) << " / b : " << std::to_string(value.b) << " / a : " << std::to_string(value.a) << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const jgl::Vector2 value)
{
	os << value.str();
	return os;
}

std::ostream& operator<<(std::ostream& os, const jgl::Vector3 value)
{
	os << value.str();
	return os;
}

std::ostream& operator<<(std::ostream& os, const jgl::Vector4 value)
{
	os << value.str();
	return os;
}

std::ostream& operator<<(std::ostream& os, const jgl::Mouse mouse)
{
	jgl::String left = (mouse.get_button(jgl::mouse_button::left) == jgl::mouse_state::up ? "Up" : (mouse.get_button(jgl::mouse_button::left) == jgl::mouse_state::down ? "Down" : "Null"));
	jgl::String center = (mouse.get_button(jgl::mouse_button::center) == jgl::mouse_state::up ? "Up" : (mouse.get_button(jgl::mouse_button::center) == jgl::mouse_state::down ? "Down" : "Null"));
	jgl::String right = (mouse.get_button(jgl::mouse_button::right) == jgl::mouse_state::up ? "Up" : (mouse.get_button(jgl::mouse_button::right) == jgl::mouse_state::down ? "Down" : "Null"));
	os << "Left : " << left << "\n" << "Middle : " << center << "\n" << "Right : " << right;
	return os;
}

std::ostream& operator<<(std::ostream& os, const jgl::Matrix2x2 data)
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

std::ostream& operator<<(std::ostream& os, const jgl::Matrix3x3 data)
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

std::ostream& operator<<(std::ostream& os, const jgl::Matrix4x4 data)
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

std::ostream& operator<<(std::ostream& os, const jgl::Line3D value)
{
	os << "(" << value.a << " / " << value.b << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const jgl::Triangle3D value)
{
	os << "(" << value.a << " / " << value.b << " / " << value.c << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const jgl::Glyph value)
{
	os << value.content();
	return os;
}

std::ostream& operator<<(std::ostream& os, const jgl::Unique_string value)
{
	for (size_t i = 0; i < value.size(); i++)
	{
		os << value[i];
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const jgl::Camera camera)
{
	os << "Camera pos : " << camera.pos() << std::endl;
	os << "Camera forward : " << camera.forward() << std::endl;
	os << "Camera right : " << camera.right() << std::endl;
	os << "Camera up : " << camera.up() << std::endl;
	os << "Camera direction : " << camera.direction() << std::endl;
	os << "Camera Model matrix : " << std::endl << camera.model() << std::endl;
	os << "Camera View matrix : " << std::endl << camera.view() << std::endl;
	os << "Camera Projection matrix : " << std::endl << camera.projection() << std::endl;
	os << "Camera MVP matrix : " << std::endl << camera.MVP() << std::endl;

	return os;
}

std::ostream& operator<<(std::ostream& os, const jgl::Face to_print)
{
	os << "Index vertices : [" << to_print.index_vertices[0] << "][" << to_print.index_vertices[1] << "][" << to_print.index_vertices[2] << "]" << std::endl;
	os << "Index uvs : [" << to_print.index_uvs[0] << "][" << to_print.index_uvs[1] << "][" << to_print.index_uvs[2] << "]" << std::endl;
	os << "Index normales : [" << to_print.index_normale[0] << "][" << to_print.index_normale[1] << "][" << to_print.index_normale[2] << "]" << std::endl;

	return (os);
}

std::ostream& operator<<(std::ostream& os, const jgl::Material to_print)
{
	os << "Material : " << to_print.name << std::endl;
	os << "		ka : " << to_print.ka << std::endl;
	os << "		kd : " << to_print.kd << std::endl;
	os << "		ks : " << to_print.ks << std::endl;
	os << "		ke : " << to_print.ke << std::endl;
	os << "		ns : " << to_print.ns << std::endl;
	os << "		ni : " << to_print.ni << std::endl;
	os << "		d : " << to_print.d << std::endl;
	os << "		illum : " << to_print.illum << std::endl;
	if (to_print.ambiant_texture != nullptr)
		os << "		ambiant texture : " << to_print.ambiant_texture->path() << std::endl;
	if (to_print.diffuse_texture != nullptr)
		os << "		diffuse texture : " << to_print.diffuse_texture->path() << std::endl;
	if (to_print.specular_texture != nullptr)
		os << "		specular texture : " << to_print.specular_texture->path() << std::endl;
	if (to_print.specular_hight_light != nullptr)
		os << "		specular hight light : " << to_print.specular_hight_light->path() << std::endl;
	if (to_print.alpha_texture != nullptr)
		os << "		alpha texture : " << to_print.alpha_texture->path() << std::endl;
	if (to_print.bump != nullptr)
		os << "		bump map : " << to_print.bump->path() << std::endl;

	return (os);
}

std::ostream& operator<<(std::ostream& os, const jgl::File value)
{
	os << "File : " << value.path << "\\" << value.name << "\\" << value.extension << " - "
		<< "Path : " << value.path << " - Name : " << value.name << " - Extension : " << value.extension
		<< " - File type : " << (value.type == jgl::File_type::file ? "File" : "Directory");

	return (os);
}

std::ostream& operator<<(std::ostream& os, const jgl::String value)
{
	os << *value;
	return os;
}

std::ostream& operator<<(std::ostream& os, const jgl::Reference_count& value)
{
	os << value.value();
	return (os);
}