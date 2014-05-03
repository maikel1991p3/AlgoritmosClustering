/*
 * Cluster.h
 *
 *  Created on: 10/04/2014
 *      Author: maikel
 */

#ifndef CLUSTER_H_
#define CLUSTER_H_

#include <vector>

#include "Objeto.h"

class Cluster {
public:
	Cluster ();
	Cluster(int, int); 	// id y num de características
	Cluster(int, int, double*); 	// id, num de características y características
	Cluster(Cluster&);
	virtual ~Cluster();

	// Sobrecarga de operadores
	friend ostream& operator<< (ostream& os, Cluster* cl);

	// Manejadores de atributos
	int getIdCluster();
	void setIdCluster(int idCluster);
	int getDimension();
	void setDimension(int dimension);
	double* getCaracteristicas();
	void setCaracteristicas(double* caracteristicas);

private:
	int _nDimension;		// número de características
	double* _VCaracteristicas;	// vector con los valores para las características del cluster
	int _idCluster;			// Identificador de cada cluster

};

#endif /* CLUSTER_H_ */
