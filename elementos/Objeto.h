/*
 * Objeto.h
 *
 *  Created on: 10/04/2014
 *      Author: maikel
 */

#ifndef OBJETO_H_
#define OBJETO_H_

#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

class Objeto {
public:
	Objeto (int);	// dimensión
	Objeto (Objeto&);
	Objeto (double*, int);
	virtual ~Objeto();

	// Sobrecarga de operadores
	friend ostream& operator<< (ostream&, Objeto*);

	// Manejadores de atributos
	int getClusterPert() const;
	void setClusterPert(int clusterPert);
	int getDimension() const;
	void setDimension(int dimension);
	double* getCaracteristicas();
	void setCaracteristicas(double* caracteristicas);

private:
	int _nDimension;			// número de características
	double* _VCaracteristicas;		// vector con el valor para cada característica
	int _clusterPert;			// cluster en el que se clasificó el objeto
};

#endif /* OBJETO_H_ */
