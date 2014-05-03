/*
 * Objeto.cpp
 *
 *  Created on: 10/04/2014
 *      Author: maikel
 */

#include "Objeto.h"

Objeto::Objeto(int nDim) {
	_nDimension = nDim;
	_VCaracteristicas = new double[_nDimension];
	for (int i = 0; i < _nDimension; ++i)
		_VCaracteristicas[i] = rand() % 10;
	_clusterPert = -1;
}

Objeto::Objeto(Objeto& obj) {
	_nDimension = obj.getDimension();
	_VCaracteristicas = new double[getDimension()];
	for (int i = 0; i < getDimension(); ++i)
		_VCaracteristicas[i] = obj.getCaracteristicas()[i];
	_clusterPert = obj.getClusterPert();
}

Objeto::Objeto(double* caract, int n) {
	_nDimension = n;
	_VCaracteristicas = new double[getDimension()];
	for (int i = 0; i < getDimension(); ++i)
		_VCaracteristicas[i] = caract[i];
	_clusterPert = -1;
}

Objeto::~Objeto() {
	if (_VCaracteristicas != NULL) {
		delete _VCaracteristicas;
		_VCaracteristicas = NULL;
	}
	_clusterPert = -1;
	_nDimension = -1;
}

// Sobrecarga de operadores
ostream& operator<<(ostream& os, Objeto* obj) {
	os << "\t[";
	for (int i = 0; i < obj->getDimension(); ++i) {
		os << " " << obj->_VCaracteristicas[i] << " ";
	}
	os << "] Cluster = " << obj->getClusterPert() << endl;
	return os;
}

// Manejadores de atributos
int Objeto::getClusterPert() const {
	return _clusterPert;
}

void Objeto::setClusterPert(int clusterPert) {
	_clusterPert = clusterPert;
}

int Objeto::getDimension() const {
	return _nDimension;
}

void Objeto::setDimension(int dimension) {
	_nDimension = dimension;
}

double* Objeto::getCaracteristicas() {
	return _VCaracteristicas;
}

void Objeto::setCaracteristicas(double* caracteristicas) {
	_VCaracteristicas = caracteristicas;
}
