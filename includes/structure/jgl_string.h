#ifndef JGL_STRING_H
#define JGL_STRING_H

#include "jgl_pool.h"
#include "jgl_unique_string.h"

namespace jgl
{
	class String
	{
	private:
		jgl::Reusable<jgl::Unique_string> _content;
	public:
		jgl::Pool< jgl::Unique_string> pool() { return (_content.elem_pool()); }
		String()
		{
			_content.obtain();
			_content->clear();
		}
		String(const char* base) : String()
		{
			for (size_t i = 0; base[i] != '\0'; i++)
				_content->push_back(base[i]);
		}
		String(const jgl::Glyph base) : String()
		{
			_content->push_back(base);
		}
		String(const std::string base) : String()
		{
			for (size_t i = 0; i < base.size(); i++)
				_content->push_back(base[i]);
		}
		String(jgl::Unique_string base) : String()
		{
			for (size_t i = 0; i < base.size(); i++)
				_content->push_back(base[i]);
		}
		String(jgl::Unique_string* base) : String()
		{
			_content = base;
		}
		String(const jgl::String& base)
		{
			_content = base._content;
		}
		void print_info();
		const jgl::Reusable<jgl::Unique_string>& content() { return (_content); }
		const jgl::Reusable<jgl::Unique_string>& content() const { return (_content); }
		void obtain() {_content.obtain();}
		void release() {_content.release();}
		void operator = (const jgl::String other);
		jgl::Unique_string& operator* () { return ((_content.operator*())); }
		jgl::Unique_string* operator-> () { return ((_content.operator->())); }
		const jgl::Unique_string& operator* () const  { return ((_content.operator*())); }
		const jgl::Unique_string* operator-> () const { return ((_content.operator->())); }
		jgl::Glyph& operator [] (size_t index) { return (_content->operator[](index)); }
		const jgl::Glyph& operator [] (size_t index) const { return (_content->operator[](index)); }
		jgl::String operator + (const jgl::String other) { _content->operator+(*other); return (*this); }
		jgl::String operator += (const jgl::String other) { _content->operator+=((*other)); return (*this);}
		bool operator==(const jgl::String other) { return (_content->operator==((*other))); }
		bool operator!=(const jgl::String other) { return (_content->operator!=((*other))); }

		//Redirection for simplicity
		size_t size() const { return (_content->size()); }
		size_t push_size() const { return (_content->push_size()); }
		size_t max_size() const { return (_content->max_size()); }
		void push_back(const jgl::Glyph element) { _content->push_back(element); }
		void push_front(const jgl::Glyph element) { _content->insert(0, element); }
		void append(const jgl::Glyph element) { push_back(element); }
		void append(const jgl::String element) { for (size_t i = 0; i < element.size(); i++)push_back(element[i]); }
		void clear() { _content->clear(); }
		void resize(size_t new_size) { _content->resize(new_size); }
		void print_content_info() {_content->print_info(); }
		bool empty() { return (_content->empty()); }
		bool find(jgl::Glyph to_find) { return (_content->find(to_find)); }
		bool contain(jgl::String to_find) { return (_content->contain(*(to_find.content().element()))); }
		void pop_back() { _content->pop_back(); }
		void erase(size_t index) { _content->erase(index); }
		jgl::Array<jgl::String> split(jgl::String delim, bool regroup = true);
		jgl::String substr(size_t start, size_t end);
		void substr(jgl::String& result, size_t start, size_t end);
		void insert(size_t index, jgl::Glyph insert_value) { _content->insert(index, insert_value); }
		void insert(size_t index, jgl::Unique_string insert_value) {
			for (size_t i = 0; i < insert_value.size(); i++)
				_content->insert(index, insert_value[i]);
		}
		void insert(size_t index, jgl::String insert_value) {
			for (size_t i = 0; i < insert_value.size(); i++)
				_content->insert(index, insert_value[i]);
		}
		std::string std() { return (_content->std()); }
	};

	jgl::String operator + (const char* str, jgl::String delta);
}

std::ostream& operator<<(std::ostream& os, jgl::String value);

#endif