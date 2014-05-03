/*
 * AlgVoraz.h
 *
 *  Created on: 12/04/2014
 *      Author: maikel
 */

#ifndef ALGVORAZ_H_
#define ALGVORAZ_H_

#include "AlgoritmoClustering.h"

class AlgVoraz : public AlgoritmoClustering {
public:
	AlgVoraz(int, vector<Objeto*>& objetos);
	virtual ~AlgVoraz();

	void faseConstructiva ();
	void ejecutarAgrupamiento ();

	bool solucionCompleta ();
	void averiguarMasCercano ();
};

#endif /* ALGVORAZ_H_ */
