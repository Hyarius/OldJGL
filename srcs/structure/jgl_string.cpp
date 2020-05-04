#include "jgl.h"

namespace jgl
{
	Glyph nullchar = Glyph('\0');

	void String::add_line()
	{
		_nb_line++;
		_max_size += _push_size;
		Glyph** old_content = _content;
		_content = new Glyph * [_nb_line + 1];
		if (old_content != nullptr)
		{
			for (size_t i = 0; i < _nb_line - 1; i++)
				_content[i] = old_content[i];
		}
		_content[_nb_line - 1] = create_line();
		_content[_nb_line] = nullptr;
		if (old_content != nullptr)
			delete old_content;
	}
	Glyph* String::create_line()
	{
		Glyph* tmp_array;

		tmp_array = new Glyph[_push_size];

		return (tmp_array);
	}

	int String::calc_line(size_t index)
	{
		return (index / _push_size);
	}
	int String::calc_index(size_t index)
	{
		return (index - (index / _push_size));
	}
	int String::calc_line(size_t index) const
	{
		return (index / _push_size);
	}
	int String::calc_index(size_t index) const
	{
		return (index - (index / _push_size));
	}

	void String::initialize()
	{
		_push_size = JGL_STRING_PUSH_SIZE;
		_size = 0;
		_max_size = 0;
		_content = nullptr;
		_nb_line = 0;
	}

	String::String(const Glyph value)
	{
		initialize();
		push_back(value);
	}

	String::String(const char *str)
	{
		initialize();
		for (size_t i = 0; str[i] != '\0'; i++)
			push_back(str[i]);
	}
	String::String(const String& old)
	{
		initialize();
		for (size_t i = 0; i < old._size; i++)
		{
			Glyph tmp = old[i];
			push_back(tmp);
		}
	}
	String::String(const std::string str)
	{
		initialize();
		char tmp[4] = { 0, 0, 0, 0 };
		size_t i = 0;
		while (i < str.size())
		{
			int delta = create_char_unicode(tmp, str.c_str(), i);
			if (delta == -1)
				error_exit(1, "Error while parsing a String");
			push_back(tmp);
			i += delta;
		}
	}
	String::String()
	{
		initialize();
	}
	String::~String()
	{
		if (_content != nullptr)
		{
			for (size_t i = 0; i < _nb_line; i++)
			{
				delete _content[i];
			}
			delete _content;
		}
	}

	void String::push_back(Glyph element)
	{
		if (_size + 1 >= _max_size)
			add_line();
		int line = calc_line(_size);
		int index = calc_index(_size);
		_content[line][index] = element;
		_size++;
	}

	void String::push_front(Glyph element)
	{
		insert(0, element);
	}

	Glyph& String::operator[](size_t i)
	{
		if (_size == 0)
			return (jgl::nullchar);
		if (i >= _size)
			return (jgl::nullchar);
		int line = calc_line(i);
		int index = calc_index(i);
		return (_content[line][index]);
	}
	const Glyph& String::operator[](size_t i) const
	{
		if (_size == 0)
			return (jgl::nullchar);
		if (i >= _size)
			return (jgl::nullchar);
		int line = calc_line(i);
		int index = calc_index(i);
		return (_content[line][index]);
	}

	void String::clear()
	{
		_size = 0;
	}

	String String::operator = (const String p_value)
	{
		clear();

		for (size_t i = 0; i < p_value.size(); i++)
			push_back(p_value[i]);

		return (*this);
	}

	String String::operator += (const String delta)
	{
		for (size_t i = 0; i < delta.size(); i++)
			push_back(delta[i]);

		return (*this);
	}

	String String::operator + (const String delta)
	{
		String result;

		for (size_t i = 0; i < this->size(); i++)
			result.push_back(this->operator[](i));

		for (size_t i = 0; i < delta.size(); i++)
			result.push_back(delta[i]);

		return (result);
	}

	void String::print_info()
	{
		std::cout << "Size : " << _size << std::endl;
		std::cout << "Nb line : " << _nb_line << std::endl;
		std::cout << "Max size : " << _max_size << std::endl;
		std::cout << "Push size : " << _push_size << std::endl;
	}

	void String::insert(const size_t index, const jgl::Glyph insert_value)
	{
		if (index >= _size + 1)
			error_exit(1, "index too high while inserting a glyph");

		size_t i = size();
		push_back('\0');
		while (i >= 1 && i > index)
		{
			Glyph tmp = this->operator[](i - 1);
			this->operator[](i) = tmp;
			i--;
		}
		this->operator[](index) = insert_value;
	}

	void String::insert(const size_t index, const jgl::String insert_value)
	{
		if (index >= _size + insert_value.size())
			error_exit(1, "index too high while inserting a string");

		size_t i = size();
		size_t tmp_size = insert_value.size();
		for (size_t j = 0; j < tmp_size; j++)
			push_back('\0');
		while (i > index)
		{
			Glyph tmp = this->operator[](i - tmp_size);
			this->operator[](i) = tmp;
			i--;
		}
		for (size_t j = 0; j < tmp_size; j++)
			this->operator[](index + j) = insert_value[j];
	}

	std::string String::std()
	{
		std::string result;

		for (size_t i = 0; i < size(); i++)
		{
			Glyph tmp_glyph = this->operator[](i);
			result.append(tmp_glyph.content());
		}

		return (result);
	}

	jgl::String operator + (const char* str, const jgl::String delta)
	{
		String result;

		for (size_t i = 0; str[i] != '\0'; i++)
			result.push_back(str[i]);

		for (size_t i = 0; i < delta.size(); i++)
			result.push_back(delta[i]);

		return (result);
	}

	jgl::String operator + (const jgl::String str, const jgl::String delta)
	{
		jgl::String result;

		result = String(str);

		for (size_t i = 0; i < delta.size(); i++)
			result.push_back(delta[i]);

		return (result);
	}

	bool String::find(const Glyph to_find)
	{
		for (size_t i = 0; i < size(); i++)
			if (this->operator[](i) == to_find)
				return(true);
		return (false);
	}

	bool String::contain(String to_find)
	{
		bool result = false;
		for (size_t i = 0; i < size(); i++)
		{
			result = false;
			for (size_t j = 0; j < to_find.size() && result == false; j++)
				if (this->operator[](i) == to_find[j])
					result = true;
			if (result == false)
				return (false);
		}
		return (true);
	}

	void String::erase(size_t index)
	{
		if (_size == 0)
			return;
		for (size_t i = index; i < _size - 1; i++)
			this->operator[](i) = this->operator[](i + 1);
		_size--;
	}

	bool String::operator == (String other)
	{
		if (size() != other.size())
			return (false);
		for (size_t i = 0; i < size(); i++)
			if (other[i] != this->operator[](i))
				return (false);
		return (true);
	}

	bool String::operator != (String other)
	{
		return (!(*this == other));
	}

	String String::substr(size_t start, size_t end)
	{
		String result;

		if (start >= _size)
			return (result);

		for (size_t i = start; i < end; i++)
		{
			result.push_back(this->operator[](i));
		}
		return (result);
	}

}