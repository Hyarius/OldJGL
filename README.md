# High level graphical library - working with SDL2 and opengl

Library created using SDL2 and OpenGL, with custom functions to draw shapes, texture, text and gui-elements on screen.

## Requirement
### Linux
Be sure to have sudo apt-get installed and available to you.

### MacOS
Be sure to have brew installed and available to you.


git clone this repo where you want to install my lib.
Do a make, and it will give you a libgraphic_library.a


## Content

### Define
You can find in includes/template/define.h some important define :
- SCREEN_WEIGHT / SCREEN_HEIGHT : describe your window dimensions
- LOG_PATH : describe the location of the log folder, relative to the executable who use my library
- FPS : set the maximum fps of your program (Used automatically by the fps handler)
- COLOR_SHADER_VERT / FRAG : describe the location, relative to the executable who use my library, of the color shader used by the drawshape functions
- TEXTURE_SHADER_VERT / FRAG : describe the location, relative to the executable who use my library, of the textured shader used by the draw image, text and tileset functions
- FONT_PATH : describe the path, relative to the executable who use my library, to the font used by draw text functions

You can find in includes/template/text_define.h some define for the draw text function :
- color definition : BLACK, WHITE, RED, etc ect
- font style : BOLD, NORMAL, etc ect

### Structure
- t_color :

Describe a rgba color. Accept double (from 0.0 to 1.0) or int (from 0 to 255).

- t_vect :

Describe a 2D point in a plane, by x and y value (in double). Accept int or double. Overloaded operators : +, -, * , /, <, >, == and !=

- t_vertex :

Describe a 3D point in space, by x, y and z value (in double). Accept int or double.

- t_point :

Describe a point on the screen, by x and y value for coordinates, and rgba for pixel color. Accept double.

- t_image :

Create an image (textured or plain color), give it to your graphical card and handle it for you.
Accept a path to an image, a SDL_Surface, or a t_color for plain color (see the t_image chapter for more informations).

- t_angle :

Describe a 3D angle, by x, y and z rotation.

- matrice :

Describe a matrice (see the matrice chapter for more informations).

- t_tileset :

Create an image, cut into multiple squares, send it to your graphical card and handle it for you.

Accept a path to an image and the number of square on the x and y axis that this image contain (see the t_tileset chapter for more informations).


### Screen handler
 - void window_initialisation(string program_name) :

  Create a window, named [program_name], of SCREEN_WEIGHT / SCREEN_HEIGHT pixel at the center of your screen and sett up everything for you.

 - void prepare_screen(void | t_color color) :

  Clear your screen, and set it to RGB(0.1, 0.1, 0.1, 1.0) or [color]

 - void render_screen(void | bool show_fps) :

 Actualize your screen, if [show_fps] is true, draw your fps on the top-left corner of your screen.

 ### Draw shape
 - void draw_rectangle(t_vect top_left, t_vect top_right, t_vect down_left, t_vect down_right, t_color c) :

 Draw a quadrilateral shape of [c] color with it's corner at [top_left - down_right] coordinates on screen.

 - void draw_rectangle(t_vect coord, t_vect size, t_color c)

 Draw a straight rectangle of [c] color at [coord] of [size].

 - void draw_centred_rectangle(t_vect coord, t_vect size, t_color c)

 Draw a straight rectangle of [c] color centered around [coord] of [size].

 - void draw_border_rectangle(t_vect coord, t_vect size, int border, t_color c, t_color c2)

 Draw a rectangle of [c2] color at [coord] of [size], and place another smaller rectangle of [c] color inside of it.

 ### Draw text
 - int draw_text(string text, int text_size, t_vect coord, int color_type)

 Draw a NORMAL style [color_type] [text] of [text_size] starting at [coord]. Return the length of the resulting image on screen. (See text_define.h for more information about color_type).

 - int draw_text(string text, int text_size, int style, t_vect coord, int color_type)

 Draw a [style] [color_type] [text] of [text_size] starting at [coord]. Return the length of the resulting image on screen. (See text_define.h for more information about color_type).

 - int draw_text(string text, int text_size, int style, int outline, t_vect coord, int color_type, int color_type2)

 Draw a [color_type] [text] of [text_size], starting at [coord] with an outline of [color_type_2] of size [outline] and of [style]. Return the length of the resulting image on screen. (See text_define.h for more information about color_type).

Each of these functions has a draw_centered_text and draw_lined_text version which respectively fully center the drawned text or center it only on the horizontal axis.

 - void draw_paragraph(string text, t_vect coord, t_vect size, int color_type)

 Draw a [color_type] [text] starting at [coord] and detect when the text need to go on the next line, depending of the [size] you have allocated for your text.

 - vector<string> prepare_paragraphe(string text, int text_size, t_vect size)

 Split a [text] into multiple strings, small enough to fit inside a rectangle of [size] if written with [text_size].

