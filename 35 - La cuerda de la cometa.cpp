#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"
#include <algorithm>

/*@ <answer>

 Utilizo programaci�n din�mica con un struct Solucion que almacena el mejor valor para cada combinaci�n
 v�lida (se pueden almacenar en la misma casilla de la matriz, porque los par�metros de entrada "cordel a escoger"
 y "longitud restante" son compartidos aunque los resultados no correspondan a la misma combinaci�n).
 Se usa programaci�n din�mica descendente.
 Coste: O(n�mero de cuerdas * longitud de la cometa)

 Recursi�n:
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
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
    if (i <= 0 && j > 0)        // caso base recursivo, no quedan cuerdas por explorar y a�n no hemos terminado la cometa
        return { 0, Infinito, Infinito };

    if (mat[i - 1][j - 1].maneras != -1)    // subproblema ya resuelto
        return mat[i - 1][j - 1];

    Cuerda cuerda = cuerdas[i - 1];
    if (cuerda.longitud <= j)
    {
        Solucion sinCoger = recursion(i - 1, j, cuerdas, mat);                     // no coger esta cuerda
        Solucion coger = recursion(i - 1, j - cuerda.longitud, cuerdas, mat);      // coger esta cuerda

        mat[i - 1][j - 1] = { sinCoger.maneras + coger.maneras,                    // soluci�n para el matem�tico
                     std::min(sinCoger.minNumCuerdas, coger.minNumCuerdas + 1),    // soluci�n para el ingeniero
                     std::min(sinCoger.minCoste, coger.minCoste + cuerda.coste)    // soluci�n para el economista
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

    // ordenado de menor a mayor (siempre se coge la m�s larga)
    std::sort(cuerdas.begin(), cuerdas.end());
    Matriz<Solucion> mat(cuerdas.size() + 1, L + 1, { -1, Infinito, Infinito });

    Solucion sol = recursion(cuerdas.size(), L, cuerdas, mat);

    if (sol.maneras == 0) std::cout << "NO\n";
    else std::cout << "SI " << sol.maneras << " " << sol.minNumCuerdas << " " << sol.minCoste << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
