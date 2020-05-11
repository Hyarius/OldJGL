#include "jgl.h"

namespace jgl
{
	w_check_component::w_check_component(bool p_state, Widget* p_owner) :
		w_component(p_owner), w_graphical_component()
	{
		_area = Vector2();
		_anchor = Vector2();
		_border = 3;
		_back = Color(150, 150, 150, 255);
		_front = Color(195, 195, 195, 255);
		_check = Color(60, 150, 255);
		_state = p_state;
	}

	bool w_check_component::check(Vector2 point)
	{
		Vector2 pos1;
		Vector2 pos2;

		pos1 = _anchor;
		pos2 = pos1 + _area;

		if (point.x < pos1.x || point.x > pos2.x || point.y < pos1.y || point.y > pos2.y)
			return (false);
		return (true);
	}

	void w_check_component::render(Viewport* viewport)
	{
		Vector2 pos_1;
		Vector2 pos_2;

		fill_rectangle(_anchor, _area, _back, viewport);
		fill_rectangle(_anchor + _border, _area - _border * 2, _front, viewport);
		if (_state == true)
			fill_rectangle(_anchor + _border * 2, _area - _border * 4, _check, viewport);
	}
}