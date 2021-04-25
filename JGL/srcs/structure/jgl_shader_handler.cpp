/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboutin <gboutin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:20:56 by gboutin           #+#    #+#             */
/*   Updated: 2019/12/12 16:21:01 by gboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jgl.h"

namespace jgl
{
	static void	compile_shader(GLuint p_id, std::string p_source)
	{
		GLint	result;
		int len;
		const char* content;

		content = p_source.c_str();
		result = GL_FALSE;
		glShaderSource(p_id, 1, &content, NULL);
		glCompileShader(p_id);
		glGetShaderiv(p_id, GL_COMPILE_STATUS, &result);
		if (result != GL_TRUE)
		{
			glGetShaderiv(p_id, GL_INFO_LOG_LENGTH, &len);
			std::vector<char> msg(len + 1);
			glGetShaderInfoLog(p_id, len, NULL, &msg[0]);
			error_exit(-2, &msg[0]);
		}
	}

	static void	compute_program(GLuint p_program_id, GLuint p_vertex_shader_id, GLuint p_fragment_shader_id)
	{
		GLint	result;

		result = GL_FALSE;
		glAttachShader(p_program_id, p_vertex_shader_id);
		glAttachShader(p_program_id, p_fragment_shader_id);
		glLinkProgram(p_program_id);
		glGetProgramiv(p_program_id, GL_LINK_STATUS, &result);
		if (result != GL_TRUE)
			error_exit(-3, "Error while computing shader program");
		glDetachShader(p_program_id, p_vertex_shader_id);
		glDetachShader(p_program_id, p_fragment_shader_id);
		glDeleteShader(p_vertex_shader_id);
		glDeleteShader(p_fragment_shader_id);
	}

	GLuint		load_shaders(std::string vertex_content,
		std::string fragment_content)
	{
		GLuint	vertex_shader_id;
		GLuint	fragment_shader_id;
		GLuint	program_id;

		

		program_id = glCreateProgram();
		fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
		vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
		compile_shader(vertex_shader_id, vertex_content);
		compile_shader(fragment_shader_id, fragment_content);
		compute_program(program_id, vertex_shader_id, fragment_shader_id);
		return (program_id);
	}
}