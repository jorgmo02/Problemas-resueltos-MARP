#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"


bool devoradoraCome(std::vector<int>& cubos, int& i, int& j) {

    if (cubos[i] > cubos[j]) {      // devvoradora elige
        i++;
        return true;
    }
    j--;
    return false;
}

/*
    caso recursivo: sol = max(comer por la izquierda, comer por la derecha)
                    comer por la izquierda = (total += grano izquierda, devoradora come, llamada recursiva i + 1)
                    comer por la derecha   = (total += grano derecha  , devoradora come, llamada recursiva j + 1)
    casos base: no quedan cubos -> sol += 0
                queda un solo cubo -> sol = único cubo

    Programación dinámica: tabla bidimensional i*j -> reducible
*/
int resolver(std::vector<int>& cubos, int i, int j, Matriz<int>& resultados)
{
    // caso base: no quedan cubos
    if (i > j) return 0;

    if (resultados[i][j] == -1)
    {
        if (i == j) resultados[i][j] = cubos[i];
        else {

            // comer por la izquierda
            int comerIzquierda = cubos[i];
            i++;
            bool izq = devoradoraCome(cubos, i, j);
            comerIzquierda += resolver(cubos, i, j, resultados);

            // deshacer cambios tras llamada recursiva
            i--;
            (izq) ? i-- : j++;
            izq = false;

            // comer por la derecha
            int comerDerecha = cubos[j];
            j--;
            izq = devoradoraCome(cubos, i, j);
            comerDerecha += resolver(cubos, i, j, resultados);

            j++;
            (izq) ? i-- : j++;
        
            resultados[i][j] = std::max(comerIzquierda, comerDerecha);
        }
    }
    return resultados[i][j];
}
//
//
//int resolverReduciendoMemoria(std::vector<int>& cubos, int i, int j, std::vector<int>& resultados)
//{
//    // caso base: no quedan cubos
//    if (i > j) return 0;
//
//    if (i == j) resultados[i] = cubos[i];
//    else
//    {
//        // comer por la izquierda
//        int comerIzquierda = cubos[i];
//        i++;
//        bool izq = devoradoraCome(cubos, i, j);
//        comerIzquierda += resolverReduciendoMemoria(cubos, i, j, resultados);
//
//        // deshacer cambios tras llamada recursiva
//        i--;
//        (izq) ? i-- : j++;
//        izq = false;
//
//        // comer por la derecha
//        int comerDerecha = cubos[j];
//        j--;
//        izq = devoradoraCome(cubos, i, j);
//        comerDerecha += resolverReduciendoMemoria(cubos, i, j, resultados);
//
//        j++;
//        (izq) ? i-- : j++;
//        
//        resultados[i][j] = std::max(comerIzquierda, comerDerecha);
//    }
//    return resultados[i][j];
//}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (N == 0)
        return false;

    std::vector<int> cubos(N);
    int cubo;
    for (int i = 0; i < N; i++) {
        std::cin >> cubo;
        cubos[i] = cubo;
    }

    Matriz<int> resultados(N, N, -1);
    int sol = resolver(cubos, 0, N-1, resultados);
    
    //std::vector<int> resultadosVector = cubos;
    //int sol = resolverReduciendoMemoria(cubos, 1, N - 1, resultadosVector);

    std::cout << sol << "\n";

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
