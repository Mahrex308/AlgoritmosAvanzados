//Programado por LozanoSoft y DaduPro69 el 27 de octubre del 2021

/* AÚN NO ESTÁ TERMINADO */

#include <utility>
#include <iostream>
#include <vector>

using namespace std;

void printVec(vector<double> v){
  cout << "[";
  for(double i: v) cout << i << ", ";
  cout << "]\n";
}

// Complejidad computacional del Quick Sort: O(n log n)
void quickSort(vector<double> &v, int left, int right){

  printVec(v);

  if(left < right){ // 0 5

    // double pivot = v[left]; // 5
    // int k = left; // k0
    
    // for(int i = left + 1; i <= right; i++){ // 1

    //   if(v[i] <= pivot){ // 5 <= 5
    //     swap(v[k++], v[i]); // v[0] = 5, v[2] = 2
    //   }

    // }

    double pivot = v[left]; // 5
    int k = left, ultimo; // 2
    
    for(int i = left + 1; i <= right; i++){  // i = 3

      if(v[i] <= pivot){ // 5 <= 5
        swap(v[k++], v[i]); 
        if(v[i] == pivot) ultimo = i;
      }

    }
    
    if(v[k] > v[ultimo]) swap(v[k], v[ultimo]);

    quickSort(v, left, k - 1); // Vamos a la izquierda
    quickSort(v, k + 1, right); // Vamos a la derecha

  }
  
}

// Fin

int main(){

  int n;
  vector<double> nums;

  cin >> n;

  for(int i = 0; i < n; i++){

    double temp;
    cin >> temp;
    nums.push_back(temp);

  }

  quickSort(nums, 0, nums.size() - 1);
  cout << "\nNúmeros ordenados:\n" << endl;

  for(int i = 0; i < nums.size(); i++){
    cout << nums[i] << endl;
  }

  return 0;

}