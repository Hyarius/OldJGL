## Enum des fonctions d'evenement' :  
### Etat du clavier : key_state::
- `up` : la touche est relachee.  
- `down` : la touche est pressee.  

### Bouton de la souris : mouse_button::
- `left` : le bouton gauche de la souris.  
- `right` : le bouton droit de la souris.    
- `middle` : le bouton centrale (la molette) de la souris.    

### Etat de la souris : mouse_state::
- `null` : le bouton n'est pas actif.  
- `down` : le bouton est actuellement enfonce.    
- `up` : le bouton vient d'etre relache.    


## Fonctions d'evenements :

- `mouse_state get_button(mouse_button type)`  
	Retourne l'etat du bouton `type` de la souris.


- `key_state get_key(int scan_code)`  
	Retourne l'etat de la touche `scan_code` du clavier.


- `void reset_key(int scan_code)`  
	Remet l'etat de la touche `scan_code` du clavier a key_state::up.



### Exemple d'utilisation
