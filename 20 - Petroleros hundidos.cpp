#include <iostream>
#include <fstream>
#include <vector>
#include "ConjuntosDisjuntos.h"

using Tablero = std::vector<std::vector<bool>>;

class MaximaMancha {
    const std::vector<std::pair<int, int>> dirs = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

private:
    Tablero visit;
    Tablero tab;
    ConjuntosDisjuntos conj;

    int F, C;
    int max;

    bool correct(int fil, int col) {
        return
            fil >= 0 && fil < F&&
            col >= 0 && col < C;
    }

    int coorToPos(int fil, int col) {
        return C * fil + col;
    }

    int dfs(Tablero const& t, int fil, int col) {
        int newMancha = 1;
        visit[fil][col] = true;
        for (auto ady : dirs) {
            int i = fil + ady.first;                  // fil del adyacente
            int j = col + ady.second;                 // col del adyacente
            if (correct(i, j) && tab[i][j] && !visit[i][j]) {       // está dentro y es una mancha
                conj.unir(coorToPos(fil, col), coorToPos(i, j));    // unimos las dos manchas
                newMancha += dfs(t, i, j);
            }
        }
        return newMancha;
    }

public:
    MaximaMancha(int fils, int cols) :
        visit(fils, std::vector<bool>(cols, false)),
        tab(fils, std::vector<bool>(cols)),
        F(fils), C(cols),
        conj(fils* cols),
        max(0)
    {
        std::cin.get();
        for (int i = 0; i < F; i++) {
            for (int j = 0; j < C; j++) {
                tab[i][j] = (std::cin.get() == '#');
            }
            std::cin.get();
        }

        for (int i = 0; i < F; i++) {
            for (int j = 0; j < C; j++) {
                if (tab[i][j] && !visit[i][j]) {
                    int newMax = dfs(tab, i, j);
                    if (newMax > max) max = newMax;
                }
            }
        }
    }

    void unir(int fil, int col) {
        if (!tab[fil][col]) {
            tab[fil][col] = true;
            for (auto ady : dirs) {
                int i = fil + ady.first;                  // fil del adyacente
                int j = col + ady.second;                 // col del adyacente
                if (correct(i, j) && tab[i][j]) {       // está dentro y es una mancha
                    conj.unir(coorToPos(fil, col), coorToPos(i, j));    // unimos las dos manchas
                }
            }
            int newMax = conj.cardinal(coorToPos(fil, col));
            if (newMax > max) max = newMax;
        }
    }

    int tamMancha() const { return max; }
};

bool resuelveCaso() {

    int F, C;
    std::cin >> F >> C;
    if (!std::cin) return false;

    MaximaMancha m(F, C);

    std::cout << m.tamMancha();

    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        int f, c;
        std::cin >> f >> c;
        m.unir(f - 1, c - 1);

        std::cout << " " << m.tamMancha();
    }

    std::cout << "\n";

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
