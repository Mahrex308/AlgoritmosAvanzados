/*
-------------------------------------------------------------------------------------------------
Actividad 1.3 Implementación de la técnica de programación "backtracking" y "ramificación y poda"
-------------------------------------------------------------------------------------------------

Autor: Ezequiel Lozano Guerrero
Matrícula: A01734172

Autor: Diego Andrés Moreno Molina
Matrícula: A01283790    

Fecha de creación: 26/08/2021
*/

/*
Casos de prueba:

1)
4
4
1 0 0 1
1 0 1 1
1 0 0 0
1 1 1 1

2)
4
4
1 0 0 0
1 1 0 1
0 1 0 0
1 1 1 1

3)
4
4
1 0 0 0
1 1 1 0
1 0 1 0
0 0 1 1

4)
10
10
1 0 0 0 1 1 1 0 1 0
1 1 1 0 0 1 1 1 0 0
1 0 1 0 1 1 1 0 0 0
0 0 1 1 0 0 0 1 1 1
0 1 0 1 1 1 1 1 1 1
0 0 0 0 0 1 0 0 0 1
1 0 0 1 1 1 1 1 1 1
1 0 1 1 1 0 1 1 1 1
1 0 1 0 0 0 1 0 0 1
0 0 1 1 1 1 1 1 1 1
*/

#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

// En el peor caso puede ser O(n*m) ya que podria llegar a checar todas las casillas
bool BackTracking(int row, int col, vector<vector<int>> laberinto, vector<pair<int,int>> &posicionesFinales){

  //Establecemos dos banderas que nos indican si la posicion en la que nos encontramos es la final. 
  bool finalRow = (row == laberinto.size()-1);
  bool finalCol  = (col == laberinto[row].size()-1);

  if (finalRow && finalCol){

    //Añadimos a nuestro vector de posiciones finales la posición actual. 
    posicionesFinales.push_back(make_pair(row, col));

    return true;

  }

  //En caso de que no hayamos llegado al final, establecemos la posición actual como 0 para determinar que hemos visitado esta posición. 
  laberinto[row][col] = 0;

  //Establecemos un vector que nos indica todas las posiciones que podemos tomar.
  vector<pair<int,int>> directions = {{-1,0}, {1,0}, {0, -1}, {0, 1}};

  for (pair<int,int> direction : directions){

    int newRow = row + direction.first;
    int newCol = col + direction.second;

    //Validamos que ambos elementos se encuentren dentro de los límites de la matriz. 
    bool validRow = newRow >= 0 && newRow < laberinto.size();
    bool validCol = newCol >= 0  && newCol < laberinto[row].size();
    
    if (validRow && validCol){

      //Establecemos una bandera que nos indica si el elemento aledaño es un 0
      bool isZero = laberinto[newRow][newCol] == 0;

      //Si no es un 0, significa que es un elemento 1 y por lo tanto es un camino viable. 
      if(!isZero){
        
        bool result = BackTracking(newRow, newCol, laberinto, posicionesFinales);

        //Si result es verdadero, significa que encontramos un camino que nos llevó hasta el final de la matriz.
        if(result){

          posicionesFinales.push_back(make_pair(row, col));
          return result;

        }

      }

    }

  }
  
  return false;

}

//Funcion que coloca el camino más optimo en una matriz espejo llena de 0
void SetFinalMatrix(vector<vector<int>> &matrix, vector<pair<int,int>> posicionesFinales){

  for(pair<int, int>posicion : posicionesFinales)
    matrix[posicion.first][posicion.second] = 1; // Se llena de 1 las posiciones correspondientes al camino correcto

}

