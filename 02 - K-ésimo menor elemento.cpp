// Jorge Moreno Mart�nez

// El problema se resuelve utilizando la variable tam_i, que
// representa el n�mero de nodos en el hijo izquierdo m�s 1.
// Este valor es suficiente para saber por d�nde hay que explorar
// (por eliminaci�n, si no coincide con la ra�z ni est� en el hijo izquierdo,
// est� en el hijo derecho o no existe el valor k-�simo).

// Para resolverlo, el algoritmo de la funci�n k-�simo (donde k es el �ndice buscado) es el siguiente:
// -Se explora el nodo ra�z (termina si el �rbol est� vac�o).
// -Si el �ndice k coincide con la ra�z, termina.
// -Si no, si el �ndice k-�simo es menor que tam_i, el nodo buscado est� en la
// rama izquierda, as� que buscamos recursivamente por ese lado restando k-tam_i.
// -Si el �ndice k-�simo es mayor que tam_i, el nodo buscado est� en la rama
// derecha o no existe, por lo que buscamos por la derecha (tambi�n restando k-tam_i).

// Al reequilibrar el �rbol, hay que actualizar los tam_i.
// El tam_i es el n�mero de nodos a la izquierda del �rbol. Esto significa que al rotar a la derecha,
// el tam_i de la antigua ra�z cambia y pasa a ser el tam_i del hijo derecho del antiguo hijo izquierdo + 1.
// No tenemos tam_d (el n�mero de nodos a la derecha), pero podemos calcularlos a partir de la diferencia
// entre la ra�z y el hijo izquierdo. Por tanto, el nuevo tam_i de la antigua ra�z al rotar a la derecha
// es: tam_i (raiz) - tam_i (hijoIzq).
// Al rotar hacia la izquierda, la operaci�n es la inversa: el tam_i que cambia es el del hijo derecho,
// y lo que hacemos es sumar los dos tam_i (de la antigua ra�z y del hijo derecho).

#include <iostream>
#include <fstream>
#include <exception>
//
//  TreeSet_AVL.h
//
//  Implementaci�n de conjuntos mediante �rboles de b�squeda AVL
//
//  Facultad de Inform�tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

#ifndef TREESET_AVL_H_
#define TREESET_AVL_H_

#include <algorithm>
#include <functional>
#include <stack>
#include <stdexcept>
#include <utility>


template <class T, class Comparator = std::less<T>>
class Set {
protected:

    /*
     Nodo que almacena internamente el elemento (de tipo T),
     punteros al hijo izquierdo y derecho, que pueden ser
     nullptr si el hijo es vacío, y la altura.
     */
    struct TreeNode;
    using Link = TreeNode*;
    struct TreeNode {
        T elem;
        Link iz, dr;
        int altura;
        int tam_i;
        TreeNode(T const& e, Link i = nullptr, Link d = nullptr,
            int alt = 1, int t_i = 1) : elem(e), iz(i), dr(d), altura(alt), tam_i(t_i) {}
    };

    // puntero a la raíz de la estructura jerárquica de nodos
    Link raiz;

    // número de elementos (cardinal del conjunto)
    int nelems;

    // objeto función que compara elementos (orden total estricto)
    Comparator menor;

public:

    // constructor (conjunto vacío)
    Set(Comparator c = Comparator()) : raiz(nullptr), nelems(0), menor(c) {}

    // constructor por copia
    Set(Set const& other) {
        copia(other);
    }

    // operador de asignación
    Set& operator=(Set const& that) {
        if (this != &that) {
            libera(raiz);
            copia(that);
        }
        return *this;
    }

    ~Set() {
        libera(raiz);
    };

    bool insert(T const& e) {
        return inserta(e, raiz);
    }

    bool empty() const {
        return raiz == nullptr;
    }

    int size() const {
        return nelems;
    }

    bool contains(T const& e) const {
        return pertenece(e, raiz);
    }

    bool erase(T const& e) {
        return borra(e, raiz);
    }

    T const& kesimo_aux(int k, Link a) const {
        if (k == a->tam_i)
            return a->elem;
        else if (menor(k, a->tam_i))
            return kesimo_aux(k, a->iz);
        else
            return kesimo_aux(k - a->tam_i, a->dr);

    }

    T const& kesimo(int k) const {
        if (k > nelems)
            throw std::domain_error("No existe k-esimo");
        return kesimo_aux(k, raiz);
    }

protected:

    void copia(Set const& other) {
        raiz = copia(other.raiz);
        nelems = other.nelems;
        menor = other.menor;
    }

    static Link copia(Link a) {
        if (a == nullptr) return nullptr;
        else return new TreeNode(a->elem, copia(a->iz), copia(a->dr), a->altura);
    }

    static void libera(Link a) {
        if (a != nullptr) {
            libera(a->iz);
            libera(a->dr);
            delete a;
        }
    }

    bool pertenece(T const& e, Link a) const {
        if (a == nullptr) {
            return false;
        }
        else if (menor(e, a->elem)) {
            return pertenece(e, a->iz);
        }
        else if (menor(a->elem, e)) {
            return pertenece(e, a->dr);
        }
        else { // e == a->elem
            return true;
        }
    }

