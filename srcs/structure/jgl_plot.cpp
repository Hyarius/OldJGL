#include "jgl.h"

c_plot::c_plot(Vector2 p_size, Plot_data p_absciss, Plot_data p_ordinate)
{
	_color = Color(220, 220, 220);
	_margin = Vector2(30, 30);
	_text_size = 16;
	set_size(p_size);
	_absciss = p_absciss;
	_ordinate = p_ordinate;
	_point_size = 5;
	_line_size = 1;
}

c_plot::~c_plot()
{

}

void c_plot::clear()
{
	_lines.clear();
}

void c_plot::actualize_point()
{
	_origin = Vector2(_margin.x, _size.y - _margin.y);
	_pos_up = _margin;
	_pos_right = _origin + Vector2(_size.x - _margin.x * 2, 0.0f);
	calc_axis_unit();
}

void c_plot::add_line(Color p_color)
{
	_lines.push_back(Line(p_color));
}

void c_plot::add_point(Vector2 p_point, size_t line)
{
	if (_lines.size() <= line)
		_lines.resize(line + 1);

	_lines[line].add_point(p_point);
}

void c_plot::set_line_color(size_t index, Color p_color)
{
	_lines[index] = Line(p_color);
}

void c_plot::calc_axis_unit()
{
	_ordinate_unit = (_pos_up - _origin) / (ordinate().max - ordinate().min);
	_absciss_unit = (_pos_right - _origin) / (absciss().max - absciss().min);
}

void c_plot::initialize()
{
	_plot = new c_image(_size.x, _size.y, _color);
}

void c_plot::draw()
{
	draw_line(Color(0, 0, 0), _origin, _pos_right, 2);
	draw_line(Color(0, 0, 0), _origin, _pos_up, 2);
	draw_absciss();
	draw_ordinate();

	for (size_t i = 0; i < _lines.size(); i++)
	{
		for (size_t j = 0; j < _lines[i].points.size(); j++)
		{
			draw_plot_point(_lines[i].points[j], _lines[i].color);
			if (j != 0)
				draw_plot_line(_lines[i].points[j - 1], _lines[i].points[j], _lines[i].color);
		}
	}
}

void c_plot::draw_absciss()
{
	draw_text(absciss().name, _pos_right - Vector2(calc_text_len(absciss().name, _text_size), 20), _text_size);
	for (float i = absciss().min; i <= absciss().max; i += absciss().delta)
		draw_absciss_point(i);
}

void c_plot::draw_plot_point(Vector2 point, Color color)
{
	float delta_x = point.x - absciss().min;
	float delta_y = point.y - ordinate().min;

	draw_point(color, _origin + _absciss_unit * delta_x + _ordinate_unit * delta_y, _point_size);
}

void c_plot::draw_plot_line(Vector2 point_a, Vector2 point_b, Color color)
{
	Vector2 tmp_a = _origin + _absciss_unit * (point_a.x - absciss().min) + _ordinate_unit * (point_a.y - ordinate().min);
	Vector2 tmp_b = _origin + _absciss_unit * (point_b.x - absciss().min) + _ordinate_unit * (point_b.y - ordinate().min);

	draw_line(color, tmp_a, tmp_b, _line_size);
}

void c_plot::draw_absciss_point(float value)
{
	string text = ftoa(value, absciss().precision);
	if (absciss().funct != nullptr)
		text = absciss().funct(value);
	float delta = value - absciss().min;
	draw_point(Color(0, 0, 0), _origin + _absciss_unit * delta, 5);
	draw_centred_text(text, _origin + _absciss_unit * delta + Vector2(0.0f, _margin.y / 2));
}

void c_plot::draw_ordinate()
{
	draw_text(ordinate().name, Vector2(10, 10), _text_size);
	for (float i = ordinate().min; i <= ordinate().max; i += ordinate().delta)
		draw_ordinate_point(i);
}

void c_plot::draw_ordinate_point(float value)
{
	string text = ftoa(value, ordinate().precision);
	float delta = value - ordinate().min;
	draw_point(Color(0, 0, 0), _origin + _ordinate_unit * delta, 5);
	draw_centred_text(text, _origin + _ordinate_unit * delta - Vector2(_margin.x / 2, 0.0f));
}

void c_plot::save(string path)
{
	_plot->active();
	draw();
	_plot->save(path);
	_plot->unactive();
}
