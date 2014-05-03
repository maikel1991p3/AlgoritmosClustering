/*
 * AlgMultiArranque.cpp
 *
 *  Created on: 12/04/2014
 *      Author: maikel
 */

#include "AlgMultiArranque.h"

AlgMultiArranque::AlgMultiArranque(vector<Cluster*>& clusters, vector<Objeto*>& objetos) {
	setNombreAlgoritmo(" Técnica MultiArranque ");
	setObjetos(objetos);
	setClusters(clusters);
	setDimension(getClusters()[0]->getDimension());

	int* sol = new int [getObjetos().size()];
	_solActual = new int [getObjetos().size()];
	_mejorSol = new int [getObjetos().size()];
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		sol[i] = -1;
	}
	setSolucion(sol);
	delete [] sol;
	_tecnicaLocal = NULL;
	_centroidesFin = new int *[getClusters().size()];
	for (unsigned int i = 0; i < getClusters().size(); ++i)
		_centroidesFin[i] = new int[getDimension()];
}

AlgMultiArranque::~AlgMultiArranque() {
	if (_mejorSol != NULL)
		delete [] _mejorSol;
	if (_solActual != NULL)
		delete [] _solActual;
	if (_tecnicaLocal != NULL)
		delete _tecnicaLocal;
}

void AlgMultiArranque::ejecutarAgrupamiento () {
	int contadorMejora = 0, tipo = 0;
	double desvMejor = 0.0;
	TIPO_TECN_LOCAL tecnicaLocal;

	cout << " Elija técnica local: 0 = LOCAL VORAZ, 1 = LOCAL GRASP " << endl;
	cin >> tipo;
	tecnicaLocal = (TIPO_TECN_LOCAL) tipo;

	//  ******   Inicialización ******
	generarCentroides();
	_solActual = busquedaLocal(tecnicaLocal);
	desvMejor = calcularDesvAgrup(_solActual);
	guardarCentroides (getClusters());
	copiarSolucion (_solActual, _mejorSol); // origen, destino

	// ****** Procedimiento MultiArranque  ******
	do {
		_solActual = busquedaLocal(tecnicaLocal);
		if (calcularDesvAgrup(_solActual) < desvMejor) {
			desvMejor = calcularDesvAgrup(_solActual);
			copiarSolucion(_solActual, _mejorSol);
			contadorMejora = 0;
			guardarCentroides(getClusters());
		}
		++contadorMejora;
		generarCentroides();

	} while (hayMejora(contadorMejora));

	// ****** Asignación de soluciones ******
	setSolucion(_mejorSol); // Asigne la sol. global del problema
	recuperarCentroides (); // Recupera los centroides de la solución que mejoró la actual mejor
	asignarClusters (); 	// Asigne a cada objeto su clasificación final

}

void AlgMultiArranque::generarCentroides () {
	for (unsigned int i = 0; i < getClusters().size(); ++i) {
		for (int j = 0; j < getClusters()[i]->getDimension(); ++j)
			getClusters()[i]->getCaracteristicas()[j] = rand () % 10;
	}
}

int* AlgMultiArranque::busquedaLocal (enum TIPO_TECN_LOCAL tipo) {
	int* resultado = NULL;

	switch (tipo) {
	case VORAZ:

		if (_tecnicaLocal)
			delete _tecnicaLocal;
		_tecnicaLocal = new AlgVoraz(getClusters().size(), getObjetos());
		_tecnicaLocal->ejecutarAgrupamiento();
		resultado = _tecnicaLocal->getSolucion();
		break;

	case GRASP:
		if (_tecnicaLocal)
			delete _tecnicaLocal;
		_tecnicaLocal = new AlgGRASP(getClusters(), getObjetos(), 2); // Nº candidatos LRC !!
		_tecnicaLocal->ejecutarAgrupamiento();
		resultado = _tecnicaLocal->getSolucion();
		break;

	/* IGNORAR */
	case GRAVITACION:
		if (_tecnicaLocal)
			delete _tecnicaLocal;
		_tecnicaLocal = new AlgGravitacion (getClusters(), getObjetos());
		_tecnicaLocal->ejecutarAgrupamiento();
		resultado = _tecnicaLocal->getSolucion();
		break;
	/* IGNORAR */

	default:
		cerr << "ERROR: ASIGNE UN TIPO DE TÉCNICA COMO BÚSQUEDA LOCAL!!" << endl;
	}
	return resultado;
}

bool AlgMultiArranque::hayMejora (int c) {
	return (c < 5000) ? true : false;
}

void AlgMultiArranque::guardarCentroides (vector<Cluster*>& centr) {
	for (unsigned int i = 0; i < centr.size(); ++i) {
		for (int j = 0; j < getDimension(); ++j) {
			_centroidesFin[i][j] = centr[i]->getCaracteristicas()[j];
		}
	}
}

void AlgMultiArranque::recuperarCentroides () {
	for (unsigned int i = 0; i < getClusters().size(); ++i) {
		for (int j = 0; j < getDimension(); ++j) {
			getClusters()[i]->getCaracteristicas()[j] = _centroidesFin[i][j];
		}
	}
}
