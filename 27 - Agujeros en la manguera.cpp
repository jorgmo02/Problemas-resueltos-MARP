#include <iostream>
#include <fstream>
#include <vector>

int voraz(const std::vector<int>& posiciones, const int L)
{
    int lastPosCubierta = -1, numParches = 0;
    for (int i = 0; i < posiciones.size(); i++) {
        if (lastPosCubierta < posiciones[i]) {
            lastPosCubierta = posiciones[i] + L;
            numParches++;
        }
    }
    return numParches;
}

bool resuelveCaso()
{
    int N, L;
    std::cin >> N >> L;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<int> posiciones(N);
    for (int i = 0; i < N; i++) {
        int pos; std::cin >> pos;
        posiciones[i] = pos;
    }

    std::cout << voraz(posiciones, L) << "\n";
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