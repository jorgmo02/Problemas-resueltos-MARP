#include <iostream>
#include <fstream>
#include <string>

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
using string = std::string;

int resolver_aux(const std::string& prim, const std::string& seg, int i, int j, Matriz<int>& mat)
{
	if (i == prim.size() || j == seg.size())
		mat[i][j] = 0;

	if (mat[i][j] == -1) {
		if (prim[i] == seg[j]) mat[i][j] = resolver_aux(prim, seg, i + 1, j + 1, mat) + 1;
		else mat[i][j] = (std::max<int>(resolver_aux(prim, seg, i + 1, j, mat), resolver_aux(prim, seg, i, j + 1, mat)));
	}

	return mat[i][j];
}

void reconstruir(const std::string& prim, const std::string& seg, int i, int j, Matriz<int>& mat, std::string& reconstruida)
{
	if (i < prim.length() && j < seg.length())	//Comprobamos que no se salga del vector con ninguna de las palabras
	{
		if (prim[i] == seg[j]) {	//Si son iguales se mete a la solucion y se avanza en ambas palabras
			reconstruida.push_back(prim[i]);
			reconstruir(prim, seg, i + 1, j + 1, mat, reconstruida);
		}
		else
		{
			if (mat[i + 1][j] > mat[i][j + 1]) {	//Si es mayor por la parte izquierda
				if (mat[i + 1][j] > mat[i + 1][j + 1]) {
					reconstruir(prim, seg, i + 1, j, mat, reconstruida);
				}
				else {
					reconstruir(prim, seg, i + 1, j + 1, mat, reconstruida);
				}
			}
			else if (mat[i][j + 1] > mat[i + 1][j + 1]) {	//Si es mayor por la parte derecha
				reconstruir(prim, seg, i, j + 1, mat, reconstruida);
			}
			else {
				reconstruir(prim, seg, i + 1, j + 1, mat, reconstruida);
			}
		}
	}
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
std::string resolver(const std::string& prim, const std::string& seg)
{
	Matriz<int> mat(prim.length() + 1, seg.length() + 1, -1);
	int length = resolver_aux(prim, seg, 0, 0, mat);
	std::string reconstruida;
	reconstruir(prim, seg, 0, 0, mat, reconstruida);
	return reconstruida;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	std::string primera, segunda;
	std::cin >> primera >> segunda;

	if (!std::cin) return false;

	std::cout << resolver(primera, segunda) << "\n";	//Te escribe la sucesion comun mas larga

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

