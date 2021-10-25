/*
------------------------------------------------------------------------------
Avance actividad 3.1  Implementación de "Tries"
------------------------------------------------------------------------------
**Para que funcione el programa deben de ser puras minusculas

Autor: Ezequiel Lozano Guerrero
Matrícula: A01734172

Autor: Diego Andrés Moreno Molina
Matrícula: A01283790    

Fecha de creación: 9/9/2021
*/
#include <iostream>
#include <string>
#include <vector>
#include <string>

using namespace std;

//Creamos el nodo de la cual estara hecha nuestro TRIE
struct node
{
    //cada nodo puede apuntar a 26 letras diferentes del alfabeto
    struct node *children[26];
 
    //nos sirve para saber si es el endal de una palabra 
    bool end;
};
 
// Retorna un nuevo nodo del Trie
struct node *newNode(void)
{
    struct node *newNodo =  new node;
 
    newNodo->end = false;
 
    for (int i = 0; i < 26; i++){
        newNodo->children[i] = NULL;
    }
 
    return newNodo;
}
 
// Inserta si no esta presente, o si el elemento es prefijo de una palabra, marcar que es una palabra tambien
void insert(struct node *root, string key)
{
    struct node *tempNodo = root;
 
    //recorremos por la longitud de la palabra
    for (int i = 0; i < key.length(); i++)
    {
        //Checamos si tiene esa letra como hijo, y si no insertamos un nuevo nodo
        int index = key[i] - 'a';
        if (!tempNodo->children[index])
            tempNodo->children[index] = newNode();
 
        tempNodo = tempNodo->children[index];
    }
 
    //Marcamos el ultimo nodo como end de la palabra
    tempNodo->end = true;
}


//buscamos si esta la palabra en el arbol
bool search(struct node *root, string key)
{
    struct node *temp = root;
    int length = 0;
    for (int i = 0; i < key.length(); i++)
    {
        
        int index = key[i] - 'a';
        if (!temp->children[index])
            return false;
 
        temp = temp->children[index];
        length++;
    }

    if(temp->end || key.length() == length){
      return true;
    }
    else{
      return false;
    }
}

void printTrie(struct node* root, char str[], int level)
{
    //vamos imprimiendo como recorre el arbol
    cout << str << endl;
    // Si el nodo esta en el final de palabra, la imprimimos.
    if (root->end) 
    {
        str[level] = '\0';
        cout << endl << "Palabra completa:" << str << endl << endl;
    }
  
    for (int i = 0; i < 26; i++) 
    {
        // Recorremos las 26 letras posibles, que puede tener de hijo.
        // Si encontramos un valor no nulo, significa que es el inicio de otra palabra
        //y la recorreremos esa rama completa llamando recursivamente la funcion
        if (root->children[i]) 
        {
            str[level] = i + 'a';
            printTrie(root->children[i], str, level + 1);
        }
    }
}

int main()
{
  int n;
  cout << "Cuantas palabras quieres insertar al Trie?" << endl;
  cin >> n;
  vector<string> elementos;
  for(int i=0; i < n; i++){
    string palabra;
    cin >> palabra;
    elementos.push_back(palabra);
  }
  
  //Creamos el nodo que será nuestra raiz
  struct node *root = newNode();

  // Construimos el TRIE
  for (int i = 0; i < n; i++){
    insert(root, elementos[i]);
  }

  string m;

  cout << "Que palabra deseas buscar en el Trie?";
  cin >> m;
  search(root, m)? cout << "True\n" : cout << "False\n";
  
  
  int level = 0;
  char str[26];
  // Contenido del Trie
  cout << endl << "Trie Completo: " << endl;
  printTrie(root, str, level);

  return 0;
    
}

