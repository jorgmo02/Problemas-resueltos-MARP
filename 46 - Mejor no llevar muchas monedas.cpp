
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Matriz.h"
#include "EnterosInf.h"

struct Moneda {
	int cant;	//Cuantas tenemos
	int valor;	//El valor que tiene 

	bool operator<(const Moneda& other) const {
		return valor < other.valor;
	}
	bool operator>(const Moneda& other) const {
		return valor > other.valor;
	}

	Moneda(int c, int v) :cant(c), valor(v) {}
};

//monedas i, j minimo numero de monedas para pagar j si tenemos disponibles desde la moneda i
EntInf calderilla(int i, int j, const std::vector<int>& valores, const std::vector<int>& cantidades, Matriz<EntInf>& S) {
	if (j == 0)
		return 0;

	if (i >= valores.size())
		return Infinito;	//Fuera de la matriz

	if (S[i][j] != -1)
		return S[i][j];		//Subproblema ya resuelto

	//Si no podemos usar otra moneda de este tipo 
	if (valores[i] > j)
		S[i][j] = calderilla(i + 1, j, valores, cantidades, S);

	//Si podemos usar moneda de este tipo
	else
	{
		EntInf min = Infinito;
		for (int k = 0; k <= cantidades[i] && valores[i] * k <= j; k++) {
			min = std::min(calderilla(i + 1, j - valores[i] * k, valores, cantidades, S) + k, min);
		}
		S[i][j]=min;
	}

	return S[i][j];
}

//int resolver(std::vector<int>& valores, std::vector<int>& monedas, int cantidadAPagar)
//{
//	Matriz<EntInf> S(cantidades.size(), cantidadAPagar, -1);
//	EntInf res = calderilla(0, cantidadAPagar, valores, cantidades, S);
//
//}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	int nTipos;
	std::cin >> nTipos;
	if (!std::cin)  // fin de la entrada
		return false;

	std::vector<int> valores;
	for (int i = 0; i < nTipos; i++) {
		int valor;
		std::cin >> valor;
		valores.push_back(valor);
	}
	std::vector<int> cantidades;
	for (int i = 0; i < nTipos; i++) {
		int cantidad;
		std::cin >> cantidad;
		cantidades.push_back(cantidad);
	}

	int cantidadAPagar;
	std::cin >> cantidadAPagar;

	//std::vector<Moneda> monedas;
	//for (int i = 0; i < nTipos; i++) {
		//monedas.push_back({ cantidades[i],valores[i] });
	//}
	//std::sort(monedas.begin(), monedas.end(), std::less<Moneda>);
	Matriz<EntInf> S(nTipos, cantidadAPagar + 1, -1);
	EntInf sol = calderilla(0, cantidadAPagar, valores, cantidades, S);

	if (sol == Infinito)
		std::cout << "NO\n";
	else
		std::cout << "SI " << sol << "\n";
	//escribir sol

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
