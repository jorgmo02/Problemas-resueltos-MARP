#include <iostream>
#include <fstream>
#include <queue>

struct Edificio
{
    int W, E;
    bool operator < (const Edificio& other) const {
        return E > other.E;
    }
};

bool coinciden(const Edificio& a, const Edificio& b) {
    return b.W < a.E;
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(std::priority_queue<Edificio>& q) {
    int nTuneles = 0;
    while (!q.empty()) {
        Edificio top = q.top();
        q.pop();
        while (!q.empty() && coinciden(top, q.top())) q.pop();
        nTuneles++;
    }
    return nTuneles;
}

bool resuelveCaso()
{
    int N;
    std::cin >> N;

    if (N == 0) return false;

    std::priority_queue<Edificio> q;
    int w, e;
    for (int i = 0; i < N; i++) {
        std::cin >> w >> e;
        q.push({ w, e });
    }

    std::cout << resolver(q) << "\n";

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
