## Fonctions d'affichage de texte :

- `int draw_text(string text, Vector2 coord, int size = 16, int outline = 0, text_color color = text_color::black, text_style type = text_style::normal, c_viewport *viewport = nullptr)`
	Affiche a l'ecran le texte passe en parametre a la coordonnee `coord` avec comme point d'ancrage le coin haut/gauche du texte a l'ecran.  
	Parametres facultatifs:  
		`size` -> La taille en pixel du texte a l'ecran.  
		`outline` -> Le detourage du texte.  
		`color` -> La couleur du texte a afficher.  
		`style` -> Le style du texte a afficher.


- `int draw_centred_text(string text, Vector2 coord, int size = 16, int outline = 0, text_color color = text_color::black, text_style type = text_style::normal, c_viewport *viewport = nullptr)`
	Affiche a l'ecran le texte passe en parametre a la coordonnee `coord` avec comme point d'ancrage le centre du texte a l'ecran.  
	Parametres facultatifs:  
		`size` -> La taille en pixel du texte a l'ecran.  
		`outline` -> Le detourage du texte.  
		`color` -> La couleur du texte a afficher.  
		`style` -> Le style du texte a afficher.


### Exemple d'utilisation
