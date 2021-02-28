#include "jgl.h"

namespace jgl
{
	static void active_tab(Data p_data)
	{
		std::vector<Button*> buttons = *(p_data.acces<std::vector<Button*>*>(0));
		std::vector<Frame*> tabs = *(p_data.acces<std::vector<Frame *>*>(1));
		uint64_t index = reinterpret_cast<uint64_t>(p_data.acces<void *>(2));

		for (uint64_t i = 0; i < buttons.size(); i++)
		{
			if (buttons[i] != nullptr)
			{
				if (i == index)
				{
					buttons[i]->set_front(Color(150, 150, 150));
					buttons[i]->set_back(Color(120, 120, 120));
				}
				else
				{
					buttons[i]->set_back(Color(150, 150, 150));
					buttons[i]->set_front(Color(195, 195, 195));
				}
			}
		}

		for (uint64_t i = 0; i < tabs.size(); i++)
		{
			if (tabs[i] != nullptr)
			{
				if (i == index)
					tabs[i]->set_active(true);
				else
					tabs[i]->set_active(false);
			}
		}
	}

	Tab::Tab(Widget* p_parent) : Widget(p_parent)
	{
		tab_area = new Frame(this);
		button_area = new Frame(this);

		button_area->set_front(Color(0, 255, 0, 0));
		button_area->set_back(Color(0, 255, 0, 0));

		tab_area->activate();
		button_area->activate();

		set_geometry(-1, -1);
	}

	Frame* Tab::add_tab(jgl::String p_name, int index)
	{
		bool tmp = (_tabs.size() == 0 ? true : false);
		Frame* new_tab = new Frame(tab_area);
		new_tab->set_border(0);
		Button* new_tab_button = new Button(&active_tab, nullptr, button_area);
		new_tab_button->label().set_text(p_name);
		new_tab_button->activate();

		if (index == -1)
			index = static_cast<int>(_tabs.size());

		for (uint32_t i = _tabs.size(); i <= static_cast<uint32_t>(index) + 1; i++)
		{
			_tabs.push_back(nullptr);
			_buttons.push_back(nullptr);
		}

		_tabs[index] = new_tab;
		_buttons[index] = new_tab_button;

		reset_size();

		if (tmp == true)
			active_tab(Data(3, &_buttons, &_tabs, index));

		return (new_tab);
	}

	void Tab::reset_size()
	{
		reset_tab();
		reset_button();
	}

	void Tab::reset_tab()
	{
		Vector2 tab_pos = Vector2(0.0f, button_area->area().y + tab_area->border() * 2);
		Vector2 tab_size = Vector2(area().x - tab_area->border(), area().y - tab_area->border() - tab_pos.y);

		tab_area->set_geometry(tab_pos, tab_size);
		for (uint32_t i = 0; i < _tabs.size(); i++)
			if (_tabs[i] != nullptr)
				_tabs[i]->set_geometry(0, tab_size - (_tabs[i]->border() * 2));
	}

	void Tab::reset_button()
	{
		Vector2 size;
		Vector2 pos = 0;
		size.y = 30.0f;

		Vector2 button_pos = tab_area->border();
		Vector2 button_size = Vector2(area().x - tab_area->border() * 2, 40.0f);

		button_area->set_geometry(button_pos, button_size);

		for (uint32_t i = 0; i < _buttons.size(); i++)
		{
			if (_buttons[i] != nullptr)
			{
				int tmp = calc_text_len(_buttons[i]->text(), 20);
				size.x = static_cast<float>(tmp);
				_buttons[i]->set_geometry(pos, size);
				pos.x += size.x + button_area->border();
				_buttons[i]->set_data(Data(3, &_buttons, &_tabs, i));
			}
		}
	}

	void Tab::move(Vector2 delta)
	{

	}

	void Tab::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{
		_viewport->resize(p_anchor, p_area);
		reset_size();
	}

	void Tab::render()
	{
		if (is_active() == false)
			return;
	}

	bool Tab::handle_mouse()
	{
		return (false);
	}

	bool Tab::handle_keyboard()
	{
		return (false);
	}
}
