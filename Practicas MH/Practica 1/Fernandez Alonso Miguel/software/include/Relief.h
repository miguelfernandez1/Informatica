#ifndef RELIEF_H
#define RELIEF_H

#include "KNN.h"

void nearestFriendEnemy(const vector<FicheroARFF*>& train, const FicheroARFF& actual, int& posFriend, int& posEnemy);
void relief(const vector<FicheroARFF*>& train, vector<double>& w);
Resultados ejecutarRelief(vector<vector<FicheroARFF*>>& particion, int num_part);

#endif