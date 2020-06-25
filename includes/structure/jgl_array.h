#ifndef JGL_ARRAY_H
#define JGL_ARRAY_H

namespace jgl
{
	static void error_exit_tmp(int error, const char* msg)
	{
		std::cout << "Error [" << error << "] : " << msg << std::endl;
		exit(1);
	}
	template <typename T>
	class Array
	{
		
	private:
		bool _computed;
		T* _computed_result;

		T** _array_content;
		size_t _size;
		size_t _max_size;
		size_t _push_size;

		void add_new_line()
		{
			T** old_array_content = _array_content;

			size_t nb_line = _max_size / _push_size;
			_max_size += _push_size;
			_array_content = new T*[nb_line + 1];

			for (size_t i = 0; i < nb_line; i++)
					_array_content[i] = old_array_content[i];

			delete [] old_array_content;
			
			_array_content[nb_line] = new T[_push_size];

		}

		void clear_computed()
		{
			if (_computed == true)
				delete _computed_result;
			_computed = false;
			_computed_result = nullptr;
		}
		void delete_array_content()
		{
			if (_max_size == 0)
				return ;

			if (_array_content != nullptr)
			{
				for (size_t i = 0; i < _max_size / _push_size; i++)
					delete _array_content[i];
				delete [] _array_content;
				_array_content = nullptr;
			}
		}
	public:
		class Iterator
		{
		private:
			Array<T>* _parent;
			size_t _index;
			T* _element;

			void calc_element()
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (_index >= _parent->size())
					_element = nullptr;
				else
					_element = &(_parent->operator[](_index));
			}
			void set_index(size_t p_delta) {
				_index = p_delta;
			}
			void set_element(T* p_delta) {
				_element = p_delta;
			}
		public:
			Iterator()
			{
				_parent = nullptr;
				_index = 0;
				_element = nullptr;
			}
			Iterator(Array<T>* p_parent, size_t p_index)
			{
				_parent = p_parent;
				_index = p_index;
				calc_element();
			}
			Array<T>* parent() const { return (_parent); }
			size_t index() const { return (_index); }
			T* element() const { return (_element); }


