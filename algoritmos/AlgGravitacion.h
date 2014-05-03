/*
 * AlgGravitacion.h
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

#ifndef ALGGRAVITACION_H_
#define ALGGRAVITACION_H_

#include "AlgoritmoClustering.h"

class AlgGravitacion : public AlgoritmoClustering {
public:
	AlgGravitacion(vector<Cluster*>& clusters, vector<Objeto*>& objetos);
	virtual ~AlgGravitacion();

	void ejecutarAgrupamiento ();

	bool solucionCompleta ();
	void averiguarMasCercano ();
	double calcularMasa (double*, int);
};

#endif