// Función que por medio del algoritmo de ramificación y poda encuentra la matriz que resuelve el laberinto empleando un BFS
// En el peor caso puede ser O(n*m) ya que podria llegar a checar todas las casillas
vector<vector<int>> ramificacionPoda(vector<vector<int>> laberinto){

  // A través de una cola, vamos ejecutando el algoritmo BFS y guardando las posiciones en donde hay 1
  // Esta cola guarda pares que contienen la posición de dicho 1 y el vector de posiciones que se 
  // recorrió para llegar a él
  
  queue<pair<pair<int, int>, vector<pair<int, int>>>> recorridos;
  vector<pair<int, int>> tmp = {{0,0}};

  recorridos.push(make_pair(make_pair(0,0), tmp));
  pair<pair<int, int>, vector<pair<int, int>>> posActual; 

  int i = 0, j = 0, colSize = laberinto.size(), rowSize = laberinto[0].size();

  while(!recorridos.empty()){ // Mientras haya elementos en la cola, se ejecuta el ciclo

    posActual = recorridos.front();
    i = posActual.first.first; j = posActual.first.second;

    // Verificamos si la posición actual es la esquina inferior derecha de nuestra matriz
    // En caso de que sí, creamos nuestra matriz que representa el recorrido que hizo el 
    // algoritmo para llegar a la meta 

    if(i == colSize-1 && j == rowSize-1){

      vector<vector<int>> resultado(colSize, vector<int> (rowSize, 0)); // Creamos una matriz con 0s
      SetFinalMatrix(resultado, posActual.second); // Insertamos en la matriz de 0s el recorrido para salir del laberinto
      return resultado;

    }

    // Derecha
    if(j+1 < rowSize && laberinto[i][j+1]){

      // Declaramos a nuestro vector temporal como el recorrido que nos permitió llegar a la posición actual
      tmp = posActual.second;
      tmp.push_back({make_pair(i, j+1)}); // Insertamos en el vector temporal la posición actual
      recorridos.push(make_pair(make_pair(i, j+1), tmp)); // Insertamos en la cola la posición y su vector de recorrido

    }

    // Abajo
    if(i+1 < colSize && laberinto[i+1][j]){
      
      tmp = posActual.second;
      tmp.push_back({make_pair(i+1, j)});
      recorridos.push(make_pair(make_pair(i+1, j), tmp));

    }

    // Izquierda
    if(j-1 >= 0 && laberinto[i][j-1]){

      tmp = posActual.second;
      tmp.push_back({make_pair(i, j-1)});
      recorridos.push(make_pair(make_pair(i, j-1), tmp));

    }

    // Arriba
    if(i-1 >= 0 && laberinto[i-1][j]){
      
      tmp = posActual.second;
      tmp.push_back({make_pair(i-1, j)});
      recorridos.push(make_pair(make_pair(i-1, j), tmp));

    }

    laberinto[i][j] = 0; // Marcamos la posición actual como 0 para no volverla a recorrer
    recorridos.pop(); // Eliminamos de la cola la posición en la que estábamos

  }

  // En el caso de que no encontremos un recorrido que nos permita llegar al final del laberinto
  // regresamos una matriz con puros 0
  return vector<vector<int>>(colSize, vector<int>(rowSize, 0));

}

int main(){

  int m = 0;
  int n = 0;
  int value = 0; // valor a ingresar a la matriz

  cout << "Ingresa la cantidad de filas: ";
  cin >> m;

  //validación de las entradas de n y m

  while(m <= 0) {

    cout << "Ingrese un numero valido" << endl;
    cin >> m;

  }
  
  cout << "\nIngresa la cantidad de columnas: ";
  cin >> n;

  while(n <= 0) {

    cout << "Ingrese un numero valido" << endl;
    cin >> n;

  }

  vector<vector<int>> maze;
  vector<int> tmp;

  // validacion de entradas

  for(int i=0; i<m; i++){

    tmp.clear();

    for(int j=0; j<n; j++){

      cin >> value;
      if(value == 0 || value == 1) tmp.push_back(value);
      else i--;

    }

    maze.push_back(tmp);

  }

  // Creamos un vector con 0's
  vector<vector<int>> mazeBacktrack(m, vector<int> (n, 0));
  
  // Si la matriz de entrada tiene en su primer elemento (0, 0) o 
  // último elemento (M-1, N-1) un 0, no hay solución

  if(!maze[0][0] || !maze[m-1][n-1]) {

    cout << "El laberinto no tiene solución\n";
    return 0;

  }
  
  //se crea un vector de pares para guardar las posiciones a obtener del backtrack
  vector<pair<int,int>> posicionesBacktrack;
  bool backtrack = BackTracking(0, 0, maze, posicionesBacktrack);

  //vaciado de las posiciones obtenidas en una matriz inicializada con 0s 
  SetFinalMatrix(mazeBacktrack, posicionesBacktrack);
  cout << "Resultado con backtracking:\n";

  for(int i = 0; i < m; i++){

    for (int j = 0; j < n; j++)
      cout << mazeBacktrack[i][j] << " ";

    cout << endl;

  }

  //se pasa el laberinto original como referencia al método ramificación y poda
  maze = ramificacionPoda(maze);
  cout << "\nResultado con ramificación y poda: \n";
  
  for(int i = 0; i < m; i++){

    for (int j = 0; j < n; j++)
      cout << maze[i][j] << " ";

    cout << endl;

  }

  return 0;

}