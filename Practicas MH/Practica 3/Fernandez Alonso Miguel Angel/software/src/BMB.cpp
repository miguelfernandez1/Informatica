#include "BMB.h"

normal_distribution<double> normal_BMB(0.0, SIGMA);
uniform_real_distribution<double> uniform_BMB(0.0, 1.0);
default_random_engine generator_BMB;

// Algoritmo de Búsqueda Multiarranque Básica (BMB)
// Función para generar una solución inicial aleatoria
void GeneraSolucion(vector<double>& w) {
    for (int i = 0; i < w.size(); i++) {
        w[i] = uniform_BMB(generator_BMB);
    }
}

// Función principal de Búsqueda Multiarranque Básica (BMB)
void BMB(const vector<FicheroCSV*>& train, vector<double>& best_w) {
    vector<double> current_w(best_w.size());
    vector<double> temp_w(best_w.size());
    double best_agr, current_agr;

    // Generar la primera solución inicial
    GeneraSolucion(current_w);

    // Optimizar la primera solución usando Búsqueda Local
    BL(train, current_w);

    // Almacenar la mejor solución inicial
    best_w = current_w;
    Resultados best_result = KNN_LOO(train, train, best_w);
    best_agr = agregado(best_result.tasa_clas, best_result.tasa_red);

    // Realizar 20 iteraciones
    for (int i = 1; i < 20; i++) {
        // Generar una nueva solución inicial
        GeneraSolucion(temp_w);

        // Optimizar la nueva solución usando Búsqueda Local
        BL(train, temp_w);

        // Evaluar la nueva solución
        Resultados temp_result = KNN_LOO(train, train, temp_w);
        current_agr = agregado(temp_result.tasa_clas, temp_result.tasa_red);

        // Comparar y almacenar la mejor solución
        if (current_agr > best_agr) {
            best_w = temp_w;
            best_agr = current_agr;
        }
    }
}


Resultados ejecutarBMB(vector<vector<FicheroCSV*>>& particion, int num_part, const int& SEED) {
    generator_BMB = default_random_engine(SEED);

    vector<FicheroCSV*> train, test;
    vector<string> clasificacion;
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
    BMB(train, best_w);
    results = KNN(train, test, best_w);
    results.tiempo = elapsed_time(REAL);

    cout << "Partición " << num_part+1 << " %_clas: " << results.tasa_clas << " %_red: " << results.tasa_red
         << " Agr: " << agregado(results.tasa_clas, results.tasa_red) << " T: " << results.tiempo << endl;

    return results;
}