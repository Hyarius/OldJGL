#include "jgl.h"

namespace jgl
{
	void			draw_image(jgl::Vector2 p_tl, jgl::Vector2 p_tr, jgl::Vector2 p_dl, jgl::Vector2 p_dr,
		float p_alpha,
		jgl::Uv p_uv_tl, jgl::Uv p_uv_tr, jgl::Uv p_uv_dl, jgl::Uv p_uv_dr)
	{
		jgl::Pixel points[] = {
			convert_screen_to_opengl(p_tl),
			convert_screen_to_opengl(p_tr),
			convert_screen_to_opengl(p_dl),
			convert_screen_to_opengl(p_dr),
			convert_screen_to_opengl(p_dl),
			convert_screen_to_opengl(p_tr)
		};
		jgl::Uv uvs[] = {
			p_uv_tl,
			p_uv_tr,
			p_uv_dl,
			p_uv_dr,
			p_uv_dl,
			p_uv_tr
		};

		draw_triangle_texture(points, uvs, p_alpha, 2);
	}

	void			draw_image(jgl::Vector2 coord, jgl::Vector2 size,
		float p_alpha,
		jgl::Uv p_uv_tl, jgl::Uv p_uv_tr, jgl::Uv p_uv_dl, jgl::Uv p_uv_dr)
	{
		jgl::draw_image(coord, jgl::Vector2(coord.x + size.x, coord.y),
			jgl::Vector2(coord.x, coord.y + size.y), jgl::Vector2(coord.x + size.x, coord.y + size.y), p_alpha,
			p_uv_tl, p_uv_tr, p_uv_dl, p_uv_dr);
	}
}