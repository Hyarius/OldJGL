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
	layout(location = 2) in float vertexA; \
	\
	out vec2 UV; \
	out float ALPHA; \
	\
	void main() \
	{\
		gl_Position.xyz = vertexPosition_modelspace;\
		UV = vertexUV;\
		ALPHA = vertexA;\
	}"
};

string texture_shader_frag = {
	"#version 330 core \
	in vec2 UV; \
	in float ALPHA; \
	\
	out vec4 color; \
	\
	uniform sampler2D myTextureSampler; \
	\
	void main() \
	{ \
		color = texture( myTextureSampler, UV ).rgba; \
		color.a = color.a * ALPHA;\
	}"
};




string color_model_shader_vert = {
	"#version 330 core \
	layout(location = 0) in vec3 vertexPosition_modelspace; \
	layout(location = 1) in vec4 vertexColor; \
	\
	out vec4 fragmentColor; \
	\
	uniform mat4 MVP; \
	\
	void main() \
	{\
		gl_Position =  MVP * vec4(vertexPosition_modelspace,1); \
		fragmentColor = vertexColor;\
	}"
};

string color_model_shader_frag = {
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





string texture_model_shader_vert = {
	"#version 330 core \
	layout(location = 0) in vec3 vertexPosition_modelspace; \
	layout(location = 1) in vec2 vertexUV; \
	layout(location = 2) in float vertexA; \
	\
	out vec2 UV; \
	out float ALPHA; \
	\
	uniform mat4 MVP; \
	void main() \
	{ \
		gl_Position =  MVP * vec4(vertexPosition_modelspace,1); \
		UV = vertexUV; \
		ALPHA = vertexA; \
	}"
};

string texture_model_shader_frag = {
	"#version 330 core \
	in vec2 UV; \
	in float ALPHA; \
	\
	out vec4 color; \
	\
	uniform sampler2D myTextureSampler; \
	\
	void main() \
	{ \
		color = texture( myTextureSampler, UV ).rgba; \
		color.a = color.a * ALPHA; \
	}"
};
