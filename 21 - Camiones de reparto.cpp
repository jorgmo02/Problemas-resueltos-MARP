#include <iostream>
#include <fstream>
#include "GrafoValorado.h"

class Solucion {
private:
    std::vector<bool> visit;
    GrafoValorado<int> gv;

public:
    Solucion(GrafoValorado<int>& grafo) :
        gv(grafo),
        visit(grafo.V(), false) { }

    void dfs(int v, const int peso, const int fin) {
        visit[v] = true;
        if (v == fin) return;
        for (auto a : gv.ady(v)) {
            if (a.valor() >= peso) {
                int w = a.otro(v);
                if (!visit[w])
                    dfs(w, peso, fin);
            }
        }
    }

    void reset() { visit = std::vector<bool>(visit.size(), false); }

    bool canGo(int i) const { return visit[i]; };

};

bool resuelveCaso() {

    int V, E, K;
    std::cin >> V >> E;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> gv(V);

    for (int i = 0; i < E; i++) {
        int v, w, valor;
        std::cin >> v >> w >> valor;
        gv.ponArista({ v - 1, w - 1, valor });
    }

    Solucion sol(gv);
    std::cin >> K;
    for (int i = 0; i < K; i++) {
        int ini, fin, peso;
        std::cin >> ini >> fin >> peso;
        ini--; fin--;
        sol.dfs(ini, peso, fin);
        std::cout << ((sol.canGo(fin)) ? "SI\n" : "NO\n");
        sol.reset();
    }

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
