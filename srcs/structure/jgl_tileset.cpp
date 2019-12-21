#include "jgl.h"

using namespace std;

c_tileset::c_tileset(string path, Vector2 p_size)
{
	_image = c_image(path);
	_size = p_size;
	_unit = _image.size() / _size;
	Vector2	tmp = Vector2(0, 0);

	while (1)
	{
		_sprites.push_back(tmp * _unit);

		if (tmp == _size - 1)
			break;
		if (tmp.x >= _size.x - 1)
		{
			tmp.x = 0;
			tmp.y++;
		}
		else
			tmp.x++;
	}
}

void c_tileset::draw(int id, Vector2 pos, Vector2 size, c_viewport *viewport)
{
	if (viewport == nullptr)
		viewport = g_application->viewport();

	SDL_Rect dest = {
			static_cast<int>(pos.x), static_cast<int>(pos.y),
			static_cast<int>(size.x + 1), static_cast<int>(size.y + 1)
		};
	SDL_Rect src = {
			static_cast<int>(_sprites[id].x), static_cast<int>(_sprites[id].y),
			static_cast<int>(_unit.x), static_cast<int>(_unit.y)};
	SDL_RenderCopyEx(viewport->renderer(), _image.texture(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}

void c_tileset::draw_centred(int id, Vector2 pos, Vector2 size, c_viewport *viewport)
{
	if (viewport == nullptr)
		viewport = g_application->viewport();

	draw(id, pos - size / 2, size, viewport);
}
