#include "ILS-ES.h"

normal_distribution<double> normal_ILS_ES(0.0, SIGMA_ILS);
uniform_real_distribution<double> uniform_ILS_ES(0.0,1.0);
default_random_engine generator_ILS_ES;


// Función ILS-ES
void ILS_ES(const vector<FicheroCSV*>& train, vector<double>& w) {
    uniform_int_distribution<int> random_int(0, w.size() - 1);
    vector<double> w_mejor;
    Resultados antiguo, nuevo;
    double agr_mejor, agr_new;
    int num_mutaciones = ceil(0.1 * w.size());
    
    // Evaluamos la solución inicial
    for (auto& weight : w)
        weight = uniform_ILS_ES(generator_ILS_ES);
    
    // Aplicamos BL y tomamos el agr actual como mejor
    BL(train, w);
    antiguo = KNN_LOO(train, train, w);
    agr_mejor = agregado(antiguo.tasa_clas, antiguo.tasa_red);
    w_mejor = w;
    
    // Parámetros de ES
    int max_vecinos = 10 * w.size();
    int max_exitos = 0.1 * max_vecinos;
    int num_eval = 0, neighbour = 0, num_exitos = max_exitos;
    double agr_ant = agr_mejor;
    
    // Inicializar temperaturas
    double To = (MU * agr_mejor) / (-1.0 * log(PHI));
    double Tf = VAL_TF;
    double beta = (To - Tf) / (MAX_ITER * To * Tf);
    double Tk = To;
    
    // Comprobamos que Tf es menor que To, si no se cumpliese multiplicamos por 0.1 la final
    while (Tf > To)
        Tf *= 0.1;
    
    // Iteraciones de ILS-ES
    for (int iter = 0; iter < 15; ++iter) {
        // Mutar la mejor solución (ILS)
        for (int j = 0; j < num_mutaciones; ++j) {
            int idx = random_int(generator_ILS_ES);
            w[idx] += normal_ILS_ES(generator_ILS_ES);
            if (w[idx] > 1.0) w[idx] = 1.0;
            else if (w[idx] < 0.0) w[idx] = 0.0;
        }
        
        // Aplicar BL y evaluar
        BL(train, w);
        nuevo = KNN_LOO(train, train, w);
        agr_new = agregado(nuevo.tasa_clas, nuevo.tasa_red);
        
        // Verificar si se acepta la nueva solución
        double diff = agr_ant - agr_new;
        if (diff < 0 || uniform_ILS_ES(generator_ILS_ES) <= exp(-diff / Tk)) {
            w_mejor = w;
            agr_mejor = agr_new;
            agr_ant = agr_new;
        } else {
            w = w_mejor;
        }
        
        // Enfriamiento (ES)
        Tk = Tk / (1.0 + beta * Tk);
        num_eval++;
        if (num_eval >= MAX_ITER) break;
    }
    
    w = w_mejor;
}

Resultados ejecutarILS_ES(vector<vector<FicheroCSV*>>& particion, int num_part, const int& SEED) {
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

    w.resize(train[0]->n);
    for (int i = 0; i < train[0]->n; i++) {
        w[i] = 0.0;
    }

    start_timers();
    ILS_ES(train, w); // Llamamos a la función ILS-ES
    results = KNN(train, test, w);
    results.tiempo = elapsed_time(REAL);

    cout << "Partición " << num_part + 1 << " %_clas: " << results.tasa_clas << " %_red: " << results.tasa_red
        << " Agr: " << agregado(results.tasa_clas, results.tasa_red) << " T: " << results.tiempo << endl;

    return results;
}