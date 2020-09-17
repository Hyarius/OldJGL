### - JGL : High level library for easy graphical interface and video game

***
## Content :  
### - Main data structure :
#### *Classes* :
- jgl::Application
	`Main classe : Handle window for the user`
- jgl::Viewport
	`Screen subdividing classe`
- jgl::Array
	`std::vector custom implementation without memory reallocation`
- jgl::Image
	`Image classe : handle GPU data for 2D/3D rendering`
- jgl::Sprite_sheet
	`jgl::Image with subdivision`
- jgl::Glyph
	`Unicode, encoded with UTF-8`
- jgl::String
	`std::string custom implementation with memory optimization`
- jgl::Unique_string
	`Strict std::string implementation`
- jgl::Pool
	`Pool design patern implementation`
- jgl::Pool_object
	`Object for jgl::pool`
- jgl::Share_object
	`Implementation of a new smart pointer`
- jgl::Mesh
	`Handle 3D data as vertices, uvs, normales, materials`
- jgl::Camera
	`Handle 3D rendering`

#### *Widgets* :
- jgl::Button
	`Custom implementation of Qt QPushbutton`
- jgl::Check_box
	`Custom implementation of Qt QCheckbox`
- jgl::Check_entry
	`A Check_box with text entry`
- jgl::Contener
	`A no-visual widget, for organization`
- jgl::Frame
	`Custom implementation of Qt QFrame`
- jgl::Image_label
	`Custom implementation of Qt QLabel - Image rendering part`
- jgl::Render_widget
	`TO BE DEFINED`
- jgl::Text_entry
	`Custom implementation of Qt QTextEdit`
- jgl::Text_label
	`Custom implementation of Qt QLabel - Text rendering part`
- jgl::Value_entry
	`A floating-point value entry`
- jgl::Value_label
	`A widget rendering a floating-point value`

#### *Structures* :
- jgl::Color
	`Storing RGBA color as float, from 0 to 1`
- jgl::Matrix2x2 / 3x3 / 4x4
	`Matrices math implementation`
- jgl::Vector2 / Vector3 / Vector4
	`Vectors math implementation`
