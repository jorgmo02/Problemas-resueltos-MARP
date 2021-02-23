
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge Moreno Martínez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <map>
#include "Matriz.h"
#include "EnterosInf.h"
#include <algorithm>
using namespace std;

/*@ <answer>

 Uso el algoritmo de Floyd para calcular el camino minimo entre cada par de
 personas de la red.
 Despues se calcula el mayor de los caminos minimos.

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& distancias) {
    int V = G.numfils();
    distancias = G;
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                EntInf temp = distancias[i][k] + distancias[k][j];
                if (temp < distancias[i][j]) { // es mejor pasar por k
                    distancias[i][j] = temp;
                }
            }
        }
    }
}

bool resuelveCaso() {

    int P, R;
    cin >> P >> R;
    if (!std::cin)  // fin de la entrada
        return false;

    map<string, int> nombres;
    Matriz<EntInf> mat(P, P, Infinito);

    int pos1 = 0, pos2 = 0;         
    string aux;
    int id = 0;             // identificador de la persona

    for (int i = 0; i < R; i++)
    {
        // primera persona
        cin >> aux;
        auto a = nombres.insert({ aux, id });       // devuelve par<iterador, bool> con la info de lo que hemos insertado y la info de si se ha insertado o no
        if (a.second)   ++id;           // persona nueva
        pos1 = a.first->second;         // id de la persona que acabamos de meter
        
        // segunda persona
        cin >> aux;
        a = nombres.insert({ aux, id });
        if (a.second)   ++id;           // persona nueva
        pos2 = a.first->second;         // id de la persona que acabamos de meter

        // almacenamos la relacion
        mat[pos1][pos2] = mat[pos2][pos1] = 1;
    }

    Matriz<EntInf> distancias;
    Floyd(mat, distancias);

    EntInf maxDist = 0;
    // hallar camino maximo, buscamos cada par de personas
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < i; j++) {
            maxDist = std::max(distancias[i][j], maxDist);
        }
    }
    if (maxDist == Infinito) cout << "DESCONECTADA\n";
    else cout << maxDist << "\n";

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
