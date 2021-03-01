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
		uint32_t _size;
		uint32_t _max_size;
		uint32_t _push_size;

		void add_new_line()
		{
			T** old_array_content = _array_content;

			uint32_t nb_line = _max_size / _push_size;
			_max_size += _push_size;
			_array_content = new T*[nb_line + 1];

			for (uint32_t i = 0; i < nb_line; i++)
				_array_content[i] = old_array_content[i];

			delete [] old_array_content;
			
			_array_content[nb_line] = new T[_push_size];
			for (uint32_t i = 0; i < _push_size; i++)
				_array_content[nb_line][i] = T();

		}

		void clear_computed()
		{
			if (_computed = true)
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
				for (uint32_t i = 0; i < _max_size / _push_size; i++)
				{
					delete[] _array_content[i];
				}
				delete[] _array_content;
				_array_content = nullptr;
			}
		}
	public:
		class Iterator
		{
		private:
			const Array<T>* _parent;
			uint32_t _index;
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
			void set_index(uint32_t p_delta) {
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
			Iterator(const Array<T>* p_parent, const uint32_t p_index)
			{
				_parent = p_parent;
				_index = p_index;
				calc_element();
			}
			const Array<T>* parent() const { return (_parent); }
			const uint32_t index() const { return (_index); }
			const T* element() const { return (_element); }


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
				if (result.index() + static_cast<uint32_t>(delta) >= result.parent()->size())
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
				if (result.index() <= static_cast<uint32_t>(delta))
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

			Iterator& operator = (const uint32_t p_value)
			{
				if (_parent == nullptr)
					error_exit_tmp(1, "No parent in jgl::Array : segfault");
				_index = p_value;
				calc_element();
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
			std::string str() const
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

		Array(const std::initializer_list<T> init) : Array<T>()
		{
			for (uint32_t i = 0; i < init.size(); i++)
				push_back(init.begin()[i]);
		}
		Array(const uint32_t p_push_size = 100)
		{
			_array_content = nullptr;
			_push_size = p_push_size;
			_size = 0;
			_max_size = 0;
			_computed = false;
			_computed_result = nullptr;
		}
		Array(const Array<T>& other) : Array<T>(other.push_size())
		{
			for (uint32_t i = 0; i < other.size(); i++)
				push_back(other[i]);
		}
		~Array()
		{
			clear_computed();
			delete_array_content();
		}
		T& push_back(const T elem)
		{
			if (_size + 1 >= _max_size)
			{
				add_new_line();
			}
			uint32_t nb_line = _size / _push_size;
			uint32_t nb_index = _size % _push_size;
			_array_content[nb_line][nb_index] = elem;
			_size++;
			clear_computed();
			return (_array_content[nb_line][nb_index]);
		}
		T& push_front(const T& elem)
		{
			return (insert(0, elem));
		}
		const Iterator front() const { return (Iterator(this, 0)); }
		const Iterator back() const { if (size() == 0)return (end()); return (Iterator(this, _size - 1)); }
		jgl::Array<T>& operator = (const jgl::Array<T>& other)
		{
			this->clear();

			for (uint32_t i = 0; i < other.size(); i++)
				push_back(other[i]);

			return (*this);
		}
		T& operator [](const uint32_t index) const
		{
			if (index >= _size)
			{
				DEBUG_LINE;
				std::cout << "Segfault in jgl::Array - Invalid acces to an array of type " << typeid(T).name() << " at index " << index << " with a size of " << _size << std::endl;
				//exit(1);
			}
			uint32_t nb_line = index / _push_size;
			uint32_t nb_index = index % _push_size;
			return (_array_content[nb_line][nb_index]);
		}
		T& insert(const uint32_t index, const T elem)
		{
			if (index >= _size + 1)
			{
				DEBUG_LINE;
				std::cout << "Segfault in jgl::Array - Invalid acces to an array of type " << typeid(T).name() << " at index " << index << " with a size of " << _size << std::endl;
				exit(1);
			}

			uint32_t i = size();
			push_back('\0');
			while (i >= 1 && i > index)
			{
				T tmp = this->operator[](i - 1);
				this->operator[](i) = tmp;
				i--;
			}
			this->operator[](index) = elem;
			clear_computed();
			return (this->operator[](index));
		}
		T& insert(const Iterator iter, const T elem)
		{
			if (iter.index() >= _size + 1)
			{
				DEBUG_LINE;
				std::cout << "Segfault in jgl::Array - Invalid acces to an array of type " << typeid(T).name() << " at index " << index << " with a size of " << _size << std::endl;
				//exit(1);
			}

			uint32_t i = size();
			push_back('\0');
			while (i >= 1 && i > iter.index())
			{
				T tmp = this->operator[](i - 1);
				this->operator[](i) = tmp;
				i--;
			}
			this->operator[](iter.index()) = elem;
			clear_computed();
			return (this->operator[](iter.index()));
		}
		jgl::Array<T> operator + (const T delta)
		{
			jgl::Array<T> result = jgl::Array<T>(push_size());

			for (uint32_t i = 0; i < this->size(); i++)
				result.push_back(this->operator[](i));

			result.push_back(delta);

			return (result);
		}
		jgl::Array<T> operator + (const jgl::Array<T> other)
		{
			jgl::Array<T> result = jgl::Array<T>(other.push_size());

			for (uint32_t i = 0; i < this->size(); i++)
				result.push_back(this->operator[](i));

			for (uint32_t i = 0; i < other.size(); i++)
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
			for (uint32_t i = 0; i < this->size(); i++)
				push_back(other[i]);
			clear_computed();
		}
		void resize(const uint32_t new_size)
		{
			while (_max_size < new_size)
				add_new_line();
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
		bool contain(const T to_find) const
		{
			for (uint32_t i = 0; i < size(); i++)
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
		void erase(const uint32_t index)
		{
			if (_size == 0)
				return;
			for (uint32_t i = index; i < _size - 1; i++)
				this->operator[](i) = this->operator[](i + 1);
			_size--;
			clear_computed();
		}

		void erase(const Iterator iter)
		{
			if (_size == 0)
				return;
			for (uint32_t i = iter.index(); i < _size - 1; i++)
				this->operator[](i) = this->operator[](i + 1);
			_size--;
			clear_computed();
		}

		void reverse()
		{
			for (uint32_t i = 0; i < _size / 2; i++)
			{
				T tmp = this->operator[](i);
				this->operator[](i) = this->operator[](_size - i - 1);
				this->operator[](_size - i - 1) = tmp;
			}
		}
		const bool computed() const { return (_computed); }
		const T* computed_content() const { return (_computed_result); }
		const T** content() const { return (_array_content); }
		const uint32_t size() const { return (_size); }
		const uint32_t max_size() const { return (_max_size); }
		const uint32_t push_size() const { return (_push_size); }
		const T* all()
		{
			if (_computed == false)
			{
				if (_computed_result != nullptr)
					delete _computed_result;
				_computed_result = new T[_size];

				for (uint32_t i = 0; i < _size; i++)
					_computed_result[i] = this->operator[](i);
				_computed = true;
			}

			return (_computed_result);
		}
		Iterator find(const T to_find) const {
			for (uint32_t i = 0; i < size(); i++)
			{
				if (this->operator[](i) == to_find)
					return (Iterator(this, i));
			}
			return (end());
		}
		Iterator find(const T to_find, const uint32_t start) const {
			for (uint32_t i = start; i < size(); i++)
			{
				if (this->operator[](i) == to_find)
					return (Iterator(this, i));
			}
			return (end());
		}
		Iterator begin() const
		{
			return (Iterator(this, 0));
		}
		Iterator end() const
		{
			return (Iterator(this, size()));
		}
	};
}

#endif
