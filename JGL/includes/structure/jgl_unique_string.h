#ifndef JGL_UNIQUE_STRING_H
#define JGL_UNIQUE_STRING_H

#include "jgl_includes.h"
#include "jgl_define.h"
#include "jgl_glyph.h"

namespace jgl
{
	extern Glyph nullchar;

	jgl::Array<class Unique_string> unique_strsplit(class Unique_string input, class Unique_string c, bool regroup);

	class Unique_string
	{
	protected:
		char* _str = nullptr;
		void clear_str()
		{
			if (_str != nullptr)
			{
				delete _str;
			}
			_str = nullptr;
		}
		jgl::Array<Glyph> _content;

	public:
		Unique_string();
		Unique_string(const Glyph value);
		Unique_string(const char* str);
		Unique_string(const std::string str);
		Unique_string(const Unique_string& old);
		~Unique_string()
		{
			clear_str();
		}

		const size_t size() const { return (_content.size()); }
		const size_t push_size() const { return (_content.push_size()); }
		const size_t max_size() const { return (_content.max_size()); }

		const jgl::Array<Glyph>& content() const { return (_content); }

		void push_back(const Glyph element) { _content.push_back(element); clear_str(); }
		void push_front(const Glyph element) { _content.insert(0, element); clear_str();}
		Glyph& operator[](const size_t i);
		const Glyph& operator[](size_t i) const;
		void clear() { _content.clear(); clear_str();}

		void resize(size_t new_size) { _content.resize(new_size); clear_str();}

		Unique_string operator + (const Unique_string delta);
		Unique_string operator += (const Unique_string delta);
		void operator = (const Unique_string delta);

		void print_info() const;

		const bool empty() const { return (_content.empty()); }
		const bool find(Glyph to_find) const;
		const bool contain(Unique_string to_find) const;
		void pop_back() { _content.pop_back(); }
		void erase(size_t index) { _content.erase(index); }

		jgl::Array<jgl::Unique_string> split(jgl::Unique_string delim, bool regroup = true) const { return (unique_strsplit(*this, delim, regroup)); }
		jgl::Unique_string substr(const size_t start, const size_t end) const;
		void substr(jgl::Unique_string& result, const size_t start, const size_t end) const;

		void insert(const size_t index, Glyph insert_value) { _content.insert(index, insert_value); }
		void insert(const size_t index, Unique_string insert_value) {
			for (size_t i = 0; i < insert_value.size(); i++)
				_content.insert(index, insert_value[i]);
		}
		const char* str();
		const char* str() const;
		const std::string std() const;

		bool operator == (const Unique_string other) const;
		bool operator != (const Unique_string other) const;

		friend std::ostream& operator<<(std::ostream& os, const jgl::Unique_string value)
		{
			for (size_t i = 0; i < value.size(); i++)
			{
				os << value[i];
			}
			return os;
		}
	};
	Unique_string operator + (const char* str, Unique_string delta);
}

#endif