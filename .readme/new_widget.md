- Creation d'un widget personnalité:  
Afin de creer un widget personnalise, il vous faudra simplement declarer votre structure comme heritant de la classe c_widget.  
A ce titre, vous aurez besoin de surcharger les deux methodes abstraites de la classe c_widget :  

1) la methode `void set_geometry_imp(Vector2 p_anchor, Vector2 p_area)`  
Cette fonction servira a definir ce que vous souhaitez que votre nouveau widget fasse lorsque l'on appellera la fonction set_geometry.  
p_anchor definira les coordonnees (exprimees en pixels) du coin haut/gauche du viewport de votre widget et p_area definira la zone a l'ecran (exprimees en pixels) dans laquelle votre widget pourra etre affiché.  

2) la methode `void render(void)`  
Cette fonction servira a definir la facon dont vous souhaitez que votre widget soit affiché a l'ecran.
Elle sera automatiquement appeller lors de l'execution du programme, a chaque frame.  
Les coordonnees de dessins de l'ecran doivent etre relatives au coin haut/gauche de votre fenetre, et non pas relative au viewport de votre widget.  

Vous avez aussi a votre disposition plusieurs autres methodes a surcharger pour personnaliser le comportement de votre widget:  
1) les fonctions `bool handle_keyboard(void)` et `bool handle_mouse()`  
Ces deux fonctions peuvent etre surchargées afin de permettre l'interaction entre votre widget et l'utilisateur.  
Ces deux fonctions doivent renvoyer true si vous avez interagit avec votre widget, et false le cas contraire.  

2) la fonction `void update(void)`  
Cette fonction va etre appellée par votre programme a chaque frame.  

3) la fonction `void move_imp(Vector2 delta)`  
Cette fonction va definir le comportement de votre widget si il est bougé par un autre widget (Scrollbar par exemple).  
Delta correspondra au deplacement sur x et sur y (exprimees en pixels) que votre widget aura a effectuer.  
