#include <iostream>
#include <fstream>
#include <queue>
#include <string>

struct Trabajo
{
    int c, f;
    bool operator < (const Trabajo& other) const {
        return c > other.c || (c == other.c && f < other.f);
    }
};

int resolver(std::priority_queue<Trabajo>& q, int C, int F)
{
    // empezamos por C porque el resto nos da igual (no metemos trabajos que no nos interesan en resuelveCaso())
    int cubierto = C;
    int nTareas = 0;

    // INVARIANTE: no puede haber huecos vacíos entre C y F.
    // vamos cogiendo tareas mientras que no haya huecos vacíos (q.top().c <= cubierto)
    // y no hayamos terminado (cubierto < F).
    while (!q.empty() && q.top().c <= cubierto && cubierto < F)
    {
        // vamos quitando elementos de la cola que solapen. Podemos coger el elemento
        // que empiece antes o en el mismo sitio que cubierto y que termine más tarde.
        // Si no hemos cogido ningún elemento, significa que no podemos unir
        // trabajos, es decir, que va a haber un momento sin que se solape ningún trabajo.
        // En ese caso devolvemos -1. Si, por el contrario, hemos cambiado el valor de "max",
        // esto significa que hemos cogido un elemento de la cola (que llega hasta el instante
        // de tiempo max).

        int max = cubierto;     // nueva variable para lo que hemos cubierto hasta el momento
        
        while (!q.empty() && q.top().c <= cubierto)
        {   // vamos quitando elementos de la cola
            if (q.top().f > max) max = q.top().f;
            q.pop();
        }
        if (max != cubierto) {
            cubierto = max;
            nTareas++;
        }
        else return -1;
    }
    return (cubierto < F) ? -1 : nTareas;
}

bool resuelveCaso()
{
    int C, F, N;
    std::cin >> C >> F >> N;

    if (C == 0 && F == 0 && N == 0)
        return false;

    std::priority_queue<Trabajo> q;
    int c, f;
    for (int i = 0; i < N; i++) {
        std::cin >> c >> f;
        if(f >= C && c <= F) q.push({ c, f });      // no metemos trabajos que no nos interesan
    }

    int sol = resolver(q, C, F);
    std::cout << ((sol != -1) ? std::to_string(sol) : "Imposible") << "\n";

    return true;
}

int main() {
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