#include "jgl.h"

namespace jgl
{

	Glyph::Glyph(size_t value)
	{
		char* str = (char*)(&value);
		int len = create_char_unicode(nullptr, str, 0);
		for (int i = 0; i < len; i++)
			_content[i] = str[i];
	}

	Glyph::Glyph(int value)
	{
		char* str = (char*)(&value);
		int len = create_char_unicode(nullptr, str, 0);
		for (int i = 0; i < len; i++)
			_content[i] = str[i];
	}

	Glyph::Glyph(char c)
	{
		_content[0] = c;
	}

	Glyph::Glyph(char* str)
	{
		int len = create_char_unicode(nullptr, str, 0);
		for (int i = 0; i < len; i++)
			_content[i] = str[i];
	}

	Glyph::Glyph(const Glyph& c)
	{
		for (size_t i = 0; i < 4; i++)
			_content[i] = c._content[i];
	}

	Glyph::Glyph()
	{
		
	}

	Glyph::Glyph(Glyph& p_value)
	{
		for (size_t i = 0; i < 4; i++)
			_content[i] = p_value._content[i];
	}

	const char* Glyph::content() const
	{
		return (_content);
	}

	void Glyph::print_info() const
	{
		std::cout << "Value total : " << value() << std::endl;
		std::cout << "Binary : ";
		for (size_t i = 0; i < 4; i++)
		{
			if (i != 0)
				std::cout << " - ";
			std::cout << std::bitset<8>(_content[i]); ;
		}
		std::cout << std::endl;
	}

	size_t Glyph::size() const
	{
		size_t result = 0;

		for (size_t i = 0; _content[i] != 0; i++)
			result++;
		return (result);
	}

	size_t Glyph::value() const
	{
		size_t self_value = 0;
		for (size_t i = 0; i < 4; i++)
			self_value += 255 * _content[i];
		return (self_value);
	}

	bool operator == (const Glyph& tmp, const Glyph& other)
	{
		if (tmp.value() == other.value())
			return (true);
		return (false);
	}
	bool operator != (const Glyph& tmp, const Glyph& other)
	{
		if (tmp.value() != other.value())
			return (true);
		return (false);
	}
	bool operator > (const Glyph& tmp, const Glyph& other)
	{
		if (tmp.value() > other.value())
			return (true);
		return (false);
	}
	bool operator < (const Glyph& tmp, const Glyph& other)
	{
		if (tmp.value() < other.value())
			return (true);
		return (false);
	}
	bool operator >= (const Glyph& tmp, const Glyph& other)
	{
		if (tmp.value() >= other.value())
			return (true);
		return (false);
	}
	bool operator <= (const Glyph& tmp, const Glyph& other)
	{
		if (tmp.value() <= other.value())
			return (true);
		return (false);
	}
}