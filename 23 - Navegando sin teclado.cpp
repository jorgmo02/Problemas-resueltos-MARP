#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include <deque>
#include "IndexPQ.h"

using Camino = std::deque<AristaDirigida<int>>;

class Dijkstra {
private:
    const int INF = 100000000000;
    int origen;
    std::vector<int> dist;
    std::vector<AristaDirigida<int>> ult;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ult[w] = a;
            pq.update(w, dist[w]);
        }
    }

public:
    Dijkstra(DigrafoValorado<int> const& g, int orig) : origen(orig),
        dist(g.V(), INF), ult(g.V()), pq(g.V())
    {
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
    Camino camino(int v) const {
        Camino cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<int> a;
        for (a = ult[v]; a.desde() != origen; a = ult[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }
};

bool resuelveCaso() {

    int N;
    std::cin >> N;

    if (N == 0)
        return false;

    DigrafoValorado<int> dgv(N);
    std::vector<int> tiemposCarga;
    for (int i = 0; i < N; i++) {
        int t;  std::cin >> t;
        tiemposCarga.push_back(t);
    }
    int M;
    std::cin >> M;
    for (int i = 0; i < M; i++) {
        int v, w, t;
        std::cin >> v >> w >> t;
        v--; w--;
        dgv.ponArista({ v, w, t + tiemposCarga[w] });
    }

    Dijkstra dij(dgv, 0);

    if (dij.hayCamino(N - 1))
        std::cout << tiemposCarga[0] + dij.distancia(N - 1) << "\n";
    else std::cout << "IMPOSIBLE\n";

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
