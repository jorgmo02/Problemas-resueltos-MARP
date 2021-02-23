
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
  
 Casos base:
    - No quedan cortes (j <= i + 1) -> esfuerzo = 0
 
 Casos recursivos:
    - Esfuerzo = minimo entre cortes
        donde cada corte = corte por la izquierda + corte por la derecha + esfuerzo de corte

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

#define INFINITO 1000000000

// i, j = rango de corte actual
int cortar(int i, int j, Matriz<int>& mat, const vector<int>& cortes)
{
    if (i + 1 >= j) return 0;

    if (mat[i][j] == -1)
    {
        int L = cortes[j] - cortes[i];
        int esfuerzo = 2 * L;

        int minCorte = INFINITO;
        for (int k = i + 1; k < j; k++)
            minCorte = min(minCorte, esfuerzo + cortar(i, k, mat, cortes) + cortar(k, j, mat, cortes));

        mat[i][j] = minCorte;
    }
    return mat[i][j];
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int L, N;
    cin >> L >> N;
    if (L == 0 && N == 0)
        return false;

    vector<int> cortes(N + 2);
    int aux;
    cortes[0] = 0;
    cortes[N + 1] = L;
    for (int i = 1; i <= N; ++i) {
        cin >> aux;
        cortes[i] = aux;
    }

    Matriz<int> mat(N + 2, N + 2, -1);
    int res = cortar(0, N + 1, mat, cortes);
    
    std::cout << res << "\n";
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
