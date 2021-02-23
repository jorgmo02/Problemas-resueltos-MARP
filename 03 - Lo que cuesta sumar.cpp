
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>

bool resuelveCaso() {

    int N;
    std::cin >> N;
    if (N == 0)
        return false;

    std::priority_queue<long long int, std::vector<long long int>, std::greater<long long int>> cola;


    for (int i = 0; i < N; i++) {
        long long int a;
        std::cin >> a;
        cola.push(a);
    }

    long long int sum = 0;
    while (cola.size() > 1) {
        long long int a = cola.top();
        cola.pop();
        long long int b = cola.top();
        cola.pop();
        cola.push(a + b);
        sum += a + b;
    }

    std::cout << sum << "\n";

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