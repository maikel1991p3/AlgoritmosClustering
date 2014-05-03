/*
 * AlgVoraz.cpp
 *
 *  Created on: 12/04/2014
 *      Author: maikel
 */

#include "AlgVoraz.h"

AlgVoraz::AlgVoraz(int nClusters, vector<Objeto*>& objetos) {
	setNombreAlgoritmo(" - Algoritmo Voraz ");
	for (int i = 0; i < nClusters; ++i) {
		getClusters().push_back(new Cluster ());
	}

	setObjetos(objetos);
	setDimension(getObjetos()[0]->getDimension());
	int* sol = new int[getObjetos().size()];
	for (unsigned int i = 0; i < getObjetos().size(); ++i)
		sol[i] = -1;
	setSolucion(sol);
	delete [] sol;
}

AlgVoraz::~AlgVoraz() {}

void AlgVoraz::ejecutarAgrupamiento() {
	faseConstructiva();
	do {
		averiguarMasCercano();

	} while (!solucionCompleta());
}

bool AlgVoraz::solucionCompleta() {
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		if (getSolucion()[i] == -1)
			break;
		if (i == getObjetos().size() - 1)
			return true;
	}
	return false;
}

void AlgVoraz::averiguarMasCercano() {
	double distancias[getObjetos().size()][getClusters().size()];
	double min = 99999.0;
	int posI = -1, posJ = -1;
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		for (unsigned int j = 0; j < getClusters().size(); ++j) {
			if (getSolucion()[i] == -1) {
				distancias[i][j] = distancia(getObjetos()[i], getClusters()[j]);

				if (distancias[i][j] < min) {
					min = distancias[i][j];
					posI = i;
					posJ = j;
				}
			}
		}
	}
	getSolucion()[posI] = getClusters().at(posJ)->getIdCluster();
	getObjetos().at(posI)->setClusterPert(getSolucion()[posI]);
}

// Fase Previa Constructiva
void AlgVoraz::faseConstructiva () {
	unsigned int nClusters = getClusters().size(), contCluster = 0;
	double max = -1.0;
	double* caract = new double[getDimension()];
	double* dist = NULL;
	int nObjeto = 0;

	// Primer Cluster: un objeto al Azar
	int primerCluster = rand() % getObjetos().size();
	getClusters().at(0)->setDimension(getDimension());
	getClusters().at(0)->setIdCluster(contCluster);

	for (int i = 0; i < getClusters().at(contCluster)->getDimension(); ++i) {
		caract[i] = getObjetos().at(primerCluster)->getCaracteristicas()[i];
	}
	getClusters().at(contCluster)->setCaracteristicas(caract);
		++contCluster;

	// Elegimos del resto de clusters los k - 1 más alejados entre sí
	do {
		dist = new double[getObjetos().size()];
		for (unsigned int i = 0; i < getObjetos().size(); ++i) {
			dist[i] = 0.0;
			for (unsigned int j = 0; j < nClusters; ++j) {
				if (getClusters().at(j) -> getDimension() > 0) {
					dist[i] += distancia(getObjetos().at(i), getClusters().at(j));
				}
			}
		}

		max = -1.0;
		nObjeto = 0;
		for (unsigned int i = 0; i < getObjetos().size(); ++i) {
			if (dist[i] > max) {
				max = dist[i];
				nObjeto = i;
			}
		}
		getClusters().at(contCluster)->setDimension(getDimension());
		getClusters().at(contCluster)->setIdCluster(contCluster);

		getClusters()[contCluster]->setCaracteristicas(new double[getDimension()]);
		for (int k = 0; k < getClusters().at(contCluster)->getDimension(); ++k) {
			getClusters()[contCluster]->getCaracteristicas()[k] = getObjetos().at(nObjeto)->getCaracteristicas()[k];
		}
		++contCluster;

	} while (contCluster < getClusters().size()); // Mientras no tengamos todos los clusters creados

}
