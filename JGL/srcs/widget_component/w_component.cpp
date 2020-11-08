#include "jgl.h"

namespace jgl
{
	w_component::w_component(Widget* p_owner)
	{
		_owner = p_owner;
		_anchor = Vector2();// +owner_anchor();
		_area = Vector2();
	}

	bool w_component::is_pointed(const Vector2 point) const
	{
		Vector2 pos1, pos2;

		pos1 = _anchor;

		pos2 = pos1 + _area;

		if (point.x < pos1.x || point.x > pos2.x || point.y < pos1.y || point.y > pos2.y)
			return (false);
		return (true);
	}
}