#include "jgl.h"

namespace jgl
{
	Glyph nullchar = Glyph('\0');

	Unique_string::Unique_string()
	{
		_content = jgl::Array<Glyph>(JGL_STRING_PUSH_SIZE);
	}

	Unique_string::Unique_string(const Glyph value) : Unique_string()
	{
		push_back(value);
	}

	Unique_string::Unique_string(const char *str) : Unique_string()
	{
		for (size_t i = 0; str[i] != '\0'; i++)
			push_back(str[i]);
	}
	Unique_string::Unique_string(const Unique_string& old)
	{
		clear();
		for (size_t i = 0; i < old.size(); i++)
		{
			Glyph tmp = old[i];
			push_back(tmp);
		}
	}
	Unique_string::Unique_string(const std::string str)
	{
		clear();

		char tmp[4] = { 0, 0, 0, 0 };
		size_t i = 0;
		while (i < str.size())
		{
			int delta = create_char_unicode(tmp, str.c_str(), i);
			if (delta == -1)
				error_exit(1, "Error while parsing a Unique_string");
			push_back(tmp);
			i += delta;
		}
	}

	Glyph& Unique_string::operator[](size_t i)
	{
		return (_content[i]);
	}
	const Glyph& Unique_string::operator[](size_t i) const
	{
		return (_content[i]);
	}

	void Unique_string::operator = (const Unique_string p_value)
	{
		clear();

		for (size_t i = 0; i < p_value.size(); i++)
			push_back(p_value[i]);
	}

	Unique_string Unique_string::operator += (const Unique_string delta)
	{
		for (size_t i = 0; i < delta.size(); i++)
			push_back(delta[i]);

		return (*this);
	}

	Unique_string Unique_string::operator + (const Unique_string delta)
	{
		for (size_t i = 0; i < delta.size(); i++)
			push_back(delta[i]);

		return (*this);
	}

	void Unique_string::print_info()
	{
		std::cout << "Size : " << _content.size() << std::endl;
		std::cout << "Max size : " << _content.max_size() << std::endl;
		std::cout << "Push size : " << _content.push_size() << std::endl;
	}

	std::string Unique_string::std() const
	{
		std::string result;

		for (size_t i = 0; i < size(); i++)
		{
			Glyph tmp_glyph = this->operator[](i);
			for (size_t i = 0; tmp_glyph.content()[i] != '\0'; i++)
				result.push_back(tmp_glyph.content()[i]);
		}

		return (result);
	}

	jgl::Unique_string operator + (const char* str, const jgl::Unique_string delta)
	{
		Unique_string result;

		for (size_t i = 0; str[i] != '\0'; i++)
			result.push_back(str[i]);

		for (size_t i = 0; i < delta.size(); i++)
			result.push_back(delta[i]);

		return (result);
	}

	jgl::Unique_string operator + (const jgl::Unique_string str, const jgl::Unique_string delta)
	{
		jgl::Unique_string result;

		result = Unique_string(str);

		for (size_t i = 0; i < delta.size(); i++)
			result.push_back(delta[i]);

		return (result);
	}

	bool Unique_string::find(const Glyph to_find)
	{
		for (size_t i = 0; i < size(); i++)
			if (this->operator[](i) == to_find)
				return(true);
		return (false);
	}

	bool Unique_string::contain(Unique_string to_find)
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

	bool Unique_string::operator == (const Unique_string other) const 
	{
		if (size() != other.size())
			return (false);
		for (size_t i = 0; i < size(); i++)
			if (other[i] != this->operator[](i))
				return (false);
		return (true);
	}

	bool Unique_string::operator != (const Unique_string other) const 
	{
		return (!(*this == other));
	}

	Unique_string Unique_string::substr(size_t start, size_t end)
	{
		Unique_string result;
		
		this->substr(result, start, end);

		return (result);
	}

	void Unique_string::substr(Unique_string& result, size_t start, size_t end)
	{
		size_t size = end - start;

		if (start >= _content.size())
		{
			result.clear();
			return ;
		}

		result.clear();
		if (result.max_size() <= size)
			result.resize(size);
		for (size_t i = 0; i < size; i++)
			result[i] = this->operator[](i + start);
	}

}