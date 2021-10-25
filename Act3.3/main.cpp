/*
--------------------------------------------------
Actividad 3.3 Implementación de "Knapsack problem"
--------------------------------------------------

Autor: Ezequiel Lozano Guerrero
Matrícula: A01734172

Autor: Diego Andrés Moreno Molina
Matrícula: A01283790    

Fecha de creación: 02/10/2021
*/

/*
Casos de prueba:

1)
3
140
60
50
20
10
5
30

2)
3
1
2
3
4
5
1
4

3)
3
60
100
120
10
20
30
50

4)
3
10
15
40
1
2
3
6
*/

#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Función que implementa el algoritmo para resolver el problema de la mochila
// ---------------------------------------------------------------------------
// Complejidad computacional: O(nP)
// n = número de elementos
// p = peso de los elementos

int knapsackAlgorithm(vector<int> valores, vector<int> pesos, int n, int peso_mochila){
    
    vector<vector<int>> V(n + 1, vector<int>(peso_mochila + 1));

    for(int i = 0; i <= n; i++){

        for(int p = 0; p <= peso_mochila; p++){

            if(i == 0 || p == 0){
                V[i][p] = 0;
            }
            else
            if(pesos[i - 1] > p){
                V[i][p] = V[i - 1][p];
            }
            else{ // pesos[i] <= p

                // Se hace un if-else para obtener el máximo valor
                if(V[i - 1][p] > valores[i - 1] + V[i - 1][p - pesos[i - 1]]){
                    V[i][p] = V[i - 1][p];
                }
                else{
                    V[i][p] = valores[i - 1] + V[i - 1][p - pesos[i - 1]];
                }

            }

        }

    }

    return V[n][peso_mochila];

}

// ---
// Fin
// ---

int main(){

    vector<int> valores;
    vector<int> pesos;
    int resultado = 0;
    int peso_mochila;
    int n;

    cout << "Escribe el número de elementos: ";
    cin >> n;
    cout << "\n";

    for(int i = 0; i < n; i++){

        int temp;

        cout << "Escribe el valor del elemento número " << i + 1 << ": ";
        cin >> temp;

        valores.push_back(temp);

    }

    cout << "\n";

    for(int i = 0; i < n; i++){

        int temp;

        cout << "Escribe el peso del elemento número " << i + 1 << ": ";
        cin >> temp;

        pesos.push_back(temp);

    }

    cout << "\nEscribe la capacidad de la mochila: ";
    cin >> peso_mochila;

    resultado = knapsackAlgorithm(valores, pesos, n, peso_mochila);
    cout << "\nEl mayor valor posible es " << resultado << endl;

    return 0;

}