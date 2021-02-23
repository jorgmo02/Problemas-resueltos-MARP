
// Grupo 13

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

class ColaUrgencias {
protected:
	struct paciente     //Struct de datos del paciente que esta dentro de la clase ColaUrgencias
	{
		std::string  nombre_;
		int gravedad_,llegada_;
        //El coste de los comparadores es O(1)
		bool operator>(const paciente& b) const
		{
			return (gravedad_>b.gravedad_) || (gravedad_==b.gravedad_ && llegada_<b.llegada_);
		}
		bool operator<(const paciente& b) const
		{
			return (gravedad_<b.gravedad_) || (gravedad_==b.gravedad_ && llegada_>b.llegada_);;
		}

		paciente(std::string nombre,int grav,int lleg):nombre_(nombre),gravedad_(grav),llegada_(lleg){}
	};
	int totIngresos_ = 0;
	std::priority_queue<paciente> queue_;

public:
    ColaUrgencias():totIngresos_(0),queue_(){};
    ~ColaUrgencias(){};
	//Coste O(log N) para N pacientes esperando
    void ingresarPaciente(std::string nombre, int gravedad)
    {
	    totIngresos_++;
		queue_.push({nombre, gravedad, totIngresos_});
    }
	//O(1)
    std::string nombrePrimero() const
    {
	    return queue_.top().nombre_;
    }
	//O(log N) para N pacientes esperando
    void atenderPaciente()
    {
    	queue_.pop();//log(N)
    }
	//O(1)
	bool quedanPacientes() const { return !queue_.empty(); };
};

//O(N log N) para el numero de operaciones 'I' 'A'
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int nActions = 0;
   std::cin>> nActions;

   if (!std::cin || nActions==0)  // fin de la entrada
      return false;
   
    char newAction = ' ';
    std::string newPatient;
    int priorityVal;

    ColaUrgencias cola;
	//O (N log N) para N acciones
	//En el peor caso todas son inserciones al contrario que la prioridad
    for (int k = 0; k < nActions; k++){
        std::cin>> newAction;
        if (newAction == 'I') {
            std::cin >> newPatient >> priorityVal;
			cola.ingresarPaciente(newPatient, priorityVal);//logN siendo N el numero de pacientes
        }
		else if (newAction == 'A'){
			std::cout << cola.nombrePrimero() << "\n";//1
            cola.atenderPaciente();//logN siendo N el numero de pacientes
        }
    }
    std::cout << "---\n";
   
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
