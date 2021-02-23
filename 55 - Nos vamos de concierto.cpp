
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"
using namespace std;

/*@ <answer>
  
 Recursion:
    Casos base:
        -Siguiente festival si no puedes ir al actual
        -0 si no quedan festivales
    Caso recursivos:
        resultado = max(ir al actual, no ir)
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Festival
{
    int grupos;
    int precio;
};

int resuelve(int i, int presupuesto, const vector<Festival>& festivales, Matriz<int>& mat)
{
    if (i >= festivales.size()) return 0;
    if (festivales[i].precio > presupuesto) return resuelve(i + 1, presupuesto, festivales, mat);

    if (mat[i][presupuesto] == -1) {
        mat[i][presupuesto] = max(resuelve(i + 1, presupuesto, festivales, mat),
            resuelve(i + 1, presupuesto - festivales[i].precio, festivales, mat) + festivales[i].grupos);
    }
    return mat[i][presupuesto];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int P, N;
    cin >> P >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<Festival> festivales(N);
    int g, pre;
    for (int i = 0; i < N; i++) {
        cin >> g >> pre;
        festivales[i] = { g, pre };
    }

    Matriz<int> mat(N, P + 1, -1);
    cout << resuelve(0, P, festivales, mat) << "\n";

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
