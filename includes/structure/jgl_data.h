#ifndef JGL_DATA_H
#define JGL_DATA_H

#include "jgl_includes.h"

namespace jgl
{
	struct Data
	{
		jgl::Array<void*> content;

		Data();
		Data(void* p_data);
		Data(int nb_param, ...);

		void operator = (void* p_data);
		void operator + (void* p_ptr);
		Data operator + (Data& delta);
		void operator += (void* p_ptr);
		void operator += (Data& delta);

		template <typename T>
		T acces(const size_t index) { return (static_cast<T>(content[index])); }
	};
}
#endif
