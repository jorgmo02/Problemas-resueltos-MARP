
/*@ <answer>
 *
 * Nombre y Apellidos:  Jorge Moreno Martínez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include <algorithm>
using namespace std;


/*@ <answer>

 recursion(bombilla, potencia):
    casos base:
         -potencia == 0 -> 0                                            // no hace falta ninguna bombilla para potencia 0
         -potencia > 0 && bombilla == 0 -> INFINITO                     // (bombilla == 0 significa que no hay ninguna bombilla)
         -Bombilla no cabe -> recursion(bombilla anterior, potencia)    // si la bombilla no cabe cogemos la anterior solución
    
    // si la bombilla cabe, tenemos dos opciones: quedarnos con la anterior solucion o quedarnos con la solución actual, es decir,
       coger la nueva bombilla y sumar su potencia a la anterior solución obtenida. Se escoge la opción de menor coste entre estas.
    caso recursivos:
         -recursion(bombilla, potencia) = min {
                        recursion(bombilla anterior, potencia)
                        recursion(bombilla, potencia anterior) + potencia de la bombilla actual
                    }

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

#define INFINITO 1000000000

struct Bombilla {
    int potencia;
    int coste = INFINITO;
};

Bombilla resolver(int Pmax, int Pmin, const std::vector<Bombilla>& bombillas, Matriz<int>& mat)
{
    int N = bombillas.size();

    // La matriz empieza con la primera fila con valor INFINITO (no hay solución aún),
    // a excepción de la primera columna que es siempre 0 (0 potencia = 0 bombillas).

    mat[0][0] = 0;
    for (int i = 1; i <= N; ++i)
    {
        mat[i][0] = 0;
        for (int j = 1; j <= Pmax; ++j)
        {
            if (bombillas[i - 1].potencia <= j)          // no se pasa de potencia la bombilla actual
            {   
                // poner una bombilla más de este tipo
                int anterior = mat[i][j - bombillas[i - 1].potencia];
                // ver qué renta más, si coger la de este tipo o no hacerlo
                mat[i][j] = min(mat[i - 1][j], anterior + bombillas[i - 1].coste);
            }
            else mat[i][j] = mat[i - 1][j];             // se pasa de potencia, cogemos la bombilla anterior
        }
    }

    // recuperar solucion
    // hallamos la solucion con menor coste entre el rango Pmin y Pmax
    int minCoste = INFINITO;
    int minPotencia = 0;
    for (int i = Pmin; i <= Pmax; i++) {
        int resultado = mat[N][i];            // la última fila es la que tiene el mejor resultado para cada potencia
        if (resultado < minCoste) {
            minCoste = resultado;
            minPotencia = i;
        }
    }
    return { minPotencia , minCoste };
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, Pmax, Pmin;
    cin >> N >> Pmax >> Pmin;
    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<Bombilla> bombillas(N);
    int aux;
    for (int i = 0; i < N; i++) {
        cin >> aux;
        bombillas[i].potencia = aux;
    }
    for (int i = 0; i < N; i++) {
        cin >> aux;
        bombillas[i].coste = aux;
    }

    Matriz<int> mat(N + 1, Pmax + 1, INFINITO);
    Bombilla ins = resolver(Pmax, Pmin, bombillas, mat);

    if (ins.coste == INFINITO) cout << "IMPOSIBLE\n";
    else cout << ins.coste << " " << ins.potencia << "\n";

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
