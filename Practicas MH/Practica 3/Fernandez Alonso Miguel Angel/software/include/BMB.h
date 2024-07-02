#ifndef BMB_H
#define BMB_H

#include "BL.h"

void BMB(const vector<FicheroCSV*>& train, vector<double>& best_w);
Resultados ejecutarBMB(vector<vector<FicheroCSV*>>& particion, int num_part, const int& SEED);
void GeneraSolucion(vector<double>& w);

#endif