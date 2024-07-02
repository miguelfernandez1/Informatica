#ifndef GRASP_H
#define GRASP_H

#include "BL.h"

vector<int> crearLRC(const vector<double>& costs, double alpha);
int seleccionAleatoria(const vector<int>& LRC);
vector<double> ConstruccionGreedyAleatorizada(const vector<FicheroCSV*>& train, double alpha);
void GRASP(const vector<FicheroCSV*>& train, vector<double>& best_w, int max_iter, double alpha);
double calcularCosto(const vector<FicheroCSV*>& train, const vector<double>& w);
Resultados ejecutarGRASP(vector<vector<FicheroCSV*>>& particion, int num_part, const int& SEED, int max_iter, double alpha);

#endif