#include "jgl.h"

void			draw_image(Vector2 p_tl, Vector2 p_tr, Vector2 p_dl, Vector2 p_dr, float p_alpha, Uv p_uv_tl, Uv p_uv_tr, Uv p_uv_dl, Uv p_uv_dr)
{
	Pixel points[] = {
		convert_screen_to_opengl(p_tl),
		convert_screen_to_opengl(p_tr),
		convert_screen_to_opengl(p_dl),
		convert_screen_to_opengl(p_dl),
		convert_screen_to_opengl(p_dr),
		convert_screen_to_opengl(p_tr)
	};
	Uv uvs[] = {
		p_uv_tl,
		p_uv_tr,
		p_uv_dl,
		p_uv_dl,
		p_uv_dr,
		p_uv_tr
	};
	float alphas[] = {
		p_alpha,
		p_alpha,
		p_alpha,
		p_alpha,
		p_alpha,
		p_alpha
	};

	draw_triangle_texture(points, uvs, alphas, 2);
}

void			draw_image(Vector2 coord, Vector2 size, float p_alpha,
						Uv p_uv_tl, Uv p_uv_tr, Uv p_uv_dl, Uv p_uv_dr)
{
	draw_image(	Vector2(coord.x, coord.y),
				Vector2(coord.x + size.x, coord.y),
				Vector2(coord.x, coord.y + size.y),
				Vector2(coord.x + size.x, coord.y + size.y), p_alpha,
				p_uv_tl, p_uv_tr, p_uv_dl, p_uv_dr);
}
