#ifndef WidgetS_H
#define WidgetS_H

#include "jgl_viewport.h"
#include "jgl_widget_component.h"

namespace jgl
{
	typedef 			void(*Funct)(Data);

	class Widget
	{
	protected:
		Widget* _parent;
		std::vector<Widget*> _childrens;
		Viewport* _viewport;
		bool _activated;
		bool _frozen;

	public:
		Widget(Widget* p_parent = nullptr);
		virtual ~Widget()
		{
			delete _viewport;
		}

		void destroy_widget();

		std::vector<Widget*>& childrens() { return (_childrens); }
		Widget* parent() const { return (_parent); }
		const Vector2 area() const { return (_viewport->area()); }
		const Vector2 anchor() const { if (_parent == nullptr)return(_viewport->anchor()); return (_viewport->anchor() + _parent->anchor()); }
		Viewport* viewport() const { return (_viewport); }

		void send_front();
		void send_back();
		void raise();
		void lower();
		void set_layer(size_t index);
		bool is_frozen() { return (_frozen); }
		bool is_active() { return (_activated); }
		bool is_pointed(Vector2 point = g_mouse->pos);
		void activate() { _activated = true; }
		void desactivate() { _activated = false; }
		void set_frozen(bool new_frozen) { _frozen = new_frozen; }
		void set_active(bool new_state) { _activated = new_state; }
		void set_parent(Widget* p_parent);
		void add_children(Widget* p_children) { _childrens.push_back(p_children); }
		void remove_children(Widget* p_target);
		bool handle_event();
		void update_children();
		void render_children();
		void quit_children();
		void set_anchor(Vector2 p_anchor) { _viewport->set_anchor(p_anchor); }
		void set_area(Vector2 p_area) { _viewport->set_area(p_area); }
		virtual void set_geometry(Vector2 p_anchor, Vector2 p_area);
		virtual void move(Vector2 delta) { std::cout << "Warning : Need creation of a function void move(Vector2) in your " << typeid(this).name() << std::endl; }

		virtual void quit() {};
		virtual void update() {};
		virtual bool handle_keyboard() { return (false); }
		virtual bool handle_mouse() { return (false); }

		virtual void set_geometry_imp(Vector2 p_anchor, Vector2 p_area) = 0;
		virtual void render() = 0;
	};
}
#endif
