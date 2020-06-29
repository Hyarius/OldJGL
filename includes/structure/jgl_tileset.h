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
		std::vector<Vector2> _sprites;

	public:
		Sprite_sheet() {
			_image = nullptr;
			_size = 0;
			_unit = 1;
			_sprites.clear();
		}
		Sprite_sheet(jgl::Image *p_image, Vector2 p_size = 0);
		Sprite_sheet(jgl::String path, Vector2 p_size = 0);
		~Sprite_sheet()
		{
			if (_image != nullptr)
				delete _image;
		}

		Image* image() { return (_image); }
		Vector2 size() { return (_size); }
		Vector2 unit() { return (_unit); }
		std::vector<Vector2>& sprites() { return (_sprites); }
		Vector2 sprite(size_t index)
		{
			if (index >= _sprites.size())
				return (-1);
			return (_sprites[index]);
		}
		Vector2 sprite(Vector2 coord)
		{
			if (coord.x < 0 || coord.x >= _size.x ||
				coord.y < 0 || coord.y >= _size.y)
				return (-1);
			return (sprite(static_cast<size_t>(coord.x + (_size.x * coord.y))));
		}

		void draw(int id, Vector2 pos, Vector2 size, float p_alpha = 1.0f, Viewport* viewport = nullptr);
		void draw_centred(int id, Vector2 pos, Vector2 size, float p_alpha = 1.0f, Viewport* viewport = nullptr);

		void draw(Vector2 sprite, Vector2 pos, Vector2 size, float p_alpha = 1.0f, Viewport* viewport = nullptr);
		void draw_centred(Vector2 sprite, Vector2 pos, Vector2 size, float p_alpha = 1.0f, Viewport* viewport = nullptr);
	};
}
#endif
