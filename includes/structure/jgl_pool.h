#ifndef JGL_POOL_H
#define JGL_POOL_H

#include "jgl_array.h"

namespace jgl {
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
		size_t size() const { return (_content.size()); }
		T* obtain()
		{
			if (_content.size() == 0)
			{
				T* new_elem = new T();
				return (new_elem);
			}
			else
			{
				typename jgl::Array<T*>::Iterator tmp = _content.back();
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
	class Reusable
	{
	protected:
		static inline jgl::Pool<T> _elem_pool = jgl::Pool<T>();

		T* _element = nullptr;
		jgl::Reference_count* _reference = nullptr;

	public:
		static const jgl::Pool<T>& elem_pool() { return (_elem_pool); } const
		Reusable()
		{
			obtain();
		}
		Reusable(T* value)
		{
			obtain();
			_element = value;
			_reference = new Reference_count();
			_reference->increment();
		}
		Reusable(T value)
		{
			obtain();
			*_element = value;
		}
		Reusable(const Reusable& value)
		{
			release();

			_element = value._element;
			_reference = value._reference;
			_reference->increment();
		}
		~Reusable()
		{
			release();
		}
		void obtain()
		{
			release();
			_element = _elem_pool.obtain();
			_reference = new Reference_count();
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
		jgl::Reusable<T>& operator = (const jgl::Reusable<T>& other)
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
		/*jgl::Reusable<T>& operator = (const T other)
		{
			obtain();
			*_element = other;
			_reference = new jgl::Reference_count();
			_reference->increment();

			return (*this);
		}*/
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