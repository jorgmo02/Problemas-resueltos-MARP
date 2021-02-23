#include <iostream>
#include <queue>
#include <fstream>

struct Tarea {
    int inicio = 0;
    int fin = 0;
    int periodo = -1;

    bool operator < (const Tarea& b) const {
        return inicio > b.inicio;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int nTareas = 0, nPeriodicas = 0;
    int nMinutos = 0;
    std::cin >> nTareas >> nPeriodicas >> nMinutos;

    if (!std::cin)  // fin de la entrada
        return false;

    int auxIni, auxFin, periodo;
    std::priority_queue<Tarea> tareas;

    for (int i = 0; i < nTareas; ++i) {
        std::cin >> auxIni >> auxFin;
        if (auxIni < nMinutos)
            tareas.push({ auxIni, auxFin });
    }

    for (int i = 0; i < nPeriodicas; ++i) {
        std::cin >> auxIni >> auxFin >> periodo;
        if (auxIni < nMinutos) {
            tareas.push({ auxIni, auxFin, periodo });
        }
    }
    
    bool chocan = false;
    int lastOccupied = -1;
    while (!chocan && !tareas.empty()) {
        const Tarea* t = &tareas.top();
        if (t->inicio < lastOccupied) chocan = true;
        else {
            if (t->periodo != -1 && t->inicio + t->periodo < nMinutos)
                tareas.push({ t->inicio + t->periodo, t->fin + t->periodo, t->periodo });
            lastOccupied = t->fin;
            tareas.pop();
        }
    }

    std::cout << ((chocan) ? "SI" : "NO") << "\n";
    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    std::streambuf* cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}