//============================================================================
// Name        : main.cpp
// Author      : Miguel
// Version     :
// Copyright   : alu4117
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <ctime>
#include <sys/time.h>
#include "Simulador.h"

// Devuelve la diferencia entra dos tiempo en segundos!!
double timeval_diff (struct timeval * a, struct timeval * b) {
	return
			(double) (a->tv_sec + (double) a->tv_usec / 10000000) -
			(double) (b->tv_sec + (double) b->tv_usec / 10000000);
}

int main() {
	struct timeval start, end;

	char aleatoriosInd = 's', resp = 's';
	unsigned int nIndividuos = 1, nClusters = 1, dim = 2;

	cout << "  ******           MENÚ PRINCIPAL         ****** " << endl;
	cout << "  Práctica Algoritmos de Clustering. DAA. "        << endl;
	cout << "  ******  ******  ******  ******  ******  ****** " << endl;
	cout << "  - Individuos aleatorios (s/n) ? ";
	cin >> aleatoriosInd;
	cout << endl;
	if (aleatoriosInd == 's'){
		cout << " - Introduzca n. de individuos a crear aleatoriamente: ";
		cin >> nIndividuos;
		cout << " - N. de características: ";
		cin >> dim;
	}
	cout << endl;


	int alg = -1;
	Simulador* _sim = NULL;
	while (true) {

		cout << " - Introduzca el n. de clusters a crear: ";
		cin >> nClusters;

		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
		cout << "  ******             MENÚ PRINCIPAL          ****** " << endl;
		cout << "  ***   Práctica Algoritmos de Clustering. DAA. *** " << endl;
		cout << "  ******  ******  ******  ******  ******  ******  *" << endl;
		cout << " 1) K-Medias. " << endl;
		cout << " 2) Técnica Voraz. " << endl;
		cout << " 3) Técnica Grasp. " << endl;
		cout << " 4) Método MultiArranque. " << endl;
		cout << " 5) Metodo VNS (Búsqueda por Entorno Variable)"<< endl;
		cout << " Otra) Salir." << endl;
		cout << " - Seleccione un algoritmo de Clustering a ejecutar: " << endl;
		cin >> alg;

		if (alg < 0 || alg > 6) // Evaluación de condición de SALIR del menú.
			break;

		if (aleatoriosInd == 's')
			_sim = new Simulador (nClusters, nIndividuos, dim, alg - 1);
		else {
			string fich;
			cout << " Introduzca fichero de datos de entrada:  " << endl;
			cin >> fich;
			_sim = new Simulador (fich, nClusters, alg - 1);
		}

		gettimeofday(&start, NULL);
		_sim->getAlgoritmo()->ejecutarAgrupamiento();
		gettimeofday(&end, NULL);
		cout << "\n\n \t + Distancia (SSE del agrupamiento)  = " << _sim->getAlgoritmo()->calcularDesvAgrup(_sim->getAlgoritmo()->getSolucion()) << endl << endl;
		cout << " \t - Tiempo de CPU consumido: " << timeval_diff(&end, &start) * 1000.0 << endl;
		cout << " ¿ Mostrar resultados ? (s/n) " << endl << endl;
		cin >> resp;
		if (resp == 's')
			_sim->getAlgoritmo()->mostrar();

		cout << " ¿ Ejecutar otro algoritmo ? (s/n)" << endl;
		cin >> resp;
		if (resp != 's')
			break;
	}

	cout << "!!! FIN DE LA EJECUCIÓN!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
