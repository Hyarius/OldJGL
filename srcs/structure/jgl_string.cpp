#include "jgl.h"

namespace jgl
{
	String::String() : jgl::Pool_object<Unique_string>()
	{
		clear();
	}
	String::String(char glyph) : jgl::Pool_object<Unique_string>()
	{
		clear();
		push_back(glyph);
	}
	String::String(jgl::Glyph glyph) : jgl::Pool_object<Unique_string>()
	{
		clear();
		push_back(glyph);
	}
	String::String(const char* str) : jgl::Pool_object<Unique_string>()
	{
		clear();
		for (size_t i = 0; str[i] != '\0'; i++)
			push_back(str[i]);
	}
	String::String(std::string str) : jgl::Pool_object<Unique_string>()
	{
		clear();
		for (size_t i = 0; i < str.size(); i++)
			push_back(str[i]);
	}
	String::String(jgl::Unique_string str) : jgl::Pool_object<Unique_string>()
	{
		clear();
		for (size_t i = 0; i < str.size(); i++)
			push_back(str[i]);
	}
	jgl::Glyph& String::operator[](size_t index)
	{
		return ((*this)->operator[](index));
	}
	jgl::Glyph String::operator[](size_t index) const
	{
		return ((*this)->operator[](index));
	}
	jgl::String String::operator + (const jgl::String other)
	{
		jgl::String result;

		for (size_t i = 0; i < this->element()->size(); i++)
		{
			result->push_back(this->operator[](i));
		}
		for (size_t i = 0; i < other->size(); i++)
		{
			result->push_back(other[i]);
		}

		return (result);
	}
	jgl::String String::operator += (const jgl::String other)
	{
		for (size_t i = 0; i < other->size(); i++)
		{
			(*this)->push_back(other[i]);
		}

		return (*this);
	}
	bool String::operator == (const jgl::String other)
	{
		return ((*this)->operator==(*other));
	}
	bool String::operator != (const jgl::String other)
	{
		return ((*this)->operator!=(*other));
	}
	const char* String::str()
	{
		std::string tmp = std();
		return (tmp.c_str());
	}
	std::string String::std()
	{
		return ((*this)->std());
	}
	jgl::Array<jgl::String> String::split(jgl::String delim, bool regroup)
	{
		return (strsplit(*this, delim, regroup));
	}

	jgl::String String::substr(size_t start, size_t end)
	{
		jgl::String result = jgl::String();

		this->substr(result, start, end);

		return (result);
	}
	void String::substr(jgl::String& result, size_t start, size_t end)
	{
		size_t size = end - start;

		if (start >= (*this)->size())
		{
			result->clear();
			return;
		}

		result->resize(size);
		for (size_t i = 0; i < size; i++)
			result[i] = this->operator[](i + start);
	}
	void String::print_info()
	{
		std::cout << "String : " << *this << "(ref : " << this->reference()->value() << ")" << std::endl;
	}
	jgl::String operator + (const char* str, jgl::String other)
	{
		jgl::String result;

		for (size_t i = 0; str[i] != '\0'; i++)
		{
			result->push_back(str[i]);
		}
		for (size_t i = 0; i < other->size(); i++)
		{
			result->push_back(other[i]);
		}

		return (result);
	}
	void String::append(jgl::String other)
	{
		for (size_t i = 0; i < other->size(); i++)
		{
			(*this)->push_back(other[i]);
		}
	}
	void String::push_back(jgl::Glyph glyph)
	{
		(*this)->push_back(glyph);
	}
	void String::push_front(jgl::Glyph glyph)
	{
		(*this)->push_front(glyph);
	}
	void String::insert(size_t index, jgl::String other)
	{
		(*this)->insert(index, *other);
	}
	void String::insert(size_t index, jgl::Glyph other)
	{
		(*this)->insert(index, other);
	}
	void String::erase(size_t index)
	{
		(*this)->erase(index);
	}
	void String::pop_back()
	{
		(*this)->pop_back();
	}

	size_t String::size()
	{
		return ((*this)->size());
	}
	bool String::find(Glyph to_find)
	{
		return ((*this)->find(to_find));
	}
	bool String::contain(Unique_string to_find)
	{
		return ((*this)->contain(to_find));
	}
	void String::clear()
	{
		(*this)->clear();
	}

}