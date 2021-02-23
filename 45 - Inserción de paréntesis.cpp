
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
using namespace std;

/*@ <answer>

 La matriz se va rellenando por diagonales, parecido a la multiplicación de matrices (ver https://www.youtube.com/watch?v=hKqLP5UzOu8).
 En la diagonal principal tenemos la palabra completa y en las diagonales de encima el resultado de poner el paréntesis en un sitio u otro.
 Las diagonales inferiores no se rellenan.
 No se puede mejorar espacio.
 Utilizamos tantas matrices de booleanos como letras haya para comprobar si en esa posicion se puede conseguir la letra objetivo.

    Supongamos un abecedario de dos letras, a y b, donde a = a * b y b = b * a, y la palabra "ab". Tenemos por tanto dos matrices A y B.
    Entonces 

        [ a |   ]
        -----------
        [   | b ]

    Es la matriz inicial, es decir:

        A:                  B: 
            [ 1 | 0 ]           [ 0 | 0 ]       
            -----------         -----------     
            [ 0 | 0 ]           [ 0 | 1 ]       

    Para calcular la casilla [1][0], es decir, la siguiente diagonal a calcular tras la llamada inicial, hay que comprobar si:
        -En la casilla [1][0] ya se puede conseguir la letra gracias a una llamada anterior (en principio falso porque aún no lo hemos rellenado).
        -En la casilla [1][0] se puede conseguir mediante la multiplicación de la anterior diagonal. Es decir:
            -Para A tiene que cumplirse "ab" -> A[(1-1)][(0)] y B[(1)][(0+1)] deben ser true.         <<  "a la izquierda" y "debajo" son otra forma
            -Para B tiene que cumplirse "ba" -> B(a la izquierda) y A(debajo) deben ser true.           de expresar B[(1-1)][(0)] y A[(1)][(0+1)]  >>

    Esto se aplica recursivamente: para rellenar cada diagonal, necesitamos la diagonal anterior (inicialmente la diagonal 0 ya rellena).

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

void rellenaTabla(const string& s, Matriz<bool>& A, Matriz<bool>& B, Matriz<bool>& C)
{
    int n = s.length();
    for (int d = 1; d < n; d++) { // recorre diagonales
        for (int i = 0; i < n - d; i++) { // recorre elementos de diagonal
            int j = i + d;
            for (int k = i; k < j; ++k)
            {
                A[i][j] = A[i][j] || (A[i][k] && C[k+1][j]) || (B[i][k] && C[k + 1][j]) || (C[i][k] && A[k + 1][j]);
                B[i][j] = B[i][j] || (A[i][k] && A[k+1][j]) || (A[i][k] && B[k + 1][j]) || (B[i][k] && B[k + 1][j]);
                C[i][j] = C[i][j] || (B[i][k] && A[k+1][j]) || (C[i][k] && B[k + 1][j]) || (C[i][k] && C[k + 1][j]);
            }
        }
    }
}

bool resuelve(string& s) {
    int n = s.length();
    Matriz<bool> A(n, n, false), B(n, n, false), C(n, n, false);
    Matriz<bool>* arr[3] = { &A, &B, &C };      // auxiliar
    for (int i = 0; i < n; i++) {
        (*arr[s[i] - 'a'])[i][i] = true;
    }
    rellenaTabla(s, A, B, C);

    return A[0][n-1];       // esquina superior derecha, en la última diagonal se almacena el resultado final
}

bool resuelveCaso() {

    string in;  cin >> in;
    if (!std::cin)  // fin de la entrada
        return false;

    cout << ((resuelve(in)) ? "SI" : "NO") << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
