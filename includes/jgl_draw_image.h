#ifndef JGL_DRAW_IMAGE_H
#define JGL_DRAW_IMAGE_H

namespace jgl
{
	void			draw_image(const Vector2 p_tl, const Vector2 p_tr, const Vector2 p_dl, const Vector2 p_dr,
		const float p_alpha = 1.0f,
		const Uv p_uv_tl = Uv(0, 0), const Uv p_uv_tr = Uv(1, 0), const Uv p_uv_dl = Uv(0, 1), const Uv p_uv_dr = Uv(1, 1),
		const jgl::Viewport* viewport = nullptr
	);

	void			draw_image(const Vector2 coord, const Vector2 size,
		const float p_alpha = 1.0f,
		const Uv p_uv_tl = Uv(0, 0), const Uv p_uv_tr = Uv(1, 0), const Uv p_uv_dl = Uv(0, 1), const Uv p_uv_dr = Uv(1, 1),
		const jgl::Viewport* viewport = nullptr
	);

	void			draw_image(const jgl::Vector2 coord, const jgl::Vector2 size,
		const float p_alpha, const jgl::Viewport* viewport);
}
#endif
