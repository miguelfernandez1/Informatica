#ifndef ILSES_H
#define ILSES_H

#include "ILS.h"
#include "ES.h"

void ILS_ES(const vector<FicheroCSV*>& train, vector<double>& w);
Resultados ejecutarILS_ES(vector<vector<FicheroCSV*>>& particion, int num_part, const int& SEED);



#endif