/*
 * AlgVNS.cpp
 *
 *  Created on: 21/04/2014
 *      Author: maikel
 */

#include "AlgVNS.h"

AlgVNS::AlgVNS(vector<Cluster*>& clusters, vector<Objeto*>& objetos, int kMax) {
	setNombreAlgoritmo(" Técnica VNS ");
	setClusters(clusters);
	setObjetos(objetos);
	setDimension(getClusters().at(0)->getDimension());
	_kMax = kMax;
	int* sol = new int [getObjetos().size()];
	_solActual = new int [getObjetos().size()];
	_mejorSol = new int [getObjetos().size()];
	_solucionMutada = new int [getObjetos().size()];
	_tecnicaLocal = NULL;
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		sol[i] = -1;
	}
	setSolucion(sol);
	delete [] sol;

	_centroidesFin = new int *[getClusters().size()];
	for (unsigned int i = 0; i < getClusters().size(); ++i)
		_centroidesFin[i] = new int[getDimension()];
}

AlgVNS::~AlgVNS() {
	if (_tecnicaLocal != NULL) {
		delete _tecnicaLocal;
		_tecnicaLocal = NULL;
	}
}

void AlgVNS::ejecutarAgrupamiento () {

	double desvMejor = 0.0;

	//  ******   Inicialización ******
	//generamos solucion inicial con técnica GRASP
	_tecnicaLocal = new AlgGRASP (getClusters(), getObjetos(), 2);
	_tecnicaLocal->ejecutarAgrupamiento();
	_solActual = _tecnicaLocal->getSolucion();
	setSolucion(_solActual);
	desvMejor = calcularDesvAgrup(_solActual);
	copiarSolucion (_solActual, _mejorSol); // origen, destino
	_solucionMutada = mutarSolucion(_solActual, 1);

	// ****** Procedimiento VNS  ******
	int k = 1;
	do {

		if (calcularDesvAgrup(_solucionMutada) < desvMejor) {
			desvMejor = calcularDesvAgrup(_solucionMutada);
			copiarSolucion(_solucionMutada, _mejorSol);
			copiarSolucion(_mejorSol, _solActual);

			k = 1;

		} else {
			++k;
		}
		copiarSolucion(_solActual, _solucionMutada);
		copiarSolucion(mutarSolucion(_solucionMutada, k), _solucionMutada);
	} while (k < _kMax);

	// ****** Asignación de soluciones ******
	setSolucion(_mejorSol); // Asigne la sol. global del problema
	asignarClusters (); 	// Asigne a cada objeto su clasificación final

}

int* AlgVNS::generarSolucion () {
	// Creamos una solucion aleatoria
	int* sol = new int[getObjetos().size()];
	for (unsigned int i = 0; i < getObjetos().size(); ++i){
		sol[i] = rand () % getClusters().size();
	}
	return sol;
}

int* AlgVNS::mutarSolucion (int* solucion, int k) {
	// Mutamos a una solución en vecindad "k", cambiamos k asignaciones al azar.
	int* sol = new int[getObjetos().size()];
	copiarSolucion(solucion, sol);
	bool repetir = false;
	int aleatorio = 0, newRndCluster = 0, kAux = 0;
	do {
		repetir = true;
		do {
			aleatorio = rand () % getObjetos().size(); // A uno de los objetos al azar
			newRndCluster = rand () % getClusters().size();
			if (sol[aleatorio] != newRndCluster) {
				repetir = false;
				kAux++;
			}
		} while (repetir);
		sol[aleatorio] = newRndCluster;
	} while (kAux < k);

	copiarSolucion(sol, solucion);
	delete sol;
	return solucion;
}
