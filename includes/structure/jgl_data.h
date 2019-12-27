#ifndef JGL_DATA_H
#define JGL_DATA_H

#include "jgl_includes.h"

using namespace std;

struct Data
{
	vector<void *> content;

	Data(void *p_data = NULL);
	Data(int nb_param, ...);

	void operator = (void *p_data);
	void operator + (void *p_ptr);
	Data operator + (const Data& delta);
	void operator += (const Data& delta);

	template <typename T>
	T acces(size_t i){return (static_cast<T>(content[i]));}
};

#endif
