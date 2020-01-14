#include "jgl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
int type = 0;
c_camera *camera;
Matrix MVP_1;
GLuint vertexbuffer;
GLuint colorbuffer;

ostream& operator<<(ostream& os, glm::mat4 data)
{
	os << "--------------------------------------------------------------" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j != 0)
				os << " - ";
			os << "[" << ftoa(data[j][i], 3) << "]";
		}
		os << endl;
	}
	os << "--------------------------------------------------------------" << endl;
	return os;
}

ostream& operator<<(ostream& os, glm::vec3 value)
{
	os << "(" << ftoa(value.x, 3) << " / " << ftoa(value.y, 3) << " / " << ftoa(value.z, 3) << ")";
	return os;
}

ostream& operator<<(ostream& os, glm::vec4 value)
{
	os << "(" << ftoa(value.x, 3) << " / " << ftoa(value.y, 3) << " / " << ftoa(value.z, 3) << " / " << ftoa(value.w, 3) << ")";
	return os;
}

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

	if (type == 0)
	{
		camera = new c_camera(Vector3(4, 3, 3), 45, 0.1f, 100.0f);
		camera->look_at(Vector3(0, 0, 0));

		//MatrixID = glGetUniformLocation(g_application->program_color_model(), "MVP");

		MVP_1 = camera->MVP();

		static const GLfloat g_vertex_buffer_data[] = {
			 0.0f, 0.0f, 0.0f,
			 0.0f, 1.0f, 0.0f,
			 0.0f, 0.0f, 1.0f,
			 0.0f, 0.0f, 0.0f,
			 0.0f, 1.0f, 0.0f,
			 1.0f, 0.0f, 0.0f,
			 0.0f, 0.0f, 0.0f,
			 0.0f, 1.0f, 0.0f,
			 -1.0f, 0.0f, 0.0f,
 			 0.0f, 0.0f, 0.0f,
 			 0.0f, 1.0f, 0.0f,
 			 0.0f, 0.0f, -1.0f
		};

		static const GLfloat g_color_buffer_data[] = {
			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f
		};

		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
		type = 1;
	}

	glClear(GL_DEPTH_BUFFER_BIT);

	glUseProgram(g_application->program_color_model());

	glUniformMatrix4fv(g_application->matrix_colorID(), 1, GL_FALSE, &(MVP_1.value[0][0]));

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

			// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			4,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
}

bool c_window::handle_keyboard()
{
	return(false);
}

bool c_window::handle_mouse()
{
	return(false);
}
