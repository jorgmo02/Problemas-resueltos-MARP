#include <iostream>
#include <queue>
#include <fstream>
#include <string>

struct Caja {
    int numCaja;
    int tiempoCliente = 0;

    bool operator < (const Caja& b) const {
        return tiempoCliente > b.tiempoCliente ||
            (tiempoCliente == b.tiempoCliente && numCaja > b.numCaja);
    }
};

//O(N log N) para el numero de operaciones 'I' 'A'
bool resuelveCaso() {

    // leer los datos de la entrada
    int nCajas = 0;
    std::cin >> nCajas;

    if (!std::cin || nCajas == 0)  // fin de la entrada
        return false;

    std::priority_queue<Caja> cajas;
    for (int i = 1; i <= nCajas; i++)
        cajas.push({ i });

    int nClients = 0;
    std::cin >> nClients;

    int timeClient = 0;
    for (int i = 0; i < nClients; i++) {
        std::cin >> timeClient;
        Caja c = cajas.top();
        c.tiempoCliente += timeClient;
        cajas.pop();
        cajas.push(c);
    }
    int res = cajas.top().numCaja;
    std::cout << res << "\n";

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