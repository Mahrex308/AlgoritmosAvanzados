/*
------------------------------------------------
Actividad 4.3 Implementación búsqueda geométrica
------------------------------------------------

Autor: Ezequiel Lozano Guerrero
Matrícula: A01734172

Autor: Diego Andrés Moreno Molina
Matrícula: A01283790    

Fecha de creación: 18/10/2021
*/

/*
Casos de prueba:

1)
6
2 3
12 30
40 50
5 1
12 10
3 4

2)
4
-2 -2
2 4
5 6
1 2

3)
7
0 0
-2 0
4 0
1 1
3 3
-2 2
5 2

4)
11
4 4
-2 -2
-3 -4
-1 3
2 3
-4 0
1 1
-1 -1
3 -1
-4 2
-2 4
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include <cfloat> // Para utilizar FLT_MAX

using namespace std;

// ----------------------------------------------------------------------------------------------------
// Estructura que sirve para manejar un punto con las coordenadas 'x' y 'y' dentro del plano cartesiano
// ----------------------------------------------------------------------------------------------------

struct Point{

  int x;
  int y;

};

// ---
// Fin
// ---

// -----------------------------------------------------------------------------------------------------------
// Función recursiva que sirve para encontrar la distancia más corta de dos puntos entre un conjunto de puntos
// -----------------------------------------------------------------------------------------------------------
// Complejidad computacional: O(n*log(n))
// Donde n = número de puntos

float getMinDistance(vector<Point> Points){

  if(Points.size() < 4){ // Caso base: si hay menos de cuatro puntos se obtiene la menor distancia mediante fuerza bruta

    // El algoritmo se vuelve de complejidad O(n^2), sin embargo, sigue siendo eficiente porque
    // son pocas iteraciones las realizadas, debido al diminuto número de puntos

    float minDistance = FLT_MAX; // Se inicializa la distancia mínima con el máximo valor de un flotante

    for(int i = 0; i < Points.size(); ++i){

      for(int j = i + 1; j < Points.size(); ++j){

        // Si la distancia entre los puntos 'i', 'j' es menor que 'minDistance'
        if(sqrt(pow((Points[i].x - Points[j].x), 2) + pow((Points[i].y - Points[j].y), 2)) < minDistance){
          minDistance = sqrt(pow((Points[i].x - Points[j].x), 2) + pow((Points[i].y - Points[j].y), 2)); // Dicha distancia se convierte en la menor
        }

      }

    }

    return minDistance;

  }

  int middleIndex = Points.size()/2; // Índice del punto medio
  Point middlePoint = Points[middleIndex]; // Obtiene el punto medio

  vector<Point> firstPoints; // Vector temporal con la primera mitad de puntos
  vector<Point> secondPoints; // Vector temporal con la segunda mitad de puntos

  firstPoints.assign(Points.begin(), Points.end() - 1); // Guarda la primera mitad del conjunto de puntos en el vector 'firstPoints'
  secondPoints.assign(Points.begin(), Points.end() - middleIndex); // Guarda la segunda mitad del conjunto de puntos en el vector 'secondPoints'

  float distanceLeft = getMinDistance(firstPoints); // Obtiene la distancia hacia el punto izquierdo más cercano del punto medio
  float distanceRight = getMinDistance(secondPoints); // Obtiene la distancia hacia el punto derecho más cercano del punto medio
  float distance_1 = ((distanceLeft < distanceRight) ? distanceLeft : distanceRight); // Obtiene la menor de las dos distancias

  vector<Point> closestPoints; // Vector de puntos con distancia más cercana a 'distance_1' del punto medio

  for(int i = 0; i < Points.size(); i++){

    // Si el valor absoluto de la diferencia de la distancia en 'x' entre el punto 'i' y el punto medio es menor a 'distance_1'
    if(abs(Points[i].x - middlePoint.x) < distance_1){
      closestPoints.push_back(Points[i]); // Se agrega el punto en 'i' al vector 'closestPoints'
    }

  }

  // Inicialización de una segunda distancia, que será igual o menor a 'distance_1'
  float distance_2 = distance_1; // Su propósito es comprobar si existe una menor distancia a 'distance_1'

  sort(closestPoints.begin(), closestPoints.end(), [](Point &firstPoint, Point &secondPoint){
    return(firstPoint.y < secondPoint.y);
  }); // Los puntos del vector 'closestPoints' se ordenan conforme a la coordenada 'y'

  for(int i = 0; i < closestPoints.size(); ++i){

    // Si la resta entre las coordenadas 'y' de los puntos 'i', 'j' es menor que 'distance_2'
    for(int j = i + 1; j < closestPoints.size() && (closestPoints[j].y - closestPoints[i].y) < distance_2; ++j){

      // Si la distancia entre los puntos 'i', 'j' es menor que 'distance_2'
      if(sqrt(pow((closestPoints[i].x - closestPoints[j].x), 2) + pow((closestPoints[i].y - closestPoints[j].y), 2)) < distance_2){
        distance_2 = sqrt(pow((closestPoints[i].x - closestPoints[j].x), 2) + pow((closestPoints[i].y - closestPoints[j].y), 2)); // Dicha distancia se convierte en 'distance_2'
      }

    }
    
  }

  float minDistance = ((distance_1 < distance_2) ? distance_1 : distance_2); // Valor mínimo entre 'distance_1' y 'distance_2'
  return minDistance;
  
}

// ---
// Fin
// ---

// -------------------------------------------------------------------------------------------------
// Función que sirve para encontrar la distancia más corta de dos puntos entre un conjunto de puntos
// -------------------------------------------------------------------------------------------------
// Complejidad computacional: O(n*log(n))
// Donde n = número de puntos

float minDistance(vector<Point> Points){

  sort(Points.begin(), Points.end(), [](Point &firstPoint, Point &secondPoint){
    return(firstPoint.x < secondPoint.x);
  }); // Los puntos del vector se ordenan conforme a la coordenada 'x'

  return getMinDistance(Points); // Llamada a la función getMinDistance() para obtener la distancia más corta

}

// ---
// Fin
// ---

int main(){

  int n;
  cin >> n;
  vector<Point> Points;

  for(int i = 0; i < n; i++){

    int x, y;
    cin >> x >> y;
    Point newPoint = {x, y};
    Points.push_back(newPoint);

  }

  cout << "La distancia más corta es: " << minDistance(Points) << endl;
  return 0;

}