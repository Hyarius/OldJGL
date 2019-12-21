#ifndef JGL_LOG_HANDLER_H
#define JGL_LOG_HANDLER_H

void open_log_file(string path, string log_name);
string get_file_info(string file, int line);
void write_in_log(string msg);

#endif
