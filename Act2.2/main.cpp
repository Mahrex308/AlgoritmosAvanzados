/*
-----------------------
Actividad 2.2 Implementación de "Sufix Array"
-----------------------

Autor: Ezequiel Lozano Guerrero
Matrícula: A01734172

Autor: Diego Andrés Moreno Molina
Matrícula: A01283790    

Fecha de creación: 12/09/2021
*/

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;


int main() {
  string n;
  cout << "Ingresa el string: ";
  cin >> n;
  
  vector<string> suffixes; 

  for(int i =n.size(); i >= 0 ; i--){
    suffixes.push_back(n.substr(i, n.size()));
  }

  sort(suffixes.begin(), suffixes.end());

  for(int i =0; i < suffixes.size(); i++){
      cout<< suffixes[i] << endl;
  }

}