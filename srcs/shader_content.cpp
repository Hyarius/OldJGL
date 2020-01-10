#include "jgl.h"

string color_shader_vert = {
	"#version 330 core \
	layout(location = 0) in vec3 vertexPosition_modelspace; \
	layout(location = 1) in vec4 vertexColor; \
	out vec4 fragmentColor; \
	void main() \
	{gl_Position.xyz = vertexPosition_modelspace;fragmentColor = vertexColor;}"
};

string color_shader_frag = {
	"#version 330 core \
	in vec4 fragmentColor; \
	out vec4 color; \
	void main() \
	{color = fragmentColor;}"
};

string texture_shader_vert = {
	"#version 330 core \
	layout(location = 0) in vec3 vertexPosition_modelspace; \
	layout(location = 1) in vec2 vertexUV; \
	layout(location = 2) in float vertexA; \
	out vec2 UV; \
	out float ALPHA; \
	void main() \
	{gl_Position.xyz = vertexPosition_modelspace;UV = vertexUV;ALPHA = vertexA;}"
};

string texture_shader_frag = {
	"#version 330 core \
in vec2 UV; \
in float ALPHA; \
out vec4 color; \
uniform sampler2D myTextureSampler; \
void main() \
{color = texture( myTextureSampler, UV ).rgba; \
color.a = color.a * ALPHA;}"
};