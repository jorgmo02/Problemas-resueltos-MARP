#include <fstream>
#include <queue>
#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Grafo {
private:
	int _V;  // número de vértices
	int _A;  // número de aristas
	std::vector<Adys> _ady;  // vector de listas de adyacentes
public:

	/**
	 * Crea un grafo con V vértices.
	 */
	Grafo(int V) : _V(V), _A(0), _ady(_V) {}

	/**
	 * Crea un grafo a partir de los datos en el flujo de entrada.
	 */
	Grafo(std::istream& flujo) : _A(0) {
		flujo >> _V;
		_ady.resize(_V);
		int E, v, w;
		flujo >> E;
		while (E--) {
			flujo >> v >> w;
			ponArista(v, w);
		}
	}

	/**
	 * Devuelve el número de vértices del grafo.
	 */
	int V() const { return _V; }

	/**
	 * Devuelve el número de aristas del grafo.
	 */
	int A() const { return _A; }

	/**
	 * Añade la arista v-w al grafo.
	 * @throws domain_error si algún vértice no existe
	 */
	void ponArista(int v, int w) {
		if (v < 0 || v >= _V || w < 0 || w >= _V)
			throw std::domain_error("Vertice inexistente");
		++_A;
		_ady[v].push_back(w);
		_ady[w].push_back(v);
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
	 * Muestra el grafo en el stream de salida o (para depurar)
	 */
	void print(std::ostream& o = std::cout) const {
		o << _V << " vértices, " << _A << " aristas\n";
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
 * Para mostrar grafos por la salida estándar
 */
inline std::ostream& operator<<(std::ostream& o, Grafo const& g) {
	g.print(o);
	return o;
}

#endif /* GRAFO_H_ */
class ColocarGuardias {
private:
	enum COLORES{NADA=0,ROJO,AZUL};
	std::vector<COLORES> colors;//0 sin visitar, colores 1 y 2
	bool bipartito = true;
	int guardias = 0;
	int componenteBipartita(const Grafo& g, int s)
	{
		std::queue<int> q;
		
		q.push(s);
		COLORES pintaColor = ROJO;
		colors[s] = AZUL;
		int numRojos=0;
		int numAzules=1;

		//realizamos un bfs marcando los colores
		
		while (!q.empty())
		{
			int v = q.front();
			q.pop();
			if(colors[v]==AZUL)
				pintaColor=ROJO;
			else
				pintaColor=AZUL;
			for (auto w : g.ady(v))
			{
				if (colors[w] == NADA)
				{
					colors[w] = pintaColor;
					q.push(w);
					if(pintaColor==ROJO)
						numRojos++;
					else
						numAzules++;
				}
				else if (colors[w] == colors[v])
				{
					bipartito=false;
					return -1;
				}
			}
		}
		return std::min(numRojos,numAzules);
	}

public:
	ColocarGuardias(const Grafo& g, int s) :
		colors(g.V(), NADA) {
		int i = 0;

		while(bipartito && i<g.V())
		{
			if(colors[i]==NADA)
				guardias+=componenteBipartita(g,i);
			++i;
		}
	}
		bool esResoluble(){return bipartito;}
	int minGuardias(){return guardias;}
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	int nNodos, nAristas;
	std::cin >> nNodos;

	if (!std::cin)  // fin de la entrada
		return false;

	std::cin >> nAristas;


	Grafo g(nNodos);
	for(int i=0;i<nAristas;i++)
	{
		int u,w;
		std::cin>>u;
		std::cin>>w;
		g.ponArista(u-1,w-1);
	}

	ColocarGuardias sol(g,0);
	if(!sol.esResoluble())
		std::cout<<"IMPOSIBLE\n";
	else
		std::cout<<sol.minGuardias()<<"\n";

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
