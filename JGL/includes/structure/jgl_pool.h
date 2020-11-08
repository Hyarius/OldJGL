#ifndef JGL_POOL_H
#define JGL_POOL_H

#include "jgl_array.h"

namespace jgl
{
	void error_exit(int num, const char* str);

	template <typename T>
	class Pool
	{
	private:
		jgl::Array<T*>_content;
	public:
		Pool() {}
		~Pool()
		{
			for (size_t i = 0; i < _content.size(); i++)
			{
				delete _content[i];
			}
			_content.~Array();
		}
		const jgl::Array<T*> content() const { return (_content); }
		const size_t size() const { return (_content.size()); }
		T* obtain()
		{
			if (_content.size() == 0)
			{
				T* new_element = new T();
				return (new_element);
			}
			else
			{
				//typename jgl::Array<T*>::Iterator tmp = _content.back();
				auto tmp = _content.back();
				T* result = _content[tmp.index()];
				_content.pop_back();
				return (result);
			}
		}
		void release(T* object)
		{
			_content.push_back(object);
		}
		T* operator[](size_t index)
		{
			return (_content[index]);
		}
	};


	template<typename T>
	class Pool_object
	{
	protected:
		static inline jgl::Pool<T> _elem_pool = jgl::Pool<T>();

		T* _element = nullptr;
		jgl::Reference_count* _reference = nullptr;
		void create_reference()
		{
			_reference = new Reference_count();
		}

	public:
		static const jgl::Pool<T>& elem_pool() { return (_elem_pool); } const
		Pool_object()
		{
			obtain();
		}
		Pool_object(T* value)
		{
			obtain();
			_element = value;
		}
		Pool_object(T value)
		{
			obtain();
			*_element = value;
		}
		Pool_object(const Pool_object& value)
		{
			release();

			_element = value._element;
			_reference = value._reference;
			_reference->increment();
		}
		~Pool_object()
		{
			release();
		}
		void obtain()
		{
			release();
			_element = _elem_pool.obtain();
			create_reference();
			_reference->increment();
		}
		void release()
		{
			if (_reference != nullptr)
			{
				_reference->decrement();
				if (_reference->value() == 0 && _element != nullptr)
				{
					_elem_pool.release(_element);
					delete _reference;
					_reference = nullptr;
				}
			}
			_element = nullptr;
		}
		const T* element() const { return (_element); }
		const jgl::Reference_count* reference() const { return (_reference); }
		jgl::Pool_object<T>& operator = (const jgl::Pool_object<T>& other)
		{
			if (this != &other)
			{
				release();
				_element = other._element;
				_reference = other._reference;
				_reference->increment();
			}
			return (*this);
		}
		T& operator* ()
		{
			return (*_element);
		}
		T* operator-> ()
		{
			return (_element);
		}
		const T& operator* () const
		{
			return (*_element);
		}
		const T* operator-> () const
		{
			return (_element);
		}
	};

}


#endif