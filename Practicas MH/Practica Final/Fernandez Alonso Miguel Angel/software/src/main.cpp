#include "Relief.h"
#include "BL.h"
#include "Geneticos.h"
#include "Memeticos.h"
#include "MVO.h"

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
		cout << "\t\t\t         MVO         " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarMVO(parts, i, seed);
			media.tasa_clas += resultados.tasa_clas;
			media.tasa_red += resultados.tasa_red;
			media.tiempo += resultados.tiempo;
		}
		cout << "/-------------------------------------------------------------------/" << endl;
		cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
		<< " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
		<< " T: " << media.tiempo/tam << endl << endl;

		//media = {0.0};

		/*cout << "/-*****************************************************************-/" << endl;
		cout << "\t\t\t    Greedy-Relief    " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarRelief(parts, i);
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
		cout << "\t\t\t   Búsqueda Local   " << endl;
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
		cout << "\t\t\t      AGG_BLX      " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarAGG_BLX(parts, i, seed);
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
		cout << "\t\t\t       AGG_CA      " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarAGG_CA(parts, i, seed);
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
		cout << "\t\t\t      AGE_BLX      " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarAGE_BLX(parts, i, seed);
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
		cout << "\t\t\t      AGE_CA      " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarAGE_CA(parts, i, seed);
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
		cout << "\t\t\t    AM_BLX_10_1_0    " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarAM_BLX_10_1_0(parts, i, seed);
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
		cout << "\t\t\t    AM_BLX_10_0_1    " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarAM_BLX_10_0_1(parts, i, seed);
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
		cout << "\t\t\t   AM_BLX_10_0_1_mej   " << endl;
		cout << "/-*****************************************************************-/" << endl;
		for(int i=0; i < parts.size(); i++){
			resultados = ejecutarAM_BLX_10_0_1_mej(parts, i, seed);
			media.tasa_clas += resultados.tasa_clas;
			media.tasa_red += resultados.tasa_red;
			media.tiempo += resultados.tiempo;
		}
		cout << "/-------------------------------------------------------------------/" << endl;
		cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
		<< " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
		<< " T: " << media.tiempo/tam << endl << endl;*/

		for(int i=0; i < parts.size(); ++i)
			casos += parts[i].size();

		cout << "Había " << casos << " casos divididos en " << categorias << " categorias." << endl;
	}

	
  return 0;
}