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
    std::priority_queue<Compa> compas;  // Cola de compa�eros, ordenada seg�n instante a partir del cual est� disponible el compa�ero
    int nComp = 0;                      // Numero total de compa�eros necesarios
    while(!charlas.empty()) {
        Charla t = charlas.top();   charlas.pop();              // coge la siguiente charla en el horario
        if (compas.empty() || compas.top().fin > t.comienzo)    // Si no hay compa�ero disponible para la charla
            nComp++;                                            //llamas a otro
        else compas.pop();                                      // Si hay un compa�ero disponible, lo sacas de la charla en la que estaba y que ya ha acabado
        compas.push({ t.fin });                                 // El nuevo compa�ero entra en la charla
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
