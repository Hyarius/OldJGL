#include "jgl.h"

std::string color_shader_vert = {
	"#version 330 core\n"
	"layout(location = 0) in vec3 model_space;"
	"layout(location = 1) in vec4 vertexColor;"
	"out vec4 fragmentColor;"
	"void main()"
	"{"
		"gl_Position = vec4(model_space, 1.0f);"
		"fragmentColor = vertexColor;"
	"}"
};

std::string color_shader_frag = {
	"#version 330 core\n"
	"in vec4 fragmentColor;"
	"out vec4 color;"
	"void main()"
	"{"
		"color = fragmentColor;"
	"}"
};




std::string texture_shader_vert = {
	"#version 330 core\n"
	"layout(location = 0) in vec3 model_space;"
	"layout(location = 1) in vec2 vertexUV;"
	"uniform float alpha_value;"
	"out vec2 UV;"
	"out float ALPHA;"
	"void main()"
	"{"
		"gl_Position = vec4(model_space, 1.0f);"
		"UV = vertexUV;"
		"ALPHA = alpha_value;"
	"}"
};

std::string texture_shader_frag = {
	"#version 330 core\n"
	"in vec2 UV;"
	"in float ALPHA;"
	"out vec4 color;"
	"uniform sampler2D textureID;"
	"void main()"
	"{"
		"color = texture(textureID, UV).rgba;"
		"color.a = color.a * ALPHA;"
	"}"
};

