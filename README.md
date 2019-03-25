# --- MY HANDMADE GRAPHICAL/GUI LIBRARY ---

Library create using SDL2 and OpenGL, with customs functions to draw shapes, texture, text and gui-elements on screen.

## - Requirement
### - Linux
Be sure to have sudo apt-get installed and availible to you

git clone this repo where you want to install my lib.
Do a make, and it will give you a libgraphic_library.a

To compile with my lib, add the following command to your compile instruction :
```
$(foreach dir, [Path to includes inside my library], -I$(dir) ) -lgraphical_library -lsdl2 -lsdl2_image -lsdl2_mixer -lsdl2_ttf -lGLEW -lGL
```

### - MacOS
Be sure to have brew installed and availible to you

git clone this repo where you want to install my lib.
Do a make, and it will give you a libgraphic_library.a

To compile with my lib, add the following command to your compile instruction :
```
$(foreach dir, [Path to includes inside my library], -I$(dir) ) $(foreach dir, $(shell find ~/.brew/include -type d), -I$(dir) ) -L ~/.brew/lib -L [Path to the library.a location] -lgraphical_library -lsdl2 -lsdl2_image -lsdl2_mixer -lsdl2_ttf -framework OpenGL
```

## --- CONTENT

### - Define
You can find in includes/template/define.h some importants define :
- SCREEN_WEIGHT / SCREEN_HEIGHT : describ your window dimensions
- LOG_PATH : describ the location of the log folder, relative to the executable who use my library
- FPS : set the maximum fps of your program (Used automaticaly inside the fps handler)
- COLOR_SHADER_VERT / FRAG : describ the location, relative to the executable who use my library, of the color shader used by the drawshape functions
- TEXTURE_SHADER_VERT / FRAG : describ the location, relative to the executable who use my library, of the textured shader used by the draw image, text and tileset functions
- FONT_PATH : describ the path, relative to the executable who use my library, to the font used by draw text functions

You can find in includes/template/text_define.h some define for the draw text function :
- color definition : BLACK, WHITE, RED, etc ect
- font style : BOLD, NORMAL, etc ect

### - Structure
- t_color :
...describ a rgba color. Can be created by double (from 0.0 to 1.0) or by int (from 0 to 255)

- t_vect :
...describ a 2D point in plane, by a x and y value (in double). Can be create by int or double. Given with operator +, -, * , /, <, >, == and !=

- t_vertex :
...describ a 3D point in space, by a x, y and z value (in double). Can be created by int or double

- t_point :
...describ a point on the screen, by a x and y value for coordinates, and rgba for pixel color. Can be create by double

- t_image :
...create an image (textured or plain color), give it to your graphical card and handle it for you
Can be create by a path to an image, a SDL_Surface, or a t_color for plain color (See t_image chapter for more informations)

- t_angle :
...describ an 3D angle, by a x, y and z rotation

- matrice :
...describ a matrice (See matrice chapter for more informations)

- t_tileset :
...create an image, cuted into multiple square, send it to your graphica card and handle it for you
...Can be created by a path to an image and the number of square on the x and y axis that this image contain (See t_tileset chapter for more information)


### - SCREEN HANDLER
 - void window_initialisation(string program_name) :
  ...Create a window, named [program_name], of SCREEN_WEIGHT / SCREEN_HEIGHT pixel, on center of your screen, and setting up everything for you.

 - void prepare_screen(void | t_color color) :
  ...Clear your screen, and set it to RGB(0.1, 0.1, 0.1, 1.0) or [color]

 - void render_screen(void | bool value) :
  Actualize your screen.
 if [value] is equal to true, draw your fps on the top-left corner of your screen.

 ### - DRAW SHAPE
 - void draw_rectangle(t_vect tl, t_vect tr, t_vect dl, t_vect dr, t_color c) :
  Draw an quadrilateral shape of [c] color, with him corner at [tl - dr] coordinates on screen

 - void draw_rectangle(t_vect coord, t_vect size, t_color c)
  Draw a straigth rectangle for [c] color at desired [coord], with a [size] describ in size.

 - void draw_centred_rectangle(t_vect coord, t_vect size, t_color c)
  Draw a straigth rectangle for [c] color centred around desired [coord], with a [size] describ in size.

 - void draw_border_rectangle(t_vect coord, t_vect size, int border, t_color c, t_color c2)
  Draw a rectangle of [c2] color, at [coord] and desired [size], and place another smaller rectangle of [c] color.

 ### - DRAW TEXT
 - int draw_text(string text, int text_size, t_vect coord, int color_type)
  Draw a [text] of [text_size] size, starting at [coord], of [color_type] (see text_define.h for more information about color_type) and of style NORMAL, and return the length of the resulting image on screen.

 - int draw_text(string text, int text_size, int style, t_vect coord, int color_type)
  Draw a [text] of [text_size] size, starting at [coord], of [color_type] (see text_define.h for more information about color_type) and of desired [style], and return the length of the resulting image on screen.

 - int draw_text(string text, int text_size, int type, int outline, t_vect coord, int color_type, int color_type2)
  Draw a [text] of [text_size] size, starting at [coord], of [color_type] (see text_define.h for more information about color_type) with an outline of [color_type_2], a size of [outile] and of desired style, and return the length of the resulting image on screen.

