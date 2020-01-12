#include "jgl.h"

using namespace std;

c_camera *camera = nullptr;
c_mesh *mesh = nullptr;
GLuint vertexbuffer = 0;
GLuint colorbuffer = 0;

c_window::c_window(c_widget *p_parent, Color p_back) : c_widget(p_parent)
{
	back = p_back;

	set_geometry(-1, -1);
}

void c_window::set_color(Color p_color)
{
	back = p_color;
}

void c_window::render()
{
	fill_rectangle(0, _viewport->area(), back, _viewport);

	if (camera == nullptr)
	{
		camera = new c_camera(Vector3(4, 3, 3));
		camera->look_at(Vector3(0, 0, 0));
	}
	// if (mesh == nullptr)
	// {
	// 	mesh = new c_mesh(Vector3(0, 0, 0));
	// 	mesh->add_point(Vector3(-1, -1, 0));
	// 	mesh->add_point(Vector3(1, -1, 0));
	// 	mesh->add_point(Vector3(0, 1, 0));
	// 	mesh->add_face(Face({0, 1, 2}, {-1, -1, -1}, Color(255, 0, 0)));
	// 	mesh->add_face(Face({2, 1, 0}, {-1, -1, -1}, Color(255, 0, 0)));
	// 	mesh->bake();
	// }
	// mesh->draw(camera, _viewport);

 	// Matrix MVP = camera->MVP();
	//
	// static const GLfloat g_vertex_buffer_data[] = {
	// 	-1.0f, -1.0f, 0.0f,
	// 	 1.0f, -1.0f, 0.0f,
	// 	 0.0f,  1.0f, 0.0f,
	// };
	//
	// static const GLfloat g_color_buffer_data[] = {
	// 	 1.0f,  0.0f, 0.0f, 1.0f,
	// 	 1.0f,  0.0f, 0.0f, 1.0f,
	// 	 1.0f,  0.0f, 0.0f, 1.0f
	// };
	//
	// Vector3 point = Vector3(g_vertex_buffer_data[0], g_vertex_buffer_data[1], g_vertex_buffer_data[2]);
	// Vector3 tmp_point = MVP * point;
	// cout << "From : " << point << " to " << tmp_point << endl;

	// if (vertexbuffer == 0)
	// {
	// 	glGenBuffers(1, &vertexbuffer);
	// 	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// 	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	// }
	//
	// if (colorbuffer == 0)
	// {
	// 	glGenBuffers(1, &colorbuffer);
	// 	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	// 	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	// }
	//
	// glUseProgram(g_application->program_color_model());
	// glUniformMatrix4fv(g_application->matrix_colorID(), 1, GL_FALSE, (float *)(&MVP));
	//
	// glEnableVertexAttribArray(0);
	// glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// glVertexAttribPointer(
	// 	0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
	// 	3,                  // size
	// 	GL_FLOAT,           // type
	// 	GL_FALSE,           // normalized?
	// 	0,                  // stride
	// 	(void*)0            // array buffer offset
	// );
	//
	// glEnableVertexAttribArray(1);
	// glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	// glVertexAttribPointer(
	// 	0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
	// 	4,                  // size
	// 	GL_FLOAT,           // type
	// 	GL_FALSE,           // normalized?
	// 	0,                  // stride
	// 	(void*)0            // array buffer offset
	// );
	//
	// // Draw the triangle !
	// glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool c_window::handle_keyboard()
{
	return(false);
}

bool c_window::handle_mouse()
{
	return(false);
}
