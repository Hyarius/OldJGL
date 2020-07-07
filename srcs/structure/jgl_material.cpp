#include "jgl.h"

namespace jgl
{
	Material::Material(jgl::String p_name)
	{
		if (_empty_texture == nullptr)
			_empty_texture = new Image(1, 1, Color(255, 255, 255));
		name = p_name.copy();
		ambiant_texture = empty_texture();
		normal_texture = empty_texture();
		diffuse_texture = empty_texture();
		specular_texture = empty_texture();
		specular_hight_light = empty_texture();
		alpha_texture = empty_texture();
		bump = empty_texture();
	}
	Material::~Material()
	{
		if (ambiant_texture != empty_texture())
			delete ambiant_texture;
		if (normal_texture != empty_texture())
			delete normal_texture;
		if (diffuse_texture != empty_texture())
			delete diffuse_texture;
		if (specular_texture != empty_texture())
			delete specular_texture;
		if (specular_hight_light != empty_texture())
			delete specular_hight_light;
		if (alpha_texture != empty_texture())
			delete alpha_texture;
		if (bump != empty_texture())
			delete bump;
	}
}
