/*
------------------------------------------------------------------------------
Actividad 1.1 Implementación de la técnica de programación "divide y vencerás"
------------------------------------------------------------------------------

Autor: Ezequiel Lozano Guerrero
Matrícula: A01734172

Autor: Diego Andrés Moreno Molina
Matrícula: A01283790    

Fecha de creación: 12/08/2021
*/

/*
Caso de prueba 1 (5 números): 25, 12, 48, 3, 35
Caso de prueba 2 (8 números): 4, 12, 9, 7, 6, 1, 15, 3
Caso de prueba 3 (10 números): -89, 12.1, 459, 12.3, -65, -12.2, 589, 45.2, 300, 0
Caso de prueba 4 (20 números): 159, 456, -300, 365, 148, -544, 96, -300, 10, 0, 879, -2, 6, 178, 100, 698, -800, 0, 2, 100
*/

#include <iostream>
#include <vector>

using namespace std;

/*
Complejidad computacional del Merge Sort: O(n log n)
*/

void merge(vector<double> &nums, int left, int middle, int right){

    // Primero sacamos el tamaño de los arreglos de cada respectivo lado, y declaramos su arreglo

    vector<double> leftT;
    vector<double> rightT;

    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    // Ahora los llenamos

    for(int i = 0; i < leftSize; i++){
        leftT.push_back(nums[left + i]);
    }
    
    for(int i = 0; i < rightSize; i++){
        rightT.push_back(nums[middle + 1 + i]);
    }

    int i = 0;
    int j = 0;
    int k = left;

    // Hacemos las comparaciones entre los dos lados, hasta acabar con un lado completo

    while(i < leftSize && j < rightSize){

        if(leftT[i] >= rightT[j]){

            nums[k] = leftT[i];
            i++;

        }
        else{

            nums[k] = rightT[j];
            j++;
            
        }

        k++;

    }

    // Tomamos el resto de los números del lado con números sobrantes

    while(i < leftSize){

        nums[k] = leftT[i];
        i++;
        k++;

    }

    while(j < rightSize){

        nums[k] = rightT[j];
        j++;
        k++;

    }

}

void mergeSort(vector<double> &nums, int left, int right){

    if(left < right){

        int middle = (left + right) / 2;

        mergeSort(nums, left, middle); // Lado izquierdo
        mergeSort(nums, middle + 1, right); // Lado derecho
        merge(nums, left, middle, right); // Mezcla

    }

}

int main(){

    int n;
    vector<double> nums;

    cout << "¿Cuántos números vas a ingresar?" << endl;
    cin >> n;
    cout << "\n";

    for(int i = 0; i < n; i++){

        double temp;
        cout << "Ingresa: ";
        cin >> temp;
        nums.push_back(temp);

    }

    mergeSort(nums, 0, nums.size() - 1);
    cout << "\nNúmeros ordenados:\n" << endl;

    for(int i = 0; i < nums.size(); i++){
        cout << nums[i] << endl;
    }

    return 0;

}