/*
----------------------------------------------------------------------------------------
Actividad 4.1 Implementación Intersección y proximidad aplicando geometría computacional
----------------------------------------------------------------------------------------

Autor: Ezequiel Lozano Guerrero
Matrícula: A01734172

Autor: Diego Andrés Moreno Molina
Matrícula: A01283790    

Fecha de creación: 14/10/2021
*/

/*
Casos de prueba:

1)
4
5 3 10 4
3 2 6 10

2)
4
1 1 10 1
1 2 10 2

3)
4
10 0 0 10
0 0 10 10

4)
4
-5 -5 0 0
1 1 10 10
*/

#include <iostream>

using namespace std;

// ----------------------------------------------------------------------------------------------------
// Estructura que sirve para manejar un punto con las coordenadas "x" y "y" dentro del plano cartesiano
// ----------------------------------------------------------------------------------------------------

struct Punto{

  int x;
  int y;

};

// -----------------------------------------------------------------------------
// Función auxiliar que ayuda a checar si un punto "i" esta en un segmento "jk"
// -----------------------------------------------------------------------------
// Complejidad computacional: O(1)

bool checkSegment(Punto j, Punto i, Punto k){
  
  // Checamos si los límites de "x" y los límites de "y", están dentro de un punto específico
  if(i.x <= max(j.x, k.x) && i.x >= min(j.x, k.x) && i.y <= max(j.y, k.y) && i.y >= min(j.y, k.y)){
    return true;
  }

  return false;

}

// ---
// Fin
// ---

// --------------------------------------------------------------------------------------
// Función que sirve para encontrar la orientación que tienen 3 puntos.
// Retorna 0 si los puntos son colineares, 1 si van en sentido del reloj y 2 contra reloj
// --------------------------------------------------------------------------------------
// Complejidad computacional: O(1)
 
int orientacion(Punto j, Punto i, Punto k){

  // La fórmula de abajo nos permite encontrar la orientación del segmento, la lógica
  // detrás de esta fórmula es utilizar la ecuación de la pendiente (y2 - y1)/(x2 - x1)
  int val = (i.y - j.y) * (k.x - i.x) - (i.x - j.x) * (k.y - i.y);

  if(val == 0){
    return 0;
  }
  else{
    return (val > 0) ? 1 : 2; 
  } 

}

// ---
// Fin
// ---
 
 // --------------------------------------------------------------------------------------
// Función que sirve para checar si dos segmentos hechos por 4 puntos intersectan entre sí
// ---------------------------------------------------------------------------------------
// Complejidad computacional: O(1)

bool intersecta(Punto p1, Punto q1, Punto p2, Punto q2){

  // Primero calculamos la orientación de todos los puntos, para saber cómo manejar el caso
  int ori1 = orientacion(p1, q1, p2);
  int ori2 = orientacion(p1, q1, q2);
  int ori3 = orientacion(p2, q2, p1);
  int ori4 = orientacion(p2, q2, q1);

  // En el caso general podemos hacer una comparación sencilla, donde si sabemos que las orientaciones no son iguales,
  // podemos acabar con el algoritmo porque estamos seguros que sí existe una intersección
  if(ori1 != ori2 && ori3 != ori4){
    return true;
  }

  // Ahora tratamos los 4 casos posibles directamente
  // Caso 1: Hay una intersección cuando p1, q1 y p2 son colineares, y p2 está en el segmento de p1q1
  if(ori2 == 0 && checkSegment(p1, q2, q1)){
    return true;
  } 

  // Caso 2: Hay una intersección cuando p2, q2, y p1 son colineares, y p1 está en el segmento de p2q2
  if(ori3 == 0 && checkSegment(p2, p1, q2)){
    return true;
  } 

  // Caso 3: Hay una intersección cuando p2, q2 y q1 son colineares, y q1 está en el segmento de p2q2
  if(ori4 == 0 && checkSegment(p2, q1, q2)){
    return true;
  } 

  // Caso 4: No se cumple ninguno de los casos anteriores, por lo que sabemos que no hay intersección
  return false; 

}

// ---
// Fin
// ---

int main(){

  int x1, y1, x2, y2, x3, y3, x4, y4;
  struct Punto p1, q1, p2, q2;
  int n, count = 0;
  cin >> n; // Se asume que en el caso de prueba n es múltiplo de 4

  for(int i = 0; i < n; i++){

    count++;
    
    if(count == 1){

      cin >> x1 >> y1;
      p1 = {x1, y1};

    }
    else
    if(count == 2){

      cin >> x2 >> y2;
      q1 = {x2, y2};
      
    }
    else
    if(count == 3){

      cin >> x3 >> y3;
      p2 = {x3, y3};
      
    }
    else
    if(count == 4){

      cin >> x4 >> y4;
      q2 = {x4, y4};

      cout << ((intersecta(p1, q1, p2, q2)) ? "true" : "false") << endl;
      count = 0;
      
    }

  }

  return 0;

}