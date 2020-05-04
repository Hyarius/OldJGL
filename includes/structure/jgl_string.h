#ifndef JGL_String_H
#define JGL_String_H

#include "jgl_includes.h"
#include "jgl_define.h"
#include "jgl_glyph.h"

namespace jgl
{
	extern Glyph nullchar;

	class String
	{
	protected:
		Glyph** _content;
		size_t _size;
		size_t _nb_line;
		size_t _max_size;
		size_t _push_size;

	private:
		void add_line();
		Glyph* create_line();
		int calc_line(size_t index);
		int calc_index(size_t index);
		int calc_line(size_t index) const ;
		int calc_index(size_t index) const ;
		void initialize();

	public:
		String(const Glyph value);
		String(const char* str);
		String(const std::string str);
		String(const String& old);
		String();
		~String();

		size_t size() { return (_size); }
		size_t push_size() { return (_push_size); }
		size_t nb_line() { return (_nb_line); }
		size_t max_size() { return (_max_size); }

		size_t size() const { return (_size); }
		size_t push_size() const { return (_push_size); }
		size_t nb_line() const { return (_nb_line); }
		size_t max_size() const { return (_max_size); }

		Glyph** content() { return (_content); }

		void push_back(const Glyph element);
		void push_front(const Glyph element);
		void append(const Glyph element) { push_back(element); }
		void append(const String element) { for (size_t i = 0; i < element.size(); i++)push_back(element[i]); }
		Glyph& operator[](const size_t i);
		const Glyph& operator[](size_t i) const;
		void clear();

		String operator + (const String delta);
		String operator += (const String delta);
		String operator = (const String delta);

		void print_info();

		bool empty() { return (_size == 0 ? true : false); }
		bool find(Glyph to_find);
		bool contain(String to_find);
		void pop_back() { if (_size > 0)_size--; }
		void erase(size_t index);

		jgl::String substr(size_t start, size_t end);

		void insert(size_t index, Glyph insert_value);
		void insert(size_t index, String insert_value);

		std::string std();

		bool operator == (String other);
		bool operator != (String other);
	};
	String operator + (const char* str, String delta);
}

std::ostream& operator<<(std::ostream& os, jgl::String value);

#endif