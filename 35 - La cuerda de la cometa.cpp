#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"
#include <algorithm>

/*@ <answer>

 Utilizo programación dinámica con un struct Solucion que almacena el mejor valor para cada combinación
 válida (se pueden almacenar en la misma casilla de la matriz, porque los parámetros de entrada "cordel a escoger"
 y "longitud restante" son compartidos aunque los resultados no correspondan a la misma combinación).
 Se usa programación dinámica descendente.
 Coste: O(número de cuerdas * longitud de la cometa)

 Recursión:
    Para las maneras: {
                            1                                    si longitud = 0
                            0                                    si no quedan cuerdas

                            maneras({cuerdas} - cuerdaelegida, longitud - longitudCuerda) +   si longitud > 0
                            maneras({cuerdas} - cuerdaelegida)  
                      }

    Para el numero de cuerdas:  {
                            0                                    si longitud = 0
                            infinito                             si no quedan cuerdas

                            maneras({cuerdas} - cuerdaelegida, longitud - longitudCuerda) +   si longitud > 0
                            maneras({cuerdas} - cuerdaelegida)
                      }
    Para el coste:    {
                            0                                    si longitud = 0
                            infinito                             si no quedan cuerdas

                            maneras({cuerdas} - cuerdaelegida, longitud - longitudCuerda) +   si longitud > 0
                            maneras({cuerdas} - cuerdaelegida)
                      }

    Se puede resumir en:        {
                            {1,0,0}                              si longitud = 0
                            {0,infinito,infinito}                si no quedan cuerdas

                            maneras({cuerdas} - cuerdaelegida, longitud - longitudCuerda) +   si longitud > 0
                            maneras({cuerdas} - cuerdaelegida)
                      }
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct Solucion {
    int64_t maneras = 0;
    EntInf minNumCuerdas = 0,
           minCoste = 0;
};

struct Cuerda {
    int longitud;
    int coste;

    bool operator <(const Cuerda& other) const {
        return longitud < other.longitud;
    }
};

Solucion recursion(int i, int j, const std::vector<Cuerda>& cuerdas, Matriz<Solucion>& mat)
{
    if (i >= 0 && j == 0)       // caso base recursivo, cometa terminada
        return { 1, 0, 0 };
    if (i <= 0 && j > 0)        // caso base recursivo, no quedan cuerdas por explorar y aún no hemos terminado la cometa
        return { 0, Infinito, Infinito };

    if (mat[i - 1][j - 1].maneras != -1)    // subproblema ya resuelto
        return mat[i - 1][j - 1];

    Cuerda cuerda = cuerdas[i - 1];
    if (cuerda.longitud <= j)
    {
        Solucion sinCoger = recursion(i - 1, j, cuerdas, mat);                     // no coger esta cuerda
        Solucion coger = recursion(i - 1, j - cuerda.longitud, cuerdas, mat);      // coger esta cuerda

        mat[i - 1][j - 1] = { sinCoger.maneras + coger.maneras,                    // solución para el matemático
                     std::min(sinCoger.minNumCuerdas, coger.minNumCuerdas + 1),    // solución para el ingeniero
                     std::min(sinCoger.minCoste, coger.minCoste + cuerda.coste)    // solución para el economista
        };
    }
    else mat[i - 1][j - 1] = recursion(i - 1, j, cuerdas, mat);

    return mat[i - 1][j - 1];
}

bool resuelveCaso()
{
    int N, L;
    std::cin >> N >> L;
    if (!std::cin) return false;

    std::vector<Cuerda> cuerdas(N);
    int longitud, coste;
    for (int i = 0; i < N; i++) {
        std::cin >> longitud >> coste;
        cuerdas[i] = { longitud, coste };
    }

    // ordenado de menor a mayor (siempre se coge la más larga)
    std::sort(cuerdas.begin(), cuerdas.end());
    Matriz<Solucion> mat(cuerdas.size() + 1, L + 1, { -1, Infinito, Infinito });

    Solucion sol = recursion(cuerdas.size(), L, cuerdas, mat);

    if (sol.maneras == 0) std::cout << "NO\n";
    else std::cout << "SI " << sol.maneras << " " << sol.minNumCuerdas << " " << sol.minCoste << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
