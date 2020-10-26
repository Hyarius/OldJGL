#ifndef JGL_COLOR_H
#define JGL_COLOR_H

#define CALC(value) ((value % 256) / 255.0f)

namespace jgl
{
	struct Color
	{
		float r;
		float g;
		float b;
		float a;

		Color();
		Color(float p_r, float p_g, float p_b, float p_a = 1.0f);
		Color(int p_r, int p_g, int p_b, int p_a = 255);

		float* decompose();

		Color operator + (const Color& delta);

		friend std::ostream& operator<<(std::ostream& os, const jgl::Color value)
		{
			os << "(r : " << std::to_string(value.r) << " / g : " << std::to_string(value.g) << " / b : " << std::to_string(value.b) << " / a : " << std::to_string(value.a) << ")";
			return os;
		}
	};
}

#endif
