// Jorge Moreno Martínez

#include <iostream>
#include <fstream>
#include <queue>

struct Cuerda {
    int nMusicos;
    int nPartituras;

    bool operator < (const Cuerda& b) const {
        if (nPartituras == 0) return false;
        if (b.nPartituras == 0) return true;
        return getMaxFromCuerda() < b.getMaxFromCuerda();
    }
    int getMaxFromCuerda() const {
        int a = 0;
        if (nMusicos % nPartituras != 0) a = 1;
        return (nMusicos / nPartituras) + a;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int p, n;
    std::cin >> p >> n;

    if (!std::cin)  // fin de la entrada
        return false;

    std::priority_queue<Cuerda> cola;

    for (int i = 0; i < n; i++) {
        int nMusicos;
        std::cin >> nMusicos;
        cola.push({ nMusicos, 0 });
    }
    for (int i = 0; i < p; i++) {
        Cuerda cima = cola.top();
        cola.pop();
        cima.nPartituras++;
        cola.push(cima);
    }
    std::cout << cola.top().getMaxFromCuerda() << "\n";

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
