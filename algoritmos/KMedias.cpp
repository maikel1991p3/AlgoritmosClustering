/*
 * KMedias.cpp
 *
 *  Created on: 10/04/2014
 *      Author: maikel
 */

#include "KMedias.h"

KMedias::KMedias(vector<Cluster*>& clusters, vector<Objeto*>& objetos) {
	setNombreAlgoritmo(" Algoritmo K Medias ");
	setClusters(clusters);
	setObjetos(objetos);
	setDimension(getClusters()[0]->getDimension());

	int* solT = new int[getObjetos().size()];
	_anteriorSolucion = new int [getObjetos().size()];
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		_anteriorSolucion[i] = 0;
		solT[i] = 0;
	}
	setSolucion(solT);
}

void KMedias::ejecutarAgrupamiento() {

	do {
		asignarCentroideMasCercano();
		recalcularCentroidesCluters();
	} while (huboCambios());
}

bool KMedias::huboCambios() {
	unsigned int dif = 0;
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		if (_anteriorSolucion[i] != getSolucion()[i]) {
			dif += 1;
		}
	}
	return (dif >= 1) ? true : false;
}

void KMedias::asignarCentroideMasCercano() {
	double distanciasClusters[getClusters().size()];
	int* sol = new int[getObjetos().size()];
	int posMin = -1;

	for (unsigned int i = 0; i < getObjetos().size(); ++i)
		_anteriorSolucion[i] = getSolucion()[i];

	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		posMin = -1;
		for (unsigned int j = 0; j < getClusters().size(); ++j) {
			distanciasClusters[j] = distancia(getObjetos()[i],
					getClusters()[j]);
		}
		posMin = minimaDist(distanciasClusters, getClusters().size());
		getObjetos()[i]->setClusterPert(posMin);
		sol[i] = posMin;
	}
	setSolucion(sol);

	delete [] sol;
}

void KMedias::recalcularCentroidesCluters() {
	vector<vector<double> > caracTemp;
	int* contadores = NULL;

	vector<double> temp;
	for (unsigned int i = 0; i < getClusters().size(); ++i) {
		temp.resize(getClusters()[i]->getDimension(), 0);
		caracTemp.push_back(temp);
	}
	contadores = new int[getClusters().size()];
	for (unsigned int i = 0; i < getClusters().size(); ++i)
		contadores[i] = 0;

	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		for (unsigned int j = 0; j < getClusters().size(); ++j) {
			if (getSolucion()[i] == getClusters()[j]->getIdCluster()){
				for (int k = 0; k < getClusters()[j]->getDimension(); ++k) {
					caracTemp[j][k] += getObjetos()[i]->getCaracteristicas()[k];
				}
				contadores[j] += 1;
			}
		}
	}

	for (unsigned int i = 0; i < getClusters().size(); ++i) {
		for (int j = 0; j < getClusters()[i]->getDimension(); ++j) {
			if (contadores[i] > 0)
				getClusters()[i]->getCaracteristicas()[j] = caracTemp[i][j] / contadores[i];
			else
				getClusters()[i]->getCaracteristicas()[j] = caracTemp[i][j];
		}
		cout << endl;
	}
}
