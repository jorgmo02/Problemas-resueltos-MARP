#include <iostream>
#include <fstream>
#include <queue>

struct Charla {
    int comienzo, fin;
    bool operator < (const Charla& other) const {
        return comienzo > other.comienzo;
    }
};

struct Compa {
    int fin;
    bool operator < (const Compa& other) const {
        return fin > other.fin;
    }
};

int solucion(std::priority_queue<Charla>& charlas) {
    std::priority_queue<Compa> compas;  // Cola de compañeros, ordenada según instante a partir del cual está disponible el compañero
    int nComp = 0;                      // Numero total de compañeros necesarios
    while(!charlas.empty()) {
        Charla t = charlas.top();   charlas.pop();              // coge la siguiente charla en el horario
        if (compas.empty() || compas.top().fin > t.comienzo)    // Si no hay compañero disponible para la charla
            nComp++;                                            //llamas a otro
        else compas.pop();                                      // Si hay un compañero disponible, lo sacas de la charla en la que estaba y que ya ha acabado
        compas.push({ t.fin });                                 // El nuevo compañero entra en la charla
    }
    return nComp - 1;                   // no te cuentas a ti mismo
}

bool resuelveCaso()
{
    int N;
    std::cin >> N;
    if (N == 0)     return false;

    std::priority_queue<Charla> tareas;
    int com, fin;
    for (int i = 0; i < N; i++) {
        std::cin >> com >> fin;
        tareas.push({ com, fin });
    }

    std::cout << solucion(tareas) << "\n";

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
