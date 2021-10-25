/*
----------------------------------------------------
Actividad 3.2 Implementación de "Dijkstra and Floyd"
----------------------------------------------------

Autor: Ezequiel Lozano Guerrero
Matrícula: A01734172

Autor: Diego Andrés Moreno Molina
Matrícula: A01283790    

Fecha de creación: 23/09/2021
*/

/*
Casos de prueba:

1)
4
0 2 -1 3
-1 0 1 5
2 3 0 -1
3 -1 4 0

2)
6
0 1 2 -1 -1 -1
1 0 -1 5 1 -1
2 -1 0 2 3 -1
-1 5 2 0 2 2
-1 1 3 2 0 1
-1 -1 -1 2 1 0

3)
5
0 2 2 -1 5
-1 0 -1 6 2
2 8 0 -1 8
9 4 5 0 -1
-1 7 6 5 0

4)
6
0 8 -1 4 -1 -1
-1 0 -1 4 3 9
5 4 0 9 -1 7
8 -1 -1 0 7 -1
9 -1 -1 5 0 6
6 8 -1 -1 5 0
*/

#include <iostream>
#include <vector>
#include <limits.h> // Para usar INT_MAX (que obtiene el máximo valor de un entero)

using namespace std;
#define INF 99999999 // Valor definido para los vértices que no tengan conexión

// ---------------------------------------------------
// Función que imprime la matriz de distancias mínimas
// ---------------------------------------------------
// Complejidad computacional: O(n)

void finalDistanceMatrix(vector<int> dist, int i, int n){

    for(int j = 0; j < n; j++){ // Se recorre el camino de vértices a partir de uno de ellos
        cout  << "node " << i + 1 << " to node " << j + 1 << ": " << dist[j] << endl;
    }

}

// ---
// Fin
// ---

// ----------------------------------------------------------
// Función que encuentra la distancia mínima hacia un vértice
// ----------------------------------------------------------
// Complejidad computacional: O(n)

int findMin(vector<int> min, vector<bool> travel, int n){ // Encontrar la distancia mínima

    int i, minVal = INT_MAX; // Se inicializa la distancia mínima como el máximo valor de un entero
 
    for(int currentV = 0; currentV < n; currentV++){ // Se recorre el camino de vértices a partir de uno de ellos

        if(travel[currentV] == false && min[currentV] <= minVal){ // Se guarda el vértice con menor distancia

            minVal = min[currentV];
            i = currentV; // Se almacena el índice del vértice con menor distancia

        }

    }
 
    return i; // Se regresa el índice del vértice con menor distancia
}

// ---
// Fin
// ---

// ----------------------------------------------------------------------------------------------------
// Función que implementa el algoritmo Dijkstra para encontrar el camino más corto de un vértice a otro
// ----------------------------------------------------------------------------------------------------
// Complejidad computacional: O(V^2); V = número de vértices

void dijkstraAlgorithm(vector<vector<int>> matrix, int start, int n){

    vector<int> min(n, 0); // Matriz de distancias mínimas
    vector<bool> travel(n, 0); // Matriz booleana que indica los vértices visitados
    
    for(int i = 0; i < n; i++){

        min[i] = INT_MAX;
        travel[i] = false;
        
    }

    min[start] = 0; // Se establece en 0 la distancia del vértice que actúa como punto de partida
    
    for(int i = 0; i < n - 1; i++){ // Se recorre la matriz para encuentrar el camino más corto para todos los vértices

        int minV = findMin(min, travel, n); // Se selecciona el vértice más cercano al que actúa como punto de partida
        travel[minV] = true; // Se establece verdadera la visita al vértice

        for(int currentV = 0; currentV < n; currentV++){ // Se recorre el camino del vértice más cercano al punto de partida para guardar la distancia mínima de los vértices adyacentes

            // Se actualiza la distancia mínima de los vértices no visitados
            if(!travel[currentV] && matrix[minV][currentV] && min[minV] != INT_MAX && min[minV] + matrix[minV][currentV] < min[currentV]){
                min[currentV] = min[minV] + matrix[minV][currentV];
            }

        }

    }

    finalDistanceMatrix(min, start, n); // Se imprimen los caminos más cortos del vértice de partida hacia los demás

}

// ---
// Fin
// ---

// --------------------------------------------------------------------------------------------------
// Función que implementa el algoritmo Floyd para encontrar el camino más corto de todos los vértices
// --------------------------------------------------------------------------------------------------
// Complejidad computacional: O(V^3); V = número de vértices

void floydAlgorithm(vector<vector<int>> matrix, int n){

    // finalMatrix es la matriz donde guardaremos la distancia mínima de todos los vértices
    vector<vector<int>> finalMatrix(n, vector<int>(n, 0));
 
    // Primero supondremos que el camino mas corto es la conexion directa que hay entre los nodos,
    // por lo que podemos empezar usando la matriz inicial como base.

    for(int i = 0; i < n; i++){
        
        for(int j = 0; j < n; j++){
            finalMatrix[i][j] = matrix[i][j];
        }

    }
 
    // Iteramos todos los vértices de la matriz, checando en cada iteracion si se encontro el camino
    // más corto entre dos vértices intermediarios

    for(int l = 0; l < n; l++){

        for(int i = 0; i < n; i++){

            for(int j = 0; j < n; j++){

                // Si el vértice "l" es el camino más corto de "i" a "j", actualizamos el valor de nuestra
                // matriz conteniendo los caminos más cortos
                
                if(finalMatrix[i][j] > (finalMatrix[i][l] + finalMatrix[l][j]) && (finalMatrix[l][j] != INF && finalMatrix[i][l] != INF)){
                    finalMatrix[i][j] = finalMatrix[i][l] + finalMatrix[l][j];
                }

            }

        }

    }

    for(int i = 0; i < n; i++){ // Impresión de la matriz final
        
        for(int j = 0; j < n; j++){

            if(finalMatrix[i][j] == INF){ // Si la distancia final hacia el vértice es infinita
                cout << "-1 "; // Se imprime un -1
            }
            else{
                cout << finalMatrix[i][j] << " "; // De lo contrario se imprime la distancia mínima
            }

        }

        cout << endl;

    }
 

}

// ---
// Fin
// ---

int main(){

  int n;
  cin >> n;

  // Se crea la matriz de adyacencias
  vector<vector<int>> matrix(n, vector<int>(n, 0));
  
  for(int i = 0; i < n; i++){ // Se solicita la entrada de datos para llenar la matriz

    for(int j = 0; j < n; j++){

      int value;
      cin >> value;
      
      if(value == -1){ // Se modifica el valor "infinito", de -1 a la variable definida INF
          value = INF;
      }

      matrix[i][j] = value; // Se guarda el valor de la entrada en la matriz

    }

  }

  cout << "\nDijkstra:\n";
  for(int i = 0; i < n; i++){ // Se llama al algoritmo dijkstra para cada vértice
    dijkstraAlgorithm(matrix, i, n);
  }

  cout << "\nFloyd:\n";
  floydAlgorithm(matrix, n); // // Se llama al algoritmo floyd con la matriz de adyacencias


  return 0;

}