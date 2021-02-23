
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge Moreno Martínez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Matriz.h"
using namespace std;

/*@ <answer>

 Recurrencia:
    -Casos base:
        0 letras: no hay palabra        
        1 letra: ya es palindromo       -> return 0

    -Casos recursivos:
        -No coinciden:
            res = min(buscar quitando de la derecha, buscar quitando de la izquierda) + 1 (por haber quitado uno)
        -Coinciden: buscar quitando de ambos a la vez

 Coste:
    resolver_rec en O(N^2) siendo N longitud palabra
    reconstruir en O(N)
    
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

// rellena la tabla
int resolver_rec(int i, int j, string& palabra, Matriz<int>& mat)
{
    int& res = mat[i][j];
    if (res == -1)
    {
        if (i > j) res = 0;
        else if (i == j)     // ya es palindromo
            res = 0;
        else if (palabra[i] != palabra[j])
            res = min(resolver_rec(i + 1, j, palabra, mat), resolver_rec(i, j - 1, palabra, mat)) + 1;    // sumamos 1 porque hay al menos una letra que no es común

        else res = resolver_rec(i + 1, j - 1, palabra, mat);      // como las letras son comunes no sumamos nada
    }

    return res;
}

// reconstruye la palabra en sol
void reconstruir(int i, int j, string& palabra, string& sol, Matriz<int>& mat)
{    
    if (i > j) return;

    // caso base
    if (i == j) sol.push_back(palabra[i]);

    // la letra coincide, no hay que hacer nada para "palindromearla"
    else if (palabra[i] == palabra[j])
    {
        sol.push_back(palabra[i]);
        reconstruir(i + 1, j - 1, palabra, sol, mat);
        sol.push_back(palabra[j]);
    }
    
    // no coincide, hay que ver qué lado es mejor duplicar (a partir del resultado almacenado en mat)
    else if (mat[i + 1][j] < mat[i][j - 1])     // duplicar la letra de la izquierda
    {
        sol.push_back(palabra[i]);
        reconstruir(i + 1, j, palabra, sol, mat);
        sol.push_back(palabra[i]);
    }
   
    else             // duplicar la letra de la derecha          
    {
        sol.push_back(palabra[j]);
        reconstruir(i, j - 1, palabra, sol, mat);
        sol.push_back(palabra[j]);
    }
}

// funcion auxiliar
int resolver(string& palabra, string& sol)
{
    Matriz<int> mat(palabra.length(), palabra.length(), -1);
    int tam = resolver_rec(0, palabra.length() - 1, palabra, mat);
    reconstruir(0, palabra.length() - 1, palabra, sol, mat);
    return tam;
}

bool resuelveCaso() {

    string in;  cin >> in;
    if (!std::cin)  // fin de la entrada
        return false;

    if (in.length() > 0) {
        string sol;
        std::cout << resolver(in, sol) << " " << sol << "\n";
    }

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

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
