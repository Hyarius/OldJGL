#ifndef JGL_ALGORITHM_H
#define JGL_ALGORITHM_H

namespace jgl
{
	bool intersect_mesh(const Mesh* to_move, const Mesh* to_check);
	bool intersect_bubble_box(const Mesh* to_move, const Mesh* to_check);
}

#endif
