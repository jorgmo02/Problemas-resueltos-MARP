// Comentario general sobre la soluci�n,
// explicando c�mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

using Matriz = std::vector<std::vector<bool>>;

//O(V)
bool esSumidero(const Matriz &g, int v){
    bool es = true;
    int i = 0;
    while(es && i<g.size()){
       if(i!=v){
          es = (g[i][v] && !g[v][i]);//si hay arista de cualquier i hasta v y no de v hasta i, es sumidero
       }
       i++;
    }
    return es;
}

//O(V)
int buscaSumidero(Matriz const& g){
   int i = 0;
   int j = 0;

   int sumidero = -1;

   //O(V) 2V en el peor caso
   while(i < g.size() && j < g.size()){
        
       if(g[i][j])  //Si i->j, i no es sumidero pero j puede serlo
            i++;
        else        // Si !i->j, i todavía puede ser sumidero
            j++;
   }
   if (i < g.size() && esSumidero(g, i)) sumidero = i;
    return sumidero;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci�n, y escribiendo la respuesta
bool resuelveCaso() {
   
   int V, A;
   std::cin >> V >> A;

   if (!std::cin)  // fin de la entrada
      return false;

   Matriz matrizAdy (V, std::vector<bool>(V, false));

   for(int i = 0; i < A; i++) {
        int v, w;
        std::cin >> v >> w;
        matrizAdy[v][w] = true;
   }
   
   int sumidero = buscaSumidero(matrizAdy);
   if(sumidero == -1) std::cout << "NO\n";
   else std::cout << "SI " << sumidero << "\n";

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