### File handler
 - ifstream	open_file(string path)

 Open a file and return it.

 - string get_str(ifstream * myfile)

 Return the next line in [myfile]

 - vector<string> get_strsplit(ifstream * myfile, const string c, int size)

 Return the next line in [myfile], splitted using the char c as delimitor. If [size] != -1, check the total number of line and return an error if not correct.

 - vector<string> list_files(string path, string extension)

 Return every file with the [extension] inside the directory at [path].

 - bool check_file_exist(string path)

 Check if the file at [path] exist, return true or false.

 - bool	copy_file(string src, string dest)

 Copy the content of the file at [src] path into a new file at [dest].
 If [dest] already exist, erase it.

 - void	write_on_file(string path, string text)

 Write at the end of the file at [path] the desired [text].

 - void rewrite_on_file(string path, string text)

 Erase the file at [path], create it again and write the desired [text] inside the new version.

### Log handler
 - void charge_log_file(string program_name)

 Create a log file stored at LOG_PATH and setup the log's header with [program_name].

 - void write_in_log(string msg)

 Write inside the log file the desired [msg] with a line count before it (sensitive to '\n').
 Do nothing if the log file isn't already created.

### Error handler
 - void error_exit(string error)

 Write inside the log file the desired [error], and close the program. Only close the program if the log file isn't already open.

 - int printOglError(const char * file, int line)

 Write in the log file the state of OpenGL at a desired moment with indication of the file and line where this function is used.
 You can also call it by using printOpenGLError() to automatically setup the file and line variable.

 - int check_sdl_error(__FILE__, __LINE__)

 Write in the log file the state of SDL at a desired moment with indication of the file and line where this function is used.
 You can also call it by using printSDLError() to automatically setup the file and line variable.

### Matrix 4x4
 There's 7 matrix's constructors already setup :
 - matrice(double a0, double a1, double a2, double a3, double b0, double b1, double b2, double b3, double c0, double c1, double c2, double c3,
 double d0, double d1, double d2, double d3)

 Create a matrix by entering 16 values.

 - matrice(X | Y | Z, double angle)

 Create a rotation matrix properly setup with the desired [angle].

 - matrice(R, double x, double y, double z)

 Create a rotation matrix properly setup  with the desired [angles x, y and z].

 - matrice(T, double t_x, double t_y, double t_z)

 Create a translation matrix and set it up to [t_x, t_y and t_z] translation.

 - matrice(S, double s_x, double s_y, double s_z)

 Create a scaling matrix and set it up to [t_x, t_y and t_z] scale.

 - The overloaded * operator is available between matrix and matrix-vertex.

### T_IMAGE
 There's 7 t_image's contructors already setup :
 - t_image(string path)

 Open the desired image at [path], store it inside the graphical card and properly setup everything for you.

 - t_image(SDL_Surface * surface)

 Send the desired [surface] to the graphical card, store it inside and properly setup everything for you.

 - t_image(t_color color)

 Create an image of plain [color], store it inside the graphical card and properly setup everything for you.

 - t_image.draw_self(t_vect tl, t_vect tr, t_vect dl, t_vect dr)

 Draw the image inside a quadrilateral shape with it's corner at [tl - dr] coordinates on screen.

 - t_image.draw_self(t_vect coord, t_vect size)

 Draw the image inside a rectangle at [coord] of [size].

 - t_image.draw_centred_self(t_vect coord, t_vect size)

 Draw the image inside a rectangle centered around [coord] of [size].

 ### T_TILESET
 There's 1 t_tileset's constructor already setup :
 - t_tileset(string path, t_vect size)

 Create a t_tileset containing the desired image at [path], and split it in multiple squares to have [size.x * size.y] sprites.

 - t_tileset.get_sprite(t_vect sprite)

 Return the number of the sprite at the [sprite.x / sprite.y] position in the tileset.

 - t_tileset.draw_self(t_vect tl, t_vect tr, t_vect dl, t_vect dr, int sprite | t_vect sprite, double alpha)

 Draw the desired [sprite] inside a quadrilateral shape of [alpha] transparency with it's corner at [tl - dr] coordinates on screen.

 - t_tileset.draw_self(t_vect coord, t_vect size, int sprite | t_vect sprite)

 Draw the desired [sprite] of [size] inside a rectangle at [coord].

 - t_tileset.draw_self(t_vect coord, t_vect size, int sprite | t_vect sprite, double alpha)

 Draw the desired [sprite] of [size] inside a rectangle at [coord] with [alpha] transparency.
