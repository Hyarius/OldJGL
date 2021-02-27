#ifndef JGL_REFERENCE_COUNT_H
#define JGL_REFERENCE_COUNT_H

namespace jgl
{
	class Reference_count
	{
	private:
		uint32_t _value;
	public:
		Reference_count() : _value(0) {}
		void increment() { _value++; }
		void decrement() { _value--; }
		const uint32_t value() const { return (_value); }
		void set_value(uint32_t p_value) { _value = p_value; }

		friend std::ostream& operator<<(std::ostream& os, const jgl::Reference_count& value)
		{
			os << value.value();
			return (os);
		}
	};
}

#endif