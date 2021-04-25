#ifndef JGL_SPRITE_SHEET_H
#define JGL_SPRITE_SHEET_H

#include "jgl_includes.h"
#include "jgl_image.h"

namespace jgl
{
	class Sprite_sheet
	{
	protected:
		Image* _image = nullptr;
		Vector2 _size = 0;
		Vector2 _unit = 1;
		jgl::Array<Vector2> _sprites;

	public:
		Sprite_sheet() {
			_image = nullptr;
			_size = 0;
			_unit = 1;
			_sprites.clear();
		}
		Sprite_sheet(const jgl::Image *p_image, const Vector2 p_size = 0);
		Sprite_sheet(const jgl::String path, const Vector2 p_size = 0);
		~Sprite_sheet()
		{
			if (_image != nullptr)
				delete _image;
		}

		const Image* image() const { return (_image); }
		const Vector2 size() const { return (_size); }
		const Vector2 unit() const { return (_unit); }
		const jgl::Array<Vector2>& sprites() const { return (_sprites); }
		const Vector2 sprite(const int index) const
		{
			if (index == -1 || static_cast<uint32_t>(index) >= _sprites.size())
				return (-1);
			return (_sprites[index]);
		}
		const Vector2 sprite(const Vector2 coord) const
		{
			if (coord.x < 0 || coord.x >= _size.x ||
				coord.y < 0 || coord.y >= _size.y)
				return (-1);
			return (sprite(static_cast<uint32_t>(coord.x + (_size.x * coord.y))));
		}

		void draw(const int id, const Vector2 pos, const Vector2 size, const float p_alpha = 1.0f, const float layer = 0.0f, const Viewport* viewport = nullptr) const;
		void draw_centred(const int id, const Vector2 pos, const Vector2 size, const float p_alpha = 1.0f, const float layer = 0.0f, const Viewport* viewport = nullptr) const;

		void draw(const Vector2 sprite, const Vector2 pos, const Vector2 size, const float p_alpha = 1.0f, const float layer = 0.0f, const Viewport* viewport = nullptr) const;
		void draw_centred(const Vector2 sprite, const Vector2 pos, const Vector2 size, const float p_alpha = 1.0f, const float layer = 0.0f, const Viewport* viewport = nullptr) const;
	};
}
#endif
