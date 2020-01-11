#include "jgl.h"

w_graphical_component::w_graphical_component()
{
	_tileset = nullptr;
	_corner_size = -1;
	_image = nullptr;
	_sprite = 0;
	_border = 3;
	_back = Color(150, 150, 150, 255);
	_front = Color(195, 195, 195, 255);
}
