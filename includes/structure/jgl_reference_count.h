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
		const size_t value() const { return (_value); }
		void set_value(size_t p_value) { _value = p_value; }
	};
}

std::ostream& operator<<(std::ostream& os, const jgl::Reference_count& value);

#endif