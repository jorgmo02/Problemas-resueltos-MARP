
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include "Grafo.h"
#include "GrafoValorado.h"
#include "DigrafoValorado.h"
#include <limits>
#include "IndexPQ.h"

template <typename Valor>
class Dijkstra
{
protected:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<int> dist;
	std::vector<AristaDirigida<Valor>> ult;
	std::vector<int> aristasHasta;
	IndexPQ<Valor> pq;
	int fin;

	void relajar(AristaDirigida<Valor> a)
	{
		int desde = a.desde(); int hasta = a.hasta();
		//std::cout << desde+1 << " --> " << hasta+1 << "\n";
		//Nuevo camino minimo
		if (dist[hasta] > dist[desde] + a.valor())
		{
			//std::cout << "Mejora " << dist[hasta] << " con " << dist[desde] + a.valor() << "\n";
			dist[hasta] = dist[desde] + a.valor();
			ult[hasta] = a;
			aristasHasta[hasta] = aristasHasta[desde] + 1;
			pq.update(hasta, dist[hasta]);
		}
		//Mismo valor
		else if (dist[hasta] == dist[desde] + a.valor())
		{
			//std::cout << "Iguala " << dist[hasta] << "\n";
			//ult[hasta].push_back(a);
			if (aristasHasta[desde] + 1 < aristasHasta[hasta])
			{
				dist[hasta] = dist[desde] + a.valor();
				ult[hasta] = a;
				aristasHasta[hasta] = aristasHasta[desde] + 1;
				// no hay que hacer update porque ya son iguales
			}
		}
		//else
			//std::cout << "No mejora " << dist[hasta] << " con " << dist[desde] + a.valor() << "\n";
	}
	int numCaminos_rec(int v) const
	{
		if (v == origen)
			return 1;
		int cam = 0;
		for (auto it = ult[v].begin(); it != ult[v].end(); ++it)
			cam += numCaminos_rec(it->desde());
		return cam;
	}
public:
	Dijkstra(DigrafoValorado<Valor>& g, int o) :
		origen(o), dist(g.V(), INF), ult(g.V()), pq(g.V()),
		aristasHasta(g.V(), 0)
	{
		dist[origen] = 0;
		aristasHasta[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty())
		{
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	bool hayCamino(int v) const { return dist[v] != INF; }
	Valor distancia(int v) const { return dist[v]; }
	std::deque<Valor> camino(int v) const
	{
		std::deque<Valor> cam;

		AristaDirigida<Valor> a;
		for (a = ult[v]; a.desde() != origen; a = ult[a.desde()])
			cam.push_front(a);
		cam.push_front(a);

		return cam;
	}
	int getAristas(int v) const {return aristasHasta[v];}
};

class BFS {
	const int INF = std::numeric_limits<int>::max();
	std::vector<int> dist;
	int alcanzados = 0;
	int total;

	void bfs(int o, Grafo const& g) {
		std::queue<int> cola;
		dist[o] = 0;
		cola.push(o);
		int nuevaDist = 0;
		alcanzados = 1;
		while (!cola.empty()) {
			int v = cola.front(); cola.pop();
			nuevaDist = dist[v] + 1;
			for (auto w : g.ady(v)) {
				if (dist[w] == INF) {
					alcanzados++;
					dist[w] = nuevaDist;
					cola.push(w);
				}
			}
		}
	}
public:
	BFS(Grafo const& g, int o) :
		dist(g.V(), INF), alcanzados(0), total(g.V()) {
		bfs(o, g);
	}

	int getDist(int v) const { return dist[v]; }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
	int nNodos;
	std::cin >> nNodos;
	if (!std::cin)  // fin de la entrada
		return false;

	Grafo g(nNodos);
	DigrafoValorado<int> gv(nNodos);
	long int nAristas;
	std::cin >> nAristas;
	for (int k = 0; k < nAristas; k++) {
		int uno, otro, valor;
		std::cin >> uno >> otro >> valor;
		g.ponArista(uno - 1, otro - 1);
		gv.ponArista({ uno - 1, otro - 1, valor });
		gv.ponArista({ otro - 1, uno - 1, valor });
	}

	int consultas;

	std::cin >> consultas;

	for (int k = 0; k < consultas; k++) {
		int desde, hasta;
		std::cin >> desde >> hasta;

		//Calculamos el cmino de coste menor y el camino con menor cantidad de aristas
		Dijkstra<int> d(gv, desde - 1);
		BFS b = BFS(g, desde - 1);

		if(!d.hayCamino(hasta - 1))
			std::cout<<"SIN CAMINO\n";
		else {
			std::cout<<d.distancia(hasta - 1);
			std::cout << ((d.getAristas(hasta - 1) == b.getDist(hasta - 1)) ? " SI\n" : " NO\n");		
		}
	}

	std::cout << "---\n";

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
