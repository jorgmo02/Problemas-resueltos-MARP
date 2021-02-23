//MARP Grupo 13
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>

struct Cancion {
	double duracion, puntuacion;
	bool operator<(Cancion const& otro) const {
		return puntuacion / duracion > otro.puntuacion / otro.duracion;
	}
};

struct Nodo {
	std::vector<int> sol; //0 es A y 1 es B, -1 si no está en ninguna
	int k;
	double grabadoA; //Duracion de canciones en la cara A
	double grabadoB; //Duracion de canciones en la cara B
	double puntos;
	double beneficio_est;
	bool operator<(Nodo const& otro) const {
		return otro.beneficio_est > beneficio_est;
	}
};

//O(N) en numero de canciones
double calculo_voraz(std::vector<Cancion> const& canciones, double M, Nodo const& X)
{
	double hueco = (2 * M) - (X.grabadoA + X.grabadoB);
	double estimacion = X.puntos;
	int i = X.k + 1;
	while (i < canciones.size() && canciones[i].duracion <= hueco) {
		hueco -= canciones[i].duracion;
		estimacion += canciones[i].puntuacion;
		++i;
	}
	if (i < canciones.size())
		estimacion += (hueco / canciones[i].duracion) * canciones[i].puntuacion;
	return estimacion; //(estimacion)
}

//Espacio de soluciones de orden 3^n
void mochila_rp(std::vector<Cancion> const& canciones, double M, std::vector<int>& sol_mejor, double& beneficio_mejor)
{
	int N = canciones.size();
	Nodo Y;
	Y.sol = std::vector<int>(N, -1);
	Y.k = -1;
	Y.grabadoB = Y.grabadoA = Y.puntos = 0;
	Y.beneficio_est = calculo_voraz(canciones, M, Y);
	std::priority_queue<Nodo> cola;
	cola.push(Y);
	beneficio_mejor = -1;
	while (!cola.empty() && cola.top().beneficio_est > beneficio_mejor) {
		Y = cola.top(); cola.pop();
		Nodo X(Y);
		++X.k;
		//Grabamos la cancion en la cara A
		if (Y.grabadoA + canciones[X.k].duracion <= M) {
			X.sol[X.k] = 0;
			X.grabadoA = Y.grabadoA + canciones[X.k].duracion;
			X.grabadoB = Y.grabadoB;
			X.puntos = Y.puntos + canciones[X.k].puntuacion;
			X.beneficio_est = Y.beneficio_est;
			if (X.k == N - 1) {
				sol_mejor = X.sol; beneficio_mejor = X.puntos;
			}
			else {
				cola.push(X);
			}
		}
		//Grabamos la cancion en la cara B
		if (Y.grabadoB + canciones[X.k].duracion <= M) {
			X.sol[X.k] = 1;
			X.grabadoB = Y.grabadoB + canciones[X.k].duracion;
			X.grabadoA = Y.grabadoA;
			X.puntos = Y.puntos + canciones[X.k].puntuacion;
			X.beneficio_est = Y.beneficio_est;
			if (X.k == N - 1) {
				sol_mejor = X.sol; beneficio_mejor = X.puntos;
			}
			else {
				cola.push(X);
			}
		}
		//No grabamos la cancion
		X.sol[X.k] = -1;
		X.grabadoA = Y.grabadoA;
		X.grabadoB = Y.grabadoB;
		X.puntos = Y.puntos;
		X.beneficio_est = calculo_voraz(canciones, M, X);
		if (X.beneficio_est > beneficio_mejor) {
			if (X.k == N - 1) {
				sol_mejor = X.sol; beneficio_mejor = X.puntos;
			}
			else {
				cola.push(X);
			}
		}
	}
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, M;
	std::cin >> N;
	if (N == 0)
		return false;
	std::cin >> M;
	std::vector<Cancion> canciones(N);
	for (int i = 0; i < N; i++)
	{
		int dur, punt;
		std::cin >> dur >> punt;
		canciones[i].duracion = dur;
		canciones[i].puntuacion = punt;
	}
	//Ordenamos las canciones segun su mayor relacion de duracion/valor
	std::sort(canciones.begin(), canciones.end());
	std::vector<int> sol;
	double beneficio;
	//Calculamos las canciones que cogemos y en que cara van
	mochila_rp(canciones, M, sol, beneficio);
	std::cout << beneficio << "\n"; //Total de tiempo que tendremos musica
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