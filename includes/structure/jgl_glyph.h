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
		Glyph(size_t value);
		Glyph(int value);
		Glyph(char c);
		Glyph(char* str);
		Glyph(Glyph& c);
		Glyph(const Glyph& c);
		Glyph();

		const char* content() const;

		void print_info() const;

		size_t size() const;
		size_t value() const;
	};

	bool operator == (const Glyph& tmp, const Glyph& other);
	bool operator != (const Glyph& tmp, const Glyph& other);
	bool operator > (const Glyph& tmp, const Glyph& other);
	bool operator < (const Glyph& tmp, const Glyph& other);
	bool operator >= (const Glyph& tmp, const Glyph& other);
	bool operator <= (const Glyph& tmp, const Glyph& other);
}

std::ostream& operator<<(std::ostream& os, const jgl::Glyph value);

#endif