/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include <queue>

using namespace std;

/*@ <answer>

 Es un ejercicio de ramificaci�n y poda de coste m�nimo, buscamos la asignaci�n con suma m�nima.

 Factibilidad: la tarea no ha sido asignada a otro funcionario
 Estimacion: cogemos la tarea m�s corta para cada trabajador, sin tener en cuenta si est� usada o no.
            Es una cota inferior ya que coge la combinaci�n que da el resultado m�s peque�o, aunque no sea factible.
 
 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

#define INFINITO 2147483647

struct Nodo {
    std::vector<bool> asignadas;   // tareas asignadas (desde 0 hasta N - 1)
    int k;                         // indice actual
    int coste;                     // coste acumulado
    int coste_estimado;            // estimaci�n, prioridad

    bool operator < (Nodo const& otro) const {
        return coste_estimado > otro.coste_estimado;
    }
};

// c�lculo voraz de todas las estimaciones de golpe, se empieza con el �ltimo trabajador
// para ir acumulando el valor (el valor m�s alto estimado est� en estimaciones[0] y el m�s bajo en estimaciones[N-1])
void estimar_costes(const Matriz<int>& mat, int N, std::vector<int>& estimaciones)
{
    int estimacion = 0;

    for (int i = N - 1; i >= 0; --i)
    {
        int menorTrabajo = INFINITO;
        for (int j = 0; j < N; ++j) {
            menorTrabajo = std::min(menorTrabajo, mat[i][j]);
        }
        estimacion += menorTrabajo;
        estimaciones[i] = estimacion;
    }
}

int sol(const Matriz<int>& mat)
{
    int N = mat.numfils();
    int coste_mejor = 2147483647;   // infinity

    std::vector<int> estimaciones(N);   // contiene la mejor tarea para cada trabajador
    estimar_costes(mat, N, estimaciones);

    Nodo Y;
    Y.asignadas = std::vector<bool>(N, false);
    Y.k = -1;
    Y.coste = 0;
    Y.coste_estimado = estimaciones[0];
    std::priority_queue<Nodo> cola;
    cola.push(Y);

    // ordenadas de menor a mayor seg�n coste_estimado, la que tenga coste estimado m�s bajo ser� la primera
    while (!cola.empty() && cola.top().coste_estimado < coste_mejor)
    {
        Y = cola.top(); cola.pop();
        for (int i = 0; i < N; ++i)     // recorremos los hijos (todas las tareas para cada trabajador)
        {
            if (!Y.asignadas[i])        // comprobamos que la tarea no est� asignada ya
            {
                // usamos la tarea con el miembro k
                Nodo X(Y);
                ++X.k;
                X.asignadas[i] = true;
                X.coste = Y.coste + mat[X.k][i];
                X.coste_estimado = X.coste;
                if (X.k < N - 1) X.coste_estimado += estimaciones[X.k + 1];

                if (X.coste_estimado < coste_mejor) {
                    if (X.k == N - 1) {     // es solucion
                        coste_mejor = X.coste;
                    }
                    else {                  // no es soluci�n pero es factible, se mete a la cola
                        cola.push(X);
                    }
                }
                X.asignadas[i] = false;
            }
        }
    }

    return coste_mejor;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;      cin >> N;
    if (N == 0) return false;       // fin de la entrada

    Matriz<int> mat(N, N);
    int n;
    for (int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j) {
            cin >> n;
            mat[i][j] = n;
        }

    cout << sol(mat) << "\n";

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
