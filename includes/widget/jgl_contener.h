#ifndef JGL_CONTENER_H
#define JGL_CONTENER_H

#include "jgl_widgets.h"

namespace jgl
{
	class Contener : public Widget
	{
	protected:
		void set_geometry_imp(Vector2 p_anchor, Vector2 p_area) {}

	public:
		Contener(Widget* p_parent = nullptr) :jgl::Widget(p_parent){}

		void render() {}
	};
}
#endif
