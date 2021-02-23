
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

#define INF 1000000000

class Dijkstra {
public:
    Dijkstra(DigrafoValorado<int> const& g, int orig) : origen(orig),
        dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    int distancia(int v) const { return dist[v]; }

private:
    int origen;
    std::vector<int> dist;
    IndexPQ<int> pq;
    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada

    int N, S, T, P;
    cin >> N >> S >> T >> P;
    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> g(N);
    int v, w, t;
    for (int i = 0; i < P; i++) {
        cin >> v >> w >> t;
        g.ponArista({ w - 1, v - 1, t });
    }

    S--;
    Dijkstra d(g, S);

    int nratones = 0;
    for (int i = 0; i < N; i++) {
        if (i != S) {
            if (d.hayCamino(i) && d.distancia(i) <= T) {
                nratones++;
            }
        }
    }

    cout << nratones << "\n";
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
