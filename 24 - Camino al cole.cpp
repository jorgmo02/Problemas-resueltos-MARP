#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include <deque>
#include "IndexPQ.h"

class Dijkstra
{
    const int INF = 1000000000;
private:
    std::vector<int> distHasta;           // la longitud minima hasta el vertice
    std::vector<int> caminosHasta;        // el numero de caminos hasta el vertice
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        int distActual = distHasta[v] + a.valor();
        if (distHasta[w] >= distActual)
        {
            if (distHasta[w] > distActual) {
                distHasta[w] = distActual;
                caminosHasta[w] = 0;
            }
            caminosHasta[w] += caminosHasta[v];
            pq.update(w, distHasta[w]);
        }
    }

public:
    Dijkstra(DigrafoValorado<int> const& g) :
        distHasta(g.V(), INF),
        pq(g.V()),
        caminosHasta(g.V(), 0)
    {
        distHasta[0] = 0;
        caminosHasta[0] = 1;
        pq.push(0, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    bool hayCamino(int v) const { return distHasta[v] != INF; }
    int distancia(int v) const { return distHasta[v]; }
    int numCaminos(int v) const { return caminosHasta[v]; }
};

bool resuelveCaso() {

    int N, C;
    std::cin >> N >> C;

    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> dgv(N);

    for (int i = 0; i < C; i++) {
        int v, w, valor;
        std::cin >> v >> w >> valor;
        dgv.ponArista({ v - 1, w - 1, valor });
        dgv.ponArista({ w - 1, v - 1, valor });
    }

    Dijkstra sol(dgv);

    std::cout << sol.numCaminos(N - 1) << "\n";

    return true;
}

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
