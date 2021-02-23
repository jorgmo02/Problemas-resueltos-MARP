
/*@ <answer>
 *
 * Nombre y Apellidos: Jorge Moreno Martínez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

/*@ <answer>

Podemos utilizar dos colas de prioridad, de prioridades no variables, para representar respectivamente
las baterías en funcionamiento y las baterías de repuesto.
Se utiliza el struct Bateria, que tiene los parámetros fin (instante de finalización de la carga de la batería),
id (el identificador de la batería) y dur (el tiempo que aguanta la carga actual).
Invariante: la cima de la cola de baterías en funcionamiento siempre será la primera batería en acabarse, o la que
tenga el menor id en caso de que dos baterías se agoten a la vez.
La cola de baterías de recarga se ordena según el id.

Según se agotan baterías en funcionamiento, se sacan de la cola y pueden ocurrir tres cosas:
    -Se puede recargar (se añade a la cola de nuevo con fin y dur actualizados)
    -No se puede recargar y quedan baterías de repuesto (se añade una batería de repuesto con fin actualizado)
    -No se puede recargar y no quedan baterías de repuesto (termina la simulación porque hay que abandonar la base)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

#include <queue>

struct Bateria
{
    int fin;
    int id;
    int dur;

    bool operator <(const Bateria& other) const
    {
        return fin > other.fin ||
            (fin == other.fin && id > other.id);
    }
};


bool resuelveCaso() {

    // leer los datos de la entrada
    int B;
    cin >> B;

    if (!cin)  // fin de la entrada
        return false;

    priority_queue<Bateria> cola;
    int id = 1, fin;
    for (int i = 0; i < B; ++i, ++id) {
        cin >> fin;
        cola.push({ fin, id, fin });
    }

    int R;
    cin >> R;
    priority_queue<Bateria> reserva;

    int dur;
    for (int i = 0; i < R; ++i, ++id) {
        cin >> dur;
        reserva.push({ 0, id, dur });
    }

    int Z, T;
    cin >> Z >> T;

    // resolver el caso

    while (!cola.empty() && cola.top().fin <= T)
    {
        Bateria act = cola.top();
        cola.pop();

        act.dur -= Z;

        if (act.dur <= 0) {
            if (!reserva.empty()) {
                Bateria nueva = reserva.top();
                reserva.pop();
                nueva.fin = act.fin + nueva.dur;
                cola.push(nueva);
            }
        }
        else {
            act.fin += act.dur;
            cola.push(act);
        }
    }

    // escribir la solución
    if (cola.empty()) cout << "ABANDONEN INMEDIATAMENTE LA BASE";
    else if (cola.size() < B) cout << "FALLO EN EL SISTEMA";
    else cout << "CORRECTO";

    while (!cola.empty()) {
        cout << "\n" << cola.top().id << " " << cola.top().fin;
        cola.pop();
    }

    cout << "\n---\n";

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