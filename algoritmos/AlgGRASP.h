/*
 * AlgGRASP.h
 *
 *  Created on: 12/04/2014
 *      Author: maikel
 */

#ifndef ALGGRASP_H_
#define ALGGRASP_H_

#include "../elementos/Objeto.h"
#include "../elementos/Cluster.h"
#include "AlgoritmoClustering.h"
#include <utility>

class AlgGRASP : public AlgoritmoClustering {
public:
	AlgGRASP(vector<Cluster*>&, vector<Objeto*>&, int);
	virtual ~AlgGRASP();

	void ejecutarAgrupamiento ();

	bool solucionCompleta ();
	void elegirCercano ();

private:
	pair<int, int>* _listaCandidatos;
	int _nCandidatos;
};

#endif /* ALGGRASP_H_ */
