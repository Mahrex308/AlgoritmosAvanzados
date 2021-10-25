/*
--------------------------------------------------------------------------------------------------------
Actividad 1.2 Implementación de la técnica de programación "Programación dinámica" y "algoritmos avaros"
--------------------------------------------------------------------------------------------------------

Autor: Ezequiel Lozano Guerrero
Matrícula: A01734172

Autor: Diego Andrés Moreno Molina
Matrícula: A01283790    

Fecha de creación: 16/08/2021
*/

/*
Caso de prueba 1:

    3 monedas
        $1
        $2
        $5
    $11 cantidad
    $20 pago
    1 elección de algoritmo

Caso de prueba 2:

    3 monedas
        $2
        $5
        $10
    $25 cantidad
    $36 pago
    1 elección de algoritmo

Caso de prueba 3:

    3 monedas
        $1
        $2
        $5
    $11 cantidad
    $20 pago
    2 elección de algoritmo

Caso de prueba 4:

    3 monedas
        $2
        $5
        $10
    $25 cantidad
    $36 pago
    2 elección de algoritmo
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Complejidad computacional del algoritmo: O(n*m)
n es la cantidad a dar de cambio
m es la cantidad de monedas diferentes
*/

void dynamicAlgorithm(int coins[], int amount, int arrSize){

    int max = amount + 1;
    int dp[amount + 1];
    
    for(int i = 0; i < amount + 1; i++){
        dp[i] = max;
    }
    
    dp[0] = 0;

    for(int i = 1; i <= amount; i++){

        for(int j = 0; j < arrSize; j++){

            if(coins[j] <= i){
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }

        }

    }

    int numCoins = (dp[amount] > amount) ? -1 : dp[amount];

    if(numCoins != -1){
        cout << "\nNúmero mínimo de monedas para dar el cambio del producto pagado: " << numCoins << endl;
    }
    else{
        cout << "\nCambio inexacto" << endl;
    }

}

/*
Complejidad computacional del algoritmo: O(n*m)
n es la cantidad a dar de cambio
m es la cantidad de monedas diferentes
*/

void greedyAlgorithm(int coins[], int amount, int arrSize){

    sort(coins, coins + arrSize); // Ordena monedas
    vector<int> ans;
    
    for(int i = arrSize - 1; i >= 0; i--){
        
        while(amount >= coins[i]){

            amount -= coins[i];
            ans.push_back(coins[i]);

        }

    }

    int numCoins = ans.size();

    if(numCoins != 0){

        if(amount == 0){

            cout << "\nNúmero mínimo de monedas para dar el cambio del producto pagado: " << numCoins << endl;
            cout << "\n- Lista de monedas que se dan de cambio -\n" << endl;

            for(int i = 0; i < ans.size(); i++){
                cout << "Moneda " << i + 1 << ": $" << ans[i] << endl;
            }

        }
        else{
            cout << "\nNo hay solución correcta con este algoritmo" << endl;
        }

    }
    else{
        cout << "\nCambio inexacto" << endl;
    }
        
}
 
int main(){

    cout << "Escribe el número de monedas a ingresar: ";

    int n;
    cin >> n;
    int coins[n];

    cout << "\n- Escribe el valor de cada moneda -\n" << endl;

    for(int i = 0; i < n; i++){

        cout << "Moneda " << i + 1 << ": $";

        int temp;
        cin >> temp;
        coins[i] = temp;

    }

    int p, q, algorithm;

    cout << "\nEscribe el precio del producto: $";
    cin >> p; // Precio
    cout << "Escribe la cantidad con la que se paga el producto: $";
    cin >> q; // Cantidad pagada

    cout << "\n- Algoritmos disponibles para solucionar el problema -\n" << endl;
    cout << "1. Algoritmo de programación avara" << endl;
    cout << "2. Algoritmo de programación dinámica" << endl;

    do{

        cout << "\nElige el algoritmo de la solución (escribe 1 o 2): ";
        cin >> algorithm;

        if(algorithm == 1){

            cout << "\nCambio: $" << q-p;
            greedyAlgorithm(coins, q-p, n);

        }
        else
        if(algorithm == 2){

            cout << "\nCambio: $" << q-p;
            dynamicAlgorithm(coins, q-p, n);

        }

    } while(algorithm != 1 && algorithm != 2);
    
    return 0;

}