Those 3 function exist as draw_centred_text and draw_lined_text, respectively to draw text centred or write from the center of the left side of your text

 - void draw_paragraph(string text, t_vect coord, t_vect size, int color_type)
  Draw a [text], starting at [coord], of [color_type], and detect when the text need to go on the next line, depending of the [size] you have allocated for your text.
  - void draw_paragraph(string text, int text_size, t_vect coord, t_vect size, int color_type)
  Draw a [text] of [text_size], starting at [coord], of [color_type], and detect when the text need to go on the next line, depending of the [size] you have allocated for your text.

 - vector<string> prepare_paragraphe(string text, int text_size, t_vect size)
  Cut a [text] into multiples strings, smaller enought to fit inside a rectangle of [size] if writed at a size of [text_size].

### - FILE HANDLER
 - ifstream	open_file(string path)
  Open a file and return it.

 - string get_str(ifstream * myfile)
  Return the next line in [myfile] file

 - vector<string> get_strsplit(ifstream * myfile, const string c, int size)
  Return the next line in [myfile] file, cut using the char c as delimitor.
 if [size] != 1, check for the number and return an error if not correct.

 - vector<string> list_files(string path, string extension)
  List every file with the [extension] desired inside the directory at [path] and return the result.

 - bool check_file_exist(string path)
  Check if the file at [path] exist, and return true or false.

 - bool	copy_file(string src, string dest)
  Copy the content of the file at [src] path into a new file at [dest].
 If [dest] already exist, erase it.

 - void	write_on_file(string path, string text)
  Write at the end of the file at [path] the desired [text].

 - void rewrite_on_file(string path, string text)
  Erase the file at [path], re-create it and write the desired [text] inside the new version.

### - LOG HANDLER
 - void charge_log_file(string program_name)
  Create a log file, stored at LOG_PATH, and setup the log's header with [program_name].

 - void write_in_log(string msg)
  Write inside the log file the desired [msg], with a line count before it. sensitive to '\n'.
 Do nothing if the log file isn't already created

### - ERROR HANDLER
 - void error_exit(string error)
  Write inside the log file the desired [error], and close the program. Just close the program if the log file isn't open already.

 - int printOglError(const char * file, int line)
  Write in the log file the state of OpenGL at a desired moment with indication of the file and line where this function is used.
 You can also call it by using printOpenGLError() to automaticly setup the file and line variable

 - int check_sdl_error(__FILE__, __LINE__)
  Write in the log file the state of SDL at a desired moment with indication of the file and line where this function is used.
 You can also call it by using printSDLError() to automaticly setup the file and line variable

### - MATRICE 4x4
 You have 7 matrice's contructors already setup :
 - matrice(double a0, double a1, double a2, double a3, double b0, double b1, double b2, double b3, double c0, double c1, double c2, double c3,
 double d0, double d1, double d2, double d3)
  Create a matrice by entering 16 values.

 - matrice(X | Y | Z, double angle)
  Create a rotation matrice setup properly with the desired [angle].

 - matrice(R, double x, double y, double z)
  Create a rotation matrice setup properly with the desired [angles x, y and z].

 - matrice(T, double t_x, double t_y, double t_z)
  Create a translation matrice and set it up to [t_x, t_y and t_z] translation.

 - matrice(S, double s_x, double s_y, double s_z)
  Create a scaling matrice and set it up to [t_x, t_y and t_z] scale.

 - This library is given with the openrator * between matrice and matrice / matrice and vertex

### - T_IMAGE
 You have 7 t_image's contructors already setup :
 - t_image(string path)
  Open the desired image at [path], store it inside the graphical card, setup properly everything for you

 - t_image(SDL_Surface * surface)
  Send the desired [surface] to the graphical card, store it inside and setup properly everything for you

 - t_image(t_color color)
  Create a image of plain desired [color], store it inside the graphical card, setup properly everything for you

 - t_image.draw_self(t_vect tl, t_vect tr, t_vect dl, t_vect dr)
  Draw the image inside a quadrilateral shape, with him corner at [tl - dr] coordinates on screen

 - t_image.draw_self(t_vect coord, t_vect size)
  Draw the image inside a rectangle at [coord], with a desired size of [size].

 - t_image.draw_centred_self(t_vect coord, t_vect size)
  Draw the image inside a rectangle centred around [coord], with a desired size of [size].

 ### - T_TILESET
 You have 1 t_tileset's constructor already setup :
 - t_tileset(string path, t_vect size)
  Create a t_tileset containing the desired image at [path], and cut it in multiple squares to have [size.x * size.y] sprites.

 - t_tileset.get_sprite(t_vect sprite)
  Return the number of the sprite at the [sprite.x / sprite.y] place in the tileset.

 - t_tileset.draw_self(t_vect tl, t_vect tr, t_vect dl, t_vect dr, int sprite | t_vect sprite, double alpha)
  Draw the desired [sprite] inside a quadrilateral shape, with him corner at [tl - dr] coordinates on screen, with the desired [alpha] transparency.

 - t_tileset.draw_self(t_vect coord, t_vect size, int sprite | t_vect sprite)
  Draw the desired [sprite] inside a rectangle at [coord], with a desired size of [size].

 - t_tileset.draw_self(t_vect coord, t_vect size, int sprite | t_vect sprite, double alpha)
  Draw the desired [sprite] inside a rectangle at [coord], with a desired size of [size],with the desired [alpha] transparency.
