#ifndef JGL_CHAR_H
#define JGL_CHAR_H

#include "jgl_includes.h"

namespace jgl
{
	class Glyph
	{
	private:
		char _content[5] = {0, 0, 0, 0, 0};

	public:
		Glyph(uint32_t value);
		Glyph(int value);
		Glyph(char c);
		Glyph(char* str);
		Glyph(Glyph& c);
		Glyph(const Glyph& c);
		Glyph();

		const char* content() const;

		uint32_t size() const;
		uint32_t value() const;

		friend std::ostream& operator<<(std::ostream& os, const jgl::Glyph value)
		{
			os << value.content();
			return os;
		}
	};

	bool operator == (const Glyph& tmp, const Glyph& other);
	bool operator != (const Glyph& tmp, const Glyph& other);
	bool operator > (const Glyph& tmp, const Glyph& other);
	bool operator < (const Glyph& tmp, const Glyph& other);
	bool operator >= (const Glyph& tmp, const Glyph& other);
	bool operator <= (const Glyph& tmp, const Glyph& other);
}

#endif