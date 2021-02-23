#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// función que resuelve el problema
// O(N), donde N es el número de pilas
int resolver(std::vector<int> pilas, const int voltaje) {

    int inicio = 0;
    int fin = pilas.size() - 1;
    int cochesFuncionando = 0;
    //Habremos encontrado la solucion cuando nos quedemos sin pilas
    while (inicio < fin)
    {
        //FUNCION DE SELECCION
        //Elegiremos la pareja que desperdicie menos energia, esto es
        //la mayor y la menor pila
        int min = pilas[inicio];
        int max = pilas[fin];

        //Test de factibilidad,
        //las pilas elegidas suman suficiente volaje
        if (min + max >= voltaje)
        {
            //pondremos las pilas
            ++inicio;
            --fin;
            cochesFuncionando++;
        }
        else
        {
            //descartamos la menor pila y pasaremos a comprobar
            //con la siguiente mas grande
            ++inicio;
        }
    }
    return cochesFuncionando;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    int nPilas, voltaje;
    std::cin >> nPilas >> voltaje;

    std::vector<int> pilas;
    for (int i = 0; i < nPilas; ++i)
    {
        int c; std::cin >> c;
        pilas.push_back(c);
    }

    //N log N
    //Ordenamos de mayor a menor
    std::sort(pilas.begin(), pilas.end());//wow!

    //coste lineal
    std::cout << resolver(pilas, voltaje) << "\n";

}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}