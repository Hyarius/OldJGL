#include "jgl.h"

string color_shader_vert = {
	"#version 330 core \
	layout(location = 0) in vec3 vertexPosition_modelspace; \
	layout(location = 1) in vec4 vertexColor; \
	\
	out vec4 fragmentColor; \
	\
	void main() \
	{\
		gl_Position.xyz = vertexPosition_modelspace;\
		fragmentColor = vertexColor;\
	}"
};

string color_shader_frag = {
	"#version 330 core \
	in vec4 fragmentColor; \
	\
	out vec4 color; \
	\
	void main() \
	{\
		color = fragmentColor;\
	}"
};




string texture_shader_vert = {
	"#version 330 core \
	layout(location = 0) in vec3 vertexPosition_modelspace; \
	layout(location = 1) in vec2 vertexUV; \
	\
	uniform float alpha_value; \
	\
	out vec2 UV; \
	out float ALPHA; \
	\
	void main() \
	{\
		gl_Position.xyz = vertexPosition_modelspace;\
		UV = vertexUV;\
		ALPHA = alpha_value;\
	}"
};

string texture_shader_frag = {
	"#version 330 core \
	in vec2 UV; \
	in float ALPHA; \
	\
	out vec4 color; \
	\
	uniform sampler2D textureID; \
	\
	void main() \
	{ \
		color = texture( textureID, UV ).rgba; \
		color.a = color.a * ALPHA;\
	}"
};




string color_model_shader_vert = {
	"#version 330 core \
	layout(location = 0) in vec3 vertexPosition_modelspace; \
	layout(location = 1) in vec4 vertexColor; \
	layout(location = 2) in vec3 normale; \
	\
	vec3 tmp_pos; \
	out vec4 fragmentColor; \
	out float value;\
	\
	uniform mat4 MVP; \
	uniform vec3 pos; \
	uniform vec3 dir_light; \
	\
	void main() \
	{\
		tmp_pos = vertexPosition_modelspace + pos;\
		gl_Position =  MVP * vec4(tmp_pos, 1); \
		fragmentColor = vertexColor;\
		value = (dot(normale, dir_light) + 1) / 2.0f;\
	}"
};

string color_model_shader_frag = {
	"#version 330 core \
	in vec4 fragmentColor; \
	in float value; \
	\
	out vec4 color; \
	\
	void main() \
	{\
		color = fragmentColor;\
		color.r = color.r * value;\
		color.g = color.g * value;\
		color.b = color.b * value;\
	}"
};





string texture_model_shader_vert = {
	"#version 330 core \
	layout(location = 0) in vec3 vertexPosition_modelspace; \
	layout(location = 1) in vec2 vertexUV; \
	layout(location = 2) in vec3 normale; \
	\
	vec3 tmp_pos; \
	out vec2 UV;\
	out float value;\
	out float alpha;\
	\
	uniform mat4 MVP; \
	uniform vec3 pos; \
	uniform vec3 dir_light; \
	uniform float alpha_value; \
	\
	void main() \
	{\
		tmp_pos = vertexPosition_modelspace + pos;\
		gl_Position =  MVP * vec4(tmp_pos, 1); \
		value = 1;\
		UV = vertexUV;\
		alpha = alpha_value;\
	}"
};

//(dot(normale, dir_light) + 1) / 2.0f;\

string texture_model_shader_frag = {
	"#version 330 core \
	in vec2 UV; \
	in float value; \
	in float alpha; \
	\
	out vec4 color; \
	\
	uniform sampler2D textureID; \
	\
	void main() \
	{ \
		color = texture( textureID, UV ).rgba; \
		color.r = color.r * value;\
		color.g = color.g * value;\
		color.b = color.b * value;\
		color.a = color.a * alpha;\
	}"
};
