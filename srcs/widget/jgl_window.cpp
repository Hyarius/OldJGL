#include "jgl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
c_camera *camera = nullptr;
GLuint vertexbuffer;
GLuint colorbuffer;
c_mesh *mesh;

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
}

bool c_window::handle_keyboard()
{
	return(false);
}

bool c_window::handle_mouse()
{
	return(false);
}
