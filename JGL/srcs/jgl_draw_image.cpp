#include "jgl.h"

namespace jgl
{
	void			draw_image(jgl::Vector2 p_tl, jgl::Vector2 p_tr, jgl::Vector2 p_dl, jgl::Vector2 p_dr,
		float p_alpha,
		jgl::Vector2 p_uv_tl, jgl::Vector2 p_uv_tr, jgl::Vector2 p_uv_dl, jgl::Vector2 p_uv_dr,
		const float layer,
		const jgl::Viewport* viewport)
	{
		if (viewport != nullptr)
			viewport->use();

		jgl::Vector3 points[] = {
			convert_screen_to_opengl(p_tl, layer),
			convert_screen_to_opengl(p_dr, layer),
			convert_screen_to_opengl(p_tr, layer),
			convert_screen_to_opengl(p_dl, layer),
			convert_screen_to_opengl(p_dr, layer),
			convert_screen_to_opengl(p_tl, layer)
		};
		jgl::Vector2 uvs[] = {
			p_uv_tl,
			p_uv_dr,
			p_uv_tr,
			p_uv_dl,
			p_uv_dr,
			p_uv_tl
		};


		draw_triangle_texture(points, uvs, p_alpha, 6);
	}

	void			draw_image(jgl::Vector2 coord, jgl::Vector2 size,
		float p_alpha,
		jgl::Vector2 p_uv_tl, jgl::Vector2 p_uv_tr, jgl::Vector2 p_uv_dl, jgl::Vector2 p_uv_dr,
		const float layer,
		const jgl::Viewport* viewport)
	{
		jgl::draw_image(coord, jgl::Vector2(coord.x + size.x, coord.y),
			jgl::Vector2(coord.x, coord.y + size.y), jgl::Vector2(coord.x + size.x, coord.y + size.y), p_alpha,
			p_uv_tl, p_uv_tr, p_uv_dl, p_uv_dr, layer, viewport);
	}

	void			draw_image(jgl::Vector2 coord, jgl::Vector2 size,
		float p_alpha, const float layer, const jgl::Viewport* viewport)
	{
		jgl::draw_image(coord, jgl::Vector2(coord.x + size.x, coord.y),
			jgl::Vector2(coord.x, coord.y + size.y), jgl::Vector2(coord.x + size.x, coord.y + size.y), p_alpha,
			Vector2(0, 0), Vector2(1, 0), Vector2(0, 1), Vector2(1, 1), layer, viewport);
	}
}