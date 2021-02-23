#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <string>
#include <limits>

const int INF = std::numeric_limits<int>::max();
class Dijkstra {
private:
    int origen;
    std::vector<int> dist;
    std::vector<AristaDirigida<int>> ulti;
    IndexPQ<int> pq;
    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }

public:
    Dijkstra(DigrafoValorado<int> const& g, int orig) : origen(orig),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
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
};

bool resuelveCaso() {

    int N, C;
    std::cin >> N >> C;

    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> g(N);
    for (int i = 0; i < C; i++) {
        int v, w, coste;
        std::cin >> v >> w >> coste;
        g.ponArista({ v - 1, w - 1, coste });
    }

    int O, P;
    std::cin >> O >> P;
    O--;
    Dijkstra d(g, O);
    Dijkstra vuelta(g.inverso(), O);
    int res = 0;
    bool imp = false;
    for (int i = 0; i < P; i++)
    {
        int casa; std::cin >> casa;
        if (!imp) {
            casa--;
            imp = !d.hayCamino(casa) || !vuelta.hayCamino(casa);
            res += d.distancia(casa);
            res += vuelta.distancia(casa);
        }
    }

    std::cout << ((!imp) ? std::to_string(res) : "Imposible") << "\n";

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
