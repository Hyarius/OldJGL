#include "jgl.h"

int type = -1;

void			draw_pixel_color(Pixel points, Color colors, size_t nb)
{
	GLfloat *g_vertex_buffer_data = (float *)(&points);

	GLfloat *g_color_buffer_data = (float *)(&colors);

	glBindVertexArray(g_application->vertex_array());

	glBindBuffer(GL_ARRAY_BUFFER, g_application->vertex_buffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nb * 3, g_vertex_buffer_data);

	glBindBuffer(GL_ARRAY_BUFFER, g_application->color_buffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nb * 4, g_color_buffer_data);

	if (type != 1)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glUseProgram(g_application->program_color());

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, g_application->vertex_buffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, g_application->color_buffer());
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		type = 1;
	}

	glDrawArrays(GL_LINES, 0, 1 * nb);
}

void			draw_line_color(Pixel *points, Color *colors, size_t nb)
{
	GLfloat *g_vertex_buffer_data = (float *)(points);

	GLfloat *g_color_buffer_data = (float *)(colors);

	glBindVertexArray(g_application->vertex_array());

	glBindBuffer(GL_ARRAY_BUFFER, g_application->vertex_buffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nb * 6, g_vertex_buffer_data);

	glBindBuffer(GL_ARRAY_BUFFER, g_application->color_buffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nb * 8, g_color_buffer_data);

	if (type != 1)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glUseProgram(g_application->program_color());

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, g_application->vertex_buffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, g_application->color_buffer());
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		type = 1;
	}

	glDrawArrays(GL_LINES, 0, 2 * nb);
}

void			draw_triangle_color(Pixel *points, Color *colors, size_t nb)
{
	GLfloat *g_vertex_buffer_data = (float *)(points);

	GLfloat *g_color_buffer_data = (float *)(colors);

	glBindVertexArray(g_application->vertex_array());

	glBindBuffer(GL_ARRAY_BUFFER, g_application->vertex_buffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nb * 9, g_vertex_buffer_data);

	glBindBuffer(GL_ARRAY_BUFFER, g_application->color_buffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nb * 12, g_color_buffer_data);

	if (type != 1)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glUseProgram(g_application->program_color());

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, g_application->vertex_buffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, g_application->color_buffer());
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		type = 1;
	}

	glDrawArrays(GL_TRIANGLES, 0, 3 * nb);
}

void			draw_triangle_texture(Pixel *points, Uv *uvs, float *alpha, size_t nb)
{
	GLfloat *g_vertex_buffer_data = (float *)(points);

	GLfloat *g_uv_buffer_data = (float *)(uvs);

	GLfloat *g_alpha_buffer_data = alpha;

	glBindVertexArray(g_application->vertex_array());

	glBindBuffer(GL_ARRAY_BUFFER, g_application->vertex_buffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nb * 9, g_vertex_buffer_data);

	glBindBuffer(GL_ARRAY_BUFFER, g_application->texture_buffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nb * 6, g_uv_buffer_data);

	glBindBuffer(GL_ARRAY_BUFFER, g_application->alpha_buffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nb * 3, g_alpha_buffer_data);

	if (type != 0)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glUseProgram(g_application->program_sprite());

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, g_application->vertex_buffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, g_application->texture_buffer());
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, g_application->alpha_buffer());
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, NULL);
		type = 0;
	}

	glDrawArrays(GL_TRIANGLES, 0, 3 * nb);
}

void			fill_triangle_color(Pixel *points, Color *colors, size_t nb)
{
	GLfloat *g_vertex_buffer_data = (float *)(points);

	GLfloat *g_color_buffer_data = (float *)(colors);

	glBindVertexArray(g_application->vertex_array());

	glBindBuffer(GL_ARRAY_BUFFER, g_application->vertex_buffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nb * 9, g_vertex_buffer_data);

	glBindBuffer(GL_ARRAY_BUFFER, g_application->color_buffer());
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nb * 12, g_color_buffer_data);

	if (type != 1)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glUseProgram(g_application->program_color());

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, g_application->vertex_buffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, g_application->color_buffer());
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		type = 1;
	}

	glDrawArrays(GL_TRIANGLES, 0, 3 * nb);
}
