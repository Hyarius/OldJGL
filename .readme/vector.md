### Vector 2 :
- `Vector2(int p_value)`  
	Initialise un Vector2 avec comme parametre x = p_value et y = p_value.


- `Vector2(float p_value = -1)`  
	Initialise un Vector2 avec comme parametre x = p_value et y = p_value.


- `Vector2(float p_x, float p_y)`  
	Initialise un Vector2 avec comme parametre x = p_x et y = p_y.


- `Vector2(int p_x, int p_y)`  
	Initialise un Vector2 avec comme parametre x = p_x et y = p_y.


- `Vector2& operator = (int p_value)`
	Renvoi un Vector2 avec comme parametre x = p_value et y = p_value.


- `Vector2& operator = (float  p_value)`  
	Renvoi un Vector2 avec comme parametre x = p_value et y = p_value.


- `Vector2 operator + (const Vector2& delta)`  
	Ajoute delta au Vector2 puis le renvoi.


- `Vector2	operator - (const Vector2& delta)`  
	Retire delta au Vector2 puis le renvoi.


- `Vector2	operator * (const Vector2& delta)`  
	Multiplie le Vector2 par delta puis le renvoi.


- `Vector2	operator / (const Vector2& delta)`  
	Divise le Vector2 par delta puis le renvoi.


- `void operator += (const Vector2& delta)`    
	Ajoute delta au Vector2.


- `void operator -= (const Vector2& delta)`  
	Retire delta au Vector2.


- `void operator *= (const Vector2& delta)`  
	Multiplie le Vector2 par delta.


- `void operator /= (const Vector2& delta)`  
	Divise le Vector2 par delta.


- `bool operator == (const Vector2& delta) const`  
	Renvoi `true` si `this` et `delta` sont strictement egaux et `false` dans le cas contraire.


- `bool operator != (const Vector2& delta) const`  
	Renvoi `false` si `this` et `delta` sont strictement egaux et `true` dans le cas contraire.


- `bool operator < (const Vector2& other) const`  
	Renvoi `true` si `other.y` > `this->y` ou que `other.y` == `this->`y && `other.x` > `this->x` et `false` dans le cas contraire.


- `bool operator > (const Vector2& other) const`  
	Renvoi `false` si `other.y` > `this->y` ou que `other.y` == `this->`y && `other.x` > `this->x` et `true` dans le cas contraire.


- `float distance(Vector2 &point)`  
	Renvoi la distance entre `point` et `this`.


- `Vector2 cross(Vector2 &other)`  
	Renvoi le produit vectoriel entre `point` et `this`.


- `Vector2 normalize()`  
	Renvoi this normalise.


- `float dot(Vector2 &other)`  
	Renvoi le produit scalaire entre `other` et `this`.


- `string str()`  
	Renvoi une string decrivant le Vector2.


- `Vector2 floor()`  
	Renvoi un Vector2 dont les valeurs on etait arrondi a l'inferieur.


- `Vector2 invert()`  
	Renvoi un Vector2 contraire a `this`.


### Vector 3 :
- `Vector3(int p_value)`  
	Initialise un Vector3 avec comme parametre x = p_value, y = p_value et z = p_value.


- `Vector3(float p_value = -1)`  
	Initialise un Vector3 avec comme parametre x = p_value, y = p_value et z = p_value.


- `Vector3(float p_x, float p_y, float p_z)`  
	Initialise un Vector3 avec comme parametre x = p_x, y = p_y et z = p_z.


- `Vector3(int p_x, int p_y, int p_z)`  
	Initialise un Vector3 avec comme parametre x = p_x, y = p_y et z = p_z.


- `Vector3& operator = (int p_value)`
	Renvoi un Vector3 avec comme parametre x = p_value, y = p_value et z = p_value.


- `Vector3& operator = (float  p_value)`  
	Renvoi un Vector3 avec comme parametre x = p_value, y = p_value et z = p_value.


- `Vector3 operator + (const Vector3& delta)`  
	Ajoute delta au Vector3 puis le renvoi.


- `Vector3	operator - (const Vector3& delta)`  
	Retire delta au Vector3 puis le renvoi.


- `Vector3	operator * (const Vector3& delta)`  
	Multiplie le Vector3 par delta puis le renvoi.


- `Vector3	operator / (const Vector3& delta)`  
	Divise le Vector3 par delta puis le renvoi.


- `void operator += (const Vector3& delta)`    
	Ajoute delta au Vector3.


- `void operator -= (const Vector3& delta)`  
	Retire delta au Vector3.


- `void operator *= (const Vector3& delta)`  
	Multiplie le Vector3 par delta.


