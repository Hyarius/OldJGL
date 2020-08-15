#ifndef JGL_STRING_H
#define JGL_STRING_H

#include "jgl_pool.h"
#include "jgl_unique_string.h"



namespace jgl
{
	class String : public jgl::Pool_object<jgl::Unique_string>
	{
	public:
		String();
		String(const char* str);
		String(char glyph);
		String(jgl::Glyph glyph);
		String(std::string str);
		String(jgl::Unique_string str);

		jgl::Glyph& operator[](size_t index);
		jgl::Glyph operator[](size_t index) const;
		bool operator < (const jgl::String other) const;
		bool operator > (const jgl::String other) const;
		jgl::String operator + (const jgl::String other);
		jgl::String operator += (const jgl::String other);
		bool operator == (const jgl::String other) const;
		bool equal (const jgl::String& other) const;
		bool operator != (const jgl::String other) const;
		bool different (const jgl::String& other) const;

		void clear();
		void append(jgl::String other);
		void push_back(jgl::Glyph glyph);
		void push_front(jgl::Glyph glyph);
		void insert(size_t index, jgl::String other);
		void insert(size_t index, jgl::Glyph other);
		void erase(size_t index);
		void pop_back();

		const size_t char_size() const;
		const size_t size() const ;
		const bool empty() const { return ((*this)->empty()); }
		const bool find(Glyph to_find) const;
		const bool contain(Unique_string to_find) const;
		void print_info() const;

		const char* str();

		const std::string std() const;
		jgl::Array<jgl::String> split(jgl::String delim, bool regroup = true) const;
		jgl::String copy() const;
		jgl::String substr(size_t start, size_t end) const;
		void substr(jgl::String& result, size_t start, size_t end) const;
	};

	jgl::String operator + (const char* str, jgl::String other);
}

std::ostream& operator<<(std::ostream& os, const jgl::String value);

#endif