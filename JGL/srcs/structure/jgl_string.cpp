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
		for (uint32_t i = 0; str[i] != '\0'; i++)
			push_back(str[i]);
	}
	String::String(std::string str) : jgl::Pool_object<Unique_string>()
	{
		clear();
		for (uint32_t i = 0; i < str.size(); i++)
			push_back(str[i]);
	}
	String::String(jgl::Unique_string str) : jgl::Pool_object<Unique_string>()
	{
		clear();
		for (uint32_t i = 0; i < str.size(); i++)
			push_back(str[i]);
	}
	jgl::Glyph& String::operator[](uint32_t index)
	{
		return ((*this)->operator[](index));
	}
	jgl::Glyph String::operator[](uint32_t index) const
	{
		return ((*this)->operator[](index));
	}
	bool String::operator < (const jgl::String other) const
	{
		for (uint32_t i = 0; i < size(); i++)
		{
			jgl::Glyph tmp2;
			jgl::Glyph tmp;
			if (other.size() > i)
				tmp = other[i];
			else
				tmp = jgl::Glyph('\0');
			tmp2 = this->operator[](i);

			if (tmp2 < tmp)
			{
				return (true);
			}
			else if (tmp2 > tmp)
			{
				return (false);
			}
		}
		if (other.size() > size())
			return (true);
		return (false);
	}
	bool String::operator > (const jgl::String other) const
	{
		for (uint32_t i = 0; i < size(); i++)
		{
			jgl::Glyph tmp;
			jgl::Glyph tmp2;
			if (other.size() > i)
				tmp = other[i];
			else
				tmp = jgl::Glyph('\0');
			tmp2 = this->operator[](i);

			if (tmp2 > tmp)
			{
				return (true);
			}
			else if (tmp2 < tmp)
			{
				return (false);
			}
		}
		if (other.size() > size())
			return (false);
		return (false);
	}
	jgl::String String::operator + (const jgl::String other)
	{
		jgl::String result;

		for (uint32_t i = 0; i < this->element()->size(); i++)
		{
			result->push_back(this->operator[](i));
		}
		for (uint32_t i = 0; i < other->size(); i++)
		{
			result->push_back(other[i]);
		}

		return (result);
	}
	jgl::String String::operator += (const jgl::String other)
	{
		for (uint32_t i = 0; i < other->size(); i++)
		{
			(*this)->push_back(other[i]);
		}

		return (*this);
	}
	bool String::operator == (const jgl::String other) const
	{
		if (size() != other.size())
			return (false);
		for (uint32_t i = 0; i < size(); i++)
			if (other[i] != this->operator[](i))
				return (false);
		return (true);
	}
	bool String::operator != (const jgl::String other) const
	{
		if (size() != other.size())
			return (true);
		for (uint32_t i = 0; i < size(); i++)
			if (other[i] != this->operator[](i))
				return (true);
		return (false);
	}
	bool String::equal (const jgl::String& other) const
	{
		if (size() != other.size())
			return (false);
		for (uint32_t i = 0; i < size(); i++)
			if (other[i].value() != this->operator[](i).value())
				return (false);
		return (true);
	}
	bool String::different (const jgl::String& other) const
	{
		if (size() != other.size())
			return (false);
		for (uint32_t i = 0; i < size(); i++)
			if (other[i].value() != this->operator[](i).value())
				return (false);
		return (true);
	}
	const char* String::str()
	{
		return ((*this)->str());
	}
	const std::string String::std() const
	{
		return ((*this)->std());
	}
	jgl::Array<jgl::String> String::split(jgl::String delim, bool regroup) const
	{
		return (strsplit(*this, delim, regroup));
	}

	jgl::String String::copy() const
	{
		jgl::String result = jgl::String();

		for (uint32_t i = 0; i < size(); i++)
			result.push_back(this->operator[](i));

		return (result);
	}

	jgl::String String::substr(uint32_t start, uint32_t end) const
	{
		jgl::String result = jgl::String();

		this->substr(result, start, end);

		return (result);
	}
	void String::substr(jgl::String& result, uint32_t start, uint32_t end) const
	{
		uint32_t size = end - start;

		if (start >= (*this)->size())
		{
			result->clear();
			return;
		}

		result->resize(size);
		for (uint32_t i = 0; i < size; i++)
			result[i] = this->operator[](i + start);
	}
	void String::print_info() const
	{
		std::cout << "String : " << *this << "(ref : " << this->reference()->value() << ")" << std::endl;
	}
	jgl::String operator + (const char* str, jgl::String other)
	{
		jgl::String result;

		for (uint32_t i = 0; str[i] != '\0'; i++)
		{
			result->push_back(str[i]);
		}
		for (uint32_t i = 0; i < other->size(); i++)
		{
			result->push_back(other[i]);
		}

		return (result);
	}
	void String::append(jgl::String other)
	{
		for (uint32_t i = 0; i < other->size(); i++)
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
	void String::insert(uint32_t index, jgl::String other)
	{
		(*this)->insert(index, *other);
	}
	void String::insert(uint32_t index, jgl::Glyph other)
	{
		(*this)->insert(index, other);
	}
	void String::erase(uint32_t index)
	{
		(*this)->erase(index);
	}
	void String::pop_back()
	{
		(*this)->pop_back();
	}

	const uint32_t String::char_size() const
	{
		uint32_t result = 0;
		for (uint32_t i = 0; i < size(); i++)
		{
			result += this->operator[](i).size();
		}
		return (result);
	}

	const uint32_t String::size() const
	{
		return ((*this)->size());
	}
	const bool String::find(Glyph to_find) const
	{
		for (uint32_t i = 0; i < size(); i++)
			if (this->operator[](i) == to_find)
				return(true);
		return (false);
	}
	const bool String::contain(Unique_string to_find) const
	{
		bool result = false;
		for (uint32_t i = 0; i < size(); i++)
		{
			result = false;
			for (uint32_t j = 0; j < to_find.size() && result == false; j++)
				if (this->operator[](i) == to_find[j])
					result = true;
			if (result == false)
				return (false);
		}
		return (true);
	}
	void String::clear()
	{
		(*this)->clear();
	}

}