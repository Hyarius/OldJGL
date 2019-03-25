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
$(foreach dir, [Path to includes inside my library], -I$(dir) ) $(foreach dir, $(shell find ~/.brew/include -type d), -I$(dir) ) -L ~/.brew/lib -L [Path to the library.a location] -lgraphical_library -lsdl2 -lsdl2_image -lsdl2_mixer -lsdl2_ttf -lGLEW -lGL
```
