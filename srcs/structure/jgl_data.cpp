#include "jgl.h"

namespace jgl
{
	jgl::Data::Data()
	{
		_content.clear();
	}

	jgl::Data::Data(void* p_data)
	{
		_content.clear();
		_content.push_back(p_data);
	}

	jgl::Data::Data(int nb_param, ...)
	{
		va_list list_param;
		va_start(list_param, nb_param);

		_content.clear();
		for (int i = 0; i < nb_param; i++)
			_content.push_back(va_arg(list_param, void*));

		va_end(list_param);
	}

	void		jgl::Data::operator = (void* p_data)
	{
		_content.clear();
		_content.push_back(p_data);
	}

	void		jgl::Data::operator + (void* p_ptr)
	{
		_content.push_back(p_ptr);
	}

	jgl::Data		jgl::Data::operator + (Data& delta)
	{
		Data result;

		result.content().clear();

		for (size_t i = 0; i < _content.size(); i++)
			result.content().push_back(this->content(i));

		for (size_t i = 0; i < delta.content().size(); i++)
			result.content().push_back(delta.content(i));

		return (result);
	}

	void 		jgl::Data::operator += (void* p_ptr)
	{
		_content.push_back(p_ptr);
	}

	void 		jgl::Data::operator += (Data& delta)
	{
		for (size_t i = 0; i < delta.content().size(); i++)
			_content.push_back(delta.content(i));
	}
}