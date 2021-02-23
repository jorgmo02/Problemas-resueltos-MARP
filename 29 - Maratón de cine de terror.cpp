#include <iostream>
#include <fstream>
#include <queue>

struct Pelicula
{
	int duracion_;
	int inicio_;
	int fin_;
	
	bool solapaConSiguiente(const Pelicula& otra)
	{	
		return inicio_ < otra.fin_ && otra.inicio_ < fin_;
	}

	//para ordenar en una cola de prioridad
	bool operator<(const Pelicula& otra) const {
		return fin_ < otra.fin_;
	}

	//para ordenar en una cola de prioridad
	bool operator>(const Pelicula& otra) const {
		return fin_ > otra.fin_;
	}

	Pelicula(int horaI, int minI, int duracion) : duracion_(duracion) {
		inicio_ = horaI * 60 + minI;
		fin_ = inicio_ + duracion_ + 10; 
	}
	
	// constructora por defecto para una primera película inicial que no solapa con ninguna otra
	Pelicula() {
		inicio_ = -1;
		fin_ = -1;
	}
}; 

int resolver(std::priority_queue<Pelicula, std::vector<Pelicula>, std::greater<Pelicula>>& cartelera)
{
	int vistas = 0;
	Pelicula viendo;
	while(!cartelera.empty())
	{
		//funcion de seleccion, elegiremos la pelicula que acaba antes que no solape con la actual
		if(!viendo.solapaConSiguiente(cartelera.top()))
		{
			viendo = cartelera.top();
			++vistas;
		}
		//despues de comprobar la pelicula
		cartelera.pop();
	}
	return vistas;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	int nPeliculas;
	std::cin >> nPeliculas;

	if (nPeliculas == 0)
		return false;

	//ordenamos las peliculas por orden de finalizacion
	std::priority_queue<Pelicula, std::vector<Pelicula>, std::greater<Pelicula>> cartelera;
	char aux;
	int horaI,minI,dur;
	for(int i = 0; i < nPeliculas ; i++) {
		std::cin >> horaI >> aux >> minI >> dur;
		cartelera.push(Pelicula(horaI, minI, dur));
	}

	int sol = resolver(cartelera);
	std::cout <<  sol << "\n";

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