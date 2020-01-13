- Fonctions de base du systeme de widget
`vector<c_widget *> childrens()`
`c_widget *parent()`
`Vector2 area()`
`Vector2 anchor()`
`c_viewport *viewport()`

`bool is_active()`
`bool is_pointed(Vector2 point);`
`void activate()`
`void desactivate()`
`void set_active(bool new_state)`
`void set_parent(c_widget *p_parent)`
`void remove_children(c_widget *p_target)`
`void set_anchor(Vector2 p_anchor)`
`void set_area(Vector2 p_area)`
