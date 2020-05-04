#ifndef JGL_CHAR_H
#define JGL_CHAR_H

#include "jgl_includes.h"

namespace jgl
{
	class Glyph
	{
	private:
		char _content[5];

		void initialize();

	public:
		Glyph(size_t value);
		Glyph(int value);
		Glyph(char c);
		Glyph(char* str);
		Glyph(Glyph& c);
		Glyph(const Glyph& c);
		Glyph();

		const char* content();
		const char* content() const ;

		void print_info();

		size_t value();
		size_t value() const;

		Glyph operator = (const Glyph p_value);

		bool operator == (Glyph c);
		bool operator != (Glyph c);

		bool operator == (Glyph& c) const ;
		bool operator != (Glyph& c) const ;

		bool operator > (Glyph& other);
		bool operator < (Glyph& other);
	};
}
std::ostream& operator<<(std::ostream& os, jgl::Glyph& value);
std::ostream& operator<<(std::ostream& os, const jgl::Glyph& value);

#endif