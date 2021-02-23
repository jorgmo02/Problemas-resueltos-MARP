
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge Moreno Martínez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

#define INFINITO 1000000000

int resuelve(int N, priority_queue<int>& bateriasA, priority_queue<int>& bateriasB)
{
    int dronesAct = 0;
    int acum = 0;
    
    priority_queue<int> auxA, auxB;      // aqui vamos metiendo las baterias que vamos usando

    while (dronesAct < N && !bateriasA.empty() && !bateriasB.empty())
    {
        int A = bateriasA.top();    bateriasA.pop();
        int B = bateriasB.top();    bateriasB.pop();
        int horas = min(A, B);
        auxA.push(A - horas);
        auxB.push(B - horas);

        dronesAct++;
        acum += horas;
    }

    while (!auxA.empty() && auxA.top() > 0) {
        bateriasA.push(auxA.top());
        auxA.pop();
    }
    while (!auxB.empty() && auxB.top() > 0) {
        bateriasB.push(auxB.top());
        auxB.pop();
    }

    return acum;
}

bool resuelveCaso() {

    int N, A, B;
    cin >> N >> A >> B;
    if (!std::cin)  // fin de la entrada
        return false;

    priority_queue<int> bateriasA, bateriasB;
    int aux;
    for (int i = 0; i < A; i++) {
        cin >> aux;
        bateriasA.push(aux);
    }
    for (int i = 0; i < B; i++) {
        cin >> aux;
        bateriasB.push(aux);
    }

    while ((aux = resuelve(N, bateriasA, bateriasB)) > 0) {
        cout << aux << " ";
    }
    cout << "\n";
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
