#ifndef JGL_TILESET_H
#define JGL_TILESET_H

using namespace std;

class c_tileset
{
private:
	c_image _image;
	Vector2 _size;
	Vector2 _unit;
	vector<Vector2> _sprites;

public:
	c_tileset(){}
	c_tileset(string path, Vector2 p_size = Vector2(0, 0));

	Vector2 size(){return (_size);}
	Vector2 unit(){return (_unit);}
	void draw(int id, Vector2 pos, Vector2 size, c_viewport *viewport = nullptr);
	void draw_centred(int id, Vector2 pos, Vector2 size, c_viewport *viewport = nullptr);
};

#endif
