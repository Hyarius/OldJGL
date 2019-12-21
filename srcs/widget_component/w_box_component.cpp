#include "jgl.h"

w_box_component::w_box_component(c_widget *p_owner) :
		w_component(p_owner), w_graphical_component()
{
	_anchor = Vector2();
	_area = Vector2();
	_border = 3;
	_delta = Color(0, 0, 0, 0);
	_back = Color(150, 150, 150, 255);
	_front = Color(195, 195, 195, 255);
}

void w_box_component::render(c_viewport *viewport)
{
	if (_owner == nullptr)
		return ;

	if (_tileset != nullptr && _tileset->size() == Vector2(6, 6))
	{
		float corner_size = (_area.x < _area.y ? _area.x : _area.y) / 3;
		if (corner_size < 32)
			corner_size = 32;
		if (corner_size * 2 > _area.x || corner_size * 2 > _area.y)
			corner_size = (_area.x < _area.y ? _area.x : _area.y) / 2;
		Vector2 h_middle_size = Vector2((_area.x - corner_size * 2) / 4, corner_size);
		Vector2 v_middle_size = Vector2(corner_size, (_area.y - corner_size * 2) / 4);
		Vector2 c_middle_size = Vector2(h_middle_size.x, v_middle_size.y);

		Vector2 pos = _anchor;
		for (int j = 0; j < 6; j++)
		{
			pos.x = _anchor.x;
			for (int i = 0; i < 6; i++)
			{
				Vector2 tmp_size;

				if (i == 0 || i == 5)
					tmp_size = corner_size;
				else
					tmp_size = h_middle_size;

				_tileset->draw(i + j * 6, pos, tmp_size, viewport);
				pos.x += tmp_size.x;
			}
			pos.y += (j == 0 || j == 5 ? corner_size : v_middle_size.y);
		}
	}
	else
	{
		fill_rectangle(_back + _delta, _anchor , _area, viewport);
		fill_rectangle(_front + _delta, _anchor + _border, _area - _border * 2, viewport);
	}
}
