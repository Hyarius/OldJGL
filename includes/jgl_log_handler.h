#ifndef JGL_LOG_HANDLER_H
#define JGL_LOG_HANDLER_H

namespace jgl
{
	void open_log_file(const jgl::String path, const jgl::String log_name);
	jgl::String get_file_info(const jgl::String file_info, const int line);
	void write_in_log(const jgl::String msg);
}
#endif
