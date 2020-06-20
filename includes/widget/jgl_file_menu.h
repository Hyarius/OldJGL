#ifndef JGL_SAVING_MENU_H
#define JGL_SAVING_MENU_H

#include "jgl_string.h"
#include "jgl_widgets.h"
#include "jgl_frame.h"
#include "jgl_file_handler.h"
#include "jgl_vscrollable_bar.h"
#include "jgl_text_label.h"
#include "jgl_text_entry.h"
#include "jgl_button.h"

class File_menu : public jgl::Widget
{
private:
	jgl::String _path;
	jgl::String _extension;
	std::vector<jgl::File> _list_file;

	jgl::Frame* _frame;

	jgl::Frame* _file_frame;
	jgl::Vscroll_bar* _scroll_bar;
	std::vector<jgl::Text_label*> _files_labels;

	jgl::Text_label* _name_indicator;
	jgl::Text_entry* _name_entry;
	jgl::Button* _valid_button;
	jgl::Button* _cancel_button;

public:
	jgl::String extension() { return (_extension); }
	jgl::String path() { return (_path); }
	jgl::Text_entry* entry() { return (_name_entry); }

	void set_extension(jgl::String p_extension)
	{
		_extension = p_extension;
	}
	void set_path(jgl::String p_path)
	{
		std::filesystem::path p = p_path->std().c_str();
		_path = std::filesystem::absolute(p).string();
	}

	File_menu(jgl::String p_path, jgl::String extension = "*", jgl::Widget *p_parent = nullptr)
	{
		set_extension(extension);
		set_path(p_path);
		_frame = new jgl::Frame(this);
		_frame->activate();
		_file_frame = new jgl::Frame(_frame);
		_file_frame->activate();
		_scroll_bar = new jgl::Vscroll_bar(_file_frame);
		_scroll_bar->set_min_pos(0);
		_scroll_bar->set_max_pos(100);
		_scroll_bar->activate();
		_name_indicator = new jgl::Text_label("Name : ", _frame);
		_name_indicator->activate();
		_name_entry = new jgl::Text_entry("", _frame);
		_name_entry->activate();
		_valid_button = new jgl::Button(nullptr, nullptr, _frame);
		_valid_button->set_text("Valid");
		_valid_button->activate();
		_cancel_button = new jgl::Button(nullptr, nullptr, _frame);
		_cancel_button->set_text("Cancel");
		_cancel_button->activate();
	}

	void actualize_files_label_geometry()
	{
		size_t nb_collum = 3;
		jgl::Vector2 label_size = jgl::Vector2((_file_frame->area().x - (20 + (nb_collum - 1) * 10)) / nb_collum - 5, 30.0f);
		for (size_t i = 0; i < _files_labels.size(); i++)
		{
			_files_labels[i]->set_geometry(jgl::Vector2(10 + ((i % nb_collum) * (label_size.x + 10)), 10 + ((i / nb_collum) * (label_size.y + 10))), label_size);
		}
		float tmp_value = (_files_labels.size() / 3) * (label_size.y + 10);
		_scroll_bar->set_max_pos(jgl::Vector2(0.0f, (tmp_value > (_file_frame->area().y - (label_size.y + 20)) ? tmp_value : (_file_frame->area().y - (label_size.y + 20)))));
	}

	void actualize_files()
	{
		for (size_t i = 0; i < _files_labels.size(); i++)
		{
			delete _files_labels[i];
		}
		_files_labels.clear();
		_list_file = jgl::list_files(_path, _extension);
		for (size_t i = 1; i < _list_file.size(); i++)
		{
			jgl::Text_label* tmp = new jgl::Text_label(_list_file[i].name, _file_frame);
			if (_list_file[i].type == jgl::File_type::file)
			{
				tmp->set_back(jgl::Color(150, 150, 150));
				tmp->set_front(jgl::Color(195, 195, 195));
			}
			else if (_list_file[i].type == jgl::File_type::directory)
			{
				tmp->set_back(jgl::Color(51, 107, 176));
				tmp->set_front(jgl::Color(92, 137, 209));
			}
			else
			{
				tmp->set_back(jgl::Color(136, 54, 173));
				tmp->set_front(jgl::Color(143, 76, 173));
			}
			tmp->activate();
			_files_labels.push_back(tmp);
		}
		actualize_files_label_geometry();
	}

	void set_valid_interation(jgl::Funct p_funct, jgl::Data p_param) {
		_valid_button->set_action(p_funct, p_param);
	}

	void set_cancel_interation(jgl::Funct p_funct, jgl::Data p_param) {
		_cancel_button->set_action(p_funct, p_param);
	}

	void set_geometry_imp(jgl::Vector2 p_anchor, jgl::Vector2 p_area)
	{
		_frame->set_geometry(p_anchor, p_area);
		jgl::Vector2 size = jgl::Vector2(150, 40);
		jgl::Vector2 pos = jgl::Vector2(10.0f, p_area.y - 50);
		_file_frame->set_geometry(10, jgl::Vector2(p_area.x - 20, pos.y - 20));
		actualize_files_label_geometry();
		_scroll_bar->set_geometry(jgl::Vector2(_file_frame->area().x - 20, 0.0f), jgl::Vector2(20.0f, _file_frame->area().y));
		_name_indicator->set_geometry(pos, size);
		pos.x += size.x + 10;
		size = jgl::Vector2(p_area.x - pos.x - 230.0f, 40.0f);
		_name_entry->set_geometry(pos, size);
		pos.x += size.x + 10;
		size = jgl::Vector2(100, 40);
		_valid_button->set_geometry(pos, size);
		pos.x += size.x + 10;
		size = jgl::Vector2(100, 40);
		_cancel_button->set_geometry(pos, size);
		pos.x += size.x + 10;
	}

	bool handle_mouse()
	{
		if (jgl::get_button(jgl::mouse_button::left) == jgl::mouse_state::release)
		{
			for (size_t i = 0; i < _files_labels.size(); i++)
			{
				if (_files_labels[i]->is_pointed() == true)
				{
					if (_list_file[i + 1].type == jgl::File_type::file)
						_name_entry->set_text(_files_labels[i]->text());
					if (_list_file[i + 1].type == jgl::File_type::directory)
					{
						jgl::String new_path;

						if (_list_file[i + 1].name == "..")
						{
							std::vector<jgl::String> tmp = strsplit(_path, "\\");
							if (tmp.size() >= 1)
							{
								_path->clear();
								for (size_t i = 0; i < tmp.size() - 1; i++)
								{
									if (i != 0)
										_path += "\\";
									_path += tmp[i];
								}
							}
						}
						else
						{
							_path += "\\" + _list_file[i + 1].name;
						}
						actualize_files();
					}
					return (true);
				}
			}
		}
		return (false);
	}

	void render(){}
};

#endif