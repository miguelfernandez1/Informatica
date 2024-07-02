#include "MVO.h"
#include <numeric>
#include <random>
#include <algorithm>

std::random_device rd;
std::mt19937 gen(rd());

double calcularFitness(const int &acierto, const int &numEjemplos, const vector<double> &pesos) {
    double tasa_clas = 100.0 * (double(acierto) / double(numEjemplos));
    double tasa_red = calcularTasaRed(pesos);
    return 0.8 * tasa_clas + 0.2 * tasa_red;
}

double funObjetivo(const vector<FicheroCSV*>& train, const vector<double> &pesos) {
    int acierto_train = 0;

    for (int i = 0; i < numEjemplos(train); i++) {
        int min_index = 0;
        double min_distance = INFINITY;

        for (int j = 0; j < numEjemplos(train); j++) {
            if (i == j) continue;

            double distance = euclideanDistance(getEjemplo(train, i).traits, getEjemplo(train, j).traits, pesos);
            if (distance < min_distance) {
                min_index = j;
                min_distance = distance;
            }
        }
        if (getEjemplo(train, min_index).category == getEjemplo(train, i).category)
            acierto_train++;
    }

    return calcularFitness(acierto_train, numEjemplos(train), pesos);
}

// Funcion para calcular la tasa de reduccion de los pesos
double calcularTasaRed(const vector<double> &pesos){
    double tasa_red = 0;
    for(auto it : pesos)
        if(it < 0.1) // Si el peso es menor que 0.1, entonces cuenta como reducido
            tasa_red++;
    return 100.0*(tasa_red/(double)pesos.size()); // Devolvemos la tasa de reduccion en porcentaje
}


double random_double(double min, double max) {
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

int random_int(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

int roulette_wheel_selection(const std::vector<double>& probabilities) {
    double max_val = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);
    double pick = random_double(0, max_val);
    double current = 0;
    for (size_t i = 0; i < probabilities.size(); ++i) {
        current += probabilities[i];
        if (current > pick) {
            return i;
        }
    }
    return probabilities.size() - 1;
}

double transfer_function(double value) {
    return 1.0 / (1.0 + exp(-value));
}

double calculate_tdr(int l, int L) {
    const int p = 6;
    return 1.0 - pow(static_cast<double>(l), 1.0 / p) / pow(static_cast<double>(L), 1.0 / p);
}

double calculate_wep(int l, int L) {
    const double MINWEP = 0.2;
    const double MAXWEP = 1.0;
    return MINWEP + l * (MAXWEP - MINWEP) / L;
}

void binary_multiverse_optimization(const vector<FicheroCSV*>& train, vector<double>& best_universe) {
    const int MAX_ITER = 15000;
    const int DIM = train[0]->traits.size();
    const int NUM_UNIVERSES = 30;
    
    std::vector<std::vector<double>> U(NUM_UNIVERSES, std::vector<double>(DIM));
    for (auto& universe : U) {
        for (auto& bit : universe) {
            bit = random_double(0.0, 1.0);
        }
    }

    best_universe = U[0];
    double best_fitness = funObjetivo(train, best_universe);

    for (int l = 0; l < MAX_ITER; ++l) {
        std::vector<double> fitness_values(NUM_UNIVERSES);
        for (int i = 0; i < NUM_UNIVERSES; ++i) {
            fitness_values[i] = funObjetivo(train, U[i]);
        }

        auto max_iter = max_element(fitness_values.begin(), fitness_values.end());
        if (*max_iter > best_fitness) {
            best_fitness = *max_iter;
            best_universe = U[distance(fitness_values.begin(), max_iter)];
        }

        std::vector<double> NF(NUM_UNIVERSES);
        double fitness_sum = accumulate(fitness_values.begin(), fitness_values.end(), 0.0);
        for (int i = 0; i < NUM_UNIVERSES; ++i) {
            NF[i] = fitness_values[i] / fitness_sum;
        }

        std::vector<std::vector<double>> SU = U;
        std::sort(SU.begin(), SU.end(), [&](const std::vector<double>& a, const std::vector<double>& b) {
            return funObjetivo(train, a) > funObjetivo(train, b);
        });

        double wep = calculate_wep(l, MAX_ITER);
        double tdr = calculate_tdr(l, MAX_ITER);

        for (int i = 0; i < NUM_UNIVERSES; ++i) {
            for (int j = 0; j < DIM; ++j) {
                double r1 = random_double(0.0, 1.0);
                if (r1 < NF[i]) {
                    int white_hole_index = roulette_wheel_selection(NF);
                    U[i][j] = SU[white_hole_index][j];
                }

                double r2 = random_double(0.0, 1.0);
                if (r2 < wep) {
                    double r3 = random_double(0.0, 1.0);
                    double r4 = random_double(0.0, 1.0);
                    double omega_t;

                    if (r3 < 0.5) {
                        omega_t = transfer_function(best_universe[j] + tdr * r4);
                    } else {
                        omega_t = transfer_function(best_universe[j] - tdr * r4);
                    }

                    U[i][j] = (omega_t > random_double(0.0, 1.0)) ? 0 : 1;
                }
            }
        }
    }
}

Resultados ejecutarMVO(vector<vector<FicheroCSV*>>& particion, int num_part, const int& SEED) {
    default_random_engine generator_MVO(SEED);

    vector<FicheroCSV*> train, test;
    vector<string> clasificacion;
    vector<double> w;
    Resultados results;

    test = particion[num_part];

    for (int i = 0; i < particion.size(); i++) {
        if (i != num_part) {
            for (int j = 0; j < particion[i].size(); j++)
                train.push_back(particion[i][j]);
        }
    }

    w.resize(train[0]->traits.size());
    for (int i = 0; i < train[0]->traits.size(); i++) {
        w[i] = 0.0;
    }

    start_timers();
    binary_multiverse_optimization(train, w);
    results = KNN(train, test, w);
    results.tiempo = elapsed_time(REAL);

    cout << "Partición " << num_part + 1 << " %_clas: " << results.tasa_clas << " %_red: " << results.tasa_red
         << " Agr: " << agregado(results.tasa_clas, results.tasa_red) << " T: " << results.tiempo << endl;

    return results;
}