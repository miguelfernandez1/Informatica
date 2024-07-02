#ifndef MVO_H
#define MVO_H


#include <vector>
#include "funciones.h"
#include "KNN.h"

// Función para generar un número aleatorio en un rango dado
double random_double(double min = 0.0, double max = 1.0);

// Función para generar un número entero aleatorio en un rango dado
int random_int(int min, int max);

// Función para realizar la selección por ruleta
int roulette_wheel_selection(const std::vector<double>& probabilities);

// Función de transferencia para convertir un valor continuo en un valor binario
double transfer_function(double value);

// Función para calcular el Travelling Distance Rate (TDR)
double calculate_tdr(int l, int L);

// Función para calcular el Wormhole Existence Probability (WEP)
double calculate_wep(int l, int L);

// Función principal del algoritmo Binary Multiverse Optimization (BMVO)
void binary_multiverse_optimization(const vector<FicheroCSV*>& train, vector<double>& best_universe);

Resultados ejecutarMVO(vector<vector<FicheroCSV*>>& particion, int num_part, const int& SEED);

double funObjetivo(const vector<FicheroCSV*>& train, const vector<double> &pesos);

double calcularFitness(const int &acierto, const int &numEjemplos, const vector<double> &pesos);

double calcularTasaRed(const vector<double> &pesos);

double random_double(double min, double max);

int random_int(int min, int max);



#endif // MVO_H