			Iterator operator + (const Iterator other)
			{
				Iterator result = *this;
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (other.parent() != _parent)
					error_exit_tmp(1, "Bad interaction between two jgl::Array::Iterator from different array");

				if (result.index() + other.index() >= result.parent()->size())
					result.set_index(result.parent()->size());
				else
					result.set_index(result.index() + other.index());
				result.calc_element();
				return (result);
			}
			Iterator operator - (const Iterator other)
			{
				Iterator result = *this;
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (other.parent() != _parent)
					error_exit_tmp(1, "Bad interaction between two jgl::Array::Iterator from different array");
				if (result.index() <= other.index())
					result.set_index(0);
				else
					result.set_index(result.index() - other.index());
				result.calc_element();
				return (result);
			}
			Iterator operator + (int delta)
			{
				Iterator result = *this;
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (result.index() + static_cast<size_t>(delta) >= result.parent()->size())
					result.set_index(result.parent()->size());
				else
					result.set_index(result.index() + delta);
				result.calc_element();
				return (result);
			}
			Iterator operator - (int delta)
			{
				Iterator result = *this;

				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (result.index() <= static_cast<size_t>(delta))
					result.set_index(0);
				else
					result.set_index(result.index() - delta);
				result.calc_element();
				return (result);
			}
			void operator ++ ()
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (_index + 1 >= _parent->size())
					_index = _parent->size();
				else
					_index++;
				calc_element();
			}
			void operator -- ()
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (_index == 0)
					return;
				_index--;
				calc_element();
			}

			Iterator& operator = (size_t p_value)
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				_index = p_value;
				calc_element();
				return (*this);
			}
			Iterator& operator = (T p_value)
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				_parent->operator[](_index) = p_value;
				return (*this);
			}
			T& operator*()
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (_element == nullptr)
					error_exit_tmp(1, "Dereferencing an empty jgl::Array::Iterator");
				return (*_element);
			}


			bool operator == (const Iterator other) const
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (_parent != other.parent())
					return (false);
				return (_index == other.index());
			}
			bool operator != (const Iterator other) const
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (_parent != other.parent())
					return (false);
				return (_index != other.index());
			}
			bool operator < (const Iterator other) const
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (_parent != other.parent())
					return (false);
				return (_index < other.index());
			}
			bool operator > (const Iterator other) const
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (_parent != other.parent())
					return (false);
				return (_index > other.index());
			}
			bool operator <= (const Iterator other) const
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (_parent != other.parent())
					return (false);
				return (_index <= other.index());
			}
			bool operator >= (const Iterator other) const
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				if (_parent != other.parent())
					return (false);
				return (_index >= other.index());
			}
			std::string str()
			{
				std::string result;
				std::ostringstream oss;
				oss << (void*)parent();
				std::ostringstream oss2;
				oss2 << (void*)element();

				result = std::string("Iterator [") + std::to_string(index()) + std::string("] in array [") + oss.str() + std::string("] = ") + oss2.str();
				return (result);
			}
		};

		Array(std::initializer_list<T> init) : Array(100)
		{
			for (size_t i = 0; i < init.size(); i++)
				push_back(init.begin()[i]);
		}
		Array(size_t p_push_size = 100)
		{
			_array_content = nullptr;
			_push_size = p_push_size;
			_size = 0;
			_max_size = 0;
			_computed = false;
			_computed_result = nullptr;
		}
		Array(const Array<T>& other) : Array(other.push_size())
		{
			resize(other.size());

			for (size_t i = 0; i < other.size(); i++)
				this->operator[](i) = other[i];
		}
		~Array()
		{
			clear_computed();
			delete_array_content();
		}
		void print()
		{
			std::cout << (char*)("Size : ") << _size << (char*)("/") << _max_size << (char*)("(") << _push_size << (char*)(")") << std::endl;
			std::cout << (char*)("Array content : ") << std::endl;
			for (size_t i = 0; i < _size; i++)
			{
				if (i != 0)
					std::cout << (char*)(" - ");
				std::cout << this->operator[](i);
			}
			std::cout << std::endl;
		}
		void print_content()
		{
			std::cout << (char*)("Array content : ");
			for (size_t i = 0; i < _size; i++)
			{
				if (i != 0)
					std::cout << (char*)(" - ");
				std::cout << this->operator[](i);
			}
			std::cout << std::endl;
		}
		void push_back(const T& elem)
		{
			if (_size + 1 >= _max_size)
			{
				add_new_line();
			}
			size_t nb_line = _size / _push_size;
			size_t nb_index = _size % _push_size;
			_array_content[nb_line][nb_index] = elem;
			_size++;
			clear_computed();
		}
		void push_front(const T& elem)
		{
			insert(0, elem);
		}
		Iterator front() { return (Iterator(this, 0)); }
		Iterator back() { if (size() == 0)return (end()); return (Iterator(this, _size - 1)); }
		void operator = (const jgl::Array<T> other)
		{
			clear_computed();
			delete_array_content();
			
			Array(other.push_size());
			resize(other.size());
			for (size_t i = 0; i < other.size(); i++)
				this->operator[](i) = other[i];

		}
		T& operator [](size_t index) const
		{
			if (index >= _max_size)
			{
				std::cout << "Segfault in jgl::Array - Invalid acces" << std::endl;
				exit(1);
			}
			size_t nb_line = index / _push_size;
			size_t nb_index = index % _push_size;
			return (_array_content[nb_line][nb_index]);
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
			clear_computed();
		}
		void insert(Iterator iter, T elem)
		{
			if (iter.index() >= _size + 1)
			{
				std::cout << "Segfault in jgl::Array - Invalid acces" << std::endl;
				exit(1);
			}

			size_t i = size();
			push_back('\0');
			while (i >= 1 && i > iter.index())
			{
				T tmp = this->operator[](i - 1);
				this->operator[](i) = tmp;
				i--;
			}
			this->operator[](iter.index()) = elem;
			clear_computed();
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

			for (size_t i = 0; i < other.size(); i++)
				result.push_back(other[i]);

			return (result);
		}
		void operator += (const T delta)
		{
			push_back(delta);
			clear_computed();
		}
		void operator += (const jgl::Array<T> other)
		{
			for (size_t i = 0; i < this->size(); i++)
				push_back(other[i]);
			clear_computed();
		}
		void resize(size_t new_size)
		{
			while (_max_size <= new_size)
				add_new_line();
			for (size_t i = _size; i < new_size; i++)
			{
				this->operator[](i) = T{};
			}
			_size = new_size;
		}
		void clear()
		{
			_size = 0;
			clear_computed();
		}
		bool empty() const
		{
			return (_size == 0 ? true : false);
		}
		bool contain(T to_find) const
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
			clear_computed();
		}
		void pop_front()
		{
			erase(0);
		}
		void erase(size_t index)
		{
			if (_size == 0)
				return;
			for (size_t i = index; i < _size - 1; i++)
				this->operator[](i) = this->operator[](i + 1);
			this->operator[](_size - 1) = nullptr;
			_size--;
			clear_computed();

		}
		void erase(Iterator iter)
		{
			if (_size == 0)
				return;
			for (size_t i = iter.index(); i < _size - 1; i++)
				this->operator[](i) = this->operator[](i + 1);
			this->operator[](_size - 1) = nullptr;
			_size--;
			clear_computed();
			iter = size();
		}
		bool computed() const { return (_computed); }
		T* computed_content() const { return (_computed_result); }
		T** content() const { return (_array_content); }
		size_t size() const { return (_size); }
		size_t max_size() const { return (_max_size); }
		size_t push_size() const { return (_push_size); }
		T* all() 
		{
			if (_computed == false)
			{
				if (_computed_result != nullptr)
					delete _computed_result;
				_computed_result = new T[_size];

				for (size_t i = 0; i < _size; i++)
					_computed_result[i] = this->operator[](i);
				_computed = true;
			}

			return (_computed_result);
		}
		Iterator find(T to_find) {
			for (size_t i = 0; i < size(); i++)
			{
				if (this->operator[](i) == to_find)
					return (Iterator(this, i));
			}
			return (end());
		}
		Iterator begin()
		{
			return (Iterator(this, 0));
		}
		Iterator end()
		{
			return (Iterator(this, size()));
		}
	};
}

#endif