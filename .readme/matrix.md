## MATRIX : Outils mathematiques
La structure Matrix stocke 16 float, servant aux calculs matriciels.

### Methodes publiques :
- `Matrix()`  
	Construit une matrice d'identite.



- `Matrix(float a0, float a1, float a2, float a3, float b0, float b1, float b2, float b3, float c0, float c1, float c2, float c3, float d0, float d1, float d2, float d3)`  
	Construit une matrice personnalisee de forme :
	a0 a1 a2 a3
	b0 b1 b2 b3
	c0 c1 c2 c3
	d0 d1 d2 d3


- `Matrix(X_ROTATE, float angle)`  
	Construit une matrice


- `Matrix(Y_ROTATE, float angle)`  
	Construit une matrice


- `Matrix(Z_ROTATE, float angle)`  
	Construit une matrice


- `Matrix(ROTATION, float x, float y, float z)`  
	Construit une matrice


- `Matrix(TRANSLATION, float t_x, float t_y, float t_z)`  
	Construit une matrice


- `Matrix(TRANSLATION, Vector3 delta)`  
	Construit une matrice


- `Matrix(SCALE, float t_x, float t_y, float t_z)`  
	Construit une matrice


- `Matrix(SCALE, Vector3 delta)`  
	Construit une matrice


- `Matrix operator * (Matrix p_matrix)`  
	Construit une matrice


- `Vector3 operator * (Vector3 vertex)`  
	Construit une matrice


- `Vector4 operator * (Vector4 vertex)`  
	Construit une matrice



### Exemple d'utilisation
