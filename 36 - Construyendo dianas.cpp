#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "EnterosInf.h"

std::vector<int> resolver(std::vector<int>& puntuaciones, int valor)
{
    int n = puntuaciones.size();
    std::vector<EntInf> dardos(valor + 1, Infinito);
    dardos[0] = 0;
    // calcular la matriz sobre el propio vector
    for (int i = 1; i <= n; ++i) {
        for (int j = puntuaciones[i - 1]; j <= valor; ++j) {
            dardos[j] = std::min(dardos[j], dardos[j - puntuaciones[i - 1]] + 1);
        }
    }
    std::vector<int> sol;
    if (dardos[valor] != Infinito) {
        int i = n, j = valor;
        while (j > 0) {
            if (puntuaciones[i - 1] <= j && dardos[j] == dardos[j - puntuaciones[i - 1]] + 1) {
                // tomamos un dardo de tipo i (con puntuacion i)
                sol.push_back(puntuaciones[i - 1]);
                j = j - puntuaciones[i - 1];
            }
            else // no tomamos más dardos de tipo i
                --i;
        }
    }
    return sol;
}

bool resuelveCaso() {

    int valor, S;
    std::cin >> valor >> S;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<int> puntuaciones(S);
    int puntuacion;
    for (int i = 0; i < S; i++) {
        std::cin >> puntuacion;
        puntuaciones[i] = puntuacion;
    }

    std::vector<int> sol = resolver(puntuaciones, valor);
    if (sol.size() > 0) {
        std::cout << sol.size() << ":";
        for (int i = 0; i < sol.size(); i++)
            std::cout << " " << sol[i];
        std::cout << "\n";
    }
    else
        std::cout << "Imposible\n";

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
