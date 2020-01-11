#include "jgl.h"

using namespace std;

c_tileset::c_tileset(string path, Vector2 p_size)
{
	_image = new c_image(path);
	_sprites.clear();
	_size = p_size;
	_unit = Vector2(1.0f / _size.x, 1.0f / _size.y);
	Vector2	tmp = 0;
	if (p_size == 1)
		_sprites.insert(_sprites.end(), 0);

	while (tmp.x * tmp.y < _size.x * (_size.y - 1))
	{
		if (tmp.x >= _size.x)
		{
			tmp.x = 0;
			tmp.y++;
		}
		Vector2 result = Vector2(tmp.x / _size.x, tmp.y / _size.y);
		_sprites.insert(_sprites.end(), result);
		tmp.x++;
	}
}

c_tileset::c_tileset(c_image *p_image, Vector2 p_size)
{
	_image = p_image;
	_sprites.clear();
	_size = p_size;
	_unit = Vector2(1.0f / _size.x, 1.0f / _size.y);
	Vector2	tmp = 0;
	if (p_size == 1)
		_sprites.insert(_sprites.end(), 0);

	else
	{
		while (tmp.x * tmp.y < _size.x * (_size.y - 1))
		{
			if (tmp.x >= _size.x)
			{
				tmp.x = 0;
				tmp.y++;
			}
			Vector2 result = Vector2(tmp.x / _size.x, tmp.y / _size.y);
			_sprites.insert(_sprites.end(), result);
			tmp.x++;
		}
	}

}

void c_tileset::draw(int id, Vector2 pos, Vector2 size, float p_alpha, c_viewport *viewport)
{
	glBindTexture(GL_TEXTURE_2D, _image->texture_id());

	Vector2 value[] = {
		pos + Vector2(0.0f, 0.0f),
		pos + Vector2(size.x, 0.0f),
		pos + Vector2(0.0f, size.y),
		pos + Vector2(0.0f, size.y),
		pos + Vector2(size.x, size.y),
		pos + Vector2(size.x, 0.0f)
	};

	Pixel points[] = {
		convert_screen_to_opengl(value[0]),
		convert_screen_to_opengl(value[1]),
		convert_screen_to_opengl(value[2]),
		convert_screen_to_opengl(value[3]),
		convert_screen_to_opengl(value[4]),
		convert_screen_to_opengl(value[5])
	};

	int			i;
	if ((unsigned int)id >= _sprites.size())
		i = 0;
	else
		i = id;

	Vector2	sprite_coord = Vector2(_sprites[i]);

	Uv uvs[] = {
		Uv(sprite_coord + Vector2(0.0f, 0.0f)),
		Uv(sprite_coord + Vector2(_unit.x, 0.0f)),
		Uv(sprite_coord + Vector2(0.0f, _unit.y)),
		Uv(sprite_coord + Vector2(0.0f, _unit.y)),
		Uv(sprite_coord + _unit),
		Uv(sprite_coord + Vector2(_unit.x, 0.0f))
	};
	float alphas[] = {
		p_alpha,
		p_alpha,
		p_alpha,
		p_alpha,
		p_alpha,
		p_alpha
	};

	draw_triangle_texture(points, uvs, alphas, 2);
}

void c_tileset::draw_centred(int id, Vector2 pos, Vector2 size, float p_alpha, c_viewport *viewport)
{
	draw(id, pos - size / 2, size, p_alpha, viewport);
}
