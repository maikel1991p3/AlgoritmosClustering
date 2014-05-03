/*
 * AlgVNS.h
 *
 *  Created on: 21/04/2014
 *      Author: maikel
 */

#ifndef ALGVNS_H_
#define ALGVNS_H_

#include "AlgoritmoClustering.h"
#include "AlgGRASP.h"

class AlgVNS : public AlgoritmoClustering {
public:
	AlgVNS(vector<Cluster*>& clusters, vector<Objeto*>& objetos, int kMax);
	virtual ~AlgVNS();

	void ejecutarAgrupamiento ();
	int* generarSolucion ();
	int* mutarSolucion (int*, int);

private:
	AlgGRASP* _tecnicaLocal;
	int _kMax;

	int* _solActual;
	int* _mejorSol;
	int* _solucionMutada;

	int** _centroidesFin;
};

#endif /* ALGVNS_H_ */
