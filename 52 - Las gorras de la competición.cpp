
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge Moreno Martínez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

/*@ <answer>
  
 Lo mejor es que siempre gane el equipo que menos gorras tenga, porque tendremos que dar menos gorras a sus fans.
 Se trata de un problema de colas de prioridad, donde ordenamos la cola en orden creciente (al inicio está el elemento más pequeño).
 Mientras que se pueda hacer un partido (haya más de un equipo), se hace el partido y se otorgan las gorras. Después se elimina al vencido.
 
 Coste en O(N log N), donde N es el número de equipos. Se hacen N operaciones de inserción y borrado.
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;  cin >> N;
    if (N == 0)
        return false;

    int aux;
    priority_queue<int64_t, vector<int64_t>, greater<int64_t>> seguidores;
    for (int i = 0; i < N; i++) {
        cin >> aux;
        seguidores.push(aux);
    }

    int64_t cont = 0;
    while (seguidores.size() > 1) {
        int64_t equipo1 = seguidores.top();     seguidores.pop();
        int64_t equipo2 = seguidores.top();     seguidores.pop();

        cont += equipo1 + equipo2;
        seguidores.push(equipo1 + equipo2);
    }
    cout << cont << "\n";
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
