#include "jgl.h"

void SAT_test(Vector2 normale, vector<Vector2> vector_list, float *min, float *max)
{
	int		i;
	float	dot_result;

	*min = INT_MAX;
	*max = INT_MIN;
	i = 0;

	while (i < vector_list.size())
	{
		dot_result = normale.dot(vector_list[i]);

		if (dot_result < *min)
			*min = dot_result;
		if (dot_result > *max)
			*max = dot_result;

		i++;
	}
}

// template<typename Type>
// void collision_detection(vector<Type> poly_source, vector<Type> poly_target)
// {
// 	int		i;
// 	float	value[4];
//
// 	i = 0;
// 	while (i < poly_source.size())
// 	{
// 		sat_test(t_face_list_get(mesh_compared->faces, i)->normale, mesh_compared->next_vertices_in_world, &(value[0]), &(value[1]));
// 		sat_test(t_face_list_get(mesh_compared->faces, i)->normale, mesh_target->vertices_in_world, &(value[2]), &(value[3]));
// 		if (!is_middle(value[0], value[1], value[2]) && !is_middle(value[2], value[3], value[0]))
// 			return (BOOL_FALSE);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < mesh_target->faces->size)
// 	{
// 		sat_test(t_face_list_get(mesh_target->faces, i)->normale, mesh_compared->next_vertices_in_world, &(value[0]), &(value[1]));
// 		sat_test(t_face_list_get(mesh_target->faces, i)->normale, mesh_target->vertices_in_world, &(value[2]), &(value[3]));
// 		if (!is_middle(value[0], value[1], value[2]) && !is_middle(value[2], value[3], value[0]))
// 			return (BOOL_FALSE);
// 		i++;
// 	}
// 	return (BOOL_TRUE);
// }
