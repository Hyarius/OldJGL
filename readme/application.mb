- c_application
Methode publique :
	`c_application(string name, Vector2 p_size = Vector2(840, 680), Color p_color = Color(50, 50, 50))`
Construit une application, initialise les composants de la librairie.
/!\ - Necessaire a l'utilisation des fonctions graphiques - /!\
`name` : Defini le nom qu'aura votre application
`p_size` : (Facultatif) Defini la taille de votre fenetre a l'ecran. Vous pouvez l'exprimer en pixel ou en rapport a la taille de l'ecran via a un ratio de 0 a 1.
`p_color` : (Facultatif) Defini la couleur du fond de votre nouvelle fenetre.

	`Vector2 size()`
Renvoi la taille de l'ecran en pixel.

	`c_widget *central_widget()`
Renvoi le widget principal de votre fenetre.

	`void set_font_path(string p_font_path)`
Defini la police de caractere a utiliser lors des appels aux fonctions de dessins le necessitant
`p_font_path` : Defini le chemin d'acces au fichier de font (Chemin relatif ou chemin absolu).

	`void quit()`
Ferme la fenetre en detruisant tout les widgets qui lui sont affilie

	`void set_background(Color p_color)`
Defini la couleur de fond de votre fenetre
`p_color` : Defini la couleur du fond de votre nouvelle fenetre.

	`void resize(Vector2 p_size)`
Change les dimensions de la fenetre en redimmensionnant les viewports qui lui sont actuellement attaches
`p_size` : (Facultatif) Defini la taille de votre fenetre a l'ecran. Vous pouvez l'exprimer en pixel ou en rapport a la taille de l'ecran via a un ratio de 0 a 1.

	`int run()`
Lance l'execution du programme. A partir de l'execution de cette fonction, votre programme lancera les fonctions `void update(void)`, `bool handle_keyboard(void)` et `bool handle_mouse()` des widgets qui lui font affilies
