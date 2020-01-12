#ifndef JGL_H
#define JGL_H

#define FPS 60.0f;

#include "jgl_includes.h"
#include "jgl_enum.h"
#include "jgl_data.h"
#include "jgl_vector.h"
#include "jgl_matrix.h"
#include "jgl_color.h"
#include "jgl_geometry.h"
#include "jgl_basics_functions.h"
#include "jgl_algorithm.h"
#include "jgl_system.h"
#include "jgl_application.h"
#include "jgl_viewport.h"
#include "jgl_camera.h"
#include "jgl_text.h"
#include "jgl_draw_image.h"
#include "jgl_draw_primitive.h"
#include "jgl_image.h"
#include "jgl_mesh.h"
#include "jgl_tileset.h"
#include "jgl_widgets.h"

#include "jgl_text_label.h"
#include "jgl_value_label.h"
#include "jgl_frame.h"
#include "jgl_button.h"
#include "jgl_text_entry.h"
#include "jgl_value_entry.h"
#include "jgl_check_box.h"
#include "jgl_check_entry.h"
#include "jgl_hour_entry.h"
#include "jgl_tab.h"
#include "jgl_vscrollable_bar.h"
#include "jgl_image_label.h"

#include "jgl_file_handler.h"
#include "jgl_log_handler.h"
#include "jgl_json_handler.h"

#include "jgl_window.h"
#include "jgl_plot.h"

#include "jgl_define.h"

extern c_application *g_application;
extern Keyboard *g_keyboard;
extern Mouse *g_mouse;

#endif