- `void operator /= (const Vector3& delta)`  
	Divise le Vector3 par delta.


- `bool operator == (const Vector3& delta) const`  
	Renvoi `true` si `this` et `delta` sont strictement egaux et `false` dans le cas contraire.


- `bool operator != (const Vector3& delta) const`  
	Renvoi `false` si `this` et `delta` sont strictement egaux et `true` dans le cas contraire.


- `bool operator < (const Vector3& other) const`  
	Renvoi `true` si `other.y` > `this->y` ou que `other.y` == `this->`y && `other.x` > `this->x` et `false` dans le cas contraire.


- `bool operator > (const Vector3& other) const`  
	Renvoi `false` si `other.y` > `this->y` ou que `other.y` == `this->`y && `other.x` > `this->x` et `true` dans le cas contraire.


- `float distance(Vector3 &point)`  
	Renvoi la distance entre `point` et `this`.


- `Vector3 cross(Vector3 &other)`  
	Renvoi le produit vectoriel entre `point` et `this`.


- `Vector3 normalize()`  
	Renvoi this normalise.


- `float dot(Vector3 &other)`  
	Renvoi le produit scalaire entre `other` et `this`.


- `string str()`  
	Renvoi une string decrivant le Vector3.


- `Vector3 floor()`  
	Renvoi un Vector3 dont les valeurs on etait arrondi a l'inferieur.


- `Vector3 invert()`  
	Renvoi un Vector3 contraire a `this`.


### Vector 3 :
- `Vector4(int p_value)`  
	Initialise un Vector4 avec comme parametre x = p_value, y = p_value, z = p_value et w = p_value.


- `Vector4(float p_value = -1)`  
	Initialise un Vector4 avec comme parametre x = p_value, y = p_value, z = p_value et w = p_value.


- `Vector4(float p_x, float p_y, float p_z, float p_w)`  
	Initialise un Vector4 avec comme parametre x = p_x, y = p_y, z = p_z et w = p_w.


- `Vector4(int p_x, int p_y, int p_z, int p_w)`  
	Initialise un Vector4 avec comme parametre x = p_x, y = p_y, z = p_z et w = p_w.


- `Vector4& operator = (int p_value)`
	Renvoi un Vector4 avec comme parametre x = p_value, y = p_value, z = p_value et w = p_value.


- `Vector4& operator = (float  p_value)`  
	Renvoi un Vector4 avec comme parametre x = p_value, y = p_value, z = p_value et w = p_value.


- `Vector4 operator + (const Vector4& delta)`  
	Ajoute delta au Vector4 puis le renvoi.


- `Vector4	operator - (const Vector4& delta)`  
	Retire delta au Vector4 puis le renvoi.


- `Vector4	operator * (const Vector4& delta)`  
	Multiplie le Vector4 par delta puis le renvoi.


- `Vector4	operator / (const Vector4& delta)`  
	Divise le Vector4 par delta puis le renvoi.


- `void operator += (const Vector4& delta)`    
	Ajoute delta au Vector4.


- `void operator -= (const Vector4& delta)`  
	Retire delta au Vector4.


- `void operator *= (const Vector4& delta)`  
	Multiplie le Vector4 par delta.


- `void operator /= (const Vector4& delta)`  
	Divise le Vector4 par delta.


- `bool operator == (const Vector4& delta) const`  
	Renvoi `true` si `this` et `delta` sont strictement egaux et `false` dans le cas contraire.


- `bool operator != (const Vector4& delta) const`  
	Renvoi `false` si `this` et `delta` sont strictement egaux et `true` dans le cas contraire.


- `bool operator < (const Vector4& other) const`  
	Renvoi `true` si `other.y` > `this->y` ou que `other.y` == `this->`y && `other.x` > `this->x` et `false` dans le cas contraire.


- `bool operator > (const Vector4& other) const`  
	Renvoi `false` si `other.y` > `this->y` ou que `other.y` == `this->`y && `other.x` > `this->x` et `true` dans le cas contraire.


- `float distance(Vector4 &point)`  
	Renvoi la distance entre `point` et `this`.


- `Vector4 cross(Vector4 &other)`  
	Renvoi le produit vectoriel entre `point` et `this`.


- `Vector4 normalize()`  
	Renvoi this normalise.


- `float dot(Vector4 &other)`  
	Renvoi le produit scalaire entre `other` et `this`.


- `string str()`  
	Renvoi une string decrivant le Vector4.


- `Vector4 floor()`  
	Renvoi un Vector4 dont les valeurs on etait arrondi a l'inferieur.


- `Vector4 invert()`  
	Renvoi un Vector4 contraire a `this`.


### Exemple d'utilisation
