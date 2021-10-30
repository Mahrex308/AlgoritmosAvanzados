//Programado por LozanoSoft y DaduPro69 el 27 de octubre del 2021

#include <iostream>
#include <vector>

using namespace std;

// Complejidad computacional del Quick Sort: O(n log n)
void quickSort(vector<double> v, vector<double> &result){

  if(v.size() > 1){

    double pivot = v[0];
    int end = v.size() - 1, middle = end/2;
    vector<double> left, right;
    
    for(int i = 1; i <= end; i++)
      if(v[i] <= pivot) left.push_back(v[i]);
      else right.push_back(v[i]);

    // Vamos a la izquierda
    quickSort(left, result);
    
    // Intentamos insertar el vector de la izquierda
    if(left.size() == 1) result.insert(result.end(), left.begin(), left.end());
    
    // Insertamos el pivote
    result.push_back(pivot);

    // Vamos a la derecha
    quickSort(right, result);

    // Intentamos insertar el vector de la izquierda
    if(right.size() == 1) result.insert(result.end(), right.begin(), right.end());

  }
  
}

// Fin

int main(){

  int n;
  vector<double> nums;
  vector<double> result;

  cin >> n;
  cout << "\n";

  for(int i = 0; i < n; i++){

    double temp;
    cin >> temp;
    nums.push_back(temp);

  }

  quickSort(nums, result);
  cout << "\nNúmeros ordenados:\n" << endl;

  for(int i = 0; i < result.size(); i++){
    cout << result[i] << endl;
  }

  return 0;

}