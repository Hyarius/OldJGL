#include "jgl.h"

string color_shader_vert = {
	"#version 330 core\n"
	"layout(location = 0)"
	"in vec3 model_space;"
	"layout(location = 1) in vec4 vertexColor;"
	"out vec4 fragmentColor;"
	"void main()"
	"{"
		"gl_Position.xyz = model_space;"
		"fragmentColor = vertexColor;"
	"}"
};

string color_shader_frag = {
	"#version 330 core\n"
	"in vec4 fragmentColor;"
	"out vec4 color;"
	"void main()"
	"{"
		"color = fragmentColor;"
	"}"
};




string texture_shader_vert = {
	"#version 330 core\n"
	"layout(location = 0) in vec3 model_space;"
	"layout(location = 1) in vec2 vertexUV;"
"uniform float alpha_value;"
"out vec2 UV;"
"out float ALPHA;"
	"void main()"
	"{"
		"gl_Position.xyz = model_space;"
		"UV = vertexUV;"
		"ALPHA = alpha_value;"
	"}"
};

string texture_shader_frag = {
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

string color_model_shader_vert = {
	"#version 330 core\n"
	"layout(location = 0) in vec3 model_space;"
	"layout(location = 1) in vec4 vertexColor;"
"layout(location = 2) in vec3 normale;"
"vec4 tmp_pos;"
"vec4 tmp_normale;"
"out vec4 fragmentColor;"
"out float value;"
"uniform mat4 MVP;"
"uniform vec3 pos;"
"uniform mat4 rot;"
"uniform vec3 dir_light;"
"void main()"
"{"
"tmp_pos = rot * vec4(model_space, 1);"
"tmp_pos = tmp_pos + vec4(pos, 1);"
"tmp_normale = rot * vec4(normale, 1);"
"gl_Position = MVP * tmp_pos;"
		"fragmentColor = vertexColor;"
		"value = (dot(vec3(tmp_normale), dir_light) + 1) / 2.0f;"
	"}"
};

string color_model_shader_frag = {
	"#version 330 core\n"
	"in vec4 fragmentColor;"
	"in float value;"
"out vec4 color;"
"float tmp_value;"
"void main()"
"{"
"color = fragmentColor;"
"tmp_value = value;"
"if (tmp_value < 0.3f)"
	"tmp_value = 0.3f;"
		"color.r = color.r * tmp_value;"
		"color.g = color.g * tmp_value;"
	"color.b = color.b * tmp_value;"
	" }"
};



string texture_model_shader_vert = {
	"#version 330 core\n"
	"layout(location = 0) in vec3 model_space;"
	"layout(location = 1) in vec2 vertexUV;"
"layout(location = 2) in vec3 normale;"
"vec4 tmp_pos;"
"vec4 tmp_normale;"
"out vec2 UV;"
"out float value;"
"out float alpha;"
"uniform mat4 MVP;"
"uniform vec3 pos;"
"uniform mat4 rot;"
"uniform vec3 dir_light;"
"uniform float alpha_value;"
"void main()"
"{"
"tmp_pos = rot * vec4(model_space, 1);"
"tmp_pos = tmp_pos + vec4(pos, 1);"
"tmp_normale = rot * vec4(normale, 1);"
"gl_Position = MVP * tmp_pos;"
		"value = (dot(vec3(tmp_normale), dir_light) + 1) / 2.0f;"
		"UV = vertexUV;"
	"alpha = alpha_value;"
	" }"
};

string texture_model_shader_frag = {
	"#version 330 core\n"
	"in vec2 UV;"
	"in float value;"
"in float alpha;"
"out vec4 color;"
"float tmp_value;"
"uniform sampler2D textureID;"
"void main()"
"{"
"color = texture(textureID, UV).rgba;"
"tmp_value = value;"
"if (tmp_value < 0.3f)"
	"tmp_value = 0.3f;"
		"color.r = color.r * tmp_value;"
		"color.g = color.g * tmp_value;"
	"color.b = color.b * tmp_value;"
		"color.a = alpha;"
	"}"
};
