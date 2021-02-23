#include <iostream>
#include <fstream>
#include <algorithm>

#include "Matriz.h"

using Tablero = Matriz<int>;

struct Sol
{
    int punt;
    int col;

    bool operator>(const Sol& otra) const
    {
        return punt > otra.punt;
    }

    bool operator<(const Sol& otra) const
    {
        return punt < otra.punt;
    }
    Sol() :punt(-1), col(-1) {}
    Sol(int pts, int c) :
        punt(pts), col(c) {}

};

// devuelve true si est� dentro del tablero, si no devuelve false
bool valido(int f, int c, const Tablero& T) {
    return f >= 0 && f < T.numfils() && c >= 0 && c < T.numcols();
}


// funci�n que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(int f, int c, const Tablero& T, Matriz<int>& resultados) {
    //hemos llegado al final
    if (valido(f, c, T)) {
        if (resultados[f][c] != -1) {
            return resultados[f][c];
        }

        if (f == 0)
            resultados[f][c] = T[f][c];
        else {
            int r = std::max(resolver(f - 1, c - 1, T, resultados),
                std::max(resolver(f - 1, c, T, resultados), resolver(f - 1, c + 1, T, resultados)));
            r += T[f][c];
            resultados[f][c] = r;
        }
        return resultados[f][c];
    }
    else return -1;
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuraci�n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    Tablero t = Tablero(N, N);
    Matriz<int> resultados(N, N, -1);    //Matriz de programación dinámica
    int aux;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> aux;
            t[i][j] = aux;
        }
    }
    Sol resultado;
    for (int i = 0; i < N; ++i)
    {
        int a = resolver(N - 1, i, t, resultados);
        if (a > resultado.punt)
        {
            resultado.punt = a;
            resultado.col = i;
        }
    }

    std::cout << resultado.punt << " " << resultado.col + 1 << "\n";

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
