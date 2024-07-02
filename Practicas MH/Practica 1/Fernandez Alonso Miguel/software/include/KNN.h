#ifndef KNN_H
#define KNN_H

#include "Funciones.h"

const double ALPHA = 0.5;

int nearestNeighour(const vector<FicheroARFF*>& train, const FicheroARFF& actual, const vector<double>& w);
Resultados KNN(const vector<FicheroARFF*>& train, const vector<FicheroARFF*>& test, const vector<double>& w);
Resultados ejecutarKNN(vector<vector<FicheroARFF*>>& particion, int num_part);
double agregado(const double& t_class, const double& t_red);

#endif