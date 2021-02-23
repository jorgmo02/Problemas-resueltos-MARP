
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge Moreno Martínez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include "Matriz.h"
using namespace std;


/*@ <answer>

 Problema parecido al de los funcionarios del ministerio. Es un ejercicio de ramificación y poda, en concreto de minimización
 Vamos recorriendo cada supermercado para cada objeto: en cada iteración decidimos dónde comprarlo.
 
 Estimación: sacamos el mínimo coste posible para los objetos restantes a partir de un objeto k (inicialmente k=0).
             El primer coste (en la posición 0) será el coste mínimo entre todos los objetos, y el último será 0 (una posible solución).
 
 Factibilidad: hay 3 objetos o menos comprados en el supermercado que estamos examinando, y el coste estimado es menor que el actual.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

#define INFINITO 1000000000

struct Nodo
{
    vector<int> comprados;      // de tamaño NUM_SUPERMERCADOS, indica en que super ha sido comprado
    int k;                      // indice del supermercado en el que queremos comprar
    int coste;                  // coste acumulado
    int coste_estimado;         // coste minimo estimado

    bool operator >(const Nodo& other) const {
        return coste_estimado > other.coste_estimado;
    }
};

void estimar_coste(Matriz<int64_t> mat, vector<int>& costesEstimados)
{
    int M = mat.numfils(), N = mat.numcols();

    int acum = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        int64_t minPrecio = INFINITO;
        for (size_t j = 0; j < M; j++) {
           minPrecio = min(minPrecio, mat[j][i]);
        }
        acum += minPrecio;
        costesEstimados[i] = acum;
    }
}

int compra(Matriz<int64_t> mat)
{
    int M = mat.numfils(), N = mat.numcols();

    vector<int> costesEstimados(N + 1);
    estimar_coste(mat, costesEstimados);

    Nodo Y;
    Y.comprados = std::vector<int>(M, 0);
    Y.k = -1;
    Y.coste = 0;
    Y.coste_estimado = costesEstimados[0];

    priority_queue<Nodo, vector<Nodo>, greater<Nodo>> cola;
    cola.push(Y);
    int coste_mejor = INFINITO;
    
    while (!cola.empty() && cola.top().coste_estimado < coste_mejor)
    {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        X.k++;

        // recorremos cada supermercado para el producto k
        for (size_t i = 0; i < M; i++)
        {
            if (X.comprados[i] < 3)
            {
                X.comprados[i]++;
                X.coste = Y.coste + mat[i][X.k];
                X.coste_estimado = costesEstimados[X.k + 1] + X.coste;
                if (X.coste_estimado < coste_mejor) {
                    if (X.k == N - 1) {
                        coste_mejor = X.coste;
                    }
                    else {
                        cola.push(X);
                    }
                }
                X.comprados[i]--;
            }
        }
    }

    return coste_mejor;
}

void resuelveCaso() {

    int M, N;
    cin >> M >> N;

    Matriz<int64_t> precios(M, N);

    int64_t aux;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> aux;
            precios[i][j] = aux;
        }
    }

    cout << compra(precios) << "\n";
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
