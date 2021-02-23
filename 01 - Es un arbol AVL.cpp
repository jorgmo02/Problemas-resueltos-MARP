#ifndef bintree_eda_h
#define bintree_eda_h

#include <memory>   // shared_ptr, make_shared
#include <stdexcept>
#include <stack>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class bintree {
protected:
   /*
    Nodo que almacena internamente el elemento (de tipo T),
    y punteros al hijo izquierdo y derecho, que pueden ser
    nullptr si el hijo es vacío (no existe).
    */
   struct TreeNode;
   using Link = std::shared_ptr<TreeNode>;
   struct TreeNode {
      TreeNode(Link const& l, T const& e, Link const& r) : elem(e), left(l), right(r) {};
      T elem;
      Link left, right;
   };
   
   // puntero a la raíz del árbol
   Link raiz;
   
   // constructora privada
   bintree(Link const& r) : raiz(r) {}
   
public:
   // árbol vacío
   bintree() : raiz(nullptr) {}
   
   // árbol hoja
   bintree(T const& e) :
      raiz(std::make_shared<TreeNode>(nullptr, e, nullptr)) {}
   
   // árbol con dos hijos
   bintree(bintree<T> const& l, T const& e, bintree<T> const& r) :
      raiz(std::make_shared<TreeNode>(l.raiz, e, r.raiz)) {}
   
   // constructora por copia, operador de asignación y destructora por defecto
   
   // consultar si el árbol está vacío
   bool empty() const {
      return raiz == nullptr;
   }
   
   // consultar la raíz
   T const& root() const {
      if (empty()) throw std::domain_error("El arbol vacio no tiene raiz.");
      else return raiz->elem;
   }
   
   // consultar el hijo izquierdo
   bintree<T> left() const {
      if (empty()) throw std::domain_error("El arbol vacio no tiene hijo izquierdo.");
      else return bintree<T>(raiz->left);
   }
   
   // consultar el hijo derecho
   bintree<T> right() const {
      if (empty()) throw std::domain_error("El arbol vacio no tiene hijo derecho.");
      else return bintree(raiz->right);
   }
   
   
   // recorridos
   
   std::vector<T> preorder() const {
      std::vector<T> pre;
      preorder(raiz, pre);
      return pre;
   }
   
   std::vector<T> inorder() const {
      std::vector<T> in;
      inorder(raiz, in);
      return in;
   }
   
   std::vector<T> postorder() const {
      std::vector<T> post;
      postorder(raiz, post);
      return post;
   }
   
   std::vector<T> levelorder() const {
      std::vector<T> levels;
      if (!empty()) {
         std::queue<Link> pendientes;
         pendientes.push(raiz);
         while (!pendientes.empty()) {
            Link sig = pendientes.front();
            pendientes.pop();
            levels.push_back(sig->elem);
            if (sig->left != nullptr)
               pendientes.push(sig->left);
            if (sig->right != nullptr)
               pendientes.push(sig->right);
         }
      }
      return levels;
   }

	size_t height()
   {
        return height_rec(raiz);
   }
   
protected:
   static void preorder(Link a, std::vector<T> & pre) {
      if (a != nullptr) {
         pre.push_back(a->elem);
         preorder(a->left, pre);
         preorder(a->right, pre);
      }
   }
   
   static void inorder(Link a, std::vector<T> & in) {
      if (a != nullptr) {
         inorder(a->left, in);
         in.push_back(a->elem);
         inorder(a->right, in);
      }
   }
   
   static void postorder(Link a, std::vector<T> & post) {
      if (a != nullptr) {
         postorder(a->left, post);
         postorder(a->right, post);
         post.push_back(a->elem);
      }
   }
   
