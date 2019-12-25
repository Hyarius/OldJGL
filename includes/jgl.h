#ifndef JGL_H
#define JGL_H

#define FPS 60.0f;
#ifdef _WIN32
#	include "dirent.h"
#endif

#include "jgl_includes.h"
#include "jgl_enum.h"
#include "structure/jgl_data.h"
#include "jgl_basics_functions.h"
#include "structure/jgl_vector.h"
#include "structure/jgl_color.h"
#include "structure/jgl_geometry.h"
#include "jgl_algorithm.h"
#include "structure/jgl_system.h"
#include "structure/jgl_application.h"
#include "structure/jgl_viewport.h"
#include "jgl_text.h"
#include "structure/jgl_image.h"
#include "structure/jgl_tileset.h"
#include "widget/jgl_widgets.h"

#include "widget/jgl_text_label.h"
#include "widget/jgl_value_label.h"
#include "widget/jgl_frame.h"
#include "widget/jgl_button.h"
#include "widget/jgl_text_entry.h"
#include "widget/jgl_value_entry.h"
#include "widget/jgl_check_box.h"
#include "widget/jgl_hour_entry.h"
#include "widget/jgl_tab.h"
#include "widget/jgl_vscrollable_bar.h"

#include "jgl_file_handler.h"
#include "jgl_log_handler.h"
#include "jgl_json_handler.h"

#include "widget/jgl_window.h"
#include "jgl_draw_primitive.h"
#include "structure/jgl_plot.h"

#include "jgl_define.h"

extern c_application *g_application;
extern t_keyboard *g_keyboard;
extern t_mouse *g_mouse;

#endif
