
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge Moreno Martínez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"
using namespace std;

/*@ <answer>

 APUNTE PARA EL LECTOR DEL FUTURO, POSIBLE HISTORIADOR INFORMÁTICO O CUALQUIER OTRA CLASE DE ENTIDAD A LA QUE LLEGARA ESTE CÓDIGO:
    No lo hagas por ascendente, es una matada y yo he tenido que pedir ayuda casi para todo :^}

 Problema de programación dinámica.
 Ver https://www.youtube.com/watch?v=nZRsGjH_SOg i guess (no le encuentro el parecido pero bueno :/ )

 Pequeño apunte: no se debería hacer una tabla con cada hora disponible porque la solucion no depende de las horas del dia.
    En su lugar, depende de las posibles colisiones entre películas al mismo tiempo (que una empiece antes de que acabe la otra).
    En el método resuelvePerezoso se ha implementado esta manera, aunque es errónea.

 Recursión:
    -Caso base:
        -no se puede ver la película porque empieza antes de que termine la actual (return recursion(siguiente peli))
        -no quedan películas para ver (return 0)
    -Caso recursivo:
        -max(ver la peli y no verla) = max(recursion(siguiente peli, fin peli) + horas peli, recursion(siguiente peli, fin actual))

    Coste en O(N^2), para sacar la siguiente peli es O(N) (aunque se podria hacer en otro sitio para bajar el coste) y se hace
    para cada peli, en total N veces.

    Para sacar la siguiente peli tenemos el vector de pelis ordenado por hora de inicio, y aumentamos hasta que encontramos una que vale
    o nos salimos del vector.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

#define MINS_DIA 1440
#define TIEMPO_ENTRE_PELIS 10

struct Pelicula {
    int ini;
    int fin;
    int dur;
    bool operator<(const Pelicula& other) {
        return ini < other.ini || (ini == other.ini && dur > other.dur);
    }
};

int siguientePeli(int i, const vector<Pelicula>& pelis)
{
    int k = i + 1;      // siguiente pelicula
    while (k < pelis.size() && pelis[k].ini < pelis[i].fin) k++;    // buscar la siguiente a la que podemos entrar
    return k;
}

int resuelveAsc(const vector<Pelicula>& pelis)
{
    int n = pelis.size();
    vector<int> sol(n, 0);

    //caso base
    sol[n - 1] = pelis[n - 1].dur;

    for (int i = n - 2; i >= 0; i--)
    {
        int k = siguientePeli(i, pelis);
        int sumaNext = pelis[i].dur;
        if (k < n) {
            sumaNext += sol[k];
        }
        sol[i] = max(sol[i + 1], sumaNext);
    }
    return sol[0];
}

int resuelveDesc(int i, const vector<Pelicula>& pelis, vector<int>& sol)
{
    if (i >= pelis.size()) return 0;
    if (sol[i] == -1) {
        sol[i] = max(resuelveDesc(i + 1, pelis, sol),
            resuelveDesc(siguientePeli(i, pelis), pelis, sol) + pelis[i].dur);
    }
    return sol[i];
}

int resuelvePerezoso(int i, int j, const vector<Pelicula>& pelis, Matriz<int>& mat)
{
    if (i >= pelis.size()) return 0;
    if (pelis[i].ini < j) return resuelvePerezoso(i + 1, j, pelis, mat);

    if (mat[i][j] == -1)
    {
        int noVer = resuelvePerezoso(i + 1, j, pelis, mat);
        int ver = resuelvePerezoso(i + 1, pelis[i].fin, pelis, mat) + pelis[i].dur;
        mat[i][j] = max(noVer, ver);
    }
    return mat[i][j];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;  cin >> N;

    if (N == 0)
        return false;

    vector<Pelicula> pelis(N);
    vector<int> duraciones(N);
    int hora, minuto, dur;
    char aux;
    for (int i = 0; i < N; i++) {
        cin >> hora >> aux >> minuto >> dur;
        pelis[i].ini = hora * 60 + minuto;
        pelis[i].fin = pelis[i].ini + dur + TIEMPO_ENTRE_PELIS;
        pelis[i].dur = dur;
    }
    
    sort(pelis.begin(), pelis.end());
    vector<int>sol(N, -1);
    cout << resuelveDesc(0, pelis, sol) << "\n";
    //cout << resuelveAsc(pelis) << "\n";

    //Matriz<int> mat(N + 1, MINS_DIA + 1, -1);  // un dia
    //cout << resuelve(0, 0, pelis, mat) << "\n";

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
