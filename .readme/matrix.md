## MATRIX : Outils mathematiques
La structure Matrix stocke 16 float, servant aux calculs matriciels.

### Methodes publiques :
- `Matrix()`  
	Construit une matrice d'identite.



- `Matrix(float a0, float a1, float a2, float a3, float b0, float b1, float b2, float b3, float c0, float c1, float c2, float c3, float d0, float d1, float d2, float d3)`  
	Construit une matrice personnalisee de forme :  
	a0 	a1 	a2 	a3  
	b0 	b1 	b2 	b3  
	c0 	c1 	c2 	c3  
	d0 	d1 	d2 	d3  


- `Matrix(X, float angle)`  
	Construit une matrice de rotation autour de l'axe X d'un angle en degree `angle`.
	Exemple :  
	`Matrix mat = Matrix(X, 145.0f);`


- `Matrix(Y, float angle)`  
	Construit une matrice de rotation autour de l'axe Y d'un angle en degree `angle`.
	Exemple :  
	`Matrix mat = Matrix(Y, 90.0f);`


- `Matrix(Z, float angle)`  
	Construit une matrice de rotation autour de l'axe Z d'un angle en degree `angle`.
	Exemple :  
	`Matrix mat = Matrix(Z, 45.0f);`


- `Matrix(R, float x, float y, float z)`  
	Construit une matrice de rotation autour des 3 axes.
	Exemple :  
	`Matrix mat = Matrix(10.0f, 10.0f, 10.0f);`


- `Matrix(T, float t_x, float t_y, float t_z)`  
	Construit une matrice de translation suivant les deplacements decrit par les floats en parametres.
	Exemple :  
	`Matrix mat = Matrix(0, 0, 1);`


- `Matrix(T, Vector3 delta)`  
	Construit une matrice de translation suivant les deplacements decrit par le [Vector3](vector.md) en parametres.
	Exemple :  
	`Matrix mat = Matrix(Vector3(0, 0, 1));`


- `Matrix(S, float t_x, float t_y, float t_z)`  
	Construit une matrice de redimensionnement suivant les deplacements decrit par les floats en parametres.
	Exemple :  
	`Matrix mat = Matrix(S, 2, 2, 2);`


- `Matrix(S, Vector3 delta)`  
	Construit une matrice de redimensionnement suivant les deplacements decrit par le [Vector3](vector.md) en parametres.
	Exemple :  
	`Matrix mat = Matrix(S, Vector3(2, 2, 2));`


- `Matrix operator * (Matrix p_matrix)`  
	Multiplie deux matrices entre elles.


- `Vector3 operator * (Vector3 vertex)`  
	Multiplie un [Vector3](vector.md) par une matrice, en conciderant le W = 1.


- `Vector4 operator * (Vector4 vertex)`  
	Multiplie un [Vector4](vector.md) par une matrice.


### Exemple d'utilisation
