## Enum des fonctions de draw texte :  
### Couleur du texte :
- black / white  
- light_blue / blue / dark_blue  
- light_red / red / dark_red  
- light_green / green / dark_green  
- light_cyan / cyan / dark_cyan  
- light_grey / grey / dark_grey  
- light_orange / orange / dark_orange  
- light_yellow / yellow / dark_yellow  
- light_purple / purple / dark_purple  

Exemple : `text_color::black`

### Couleur du texte :  
- normal  
- bold  
- italic  
- underline  
- strike   

Exemple : `text_style::normal`


## Fonctions d'affichage de texte :

- `int draw_text(string text, Vector2 coord, int size = 16, int outline = 0, text_color color = text_color::black, text_style type = text_style::normal, c_viewport *viewport = nullptr)`  
	Affiche a l'ecran le texte passe en parametre a la coordonnee `coord` avec comme point d'ancrage le coin haut/gauche du texte a l'ecran.  
	Parametres facultatifs:  
		`size` -> La taille en pixel du texte a l'ecran.  
		`outline` -> Le detourage du texte.  
		`color` -> La couleur du texte a afficher.  
		`style` -> Le style du texte a afficher.  
		`viewport` -> Le viewport dans lequel le texte doit apparaitre.  


- `int draw_centred_text(string text, Vector2 coord, int size = 16, int outline = 0, text_color color = text_color::black, text_style type = text_style::normal, c_viewport *viewport = nullptr)`  
	Affiche a l'ecran le texte passe en parametre a la coordonnee `coord` avec comme point d'ancrage le centre du texte a l'ecran.  
	Parametres facultatifs:  
		`size` -> La taille en pixel du texte a l'ecran.  
		`outline` -> Le detourage du texte.  
		`color` -> La couleur du texte a afficher.  
		`style` -> Le style du texte a afficher.  
		`viewport` -> Le viewport dans lequel le texte doit apparaitre.  


### Exemple d'utilisation
