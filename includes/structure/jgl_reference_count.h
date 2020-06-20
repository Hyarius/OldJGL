#ifndef JGL_REFERENCE_COUNT_H
#define JGL_REFERENCE_COUNT_H

namespace jgl
{
	class Reference_count
	{
	private:
		size_t _value;
	public:
		Reference_count() : _value(0) {}
		void increment() { _value++; }
		void decrement() { _value--; }
		size_t value() { return (_value); }
		void set_value(size_t p_value) { _value = p_value; }
	};
}

#endif