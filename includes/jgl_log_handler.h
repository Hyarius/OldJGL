#ifndef JGL_LOG_HANDLER_H
#define JGL_LOG_HANDLER_H

namespace jgl
{
	void open_log_file(jgl::String path, jgl::String log_name);
	jgl::String get_file_info(jgl::String file_info, int line);
	void write_in_log(jgl::String msg);
}
#endif
