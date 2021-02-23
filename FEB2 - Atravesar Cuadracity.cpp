
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge Moreno Martínez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const vector<pair<int, int>> dirs = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
#define INF 1000000000

bool valido(int i, int j, vector<string>& mapa) {
    int N = mapa.size();
    int M = mapa[0].size();
    return (
        i >= 0 && j >= 0 &&
        i < N&& j < M &&
        mapa[i][j] != 'P'
        );
}

int resolver(vector<string>& mapa) {
    int N = mapa.size();
    int M = mapa[0].length();

    Matriz<int> dist(N, M, INF);
    Matriz<int> ncam(N, M, 0);

    dist[0][0] = 0;
    ncam[0][0] = 1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (auto p : dirs) {
                int k = i + p.first, l = j + p.second;
                if (valido(k, l, mapa)) {
                    if (dist[k][l] == INF) {
                        dist[k][l] = dist[i][j] + 1;
                        ncam[k][l] = ncam[i][j];
                    }
                    else {
                        int newDist = dist[i][j] + 1;
                        if (dist[k][l] > newDist) {
                            dist[k][l] = newDist;
                            ncam[k][l] = ncam[i][j];
                        }
                        else if (dist[k][l] == newDist) {
                            ncam[k][l] += ncam[i][j];
                        }
                    }
                }
            
            }
        }
    }
    return ncam[N - 1][M - 1];
}

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int N, M;
    cin >> N >> M;
   
   if (!std::cin)  // fin de la entrada
      return false;
   
   vector<string> mapa(N);
   for (string& s : mapa) {
       cin >> s;
   }
   
   cout << resolver(mapa) << "\n";

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
