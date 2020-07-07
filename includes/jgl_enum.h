#ifndef JGL_ENUM_H
#define JGL_ENUM_H

namespace jgl
{
	enum class alignment
	{
		left = 0,
		centred = 1,
		right = 2
	};

	enum class key
	{
		a = 0,
		b = 1,
		c = 2,
		d = 3,
		e = 4,
		f = 5,
		g = 6,
		h = 7,
		i = 8,
		j = 9,
		k = 10,
		l = 11,
		m = 12,
		n = 13,
		o = 14,
		p = 15,
		q = 16,
		r = 17,
		s = 18,
		t = 19,
		u = 20,
		v = 21,
		w = 22,
		x = 23,
		y = 24,
		z = 25,
		key_1 = 26,
		key_2 = 27,
		key_3 = 28,
		key_4 = 29,
		key_5 = 30,
		key_6 = 31,
		key_7 = 32,
		key_8 = 33,
		key_9 = 34,
		key_0 = 35,
		minus = 36,
		equal = 37,
		key_pad_1 = 38,
		key_pad_2 = 39,
		key_pad_3 = 40,
		key_pad_4 = 41,
		key_pad_5 = 42,
		key_pad_6 = 43,
		key_pad_7 = 44,
		key_pad_8 = 45,
		key_pad_9 = 46,
		key_pad_0 = 47,
		F1 = 48,
		F2 = 49,
		F3 = 50,
		F4 = 51,
		F5 = 52,
		F6 = 53,
		F7 = 54,
		F8 = 55,
		F9 = 56,
		F10 = 57,
		F11 = 58,
		F12 = 59,
		up_arrow = 60,
		down_arrow = 61,
		left_arrow = 62,
		right_arrow = 63,
		escape = 64,
		left_alt = 65,
		right_alt = 66,
		left_control = 67,
		right_control = 68,
		return_key = 69,
		key_pad_return_key = 70,
		backspace = 71,
		delete_key = 72,
		space = 73,
		left_shift = 74,
		right_shift = 75,
		tab = 76,
		count
	};

	enum class text_color
	{
		black = 0,
		white = 1,
		light_blue = 2,
		blue = 3,
		dark_blue = 4,
		light_red = 5,
		red = 6,
		dark_red = 7,
		light_green = 8,
		green = 9,
		dark_green = 10,
		light_cyan = 11,
		cyan = 12,
		dark_cyan = 13,
		light_grey = 14,
		grey = 15,
		dark_grey = 16,
		light_orange = 17,
		orange = 18,
		dark_orange = 19,
		light_yellow = 20,
		yellow = 21,
		dark_yellow = 22,
		light_purple = 23,
		purple = 24,
		dark_purple = 25
	};

	enum class text_style
	{
		normal = TTF_STYLE_NORMAL,
		bold = TTF_STYLE_BOLD,
		italic = TTF_STYLE_ITALIC,
		underline = TTF_STYLE_UNDERLINE,
		strike = TTF_STYLE_STRIKETHROUGH
	};

	enum class key_state
	{
		down = 0,
		release = 1,
		up = 2,
		pressed = 3,
	};

	enum class mouse_button
	{
		right = 0,
		left = 1,
		center = 2,
		count = 3
	};

	enum class mouse_state
	{
		down = 0,
		release = 1,
		up = 2,
		pressed = 3,
	};
}

#endif
