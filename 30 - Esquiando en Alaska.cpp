#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>

int voraz(std::priority_queue<int>& esquiadores, std::priority_queue<int>& esquis) {
    int sum = 0;
    while (!esquiadores.empty()) {
        sum += abs(esquiadores.top() - esquis.top());
        esquiadores.pop();
        esquis.pop();
    }
    return sum;
}

bool resuelveCaso() {

    int N;
    std::cin >> N;

    if (N == 0) return false;

    std::priority_queue<int> esquiadores;
    std::priority_queue<int> esquis;

    int aux;
    for (int i = 0; i < N; i++) {
        std::cin >> aux;
        esquiadores.push(aux);
    }
    for (int i = 0; i < N; i++) {
        std::cin >> aux;
        esquis.push(aux);
    }

    std::cout << voraz(esquiadores, esquis) << "\n";
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
