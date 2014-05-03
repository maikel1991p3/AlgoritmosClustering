/*
 * KMedias.h
 *
 *  Created on: 10/04/2014
 *      Author: maikel
 */

#ifndef KMEDIAS_H_
#define KMEDIAS_H_

#include "AlgoritmoClustering.h"
#include <math.h>

class KMedias : public AlgoritmoClustering {
public:
	KMedias(vector<Cluster*>&, vector<Objeto*>&);
	virtual ~KMedias() {}

	// Propios
	bool huboCambios ();
	void asignarCentroideMasCercano ();
	void recalcularCentroidesCluters ();

	// Heredados
	void ejecutarAgrupamiento ();

private:
	int* _anteriorSolucion;
};

#endif /* KMEDIAS_H_ */
