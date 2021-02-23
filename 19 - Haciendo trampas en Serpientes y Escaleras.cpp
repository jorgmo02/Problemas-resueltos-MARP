#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using Tablero = std::vector<int>;

int adyacente(Tablero& tablero, int i, int nodo) {
    int pos = nodo + i;
    if (pos >= tablero.size()) return -1;
    if (tablero[pos] == -1) return pos;
    return tablero[pos];
}

class BFSescalera {
    std::vector<bool> visit;
    std::vector<int> dist;
    int caras;
    int numTiradas;

public:
    BFSescalera(Tablero& tablero, int K) :
        visit(tablero.size(), false),
        dist(tablero.size()),
        caras(K)
    {
        numTiradas = bfs(tablero);
    }

    int bfs(Tablero& tablero) {
        std::queue<int> q;
        visit[0] = true;
        dist[0] = 0;
        q.push(0);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = 1; i <= caras; i++) {
                int w = adyacente(tablero, i, v);
                if (w != -1 && !visit[w]) {                                         // tirada válida a una casilla no visitada  
                    visit[w] = true;
                    dist[w] = dist[v] + 1;
                    if (w == (tablero.size() - 1)) return dist[w];                     // llegamos a la última casilla
                    else q.push(w);
                }
            }
        }
    }

    int getTiradas() const { return numTiradas; };

};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int N, K, S, E;
    std::cin >> N >> K >> S >> E;

    if (N == 0) return false;

    Tablero tablero(N * N, -1);

    for (int i = 0; i < S + E; i++) {
        int casilla, next;
        std::cin >> casilla >> next;
        tablero[casilla - 1] = next - 1;
    }

    BFSescalera b(tablero, K);

    std::cout << b.getTiradas() << "\n";

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
