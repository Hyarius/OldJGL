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

	if (_tileset != nullptr && _tileset->size() == Vector2(3, 3))
	{
		float corner_size = (_area.x < _area.y ? _area.x : _area.y) / 2;
		if (corner_size < 16)
			corner_size = 16;
		if (corner_size * 2 > _area.x || corner_size * 2 > _area.y)
			corner_size = (_area.x < _area.y ? _area.x : _area.y) / 2;
		if (corner_size > 36)
			corner_size = 36;
		int nb_sub_x = ceil((_area.x - corner_size * 2) / corner_size);
		int nb_sub_y = ceil((_area.y - corner_size * 2) / corner_size);
		if (nb_sub_x < 0)
			nb_sub_x = 0;
		if (nb_sub_y < 0)
			nb_sub_y = 0;
		Vector2 h_middle_size = Vector2((_area.x - corner_size * 2) / (nb_sub_x == 0 ? 1 : nb_sub_x), corner_size);
		Vector2 v_middle_size = Vector2(corner_size, (_area.y - corner_size * 2) / (nb_sub_y == 0 ? 1 : nb_sub_y));
		Vector2 c_middle_size = Vector2(h_middle_size.x, v_middle_size.y);

		Vector2 pos = _anchor;
		for (int j = 0; j < nb_sub_y + 2; j++)
		{
			pos.x = _anchor.x;
			for (int i = 0; i < nb_sub_x + 2; i++)
			{
				Vector2 tmp_size;
				int sprite;
				if (i == 0 || i == nb_sub_x + 1)
				{
					if (i == 0)
					{
						if (j == 0)
							sprite = 0;
						else if (j == nb_sub_y + 1)
							sprite = 6;
						else
							sprite = 3;
					}
					else
					{
						if (j == 0)
							sprite = 2;
						else if (j == nb_sub_y + 1)
							sprite = 8;
						else
							sprite = 5;
					}
					tmp_size = corner_size;
				}
				else
				{
					if (j == 0)
						sprite = 1;
					else if (j == nb_sub_y + 1)
						sprite = 7;
					else
						sprite = 4;
					tmp_size = h_middle_size;
				}

				_tileset->draw(sprite, pos, tmp_size, viewport);
				pos.x += tmp_size.x;
			}
			pos.y += (j == 0 || j == nb_sub_y + 1 ? corner_size : v_middle_size.y);
			// if (nb_sub_y <= 0)
			// 	pos.y = _anchor.x + _area.y - 30;
		}
	}
	else
	{
		fill_rectangle(_back + _delta, _anchor, _area, viewport);
		fill_rectangle(_front + _delta, _anchor + _border, _area - _border * 2, viewport);
	}
}
