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

		jgl::Glyph& operator[](uint32_t index);
		jgl::Glyph operator[](uint32_t index) const;
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
		void insert(uint32_t index, jgl::String other);
		void insert(uint32_t index, jgl::Glyph other);
		void erase(uint32_t index);
		void pop_back();

		const uint32_t char_size() const;
		const uint32_t size() const ;
		const bool empty() const { return ((*this)->empty()); }
		const bool find(Glyph to_find) const;
		const bool find(const char* to_find) const;
		const bool find(Unique_string to_find) const;
		const bool compose_only(Unique_string to_find) const;

		const char* str();

		const std::string std() const;
		jgl::Array<jgl::String> split(jgl::String delim, bool regroup = true) const;
		jgl::String copy() const;
		jgl::String substr(uint32_t start, uint32_t end) const;
		void substr(jgl::String& result, uint32_t start, uint32_t end) const;

		friend std::ostream& operator<<(std::ostream& os, const jgl::String value)
		{
			os << *value;
			return os;
		}
	};

	jgl::String operator + (const char* str, jgl::String other);
}

#endif