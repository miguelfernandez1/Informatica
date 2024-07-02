#include "GRASP.h"

extern normal_distribution<double> normal_BL;
extern uniform_real_distribution<double> uniform_BL;
extern default_random_engine generator_BL;

// Función para crear una lista restringida de candidatos (LRC)
vector<int> crearLRC(const vector<double>& costs, double alpha) {
    vector<int> LRC;
    double cmejor = *min_element(costs.begin(), costs.end());
    double cpeor = *max_element(costs.begin(), costs.end());
    double umbral = cmejor + alpha * (cpeor - cmejor);

    for (int i = 0; i < costs.size(); ++i) {
        if (costs[i] <= umbral) {
            LRC.push_back(i);
        }
    }
    return LRC;
}

// Función para seleccionar aleatoriamente un elemento de una lista
int seleccionAleatoria(const vector<int>& LRC) {
    uniform_int_distribution<int> dist(0, LRC.size() - 1);
    return LRC[dist(generator_BL)];
}

double calcularCosto(const vector<FicheroCSV*>& train, const vector<double>& w) {
    Resultados resultado = KNN_LOO(train, train, w);
    return agregado(resultado.tasa_clas, resultado.tasa_red);
}

// Implementación de la construcción greedy aleatorizada
vector<double> ConstruccionGreedyAleatorizada(const vector<FicheroCSV*>& train, double alpha) {
    vector<double> w(train[0]->n, 0.0);
    vector<double> costs(train[0]->n, 1.0);  // Inicialmente todos los costos son iguales
    vector<int> LRC;

    // Repetir hasta que la solución esté completamente construida
    for (int k = 0; k < w.size(); ++k) {
        // Crear la Lista Restringida de Candidatos (LRC)
        LRC = crearLRC(costs, alpha);

        // Selección aleatoria de un candidato de la LRC
        int seleccionado = seleccionAleatoria(LRC);

        // Añadir el candidato seleccionado a la solución parcial
        w[seleccionado] = uniform_BL(generator_BL);

        // Adaptar la función de selección: actualizar los costos
        costs[seleccionado] = -1;  // Marcamos el candidato seleccionado
        for (int i = 0; i < costs.size(); ++i) {
            if (costs[i] != -1) {
                vector<double> w_parcial = w;
                w_parcial[i] = uniform_BL(generator_BL); // Probar nuevo valor
                costs[i] = calcularCosto(train, w_parcial);
            }
        }
    }

    return w;
}

void GRASP(const vector<FicheroCSV*>& train, vector<double>& best_w, int max_iter, double alpha) {
    vector<double> current_w(train[0]->n);
    double best_agr = -1.0, current_agr;

    for (int iter = 0; iter < max_iter; iter++) {
        // Construcción de la Solución Greedy Aleatorizada
        current_w = ConstruccionGreedyAleatorizada(train, alpha);

        // Aplicar Búsqueda Local
        BL(train, current_w);

        // Evaluar la solución actual
        Resultados current_result = KNN_LOO(train, train, current_w);
        current_agr = agregado(current_result.tasa_clas, current_result.tasa_red);

        // Actualizar la mejor solución
        if (current_agr > best_agr) {
            best_w = current_w;
            best_agr = current_agr;
        }
    }
}

Resultados ejecutarGRASP(vector<vector<FicheroCSV*>>& particion, int num_part, const int& SEED, int max_iter, double alpha) {
    generator_BL = default_random_engine(SEED);

    vector<FicheroCSV*> train, test;
    vector<double> best_w;
    Resultados results;

    test = particion[num_part];

    for (int i = 0; i < particion.size(); i++) {
        if (i != num_part) {
            for (int j = 0; j < particion[i].size(); j++)
                train.push_back(particion[i][j]);
        }
    }

    best_w.resize(train[0]->n);

    start_timers();
    GRASP(train, best_w, max_iter, alpha);
    results = KNN(train, test, best_w);
    results.tiempo = elapsed_time(REAL);

    cout << "Partición " << num_part+1 << " %_clas: " << results.tasa_clas << " %_red: " << results.tasa_red
         << " Agr: " << agregado(results.tasa_clas, results.tasa_red) << " T: " << results.tiempo << endl;

    return results;
}