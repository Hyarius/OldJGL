#include "jgl.h"

static void active_tab(Data p_data)
{
	vector<c_button *> buttons = *(vector<c_button *> *)(p_data.content[0]);
	vector<c_frame *> tabs = *(vector<c_frame *> *)(p_data.content[1]);
	size_t index = (size_t)(p_data.content[2]);

	for (size_t i = 0; i < buttons.size(); i++)
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

	for (size_t i = 0; i < tabs.size(); i++)
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

c_tab::c_tab(c_widget *p_parent) : c_widget(p_parent)
{
	tab_area = new c_frame(this);
	button_area = new c_frame(this);

	button_area->set_front(Color(0, 255, 0, 0));
	button_area->set_back(Color(0, 255, 0, 0));

	tab_area->activate();
	button_area->activate();

	set_geometry(-1, -1);
}

c_frame *c_tab::add_tab(string p_name, int index)
{
	bool tmp = (_tabs.size() == 0 ? true : false);
	c_frame *new_tab = new c_frame(tab_area);
	new_tab->set_border(0);
	c_button *new_tab_button = new c_button(&active_tab, nullptr, button_area);
	new_tab_button->label().set_text(p_name);
	new_tab_button->activate();

	if (index == -1)
		index = _tabs.size();

	for (size_t i = _tabs.size(); i <= index + 1; i++)
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

void c_tab::reset_size()
{
	reset_tab();
	reset_button();
}

void c_tab::reset_tab()
{
	Vector2 tab_pos = Vector2(0.0f, button_area->area().y + tab_area->border() * 2);
	Vector2 tab_size = Vector2(area().x - tab_area->border(), area().y - tab_area->border() - tab_pos.y);

	tab_area->set_geometry(tab_pos, tab_size);
	for (size_t i = 0; i < _tabs.size(); i++)
		if (_tabs[i] != nullptr)
			_tabs[i]->set_geometry(0, tab_size - (_tabs[i]->border() * 2));
}

void c_tab::reset_button()
{
	Vector2 size;
	Vector2 pos = 0;
	size.y = 30.0f;

	Vector2 button_pos = tab_area->border();
	Vector2 button_size = Vector2(area().x - tab_area->border() * 2, 40.0f);

	button_area->set_geometry(button_pos, button_size);

	for (size_t i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i] != nullptr)
		{
			float tmp = calc_text_len(_buttons[i]->text(), 20);
			size.x = tmp;
			_buttons[i]->set_geometry(pos, size);
			pos.x += size.x + button_area->border();
			_buttons[i]->set_data(Data(3, &_buttons, &_tabs, i));
		}
	}
}

void c_tab::move(Vector2 delta)
{

}

void c_tab::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	reset_size();
}

void c_tab::render()
{
	if (is_active() == false)
		return ;
}

bool c_tab::handle_mouse()
{
	return (false);
}

bool c_tab::handle_keyboard()
{
	return (false);
}
