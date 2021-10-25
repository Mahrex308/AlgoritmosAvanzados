/*
-----------------------
Actividad Integradora 1
-----------------------

Autor: Ezequiel Lozano Guerrero
Matrícula: A01734172

Autor: Diego Andrés Moreno Molina
Matrícula: A01283790

Fecha de creación: 12/09/2021
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// ----------------------------------------------------------------------------------
// Función que encuentra el substring más largo entre los dos archivos de transmisión
// ----------------------------------------------------------------------------------
// Complejidad computacional: O(n*m)

void searchLCS(string t1, string t2){

  int rows = t1.length();
  int cols = t2.length();

  vector<vector<int>> dp(rows, vector<int>(cols, 0));

  int m = 0;
  int endingIndex = rows;

  for(int i = 1; i < rows; i++){

    for(int j = 1; j < cols; j++){

      if(t1[i] == t2[j]){ // Si son iguales, le sumamos 1 más lo que está en la diagonal de abajo (la suma de lo que lleva el substring)
          
        dp[i][j] = dp[i-1][j-1] + 1;
        
        // Actualiza la longitud máxima y el índice final
        if(dp[i][j] > m){

          m = dp[i][j];
          endingIndex = i;

        }

      }
      else{
        dp[i][j] = 0;
      }

    }

  }

  if(endingIndex < rows){
    
    // Impresión de los índices del substring común más largo entre transmission1.txt y transmission2.txt
    cout << endingIndex - m + 2 << " " << endingIndex + 1 << endl;

    // Impresión del substring común más largo entre transmission1.txt y transmission2.txt
    cout << t1.substr(endingIndex - m + 1, m) << endl;

  }
  else{
    cout << "No hay coincidencias entre ambas transmisiones" << endl;
  }

}

// ---
// Fin
// ---

// ---------------------------------------------------------------------------------
// Función auxiliar que ocupa el manacher para obtener el menor valor de dos números
// ---------------------------------------------------------------------------------
// Complejidad computacional: O(1)

int min(int a, int b){

    int res = a;

    if(b < a){
      res = b;
    }

    return res;

}

// ---
// Fin
// ---

// --------------------------------------------------------
// Función que aplica el algoritmo manacher, para encontrar
// el palíndromo más largo en cada cadena de transmisión
// --------------------------------------------------------
// Complejidad computacional: O(n)

void searchManacher(string text){

  int N = text.size();

  if(N == 0)
    return;
    
  N = 2*N + 1; // Contador de posiciones
  int L[N]; // Arreglo para el manacher
  L[0] = 0;
  L[1] = 1;
  int C = 1; // Posición central
  int R = 2; // Posición central derecha
  int i = 0; // Posición derecha actual
  int iMirror; // Posición izquierda actual
  int maxLPSLength = 0;
  int maxLPSCenterPosition = 0;
  int start = -1;
  int end = -1;
  int diff = -1;
    
  for(i = 2; i < N; i++){

    // Obtiene la posición izquierda actual 'iMirror' para la posición derecha actual 'i'
    iMirror = 2*C - i;
    L[i] = 0;
    diff = R - i;
    
    // Si la posición derecha actual 'i' está dentro de la posición central derecha 'R'
    if(diff > 0){
      L[i] = min(L[iMirror], diff);
    }

    // Se expande el palíndromo centrado en la posición derecha actual 'i'.
    // Para posiciones impares, se comparan caracteres y si coinciden,
    // se incrementa la longitud del manacher en 1; Si la posición es par,
    // se incrementa el manacher en 1 también, pero sin ninguna comparación de caracteres.

    while(((i + L[i]) < N && (i - L[i]) > 0) && (((i + L[i] + 1) % 2 == 0) || (text[(i + L[i] + 1) / 2] == text[(i - L[i] - 1)/2]))){
      L[i]++;
    }

    if(L[i] > maxLPSLength){ // Si el valor de L[i] es mayor a maxLPSLength

      maxLPSLength = L[i];
      maxLPSCenterPosition = i;

    }

    // Si el palíndromo está centrado en la posición derecha actual 'i',
    // se expande la posición central derecha 'R', y se
    // ajusta la posición central 'C' basada en el palíndromo.

    if(i + L[i] > R){

      C = i;
      R = i + L[i];

    }
    
  }

  start = (maxLPSCenterPosition - maxLPSLength) / 2;
  end = start + maxLPSLength - 1;

  if(end == -1){
    end++;
  }
  
  // Impresión de los índices de inicio y fin del palíndromo más largo (comenzando en 1)
  cout << (start + 1) << " " << (end + 1) << endl;
  
  // Impresión del palíndromo más largo
  for(i = start; i <= end; i++)
    cout << text[i];
  cout << "\n";

}

// ---
// Fin
// ---

// -----------------------------------------------------
// Función que aplica el algoritmo KMP, para determinar 
// si el mcodeY.txt se encuentra en el transmissionX.txt
// -----------------------------------------------------
// Complejidad computacional: O(n)

vector<int> searchKMP(string pat, string txt){

  vector<int> v;

  for(int i = 0; i < txt.length(); i++){
        
    if(txt[i] == pat[0] && txt.substr(i, pat.length()) == pat){ // Comprueba si el patrón está en el texto completo

      v.push_back(i); // Se ingresa el índice inicial de la coincidencia al vector
      v.push_back(i + pat.length() - 1); // Se ingresa el índice final de la coincidencia al vector

    }

  }

  if(v.empty()) v.push_back(-1); // Si no encontró ni una vez el patrón en el texto completo
  return v;

}

// ---
// Fin
// ---

// -----------------------------------------------------------------
// Función que convierte el contenido de un archivo .txt a un string
// -----------------------------------------------------------------
// Complejidad computacional: O(n)

string readTxt(string fileName){

  string fullTxt = "";
  string current;
  fstream file;

  file.open(fileName.c_str());

  // Lee renglón por renglón

  while(getline(file, current)){
    fullTxt += current + '\n';
  }

  fullTxt = fullTxt.substr(0, fullTxt.length() - 1);
  return fullTxt;

}

// ---
// Fin
// ---

int main(){

  // Convertimos los archivos en strings con la función readTxt
  
  string mcode1 = readTxt("mcode1.txt");
  string mcode2 = readTxt("mcode2.txt");
  string mcode3 = readTxt("mcode3.txt");
  string transmission1 = readTxt("transmission1.txt");
  string transmission2 = readTxt("transmission2.txt");

  // Parte 1

  cout << "-------" << endl;
  cout << "Parte 1" << endl;
  cout << "-------\n" << endl;
  cout << "Formato:" << endl;
  cout << "- true|false índiceInicio índiceFinal (el índice comienza desde CERO)\n" << endl;

  if(searchKMP(mcode1, transmission1)[0] == -1) cout << "false" << endl;
  else cout << "true " << searchKMP(mcode1, transmission1)[0] << " " << searchKMP(mcode1, transmission1)[1] << endl;

  if(searchKMP(mcode2, transmission1)[0] == -1) cout << "false" << endl;
  else cout << "true " << searchKMP(mcode2, transmission1)[0] << " " << searchKMP(mcode2, transmission1)[1] << endl;

  if(searchKMP(mcode3, transmission1)[0] == -1) cout << "false" << endl;
  else cout << "true " << searchKMP(mcode3, transmission1)[0] << " " << searchKMP(mcode3, transmission1)[1] << endl;

  if(searchKMP(mcode1, transmission2)[0] == -1) cout << "false" << endl;
  else cout << "true " << searchKMP(mcode1, transmission2)[0] << " " << searchKMP(mcode1, transmission2)[1] << endl;

  if(searchKMP(mcode2, transmission2)[0] == -1) cout << "false" << endl;
  else cout << "true " << searchKMP(mcode2, transmission2)[0] << " " << searchKMP(mcode2, transmission2)[1] << endl;

  if(searchKMP(mcode3, transmission2)[0] == -1) cout << "false" << endl;
  else cout << "true " << searchKMP(mcode3, transmission2)[0] << " " << searchKMP(mcode3, transmission2)[1] << endl;

  cout << "\n---" << endl;
  cout << "Fin" << endl;
  cout << "---\n" << endl;

  // Fin

  // Parte 2

  cout << "-------" << endl;
  cout << "Parte 2" << endl;
  cout << "-------\n" << endl;
  cout << "Formato:" << endl;
  cout << "- índiceInicio índiceFinal (el índice comienza desde UNO)" << endl;
  cout << "- Palíndromo más largo\n" << endl;

  searchManacher(transmission1);
  searchManacher(transmission2);

  cout << "\n---" << endl;
  cout << "Fin" << endl;
  cout << "---\n" << endl;

  // Fin

  // Parte 3

  cout << "-------" << endl;
  cout << "Parte 3" << endl;
  cout << "-------\n" << endl;
  cout << "Formato:" << endl;
  cout << "- índiceInicio índiceFinal (el índice comienza desde UNO)" << endl;
  cout << "- Substring común más largo\n" << endl;

  searchLCS(transmission1, transmission2);

  cout << "\n---" << endl;
  cout << "Fin" << endl;
  cout << "---" << endl;

  // Fin

  return 0;

}