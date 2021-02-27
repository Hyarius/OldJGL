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
		for (uint32_t i = 0; str[i] != '\0'; i++)
			push_back(str[i]);
	}
	Unique_string::Unique_string(const Unique_string& old)
	{
		clear();
		for (uint32_t i = 0; i < old.size(); i++)
		{
			Glyph tmp = old[i];
			push_back(tmp);
		}
	}
	Unique_string::Unique_string(const std::string str)
	{
		clear();

		char tmp[4] = { 0, 0, 0, 0 };
		uint32_t i = 0;
		while (i < str.size())
		{
			int delta = create_char_unicode(tmp, str.c_str(), i);
			if (delta == -1)
				error_exit(1, "Error while parsing a Unique_string");
			push_back(tmp);
			i += delta;
		}
	}

	Glyph& Unique_string::operator[](uint32_t i)
	{
		return (_content[i]);
	}
	const Glyph& Unique_string::operator[](uint32_t i) const
	{
		return (_content[i]);
	}

	void Unique_string::operator = (const Unique_string p_value)
	{
		clear();

		for (uint32_t i = 0; i < p_value.size(); i++)
			push_back(p_value[i]);
	}

	Unique_string Unique_string::operator += (const Unique_string delta)
	{
		for (uint32_t i = 0; i < delta.size(); i++)
			push_back(delta[i]);

		return (*this);
	}

	Unique_string Unique_string::operator + (const Unique_string delta)
	{
		for (uint32_t i = 0; i < delta.size(); i++)
			push_back(delta[i]);

		return (*this);
	}

	void Unique_string::print_info() const
	{
		std::cout << "Size : " << _content.size() << std::endl;
		std::cout << "Max size : " << _content.max_size() << std::endl;
		std::cout << "Push size : " << _content.push_size() << std::endl;
	}
	const char* Unique_string::str()
	{
		uint32_t c = 0;

		if (_str == nullptr)
		{
			_str = new char[size()];

			for (uint32_t i = 0; i < size(); i++)
			{
				jgl::Glyph tmp = this->operator[](i);
				for (uint32_t j = 0; j < tmp.size(); j++)
				{
					_str[c] = tmp.content()[j];
					c++;
				}
			}
		}

		return (_str);
	}
	const std::string Unique_string::std() const
	{
		std::string result;

		for (uint32_t i = 0; i < size(); i++)
		{
			Glyph tmp_glyph = this->operator[](i);
			for (uint32_t i = 0; tmp_glyph.content()[i] != '\0'; i++)
				result.push_back(tmp_glyph.content()[i]);
		}

		return (result);
	}

	jgl::Unique_string operator + (const char* str, const jgl::Unique_string delta)
	{
		Unique_string result;

		for (uint32_t i = 0; str[i] != '\0'; i++)
			result.push_back(str[i]);

		for (uint32_t i = 0; i < delta.size(); i++)
			result.push_back(delta[i]);

		return (result);
	}

	jgl::Unique_string operator + (const jgl::Unique_string str, const jgl::Unique_string delta)
	{
		jgl::Unique_string result;

		result = Unique_string(str);

		for (uint32_t i = 0; i < delta.size(); i++)
			result.push_back(delta[i]);

		return (result);
	}

	const bool Unique_string::find(const Glyph to_find) const
	{
		for (uint32_t i = 0; i < size(); i++)
			if (this->operator[](i) == to_find)
				return(true);
		return (false);
	}

	const bool Unique_string::contain(const Unique_string to_find) const
	{
		bool result = false;
		for (uint32_t i = 0; i < size(); i++)
		{
			result = false;
			for (uint32_t j = 0; j < to_find.size() && result == false; j++)
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
		for (uint32_t i = 0; i < size(); i++)
			if (other[i] != this->operator[](i))
				return (false);
		return (true);
	}

	bool Unique_string::operator != (const Unique_string other) const 
	{
		return (!(*this == other));
	}

	Unique_string Unique_string::substr(const uint32_t start, const uint32_t end) const
	{
		Unique_string result;
		
		this->substr(result, start, end);

		return (result);
	}

	void Unique_string::substr(Unique_string& result, const uint32_t start, const uint32_t end) const
	{
		uint32_t size = end - start;

		if (start >= _content.size())
		{
			result.clear();
			return ;
		}

		result.clear();
		if (result.max_size() <= size)
			result.resize(size);
		for (uint32_t i = 0; i < size; i++)
			result[i] = this->operator[](i + start);
	}

}