#ifndef JGL_DRAW_IMAGE_H
#define JGL_DRAW_IMAGE_H

namespace jgl
{
	void			draw_image(const Vector2 p_tl, const Vector2 p_tr, const Vector2 p_dl, const Vector2 p_dr,
		const float p_alpha = 1.0f,
		const Vector2 p_uv_tl = Vector2(0, 0), const Vector2 p_uv_tr = Vector2(1, 0), const Vector2 p_uv_dl = Vector2(0, 1), const Vector2 p_uv_dr = Vector2(1, 1),
		const float layer = 0.0f,
		const jgl::Viewport* viewport = nullptr
	);

	void			draw_image(const Vector2 coord, const Vector2 size,
		const float p_alpha = 1.0f,
		const Vector2 p_uv_tl = Vector2(0, 0), const Vector2 p_uv_tr = Vector2(1, 0), const Vector2 p_uv_dl = Vector2(0, 1), const Vector2 p_uv_dr = Vector2(1, 1),
		const float layer = 0.0f,
		const jgl::Viewport* viewport = nullptr
	);

	void			draw_image(const jgl::Vector2 coord, const jgl::Vector2 size,
		const float p_alpha, const float layer, const jgl::Viewport* viewport);
}
#endif
