#include <iostream>
#include <fstream>
#include "Grafo.h"

// clase que busca las componentes conexas de un grafo y almacena el tamaño de cada una
class RecorreParaCada {
private:
    std::vector<int> componente;        // componente a la que corresponde cada vértice
    std::vector<int> tamsComponentes;   // tamaño de cada componente conexa (contiene N elementos, donde N es el número de componentes conexas)
    int componenteActual = 0;           // componente conexa en la que estamos trabajando ahora

public:
    RecorreParaCada(Grafo const& g) :
        componente(g.V(), -1)
    {
        for (int i = 0; i < g.V(); i++)
        {    
            if (componente[i] == -1) {  // vértice no visitado, es decir, nueva componente
                tamsComponentes.push_back(dfs(g, i));   // añadir tamaño calculado con dfs al vector de componentes
                componenteActual++;
            }
        }
    }

    int dfs(Grafo const& g, int s) {

        int acum = 1;
        componente[s] = componenteActual;

        for (int w : g.ady(s)) {
            if (componente[w] == -1) {
                acum += dfs(g, w);
            }
        }

        return acum;
    }

    const void print() {
        for(int a : componente)
            std::cout << tamsComponentes[a] << " ";
    }
};

void rellenaGrafo(Grafo& g, int numUsers) {
    int idUser;
    std::cin >> idUser;
    for (int i = 1; i < numUsers; i++) {
        int nextUser;
        std::cin >> nextUser;
        g.ponArista(idUser - 1, nextUser - 1);
        idUser = nextUser;
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int N, M;
    std::cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;

    Grafo grafo(N);
    
    for (int i = 0; i < M; i++)
    {
        int numUsers;
        std::cin >> numUsers;
        if (numUsers > 0)
            rellenaGrafo(grafo, numUsers);
    }

    RecorreParaCada rpc(grafo);
    rpc.print();
    std::cout << "\n";

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
