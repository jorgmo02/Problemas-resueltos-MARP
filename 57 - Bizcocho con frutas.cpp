
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge Moreno Martínez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"
using namespace std;

/*@ <answer>
  
 Programación dinámica descendente:
    Caso base:
        -No queda bizcocho (i >= j) -> 0 puntos
    Caso recursivo:
        -Tres posibilidades: comer por la izquierda, comer por la derecha o comer por ambos a la vez
                                A ambos se les suma la puntuacion de comer por cualquiera de los lados
        Puntos = max(izq, der, ambos)
    
    Coste: O(N^2) siendo N el tamaño del bizcocho

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int getPuntos(int i, int j, const vector<int>& bizcocho)
{
    if (i >= j) return 0;
    return ((bizcocho[i] != 0 && bizcocho[i] == bizcocho[j]) ? 1 : 0);
}

int resuelve(int i, int j, const vector<int>& bizcocho, Matriz<int>& mat)
{
    if (i >= j) return 0;
    
    if (mat[i][j] == -1)
    {
        int distintos = resuelve(i + 1, j - 1, bizcocho, mat) + getPuntos(i, j, bizcocho);
        int der = resuelve(i, j - 2, bizcocho, mat) + getPuntos(j, j - 1, bizcocho);
        int izq = resuelve(i + 2, j, bizcocho, mat) + getPuntos(i, i + 1, bizcocho);

        mat[i][j] = max(distintos, max(der, izq));
    }
    return mat[i][j];
}

int resuelve_aux(const vector<int>& bizcocho)
{
    int N = bizcocho.size();

    Matriz<int> mat(N, N, -1);
    int res = resuelve(0, N - 1, bizcocho, mat);
    return res;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;  cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> bizcocho(N);
    int aux;
    for (int i = 0; i < N; i++) {
        cin >> aux;
        bizcocho[i] = aux;
    }
    
    cout << resuelve_aux(bizcocho) << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
