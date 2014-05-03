/*
 * Simulador.cpp
 *
 *  Created on: 10/04/2014
 *      Author: maikel
 */

#include "Simulador.h"

Simulador::Simulador(int nClusters, int nObj, int dim, int algoritmo) {
	_nClusters = nClusters;
	_nObjetos = nObj;
	_algoritmo = NULL;
	_dimension = dim;
	srand(time(NULL));
	creacionAleatoriaPura(true, true); // crea clusters y objetos aleatorios
	setAlgoritmo(algoritmo);
}

Simulador::Simulador(string nombreFich, int nClusters, int algoritmo) {

	fstream fichIn;
	double* caract = NULL;
	Objeto* objTemp = NULL;
	char resp;
	_nClusters = nClusters;
	fichIn.open(nombreFich.c_str(), fstream::in);
	if (fichIn.is_open()) {
		fichIn >> _nObjetos >> _dimension;
		caract = new double[_dimension];
		while (!fichIn.eof()) {
			for (int i = 0; i < getDimension(); ++i) {
				fichIn >> caract[i];
			}
			objTemp = new Objeto(caract, getDimension());
			_objetos.push_back(objTemp);
		}
		fichIn.close();

		cout << " ¿Clusters aleatorios? (s = si)?";
		cin >> resp;
		if (resp == 's') {
			srand(time(NULL));
			creacionAleatoriaPura(true, false); // crea clusters aleatorios y no crea objetos

		} else
			crearClustersDesdeFichero();

		_algoritmo = NULL;
		setAlgoritmo(algoritmo);

	} else
		cerr	<< "ERROR: Hubo un problema al cargar el fichero de ENTRADA!! REINICIE!!"
		<< endl;
}

Simulador::~Simulador() {
	if (_algoritmo != NULL) {
		delete[] _algoritmo;
		_algoritmo = NULL;
	}
	_nClusters = -1;
	_nObjetos = -1;
	_dimension = -1;
}

/********************************************************************************
 * 		Métodos de creación de instancias iniciales								*
 ********************************************************************************/
void Simulador::creacionAleatoriaPura(bool clusters, bool obj) {
	Cluster* clusterTemp = NULL;
	Objeto* objetoTemp = NULL;

	if (clusters) {
		for (int i = 0; i < _nClusters; ++i) {
			clusterTemp = new Cluster(i, getDimension());
			_clusters.push_back(clusterTemp);
		}
	}
	if (obj) {
		for (int j = 0; j < _nObjetos; ++j) {
			objetoTemp = new Objeto(getDimension());
			_objetos.push_back(objetoTemp);
		}
	}
}

void Simulador::crearClustersDesdeFichero() {
	fstream fichIn;
	double* caractTemp;
	Cluster* clTemp = NULL;

	fichIn.open("clusters.data");
	if (fichIn.is_open()) {
		fichIn >> _nClusters >> _dimension;
		for (int i = 0; i < _nClusters; ++i) {
			caractTemp = new double[getDimension()];
			for (int j = 0; j < getDimension(); ++j) {
				fichIn >> caractTemp[j];
			}
			clTemp = new Cluster(i, getDimension(), caractTemp);
			_clusters.push_back(clTemp);
		}
		fichIn.close();
	} else {
		cerr
		<< "ERROR: algo sucedió al cargar los clusters desde fichero. Revíselo!! "
		<< endl;
	}
}

/************  FIN ** Métodos de creación de instancias iniciales ***************/

/********************************************************************************
 * 		Métodos Auxiliares                       								*
 ********************************************************************************/
void Simulador::mostrarClusters() {
	cout << endl << " + CLUSTERs:    num = " << _nClusters << endl;
	for (int i = 0; i < _nClusters; ++i)
		cout << _clusters[i];
}

void Simulador::mostrarObjetos() {
	cout << endl << " + OBJETOS:     num = " << _nObjetos << endl;
	for (int i = 0; i < _nObjetos; ++i)
		cout << _objetos[i];
}

void Simulador::setAlgoritmo(int tipo) {
	int k = 0;
	switch (tipo) {
	case 0:
		_algoritmo = new KMedias(_clusters, _objetos);
		break;

	case 1:
		_algoritmo = new AlgVoraz (_clusters.size(), _objetos);
		break;

	case 2:
		_algoritmo = new AlgGRASP (_clusters, _objetos, 2);
		break;

	case 3:
		_algoritmo = new AlgMultiArranque (_clusters, _objetos);
		break;

	case 4:
		cout << " Introduzca K para vecindad: ";
		cin >> k;
		_algoritmo = new AlgVNS (_clusters, _objetos, k);
		break;

	case 5:
		_algoritmo = new AlgGravitacion (_clusters, _objetos);
	}
}

/************    FIN **      Métodos auxiliares                   ***************/

// Majenadores de atributos
vector<Cluster*>& Simulador::getClusters() {
	return _clusters;
}

int Simulador::getClusters() const {
	return _nClusters;
}

void Simulador::setClusters(int clusters) {
	_nClusters = clusters;
}

int Simulador::getObjetos() const {
	return _nObjetos;
}

void Simulador::setObjetos(int objetos) {
	_nObjetos = objetos;
}

vector<Objeto*>& Simulador::getObjetos() {
	return _objetos;
}

void Simulador::setObjeto(Objeto* objeto, int pos) {
	_objetos[pos] = objeto;
}

AlgoritmoClustering*& Simulador::getAlgoritmo() {
	return _algoritmo;
}

int Simulador::getDimension() {
	return _dimension;
}

void Simulador::setDimension(int dimension) {
	_dimension = dimension;
}
