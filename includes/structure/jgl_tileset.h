#ifndef JGL_TILESET_H
#define JGL_TILESET_H

#include "jgl_includes.h"
#include "jgl_image.h"

using namespace std;

class c_tileset
{
private:
	c_image *_image;
	Vector2 _size;
	Vector2 _unit;
	vector<Vector2> _sprites;

public:
	c_tileset(){
		_image = nullptr;
		_size = 0;
		_unit = 1;
		_sprites.clear();
	}
	c_tileset(c_image *p_image, Vector2 p_size = 1);
	c_tileset(string path, Vector2 p_size = 0);

	c_image *image(){return (_image);}
	Vector2 size(){return (_size);}
	Vector2 unit(){return (_unit);}
	vector<Vector2> &sprites(){return (_sprites);}
	Vector2 sprite(size_t index)
	{
		if (index >= _sprites.size())
			return (-1);
		return (_sprites[index]);
	}
	Vector2 sprite(Vector2 coord)
	{
		if (coord.x < 0 || coord.x >= _size.x ||
			coord.y < 0 || coord.y >= _size.y)
			return (-1);
		return (sprite(static_cast<size_t>(coord.x + (_size.x * coord.y))));
	}

	void draw(int id, Vector2 pos, Vector2 size, float p_alpha = 1.0f, c_viewport *viewport = nullptr);
	void draw_centred(int id, Vector2 pos, Vector2 size, float p_alpha = 1.0f, c_viewport *viewport = nullptr);
};

#endif
