#ifndef JGL_DATA_H
#define JGL_DATA_H

#include "jgl_includes.h"

namespace jgl
{
	class Data
	{
	private:
		jgl::Array<void*> _content;

	public:		
		Data();
		Data(void* p_data);
		Data(int nb_param, ...);

		jgl::Array<void*>& content() { return (_content); }
		void* content(size_t index) { return (_content[index]); }
		size_t size() { return (_content.size()); }

		void operator = (void* p_data);
		void operator + (void* p_ptr);
		Data operator + (Data& delta);
		void operator += (void* p_ptr);
		void operator += (Data& delta);

		template <typename T>
		T acces(const size_t index) { return (static_cast<T>(_content[index])); }
	};
}
#endif
