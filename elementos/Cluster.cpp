/*
 * Cluster.cpp
 *
 *  Created on: 10/04/2014
 *      Author: maikel
 */

#include "Cluster.h"

Cluster::Cluster() {
	_idCluster = -1;
	_nDimension = -1;
	_VCaracteristicas = NULL;
}

Cluster::Cluster(int id, int dim) {
	_idCluster = id;
	_nDimension = dim;
	_VCaracteristicas = new double[getDimension()];
	for (int i = 0; i < getDimension(); ++i)
		_VCaracteristicas[i] = rand () % 10;
}

Cluster::Cluster(int id, int dim, double* caract) {
	_idCluster = id;
		_nDimension = dim;
		_VCaracteristicas = new double[getDimension()];
		for (int i = 0; i < getDimension(); ++i)
			_VCaracteristicas[i] = caract[i];
}

Cluster::Cluster(Cluster& cl) {
	_idCluster = cl.getIdCluster();
	_nDimension = cl.getDimension();
	_VCaracteristicas = new double[getDimension()];
	for (int i = 0; i < getDimension(); ++i)
		_VCaracteristicas[i] = cl.getCaracteristicas()[i];
}

Cluster::~Cluster() {
	if (_VCaracteristicas != NULL) {
		delete _VCaracteristicas;
	}
	_idCluster = -1;
	_nDimension = -1;
}

// Sobrecarga de operadores
ostream& operator<< (ostream& os, Cluster* cl) {
	os << "  Cluster: " << cl -> getIdCluster() + 1 << endl;
	os << "\tCaracterísticas: ";
	for (int i = 0; i < cl -> getDimension(); ++i) {
		 os << cl -> _VCaracteristicas[i] << "  ";
	}
	os << endl;
	return os;
}

// Manejadores de atributos
int Cluster::getIdCluster() {
	return _idCluster;
}

void Cluster::setIdCluster(int idCluster) {
	_idCluster = idCluster;
}

int Cluster::getDimension() {
	return _nDimension;
}

void Cluster::setDimension(int dimension) {
	_nDimension = dimension;
}

double* Cluster::getCaracteristicas() {
	return _VCaracteristicas;
}

void Cluster::setCaracteristicas(double* caracteristicas) {
	_VCaracteristicas = caracteristicas;
}
