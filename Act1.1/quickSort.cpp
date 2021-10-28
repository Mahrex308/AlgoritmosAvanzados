//Programado por LozanoSoft y DaduPro69 el 27 de octubre del 2021

#include <iostream>
#include <vector>

using namespace std;

void printVect(vector<double> v){
  cout << "[";
  for(double i: v) cout << i << ", ";
  cout << "]\n"; 
}

// Complejidad computacional del Quick Sort: O(n log n)
void quickSort(vector<double> v, vector<double> &result){

  if(v.size() > 1){ // 0 < 13

    double pivot = v[0]; // 8
    int end = v.size()-1; // 12
    int middle = end/2; // 6
    vector<double> left;
    vector<double> right;
    
    for(int i = 1; i <= end; i++){

      if(v[i] <= pivot){
        left.push_back(v[i]); // 1 5 4 6 2 7
      }
      else{
        right.push_back(v[i]); // 14 15 12 11 10 9
      }

    }

    // Vamos a la izquierda
    quickSort(left, result);
    
    // Intentamos insertar el vector de la izquierda
    if(left.size() == 1){ 
      result.insert(result.end(), left.begin(), left.end()); // 1 x
    }

    cout << "left" << endl;
    if(result.size() > 0) printVect(result);
    
    // Insertamos el pivote
    result.push_back(pivot);

    cout << "pivot" << endl;
    if(result.size() > 0) printVect(result);
    
    // Vamos a la derecha
    quickSort(right, result);

    // Intentamos insertar el vector de la izquierda
    if(right.size() == 1){
      result.insert(result.end(), right.begin(), right.end()); // 5
    }

    cout << "right" << endl;
    if(result.size() > 0) printVect(result);
  
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