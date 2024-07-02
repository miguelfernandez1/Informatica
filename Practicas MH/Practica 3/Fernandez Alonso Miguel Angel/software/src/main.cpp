#include "BMB.h"
#include "ES.h"
#include "ILS.h"
#include "ILS-ES.h"

int main(int argc, char *argv[]) {
	int seed;
	double tam = 5.0;

	if(argc==3){
		vector<FicheroCSV> v;
		vector<vector<FicheroCSV*>> parts;
		int casos = 0;
		int categorias = 0;
		Resultados resultados;
		Resultados media = {0.0};
		seed = stoi(argv[2]);

		read_csv(argv[1], v);
		categorias = makePartitions(v, parts);
		cout << "/-*****************************************************************-/" << endl;
		cout << "\t\t\t         1-NN         " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarKNN(parts, i);
			media.tasa_clas += resultados.tasa_clas;
			media.tasa_red += resultados.tasa_red;
			media.tiempo += resultados.tiempo;
		}
		cout << "/-------------------------------------------------------------------/" << endl;
		cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
		<< " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
		<< " T: " << media.tiempo/tam << endl << endl;

		media = {0.0};

		cout << "/-*****************************************************************-/" << endl;
		cout << "\t\t\t    Búsqueda Local    " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarBL(parts, i, seed);
			media.tasa_clas += resultados.tasa_clas;
			media.tasa_red += resultados.tasa_red;
			media.tiempo += resultados.tiempo;
		}
		cout << "/-------------------------------------------------------------------/" << endl;
		cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
		<< " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
		<< " T: " << media.tiempo/tam << endl << endl;

		media = {0.0};

		cout << "/-*****************************************************************-/" << endl;
		cout << "\t\t    		ES	    " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarES(parts, i, seed);
			media.tasa_clas += resultados.tasa_clas;
			media.tasa_red += resultados.tasa_red;
			media.tiempo += resultados.tiempo;
		}
		cout << "/-------------------------------------------------------------------/" << endl;
		cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
		<< " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
		<< " T: " << media.tiempo/tam << endl << endl;

		media = {0.0};

		cout << "/-*****************************************************************-/" << endl;
		cout << "\t\t    		ILS	    " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarILS(parts, i, seed);
			media.tasa_clas += resultados.tasa_clas;
			media.tasa_red += resultados.tasa_red;
			media.tiempo += resultados.tiempo;
		}
		cout << "/-------------------------------------------------------------------/" << endl;
		cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
		<< " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
		<< " T: " << media.tiempo/tam << endl << endl;

		media = {0.0};

		cout << "/-*****************************************************************-/" << endl;
		cout << "\t\t    		BMB	    " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarBMB(parts, i, seed);
			media.tasa_clas += resultados.tasa_clas;
			media.tasa_red += resultados.tasa_red;
			media.tiempo += resultados.tiempo;
		}
		cout << "/-------------------------------------------------------------------/" << endl;
		cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
		<< " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
		<< " T: " << media.tiempo/tam << endl << endl;

		media = {0.0};

		cout << "/-*****************************************************************-/" << endl;
		cout << "\t    		ILS-ES	    " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarILS_ES(parts, i, seed);
			media.tasa_clas += resultados.tasa_clas;
			media.tasa_red += resultados.tasa_red;
			media.tiempo += resultados.tiempo;
		}
		cout << "/-------------------------------------------------------------------/" << endl;
		cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
		<< " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
		<< " T: " << media.tiempo/tam << endl << endl;

		for(int i=0; i < parts.size(); ++i)
			casos += parts[i].size();

		cout << "Había " << casos << " casos divididos en " << categorias << " categorias." << endl;
	}

    return 0;
}