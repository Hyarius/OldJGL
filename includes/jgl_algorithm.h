#ifndef JGL_ALGORITHM_H
#define JGL_ALGORITHM_H

void SAT_test(Vector3 normale, vector<Vector3> vector_list, Vector3 pos, float *min, float *max);
bool intersect_mesh(c_mesh *to_move, c_mesh *to_check);
bool intersect_bubble_box(c_mesh *to_move, c_mesh *to_check);

#endif
