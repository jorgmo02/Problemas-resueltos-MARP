#include <iostream>
#include <fstream>
#include <queue>

using Cola = std::priority_queue<int, std::vector<int>, std::greater<int>>;

void voraz(Cola& atacantes, Cola& defensores) {
    while (!defensores.empty())
    {
        while (!defensores.empty() && defensores.top() < atacantes.top())
            defensores.pop();

        if (!defensores.empty()) {
            atacantes.pop();
            defensores.pop();
        }
    }
}

bool resuelveCaso()
{
    int N;
    std::cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;
    
    int n;
    Cola atacantes, defensores;
    for (int i = 0; i < N; i++) {
        std::cin >> n;
        atacantes.push(n);
    }
    for (int i = 0; i < N; i++) {
        std::cin >> n;
        defensores.push(n);
    }

    voraz(atacantes, defensores);
    std::cout << N - atacantes.size() << "\n";
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