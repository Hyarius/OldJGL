#ifndef DEFINE_H
# define DEFINE_H

#ifdef _WIN32
#	define strtok_r strtok_s
#endif

#define LOG_PATH	("log/")


#define SCREEN_WEIGHT 680
#define SCREEN_HEIGHT 420

#define FPS 60

#define COLOR_SHADER_VERT "shader/color_shader.vert"
#define COLOR_SHADER_FRAG "shader/color_shader.frag"
#define TEXTURE_SHADER_VERT "shader/texture_shader.vert"
#define TEXTURE_SHADER_FRAG "shader/texture_shader.frag"

#define FONT_PATH "font/Tinos-Regular.ttf"

#endif
