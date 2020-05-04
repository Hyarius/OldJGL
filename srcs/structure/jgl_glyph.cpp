#include "jgl.h"

namespace jgl
{
	void Glyph::initialize()
	{
		for (size_t i = 0; i < 5; i++)
			_content[i] = 0;
	}

	Glyph::Glyph(size_t value)
	{
		char* str = (char*)(&value);
		initialize();
		int len = create_char_unicode(nullptr, str, 0);
		for (int i = 0; i < len; i++)
			_content[i] = str[i];
	}
	Glyph::Glyph(int value)
	{
		char* str = (char*)(&value);
		initialize();
		int len = create_char_unicode(nullptr, str, 0);
		for (int i = 0; i < len; i++)
			_content[i] = str[i];
	}
	Glyph::Glyph(char c)
	{
		initialize(); _content[0] = c;
	}
	Glyph::Glyph(char* str)
	{
		initialize();
		int len = create_char_unicode(nullptr, str, 0);
		for (int i = 0; i < len; i++)
			_content[i] = str[i];
	}
	Glyph::Glyph(const Glyph& c)
	{
		initialize();
		for (size_t i = 0; i < 4; i++)
			_content[i] = c._content[i];
	}
	Glyph::Glyph()
	{
		initialize();
	}
	Glyph::Glyph(Glyph& p_value)
	{
		initialize();
		for (size_t i = 0; i < 4; i++)
			_content[i] = p_value._content[i];
	}

	const char* Glyph::content()
	{
		return (_content);
	}

	const char* Glyph::content() const
	{
		return (_content);
	}

	void Glyph::print_info()
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

	size_t Glyph::value()
	{
		size_t self_value = 0;
		for (size_t i = 0; i < 4; i++)
			self_value += 255 * _content[i];
		return (self_value);
	}

	size_t Glyph::value() const
	{
		size_t self_value = 0;
		for (size_t i = 0; i < 4; i++)
			self_value += 255 * _content[i];
		return (self_value);
	}

	/*Glyph Glyph::operator = (Glyph& p_value)
	{
		for (size_t i = 0; i < 4; i++)
			_content[i] = p_value._content[i];

		return (*this);
	}*/

	Glyph Glyph::operator = (const Glyph p_value)
	{
		for (size_t i = 0; i < 4; i++)
			_content[i] = p_value._content[i];

		return (*this);
	}

	bool Glyph::operator == (Glyph c)
	{
		return (value() == c.value());
	}
	bool Glyph::operator != (Glyph c)
	{
		return (value() != c.value());
	}

	bool Glyph::operator == (Glyph& c) const
	{
		return (value() == c.value());
	}
	bool Glyph::operator != (Glyph& c) const
	{
		return (value() != c.value());
	}

	bool Glyph::operator > (Glyph& other)
	{
		return (value() > other.value());
	}
	bool Glyph::operator < (Glyph& other)
	{
		return (value() < other.value());
	}
}