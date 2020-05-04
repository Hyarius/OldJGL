#ifndef JGL_ALGORITHM_H
#define JGL_ALGORITHM_H

namespace jgl
{
	bool intersect_mesh(Mesh* to_move, Mesh* to_check);
	bool intersect_bubble_box(Mesh* to_move, Mesh* to_check);
}

#endif
