#include "jgl.h"

static void active_tab(Data p_data)
{
	vector<c_button *> buttons = *(vector<c_button *> *)(p_data.content[0]);
	vector<c_frame *> tabs = *(vector<c_frame *> *)(p_data.content[1]);
	size_t index = (size_t)(p_data.content[2]);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		if (i == index)
		{
			buttons[i]->box().set_front(Color(150, 150, 150));
			buttons[i]->box().set_back(Color(120, 120, 120));
		}
		else
		{
			buttons[i]->box().set_back(Color(150, 150, 150));
			buttons[i]->box().set_front(Color(195, 195, 195));
		}
	}

	for (size_t i = 0; i < tabs.size(); i++)
	{
		if (i == index)
			tabs[i]->set_active(true);
		else
			tabs[i]->set_active(false);
	}
}

c_tab::c_tab(c_widget *p_parent)
{
	tab_area = new c_frame(this);
	button_area = new c_frame(this);

	button_area->box().set_front(Color(0, 255, 0, 0));
	button_area->box().set_back(Color(0, 255, 0, 0));

	tab_area->activate();
	button_area->activate();

	add_tab("Tab 1");
	add_tab("Tab 2");
}

void c_tab::add_tab(string p_name, int index)
{
	c_frame *new_tab = new c_frame(tab_area);
	c_button *new_tab_button = new c_button(&active_tab, nullptr, button_area);
	new_tab_button->text().set_text(p_name);
	new_tab_button->activate();

	if (index == -1)
		index = _tabs.size();

	_tabs.insert(_tabs.begin() + index, new_tab);
	_buttons.insert(_buttons.begin() + index, new_tab_button);

	reset_button();
}

void c_tab::reset_button()
{
	Vector2 size;
	Vector2 pos = 0;

	float tmp = (button_area->box().area().x - (button_area->box().border() * _buttons.size() - 2)) / _buttons.size();
	size.x = (tmp <= 150.0f ? tmp : 150.0f);
	size.y = 50.0f;

	for (size_t i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->set_geometry(pos, size);
		pos.x += size.x + button_area->box().border();
		_buttons[i]->set_data(Data(3, &_buttons, &_tabs, i));
	}
}

void c_tab::move(Vector2 delta)
{

}

void c_tab::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{
	Vector2 button_pos = tab_area->box().border();
	Vector2 button_size = Vector2(p_area.x - tab_area->box().border() * 2, 50.0f);

	Vector2 tab_pos = button_pos + Vector2(0, 50 + tab_area->box().border());
	Vector2 tab_size = Vector2(p_area.x - tab_area->box().border() * 2, p_area.y - tab_area->box().border() - tab_pos.y);

	button_area->set_geometry(button_pos, button_size);

	tab_area->set_geometry(tab_pos, tab_size);
	for (size_t i = 0; i < _tabs.size(); i++)
		_tabs[i]->set_geometry(tab_pos + _tabs[i]->box().border(), tab_size - (_tabs[i]->box().border() * 2));

	reset_button();
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
