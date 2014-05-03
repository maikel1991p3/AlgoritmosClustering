/*
 * AlgoritmoClustering.cpp
 *
 *  Created on: 10/04/2014
 *      Author: maikel
 */

#include "AlgoritmoClustering.h"

AlgoritmoClustering::~AlgoritmoClustering() {
	if (!_clusters.empty()) {
		for (unsigned int i = 0; i < _clusters.size(); ++i) {
			if (_clusters[i] != NULL) {
				delete _clusters[i];
				_clusters[i] = NULL;
			}
		}
	}
	if (!_objetos.empty()) {
		for (unsigned int i = 0; i < _objetos.size(); ++i) {
			if (_objetos[i] != NULL) {
				delete _objetos[i];
				_objetos[i] = NULL;
			}
		}
	}
}

void AlgoritmoClustering::mostrar() {
	cout << "\n\n "  << getNombreAlgoritmo () << " :: mostrar ()" << endl << endl;

	cout << " + Información de los CLUSTERS: " << endl;
	for (unsigned int i = 0; i < getClusters().size(); ++i)
		cout << getClusters().at(i);

	cout << "\n\n + Información de los objetos: " << endl;
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		cout << getObjetos().at(i);
	}
	cout << endl << " Solución: " << endl;
	for (unsigned int i = 0; i < getObjetos().size(); ++i)
		cout << " " << getSolucion()[i] << " ";
	cout << endl;
}

double AlgoritmoClustering::calcularDesvAgrup (int* solucion) {
	double resultado = 0.0;
	for (unsigned int i = 0; i < getObjetos().size(); ++i){
		for (int j = 0; j < getDimension(); ++j) {
			resultado += pow (getObjetos().at(i)->getCaracteristicas()[j] - getClusters().at (solucion[i])->getCaracteristicas()[j], 2);
		}
	}
	return resultado;
}

double AlgoritmoClustering::distancia(Objeto* obj, Cluster* clust) {
	double suma = 0.0;
	for (int i = 0; i < obj->getDimension(); ++i) {
		suma += sqrt (pow(obj->getCaracteristicas()[i] - clust->getCaracteristicas()[i],
				2));
	}
	return suma;
}

int AlgoritmoClustering::minimaDist(double* distancias, int n) {
	double min = 99999.0;
	int pos = -1;
	for (int i = 0; i < n; ++i) {
		if (distancias[i] < min) {
			min = distancias[i];
			pos = i;
		}
	}
	return pos;
}


void AlgoritmoClustering::copiarSolucion (int* origen, int* destino) {
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		destino[i] = origen[i];
	}
}


void AlgoritmoClustering::asignarClusters () {
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		getObjetos()[i]->setClusterPert(getSolucion()[i]);
	}
}

// Manejadores de atributos
vector<Cluster*>& AlgoritmoClustering::getClusters() {
	return _clusters;
}

void AlgoritmoClustering::setClusters(vector<Cluster*>& clusters) {
	Cluster* clusterTemp = NULL;
	for (unsigned int i = 0; i < clusters.size(); ++i) {
		clusterTemp = new Cluster(*clusters[i]);
		_clusters.push_back(clusterTemp);
	}
	//_clusters = clusters;
}

vector<Objeto*>& AlgoritmoClustering::getObjetos() {
	return _objetos;
}

void AlgoritmoClustering::setObjetos(vector<Objeto*>& objetos) {
	Objeto* objTemp = NULL;
	for (unsigned int i = 0; i < objetos.size(); ++i) {
		objTemp = new Objeto(*objetos[i]);
		_objetos.push_back(objTemp);
	}
	//_objetos = objetos;
}

int* AlgoritmoClustering::getSolucion() {
	return _solucion;
}

void AlgoritmoClustering::setSolucion(int* solucion) {
	if (_solucion)
		delete _solucion;
	_solucion = new int[getObjetos().size()];
	for (unsigned int i = 0; i < getObjetos().size(); ++i)
		_solucion[i] = solucion[i];
}

int AlgoritmoClustering::getDimension() {
	return _dimension;
}

void AlgoritmoClustering::setDimension(int dimension) {
	_dimension = dimension;
}

const string& AlgoritmoClustering::getNombreAlgoritmo() const {
	return nombreAlgoritmo;
}

void AlgoritmoClustering::setNombreAlgoritmo(const string& nombreAlgoritmo) {
	this->nombreAlgoritmo = nombreAlgoritmo;
}
