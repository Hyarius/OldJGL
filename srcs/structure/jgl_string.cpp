#include "jgl.h"

namespace jgl
{
	jgl::Array<jgl::String> String::split(jgl::String delim, bool regroup)
	{
		return (strsplit(*this, delim, regroup));
	}
	
	void String::operator = (const jgl::String other)
	{
		_content = other.content();
	}

	jgl::String operator + (const char* str, const jgl::String delta)
	{
		String result;

		for (size_t i = 0; str[i] != '\0'; i++)
			result->push_back(str[i]);

		for (size_t i = 0; i < delta->size(); i++)
			result->push_back(delta[i]);

		return (result);
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

		if (start >= this->size())
		{
			result.clear();
			return;
		}

		result.resize(size);
		for (size_t i = 0; i < size; i++)
			result[i] = this->operator[](i + start);
	}
	void String::print_info()
	{
		std::cout << "String : " << *this << "(ref : " << this->content().reference()->value() << ")" << std::endl;
	}
}