## C_APPLICATION : Classe gestionnaire de fenetre

la classe c_application est la classe principale de la JGL

### Methodes publiques :

- `c_application(string name, Vector2 p_size = Vector2(840, 680), Color p_color = Color(50, 50, 50))`  
Construit une application, initialise les composants de la librairie.  
/!\ - Necessaire a l'utilisation des fonctions graphiques - /!\  
`name` : Defini le nom qu'aura votre application  
`p_size` : (Facultatif) Defini la taille de votre fenetre a l'ecran. Vous pouvez l'exprimer en pixel ou en rapport a la taille de l'ecran via a un ratio de 0 a 1.  
`p_color` : (Facultatif) Defini la couleur du fond de votre nouvelle fenetre.  


- `Vector2 size()`  
Renvoi la taille de l'ecran en pixel.  


- `c_widget *central_widget()`  
Renvoi le widget principal de votre fenetre.  


- `void set_font_path(string p_font_path)`  
Defini la police de caractere a utiliser lors des appels aux fonctions de dessins le necessitant  
`p_font_path` : Defini le chemin d'acces au fichier de font (Chemin relatif ou chemin absolu).  


- `void quit()`  
Ferme la fenetre en detruisant tout les widgets qui lui sont affilie  


- `void set_background(Color p_color)`  
Defini la couleur de fond de votre fenetre  
`p_color` : Defini la couleur du fond de votre nouvelle fenetre.  


- `void resize(Vector2 p_size)`  
Change les dimensions de la fenetre en redimmensionnant les viewports qui lui sont actuellement attaches  
`p_size` : (Facultatif) Defini la taille de votre fenetre a l'ecran. Vous pouvez l'exprimer en pixel ou en rapport a la taille de l'ecran via a un ratio de 0 a 1.  


- `int run()`  
Lance l'execution du programme. A partir de l'execution de cette fonction, votre programme lancera les fonctions `void update(void)`, `bool handle_keyboard(void)` et `bool handle_mouse()` des widgets qui lui font affilies  

### Exemple d'utilisation

```
int main()
{
	// Creation de la fenetre puis definition de la police d'ecriture
	c_application app = c_application("JGL_Exemple", Vector2(0.8f, 0.8f), Color(255, 0, 0, 255));
	app.set_font_path("ressources/font/arial.ttf");

	// Ajoutez des widgets a l'application -> une c_frame dans cet exemple
	c_frame frame = c_frame(app.central_widget());
	// Definition de la taille de notre frame via c_application::size() et des calculs vectoriels
	frame.set_geometry(Vector2(50, 50), app.size() - Vector2(100, 100));
	frame.activate();

	//Lancement de notre application jusqu'a la fermeture de la fenetre
	return (app.run());
}
```
