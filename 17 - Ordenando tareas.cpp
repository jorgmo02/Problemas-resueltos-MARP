//
//  Digrafo.h
//
//  Implementación de grafos dirigidos
//
//  Facultad de InformÃ¡tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef DIGRAFO_H_
#define DIGRAFO_H_

#include <iostream>
#include <stdexcept>
#include <vector>

using Adys = std::vector<int>;  // lista de adyacentes a un vÃ©rtice

class Digrafo {

    int _V;   // nÃºmero de vÃ©rtices
    int _A;   // nÃºmero de aristas
    std::vector<Adys> _ady;   // vector de listas de adyacentes

public:

    /**
     * Crea un grafo dirigido con V vÃ©rtices.
     */
    Digrafo(int V) : _V(V), _A(0), _ady(_V) {}

    /**
     * Crea un grafo dirigido a partir de los datos en el flujo de entrada (si puede).
     * primer es el Ã­ndice del primer vÃ©rtice del grafo en el entrada.
     */
    Digrafo(std::istream& flujo, int primer = 0) : _A(0) {
        flujo >> _V;
        if (!flujo) return;
        _ady.resize(_V);
        int E, v, w;
        flujo >> E;
        while (E--) {
            flujo >> v >> w;
            ponArista(v - primer, w - primer);
        }
    }

    /**
     * Devuelve el nÃºmero de vÃ©rtices del grafo.
     */
    int V() const { return _V; }

    /**
     * Devuelve el nÃºmero de aristas del grafo.
     */
    int A() const { return _A; }

    /**
     * AÃ±ade la arista dirigida v-w al grafo.
     * @throws domain_error si algÃºn vÃ©rtice no existe
     */
    void ponArista(int v, int w) {
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::domain_error("Vertice inexistente");
        ++_A;
        _ady[v].push_back(w);
    }


    /**
     * Comprueba si hay arista de u a v.
     */
    bool hayArista(int u, int v) const {
        for (int w : _ady[u])
            if (w == v) return true;
        return false;
    }


    /**
     * Devuelve la lista de adyacencia de v.
     * @throws domain_error si v no existe
     */
    Adys const& ady(int v) const {
        if (v < 0 || v >= _V)
            throw std::domain_error("Vertice inexistente");
        return _ady[v];
    }


    /**
     * Devuelve el grafo dirigido inverso.
     */
    Digrafo inverso() const {
        Digrafo inv(_V);
        for (int v = 0; v < _V; ++v) {
            for (int w : _ady[v]) {
                inv.ponArista(w, v);
            }
        }
        return inv;
    }


    /**
     * Muestra el grafo en el stream de salida o (para depurar)
     */
    void print(std::ostream& o = std::cout) const {
        o << _V << " vÃ©rtices, " << _A << " aristas\n";
        for (int v = 0; v < _V; ++v) {
            o << v << ": ";
            for (int w : _ady[v]) {
                o << w << " ";
            }
            o << "\n";
        }
    }

};

/**
 * Para mostrar grafos por la salida estÃ¡ndar.
 */
inline std::ostream& operator<<(std::ostream& o, Digrafo const& g) {
    g.print(o);
    return o;
}


#endif /* DIGRAFO_H_ */


#include <iostream>
#include <fstream>
#include <deque>
#include <queue>

class OrdenacionTopologicaSinCiclos {

    std::deque<int> ordenTopologico;
    std::vector<bool> visit;
    std::vector<bool> apilado;
    bool hayCiclo = false;

public:

    OrdenacionTopologicaSinCiclos(Digrafo& g) :
        visit(g.V(), false),
        apilado(g.V(), false)
    {
        for (int i = 0; i < g.V(); i++) {
            if (!visit[i])
                dfs(g, i);
            if (hayCiclo) return;
        }
    }

    void dfs(Digrafo& g, int v) {
        visit[v] = true;
        apilado[v] = true;
        for (int w : g.ady(v))
        {
            if (hayCiclo) return;
            if (!visit[w]) dfs(g, w);
            else if (apilado[w]) hayCiclo = true;
        }
        ordenTopologico.push_front(v);
        apilado[v] = false;
    }

    bool getHayCiclo() const { return hayCiclo; };

    std::deque<int> const& orden() const { return ordenTopologico; };
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int V, A;
    std::cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo g(V);

    for (int i = 0; i < A; i++) {
        int A, B;
        std::cin >> A >> B;
        g.ponArista(A - 1, B - 1);
    }

    OrdenacionTopologicaSinCiclos otsc(g);

    if (otsc.getHayCiclo()) std::cout << "Imposible\n";
    else
    {
        std::deque<int> orden = otsc.orden();
        while (!orden.empty()) {
            std::cout << orden.front() + 1 << " ";
            orden.pop_front();
        }
        std::cout << "\n";
    }
    return true;
}

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
