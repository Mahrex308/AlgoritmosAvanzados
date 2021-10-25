/*
------------------------------------------------
Actividad 3.4 Implementación de "Graph coloring"
------------------------------------------------

Autor: Ezequiel Lozano Guerrero
Matrícula: A01734172

Autor: Diego Andrés Moreno Molina
Matrícula: A01283790    

Fecha de creación: 07/10/2021
*/

/*
Casos de prueba:

1)
5
0 0 1 0 1
0 0 1 1 1
1 1 0 1 0
0 1 1 0 1
1 1 0 1 0

2)
5
0 0 0 0 0
1 0 0 0 0
1 1 0 0 0
0 1 1 0 0
0 0 0 1 0

3)
5
0 1 1 0 0 
1 0 1 1 0
1 1 0 1 0
0 1 1 0 1
0 0 0 1 0

4)
5
0 1 1 0 0
1 0 1 0 1
1 1 0 0 1
0 0 0 0 1
0 1 1 1 0
*/

#include <iostream>
#include <vector>

using namespace std;

// --------------------------------------------------------------------------------------------
// Función que implementa el algoritmo de coloreo de un grafo, usando una matriz de adyacencias
// --------------------------------------------------------------------------------------------
// Complejidad computacional: O(n^2)
// Donde n es la cantidad de nodos/vértices


void graphColoring(vector<vector<int>> matrix, int n){
    
    int finalMatrix[n]; // Matriz con los colores resultantes para cada vértice
    finalMatrix[0] = 0; // El vértice inicial tiene el color inicial

    for(int i = 1; i < n; i++){ // Itera la matriz resultante, partiendo de 1
        finalMatrix[i] = -1;  // Asigna un -1 indicando que el vértice no tiene color
    }

    // Matriz que indica los colores disponibles
    bool colors[n]; // true = asignado; false = no asignado (a los vértices adyacentes)

    for(int i = 0; i < n; i++){
        colors[i] = false; // Se inicializan los colores (se marcan como no asignados)
    }

    for(int i = 1; i < n; i++){ // Itera la matriz de adyacencias para asignar a cada vértice un color

        for(int j = 0; j < matrix[i].size(); j++){ // Itera los vértices adyacentes al vértice i
            
            if(matrix[i][j] == 1) { // Si existe una conexión
            
              if(finalMatrix[j] != -1){ // Si el vértice tiene un color asignado
                colors[finalMatrix[j]] = true; // Se establece que el color ya se asignó (ya no se puede volver a usar)
              }

            }
            

        }

        int k;

        for(k = 0; k < n; k++){ // Se iteran los colores disponibles (no usados)
            
            if(colors[k] == false){
                break; // La variable k contiene el primer color que se puede usar (no está asignado)
            }

        }
 
        finalMatrix[i] = k; // Asigna al vértice i el color k

        for(int j = 0; j < matrix[i].size(); j++){ // Itera los vértices adyacentes al vértice i

            if(matrix[i][j] == 1) { // Si existe una conexión

              if(finalMatrix[j] != -1){ // Si el vértice tiene un color asignado
                colors[finalMatrix[j]] = false;
              }

            }

        }

    }

    for(int i = 0; i < n; i++){ // Se itera la matriz con los colores finales de cada vértice
        cout << "Node: " << i << ", Assigned Color: " << finalMatrix[i] << endl;
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
            matrix[i][j] = value; // Se guarda el valor de la entrada en la matriz

        }

    }
    
    graphColoring(matrix, n); // Se llama al algoritmo de coloreo de grafo
    return 0;

}