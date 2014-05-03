/*
 * AlgGRASP.cpp
 *
 *  Created on: 12/04/2014
 *      Author: maikel
 */

#include "AlgGRASP.h"

AlgGRASP::AlgGRASP(vector<Cluster*>& clusters, vector<Objeto*>& objetos, int nCand) {
	setNombreAlgoritmo(" Técnica GRASP (Greedy Randomized Adaptative Search Procedure) ");
	setClusters(clusters);
	setObjetos(objetos);
	setDimension(getClusters()[0]->getDimension());
	int* sol = new int[getObjetos().size()];
	for (unsigned int i = 0; i < getObjetos().size(); ++i)
		sol[i] = -1;
	setSolucion(sol);
	delete [] sol;
	_nCandidatos = nCand;
	_listaCandidatos = NULL;
}

AlgGRASP::~AlgGRASP() {
	if (getSolucion() != NULL)
		delete [] getSolucion();
	if (_listaCandidatos != NULL)
		delete [] _listaCandidatos;
}

void AlgGRASP::ejecutarAgrupamiento () {
	do {
		elegirCercano();

	} while (!solucionCompleta());

}

bool AlgGRASP::solucionCompleta () {
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		if (getSolucion()[i] == -1)
			break;
		if (i == getObjetos().size() - 1)
			return true;
	}
	return false;
}

void AlgGRASP::elegirCercano () {
	// Rellenamos tabla de distancias Objetos - Clusters
	int distancias[getObjetos().size()][getClusters().size()];
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		for (unsigned int j = 0; j < getClusters().size(); ++j) {
			if (getSolucion()[i] == -1) {
				distancias[i][j] = distancia(getObjetos()[i], getClusters()[j]);
			}
		}
	}

	// Buscamos los "nCandodatos" con menor distancia
	// n Objetos 'i' con menor distancia al cluster 'j'
	int min = 99999.0;
	_listaCandidatos = new pair<int, int> [_nCandidatos];
	int pos = 0;
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		for (unsigned int j = 0; j < getClusters().size(); ++j) {
			if (getSolucion()[i] == -1 && distancias[i][j] < min) {
				min = distancias[i][j];
				_listaCandidatos[pos].first = i;
				_listaCandidatos[pos].second = j;
				++pos;
				if (pos == _nCandidatos)
					pos = 0;
			}
		}
	}
	// Elegimos un candidato de la lista al azar
	int aleatorio = rand () % _nCandidatos;
	getSolucion()[_listaCandidatos[aleatorio].first] = getClusters().at(_listaCandidatos[aleatorio].second)->getIdCluster();
	getObjetos().at(_listaCandidatos[aleatorio].first)->setClusterPert(getSolucion()[_listaCandidatos[aleatorio].first]);
}
