#include <iostream>
#include <fstream>
#include <vector>

using Mapa = std::vector<std::string>;

class MaximaMancha
{
private:
    std::vector<std::vector<bool>> visit;
    int max = 0;
    int F = 0, C = 0;
    int numManchas = 0;

    bool correcta(int i, int j) const {
        return i >= 0 && j >= 0 && i < F && j < C;
    }

public:
    MaximaMancha(Mapa& M) :
        F(M.size()), C(M[0].size()),
        max(0)
    {
        visit = std::vector<std::vector<bool>>(F, (std::vector<bool>(C, false)));
        for (int i = 0; i < F; i++) {
            for (int j = 0; j < C; j++) {
                if (!visit[i][j] && M[i][j] == '#') { // se recorre una nueva componente conexa
                    int tam = dfs(M, i, j);
                    if (tam > max) max = tam;
                    numManchas++;
                }
            }
        }
    }
    
    const std::vector<std::pair<int, int>> dirs = { {1,0},{0,1},{-1,0},{0,-1} };

    int dfs(Mapa const& M, int i, int j) {
        visit[i][j] = true;
        int tam = 1;
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (correcta(ni, nj) && M[ni][nj] == '#' && !visit[ni][nj]) {
                tam += dfs(M, ni, nj);
            }
        }
        return tam;
    }

    int getMax() const { return max; };
    
    int getNumManchas() const { return numManchas; };
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int F, C;
    std::cin >> F >> C;

    if (!std::cin)  // fin de la entrada
        return false;

    Mapa m(F);

    for (std::string& linea : m)
        std::cin >> linea;

    MaximaMancha c(m);
    std::cout << c.getNumManchas() << ' ' << c.getMax()<< '\n';
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
