### - JGL : High level library for easy graphical interface and video game

***
## Content :  
### - Main data structure :
#### *Classes* :
- [jgl::Application](LIEN)
	`Main classe : Handle window for the user`
- [jgl::Viewport](LIEN)
	`Screen subdividing classe`
- [jgl::Array](LIEN)
	`std::vector custom implementation without memory reallocation`
- [jgl::Image](LIEN)
	`Image classe : handle GPU data for 2D/3D rendering`
- [jgl::Sprite_sheet](LIEN)
	`jgl::Image with subdivision`
- [jgl::Glyph](LIEN)
	`Unicode, encoded with UTF-8`
- [jgl::String](LIEN)
	`std::string custom implementation with memory optimization`
- [jgl::Unique_string](LIEN)
	`Strict std::string implementation`
- [jgl::Pool](LIEN)
	`Pool design patern implementation`
- [jgl::Pool_object](LIEN)
	`Object for jgl::pool`
- [jgl::Share_object](LIEN)
	`Implementation of a new smart pointer`
- [jgl::Mesh](LIEN)
	`Handle 3D data as vertices, uvs, normales, materials`
- [jgl::Camera](LIEN)
	`Handle 3D rendering`

#### *Widgets* :
- [jgl::Button](LIEN)
	`Custom implementation of Qt QPushbutton`
- [jgl::Check_box](LIEN)
	`Custom implementation of Qt QCheckbox`
- [jgl::Check_entry](LIEN)
	`A Check_box with text entry`
- [jgl::Contener](LIEN)
	`A no-visual widget, for organization`
- [jgl::Frame](LIEN)
	`Custom implementation of Qt QFrame`
- [jgl::Image_label](LIEN)
	`Custom implementation of Qt QLabel - Image rendering part`
- [jgl::Render_widget](LIEN)
	`TO BE DEFINED`
- [jgl::Text_entry](LIEN)
	`Custom implementation of Qt QTextEdit`
- [jgl::Text_label](LIEN)
	`Custom implementation of Qt QLabel - Text rendering part`
- [jgl::Value_entry](LIEN)
	`A floating-point value entry`
- [jgl::Value_label](LIEN)
	`A widget rendering a floating-point value`

#### *Structures* :
- [jgl::Color](LIEN)
	`Storing RGBA color as float, from 0 to 1`
- [jgl::Matrix2x2 / 3x3 / 4x4](LIEN)
	`Matrices math implementation`
- [jgl::Vector2 / Vector3 / Vector4](LIEN)
	`Vectors math implementation`