public:
   // iterador que recorre el árbol en inorden
   class const_iterator {
   public:
      T const& operator*() const {
         if (ptr == nullptr) throw std::out_of_range("fuera del arbol");
         return ptr->elem;
      }
      
      T const* operator->() const {
         return &operator*();
      }
      
      bool operator==(const_iterator const& other) const {
         return ptr == other.ptr;
      }
      bool operator!=(const_iterator const& other) const {
         return !(*this == other);
      }
      
      const_iterator & operator++() {  // ++ prefijo
         next();
         return *this;
      }
      
   private:
      friend class bintree;
      Link ptr;
      std::stack<Link> ancestros;
      
      // constructores privados
      // construye el iterador al primero
      const_iterator(Link raiz) { ptr = first(raiz); }
      
      // construye el iterador al último
      const_iterator() : ptr(nullptr) {}

      Link first(Link act) {
         if (act == nullptr) {
            return nullptr;
         } else {
            while (act->left != nullptr) {
               ancestros.push(act);
               act = act->left;
            }
            return act;
         }
      }
      
      void next() {
         if (ptr == nullptr) {
            throw std::range_error("El iterador no puede avanzar");
         } else if (ptr->right != nullptr) { // primero del hijo derecho
            ptr = first(ptr->right);
         } else if (ancestros.empty()) { // hemos llegado al final
            ptr = nullptr;
         } else { // podemos retroceder
            ptr = ancestros.top();
            ancestros.pop();
         }
      }
      
   };
   
   const_iterator begin() const {
      return const_iterator(raiz);
   }
   const_iterator end() const {
      return const_iterator();
   }
   
};

// lee un árbol binario de la entrada estándar
template <typename T>
inline bintree<T> leerArbol(T vacio) {
   T raiz;
   std::cin >> raiz;
   if (raiz == vacio) { // es un árbol vacío
      return {};
   } else { // leer recursivamente los hijos
      auto iz = leerArbol(vacio);
      auto dr = leerArbol(vacio);
      return {iz, raiz, dr};
   }
}

#endif // bintree_eda_h

// Coste O(N) en el numero de elementos del arbol
int estaEquilibrado_rec(const bintree<int>& arbol, int height, bool& isEquilibrado){
    if (!arbol.empty() && isEquilibrado){
        height++;
        int leftHeight = estaEquilibrado_rec(arbol.left(), height, isEquilibrado);
        int rightHeight = estaEquilibrado_rec(arbol.right(), height, isEquilibrado);
        if (abs(leftHeight - rightHeight) > 1)  isEquilibrado = false; //Obtenemos las alturas de ambas ramas y las comparamos

        height = (leftHeight > rightHeight) ? leftHeight : rightHeight;
    }
    return height;
}

// Coste O(N) en el numero de elementos del árbol
bool esDeBusqueda(const bintree<int>& arbol)
{
    if (arbol.empty()) return true;
    vector<int> inorden = arbol.inorder();
    int i = 0;
    auto it = inorden.begin();
    while (std::next(it) != inorden.end() && *it < *(std::next(it)))
    {
	    ++it;
    }
    ++it;//tras el bucle, si es de orden el iterador quedará antes del final
		 return it == inorden.end();
    //while (i < inorden.size() - 1 && inorden[i] < inorden[i + 1])
    //    i++;
    //return i == inorden.size() - 1;
}

// Coste O(N) en el numero de elementos del arbol
bool estaEquilibrado(const bintree<int>& arbol)
{
    bool isEquilibrado = true;
    
    estaEquilibrado_rec(arbol, 0, isEquilibrado);

    return isEquilibrado;
}

// O(N) en el numero de elementos del arbol
bool resolver(const bintree<int>& arbol)
{
    return esDeBusqueda(arbol) && estaEquilibrado(arbol);
}

// O(N) en el número de elementos del árbol
void resuelveCaso()
{
    bintree<int> arbol;
    arbol = leerArbol(-1);

    cout << ((resolver(arbol)) ? "SI" : "NO") << endl;
}

// O(Número de casos de prueba * N) siendo N el número de nodos de cada caso de prueba
int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream entrada("casos.txt");
   auto cinbuf = cin.rdbuf(entrada.rdbuf());
#endif
   
   int numCasos;
   cin >> numCasos;
   for (int i = 0; i < numCasos; ++i) 
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
