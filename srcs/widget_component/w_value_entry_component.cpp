#include "jgl.h"

namespace jgl
{
	w_value_entry_component::w_value_entry_component(Widget* p_owner, float p_value) :
		w_entry_component(p_owner, "")
	{
		set_precision(3);
		set_value(p_value);
	}
}