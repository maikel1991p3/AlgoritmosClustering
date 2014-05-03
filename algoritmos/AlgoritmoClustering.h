/*
 * AlgoritmoClustering.h
 *
 *  Created on: 10/04/2014
 *      Author: maikel
 */

#ifndef ALGORITMOCLUSTERING_H_
#define ALGORITMOCLUSTERING_H_

#include "../elementos/Cluster.h"
#include "../elementos/Objeto.h"
#include <math.h>

class AlgoritmoClustering {
public:
	AlgoritmoClustering() : _solucion(NULL), _dimension(-1), nombreAlgoritmo("") {}
	virtual ~AlgoritmoClustering();

	void mostrar ();
	virtual void ejecutarAgrupamiento () {}

	double calcularDesvAgrup (int* solucion);

	double distancia (Objeto*, Cluster*);	// Distancia euclídea entre sus características.
	int minimaDist (double*, int);

	void volcarResultadoAFichero (string nombreFich);

	// Para multiarranque y VNS
	void copiarSolucion (int*, int*);
	void asignarClusters ();

	// Manejadores de atributos
	vector<Cluster*>& getClusters();
	void setClusters(vector<Cluster*>& clusters);
	vector<Objeto*>& getObjetos();
	void setObjetos(vector<Objeto*>& objetos);
	int* getSolucion();
	void setSolucion(int* solucion);
	int getDimension();
	void setDimension(int dimension);
	const string& getNombreAlgoritmo() const;
	void setNombreAlgoritmo(const string& nombreAlgoritmo);

private:
	vector<Cluster*> _clusters;
	vector<Objeto*> _objetos;
	int* _solucion;
	int _dimension;

	string nombreAlgoritmo;
};

#endif /* ALGORITMOCLUSTERING_H_ */
