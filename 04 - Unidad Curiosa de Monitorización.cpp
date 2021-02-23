#include <iostream>
#include <fstream>
#include <queue>

struct User {
    long int identifier;
    int period;
    int currTick;

    bool operator < (const User& other) const {
        return currTick > other.currTick ||
            currTick == other.currTick && identifier > other.identifier;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada

    int nUsers;
    std::cin >> nUsers;

    if (nUsers == 0) return false;

    std::priority_queue<User> q;

    for (int i = 0; i < nUsers; i++) {
        long int newId, newPer;
        std::cin >> newId >> newPer;
        q.push({ newId, newPer, newPer });
    }

    int nEnvios;
    std::cin >> nEnvios;
    for(int i = 0; i < nEnvios; i++) {
        User aux = q.top();
        q.pop();
        std::cout << aux.identifier << "\n";
        q.push({ aux.identifier, aux.period, aux.period + aux.currTick });
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

