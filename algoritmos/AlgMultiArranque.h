/*
 * AlgMultiArranque.h
 *
 *  Created on: 12/04/2014
 *      Author: maikel
 */

#ifndef ALGMULTIARRANQUE_H_
#define ALGMULTIARRANQUE_H_

#include "AlgoritmoClustering.h"
#include "AlgVoraz.h"
#include "AlgGRASP.h"
#include "KMedias.h"
#include "AlgGravitacion.h"

enum TIPO_TECN_LOCAL { VORAZ = 0, GRASP, GRAVITACION };

class AlgMultiArranque : public AlgoritmoClustering {
public:
	AlgMultiArranque(vector<Cluster*>& clusters, vector<Objeto*>& objetos);
	virtual ~AlgMultiArranque();

	void ejecutarAgrupamiento ();
	void generarCentroides ();
	int* busquedaLocal (TIPO_TECN_LOCAL);
	bool hayMejora (int);
	void guardarCentroides (vector<Cluster*>&);
	void recuperarCentroides ();

private:
	int* _solActual;
	int* _mejorSol;
	AlgoritmoClustering* _tecnicaLocal;
	int** _centroidesFin;
};

#endif /* ALGMULTIARRANQUE_H_ */
