/*
 * Simulador.h
 *
 *  Created on: 10/04/2014
 *      Author: maikel
 */

#ifndef SIMULADOR_H_
#define SIMULADOR_H_

#include "elementos/Objeto.h"
#include "elementos/Cluster.h"
#include "algoritmos/AlgoritmoClustering.h"
#include "algoritmos/KMedias.h"
#include "algoritmos/AlgVoraz.h"
#include "algoritmos/AlgMultiArranque.h"
#include "algoritmos/AlgGRASP.h"
#include "algoritmos/AlgGravitacion.h"
#include "algoritmos/AlgVNS.h"

#include <fstream>

class Simulador {
public:
	Simulador(int, int, int, int); // aleatorio
	Simulador(string, int, int);		   // desde fichero de entrada
	virtual ~Simulador();

	// Creación de instancias iniciales: centroides y objetos
	void creacionAleatoriaPura (bool, bool);
	void crearClustersDesdeFichero ();

	// Métodos auxiliares
	void mostrarClusters ();
	void mostrarObjetos ();
	void setAlgoritmo (int);

	// Manejadores de atributos
	vector<Cluster*>& getClusters();
	int getClusters() const;
	void setClusters(int);
	int getObjetos() const;
	void setObjetos(int);
	vector<Objeto*>& getObjetos();
	void setObjeto(Objeto*, int);
	AlgoritmoClustering*& getAlgoritmo();
	int getDimension();
	void setDimension(int dimension);

private:
	int _nClusters;		// num. de clusters = num. de centroides
	int _nObjetos;		// num. de objetos a agrupar
	int _dimension;		// num. de caracteristicas
	vector<Cluster*> _clusters;	// Clusters en los que agrupar
	vector<Objeto*> _objetos;	// Objetos para agrupar
	AlgoritmoClustering* _algoritmo; 	// Método de agrupamiento!!
};

#endif /* SIMULADOR_H_ */
