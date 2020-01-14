#include "jgl.h"

Data::Data(void *p_data)
{
	content.clear();
	content.push_back(p_data);
}

Data::Data(int nb_param, ...)
{
	va_list list_param;
    va_start(list_param, nb_param);

	content.clear();
	for (int i = 0; i < nb_param; i++)
		content.push_back(va_arg(list_param, void *));

	va_end(list_param);
}

void		Data::operator = (void *p_data)
{
	content.clear();
	content.push_back(p_data);
}

void		Data::operator + (void *p_ptr)
{
	content.push_back(p_ptr);
}

Data		Data::operator + (const Data& delta)
{
	Data result;

	result.content.clear();

	for (size_t i = 0; i < this->content.size(); i++)
		result.content.push_back(this->content[i]);

	for (size_t i = 0; i < delta.content.size(); i++)
		result.content.push_back(delta.content[i]);

	return (result);
}

void 		Data::operator += (void *p_ptr)
{
	this->content.push_back(p_ptr);
}

void 		Data::operator += (const Data& delta)
{
	for (size_t i = 0; i < delta.content.size(); i++)
		this->content.push_back(delta.content[i]);
}
