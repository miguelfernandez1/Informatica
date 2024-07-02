#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include "timer.h"

using namespace std;

struct FicheroARFF{
    int n;
    vector<double> traits;
    string category;
};

struct Resultados{
    double tasa_class;
    double tasa_red;
    double tiempo;
    int aciertos;
};

void read_arff(string filename, vector<FicheroARFF>& result);
int makePartitions(vector<FicheroARFF>& datos, vector<vector<FicheroARFF*>>& particion);
double euclideanDistance(const vector<double>& v1, const vector<double>& v2, const vector<double>& pesos);
double euclideanDistance(const vector<double>& v1, const vector<double>& v2);
void read_csv(string filename, vector<FicheroARFF>& result);

#endif