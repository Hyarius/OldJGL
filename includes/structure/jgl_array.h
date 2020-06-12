#ifndef JGL_ARRAY_H
#define JGL_ARRAY_H

namespace jgl
{
	template <typename T>
	class Array
	{
	private:
		bool _computed;
		T* _computed_content;

		T** _content;
		size_t _size;
		size_t _max_size;
		size_t _push_size;

		void add_new_line()
		{
			T** old_content = _content;

			size_t nb_line = _max_size / _push_size;
			_max_size += _push_size;
			_content = new T*[nb_line + 1];

			for (size_t i = 0; i < nb_line; i++)
				_content[i] = old_content[i];

			delete old_content;
		}

	public:
		Array(size_t p_push_size = 100)
		{
			_push_size = p_push_size;
			_size = 0;
			_max_size = 0;
			_computed = false;
			add_new_line();
		}

		void push_back(T elem)
		{
			if (_size + 1 == _max_size)
				add_new_line();
			size_t nb_line = _size / _push_size;
			size_t nb_index = _size % _push_size;
			_content[nb_line][nb_index] = elem;
			_size++;
			_computed = false;
		}
		void push_front(T elem)
		{
			insert(0, elem);
		}
		T& operator [](size_t index)
		{
			if (index >= _size)
			{
				std::cout << "Segfault in jgl::Array - Invalid acces" << std::endl;
				exit(1);
			}
			size_t nb_line = index / _push_size;
			size_t nb_index = index % _push_size;
			return (_content[nb_line][nb_index]);
		}

		void insert(size_t index, T elem)
		{
			if (index >= _size + 1)
			{
				std::cout << "Segfault in jgl::Array - Invalid acces" << std::endl;
				exit(1);
			}

			size_t i = size();
			push_back('\0');
			while (i >= 1 && i > index)
			{
				T tmp = this->operator[](i - 1);
				this->operator[](i) = tmp;
				i--;
			}
			this->operator[](index) = elem;
			_computed = false;
		}

		jgl::Array<T> operator + (const T delta)
		{
			jgl::Array<T> result = jgl::Array<T>(push_size());

			for (size_t i = 0; i < this->size(); i++)
				result.push_back(this->operator[](i));

			result.push_back(delta);

			return (result);
		}

		jgl::Array<T> operator + (const jgl::Array<T> other)
		{
			jgl::Array<T> result = jgl::Array<T>(other.push_size());

			for (size_t i = 0; i < this->size(); i++)
				result.push_back(this->operator[](i));

			for (size_t i = 0; i < this->size(); i++)
				result.push_back(other[i]);

			return (result);
		}
		void operator += (const T delta)
		{
			push_back(delta);
			_computed = false;
		}

		void operator += (const jgl::Array<T> other)
		{
			for (size_t i = 0; i < this->size(); i++)
				push_back(other[i]);
			_computed = false;
		}

		jgl::Array<T> operator = (const jgl::Array<T> other)
		{
			jgl::Array<T> result = jgl::Array<T>(other.push_size());

			for (size_t i = 0; i < this->size(); i++)
				result.push_back(other[i]);

			return (result);
		}
			

		void clear()
		{
			_size = 0;
			_computed = false;
		}

		bool empty()
		{
			return (_size == 0 ? true : false);
		}

		bool contain(T to_find)
		{
			for (size_t i = 0; i < size(); i++)
				if (this->operator[](i) == to_find)
					return(true);
			return (false);
		}
		void pop_back()
		{
			if (_size > 0)
				_size--;
			_computed = false;
		}
		void erase(size_t index)
		{
			if (_size == 0)
				return;
			for (size_t i = index; i < _size - 1; i++)
				this->operator[](i) = this->operator[](i + 1);
			_size--;
			_computed = false;
		}

		size_t size() { return (_size); }
		size_t max_size() { return (_max_size); }
		size_t push_size() { return (_push_size); }

		T* content()
		{
			if (_computed == false)
			{
				_computed_content = new T[_size];

				for (size_t i = 0; i < _size; i++)
					_computed_content[i] = this->operator[](i);
				_computed = true;
			}

			return (_computed_content);
		}
	};
}

#endif