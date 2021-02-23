#include <iostream>
#include <fstream>
#include <algorithm>
#include "Matriz.h"
#include <stack>

struct Tesoro
{
    int profundidad;
    int oro;
};

std::ostream& operator<<(std::ostream& os, const Tesoro& tesoro) {
    os << (tesoro.profundidad / 3) << " " << tesoro.oro << "\n";
    return os;
}

int resolver(const std::vector<Tesoro>& cofres, Matriz<int>& resultados, int i, int j)
{
    if (resultados[i][j] == -1) {
        if (i == 0 || j == 0) resultados[i][j] = 0;
        else if (cofres[i-1].profundidad > j) {
            resultados[i][j] = resolver(cofres, resultados, i-1, j);
        }
        else {
            resultados[i][j] = std::max(resolver(cofres, resultados, i - 1, j),
                                        resolver(cofres, resultados, i - 1, j - cofres[i-1].profundidad) + cofres[i-1].oro);
        }
    }
    return resultados[i][j];
}

bool resuelveCaso() {

    int T, N;
    std::cin >> T >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    int profundidad, oro;
    std::vector<Tesoro> cofres(N);
    for (int i = 0; i < N; i++) {
        std::cin >> profundidad >> oro;
        cofres[i] = { 3 * profundidad, oro };
    }
    Matriz<int> resultados(N + 1, T + 1, -1);

    int sol = resolver(cofres, resultados, N, T);

    std::stack<int> recover;
    int i = N, j = T;
    while (i > 0 && j > 0) {
        if (resultados[i][j] > resultados[i - 1][j]) {
            recover.push(i - 1);
            j -= cofres[i-1].profundidad;
        }
        --i;
    }

    std::cout << sol << "\n" << recover.size() << "\n";
    while (!recover.empty()) {
        std::cout << cofres[recover.top()];
        recover.pop();
    }
    std::cout << "---\n";

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