    bool inserta(T const& e, Link& a) {
        bool crece;
        if (a == nullptr) { // se inserta el nuevo elemento e
            a = new TreeNode(e);
            ++nelems;
            crece = true;
        }
        else if (menor(e, a->elem)) {
            crece = inserta(e, a->iz);
            if (crece) {
                a->tam_i++;
                reequilibraDer(a);
            }
        }
        else if (menor(a->elem, e)) {
            crece = inserta(e, a->dr);
            if (crece) reequilibraIzq(a);
        }
        else // el elemento e ya está en el árbol
            crece = false;
        return crece;
    }

    int altura(Link a) {
        if (a == nullptr) return 0;
        else return a->altura;
    }

    void rotaDer(Link& r2) {
        Link r1 = r2->iz;

        r2->tam_i -= r1->tam_i;

        r2->iz = r1->dr;
        r1->dr = r2;
        r2->altura = std::max(altura(r2->iz), altura(r2->dr)) + 1;
        r1->altura = std::max(altura(r1->iz), altura(r1->dr)) + 1;
        r2 = r1;
    }

    void rotaIzq(Link& r1) {
        Link r2 = r1->dr;

        r2->tam_i += r1->tam_i;

        r1->dr = r2->iz;
        r2->iz = r1;
        r1->altura = std::max(altura(r1->iz), altura(r1->dr)) + 1;
        r2->altura = std::max(altura(r2->iz), altura(r2->dr)) + 1;
        r1 = r2;
    }

    void rotaIzqDer(Link& r3) {
        rotaIzq(r3->iz);
        rotaDer(r3);
    }

    void rotaDerIzq(Link& r1) {
        rotaDer(r1->dr);
        rotaIzq(r1);
    }

    void reequilibraIzq(Link& a) {
        if (altura(a->dr) - altura(a->iz) > 1) {
            if (altura(a->dr->iz) > altura(a->dr->dr))
                rotaDerIzq(a);
            else rotaIzq(a);
        }
        else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
    }

    void reequilibraDer(Link& a) {
        if (altura(a->iz) - altura(a->dr) > 1) {
            if (altura(a->iz->dr) > altura(a->iz->iz))
                rotaIzqDer(a);
            else rotaDer(a);
        }
        else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
    }

    // devuelve y borra el mínimo del árbol con raíz en a
    T borraMin(Link& a) {
        if (a->iz == nullptr) {
            T min = a->elem;
            a = a->dr;
            --nelems;
            return min;
        }
        else {
            T min = borraMin(a->iz);
            reequilibraIzq(a);
            return min;
        }
    }

    bool borra(T const& e, Link& a) {
        bool decrece = false;
        if (a != nullptr) {
            if (menor(e, a->elem)) {
                decrece = borra(e, a->iz);
                if (decrece) reequilibraIzq(a);
            }
            else if (menor(a->elem, e)) {
                decrece = borra(e, a->dr);
                if (decrece) reequilibraDer(a);
            }
            else { // e == a->elem
                if (a->iz == nullptr || a->dr == nullptr) {
                    Link aux = a;
                    a = (a->iz == nullptr) ? a->dr : a->iz;
                    --nelems;
                    delete aux;
                }
                else { // tiene dos hijos
                    T min = borraMin(a->dr);
                    a->elem = min;
                    reequilibraDer(a);
                }
                decrece = true;
            }
        }
        return decrece;
    }

public:
    // iteradores que recorren los elementos del conjunto de menor a mayor
    class const_iterator {
    public:
        T const& operator*() const {
            if (act == nullptr)
                throw std::out_of_range("No hay elemento a consultar");
            return act->elem;
        }

        T const* operator->() const {
            return &operator*();
        }

        const_iterator& operator++() {  // ++ prefijo
            next();
            return *this;
        }

        bool operator==(const_iterator const& that) const {
            return act == that.act;
        }

        bool operator!=(const_iterator const& that) const {
            return !(this->operator==(that));
        }

    protected:
        friend class Set;
        Link act;
        std::stack<Link> ancestros;  // antecesores no visitados

        // construye el iterador al primero
        const_iterator(Link raiz) { act = first(raiz); }

        // construye el iterador al último
        const_iterator() : act(nullptr) {}

        Link first(Link ptr) {
            if (ptr == nullptr) {
                return nullptr;
            }
            else { // buscamos el nodo más a la izquierda
                while (ptr->iz != nullptr) {
                    ancestros.push(ptr);
                    ptr = ptr->iz;
                }
                return ptr;
            }
        }

        void next() {
            if (act == nullptr) {
                throw std::out_of_range("El iterador no puede avanzar");
            }
            else if (act->dr != nullptr) { // primero del hijo derecho
                act = first(act->dr);
            }
            else if (ancestros.empty()) { // hemos llegado al final
                act = nullptr;
            }
            else { // podemos retroceder
                act = ancestros.top();
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


#endif

// funci�n que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver(const Set<int>& set, int k) {
    try {
        int res = set.kesimo(k);
        std::cout << res << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "??" << std::endl;
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci�n, y escribiendo la respuesta
bool resuelveCaso() {

    int n; //n de casos
    std::cin >> n;
    if (n <= 0)
        return false;
    Set<int> set;
    for (int i = 0; i < n; i++) {
        int aux;
        std::cin >> aux;
        set.insert(aux);
    }

    int m;//n de consultas
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int consulta;
        std::cin >> consulta;

        resolver(set, consulta);
    }

    std::cout << "---" << std::endl;

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