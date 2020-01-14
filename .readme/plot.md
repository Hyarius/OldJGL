## C_PLOT : gestionnaire de graphique
la classe c_plot est la classe permettant de creer des graphiques et de les exporter en fichier image.  

### Methodes publiques :
c_plot(Vector2 p_size = Vector2(1280, 1080), Plot_data p_absciss = Plot_data("Absciss"), Plot_data p_ordinate = - `Plot_data("Ordinate"))`



- `void initialize()`



- `void clear()`



- `void draw()`



- `void draw_plot_point(Vector2 point, Color color)`



- `void draw_plot_line(Vector2 point_a, Vector2 point_b, Color color)`



- `void draw_absciss()`



- `void draw_absciss_point(float value)`



- `void draw_ordinate()`



- `void draw_ordinate_point(float value)`



- `void save(string path)`



- `void actualize_point()`



- `void calc_axis_unit()`



- `void add_line(Color p_color = Color(0, 0, 0))`



- `void add_point(Vector2 p_point, size_t line = 0)`



- `void add_point(float p_a, float p_b, size_t line = 0)`



- `void set_line_color(size_t index, Color p_color)`



- `void set_point_size(size_t p_size)`



- `void set_line_size(size_t p_size)`



- `void set_size(Vector2 p_size)`



- `void set_margin(Vector2 p_margin)`



- `void set_color(Color p_color)`



- `void set_absciss(Plot_data p_absciss)`



- `void set_ordinate(Plot_data p_ordinate)`



- `void set_absciss_name(string p_name)`



- `void set_absciss_funct(string (*p_funct)(float))`



- `void set_absciss_min(float p_min)`



- `void set_absciss_max(float p_max)`



- `void set_absciss_gap(float p_gap)`



- `void divide_absciss(size_t subdivision)`



- `void set_absciss_precision(int p_precision)`



- `void set_ordinate_name(string p_name)`



- `void set_ordinate_funct(string (*p_funct)(float))`



- `void set_ordinate_min(float p_min)`



- `void set_ordinate_max(float p_max)`



- `void set_ordinate_gap(float p_gap)`



- `void divide_ordinate(size_t subdivision)`



- `void set_ordinate_precision(int p_precision)`




### Exemple d'utilisation
