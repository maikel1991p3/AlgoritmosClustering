/*
 * AlgVoraz.cpp
 *
 *  Created on: 12/04/2014
 *      Author: maikel
 *
 *  Descripción: Algoritmo en estudio, pensado por MÍ :), basado en la Ley de la Gravitación
 *  Universal (F = G * M*m/r^2).
 *
 *  Se basa, en cada iteración, en ir uniendo a una serie de objetos al cluster
 *  que mayor "fuerza gravitacional" ejerza sobre él. Hasta obtener solución.
 *
 *  Resultados experimentales:
 *    - Realizando un multiArranque se han encontrado resultados comparables a los
 *    del resto de técnicas programadas.
 *
 */

#include "AlgGravitacion.h"

AlgGravitacion::AlgGravitacion(vector<Cluster*>& clusters, vector<Objeto*>& objetos) {
	setNombreAlgoritmo(" kMEdias - Algoritmo basado en LEY GRAVITACIÓN UNIVERSAL ");
	setClusters(clusters);
	setObjetos(objetos);
	setDimension(getClusters()[0]->getDimension());
	int* sol = new int[getObjetos().size()];
	for (unsigned int i = 0; i < getObjetos().size(); ++i)
		sol[i] = -1;
	setSolucion(sol);
	delete [] sol;
}

AlgGravitacion::~AlgGravitacion() {}

void AlgGravitacion::ejecutarAgrupamiento() {
	do {
		averiguarMasCercano();

	} while (!solucionCompleta());
}

bool AlgGravitacion::solucionCompleta() {
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		if (getSolucion()[i] == -1)
			break;
		if (i == getObjetos().size() - 1)
			return true;
	}
	return false;
}

void AlgGravitacion::averiguarMasCercano() {
	const double G = 6.67329E-11;
	double fAtraccion[getObjetos().size()][getClusters().size()];
	double max = -9999.0;
	int posI = -1, posJ = -1;
	for (unsigned int i = 0; i < getObjetos().size(); ++i) {
		for (unsigned int j = 0; j < getClusters().size(); ++j) {
			if (getSolucion()[i] == -1) {
				// Actualizamos tabla
				fAtraccion[i][j] = (G * calcularMasa(getObjetos().at(i)->getCaracteristicas(), getObjetos().at(i)->getDimension()) *
						calcularMasa(getClusters().at(j)->getCaracteristicas(), getClusters().at(j)->getDimension()))
						/ pow (distancia(getObjetos()[i], getClusters()[j]), 2);
				// Actualizamos máximo
				if (fAtraccion[i][j] > max) {
					max = fAtraccion[i][j];
					posI = i;
					posJ = j;
				}
			}
		}
	}
	getSolucion()[posI] = getClusters().at(posJ)->getIdCluster();
	getObjetos().at(posI)->setClusterPert(getSolucion()[posI]);
}

double AlgGravitacion::calcularMasa (double* caract, int sz) {
	if (sz <= 0)
		cerr << "CALCULAR MASA () -- DIVISIÓN por cero!! " << endl;
	double masa = 0.0;
	for (int i = 0; i < sz; ++i)
		masa += caract[i];
	return masa / sz;
}
