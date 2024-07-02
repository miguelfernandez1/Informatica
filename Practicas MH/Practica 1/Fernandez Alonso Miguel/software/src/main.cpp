#include "Relief.h"
#include "BL.h"

int main(int argc, char *argv[]){
    int seed;
    double tam = 5.0;

    if(argc == 3){
        vector<vector<FicheroARFF*>> parts;
        vector<FicheroARFF> v;
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

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarKNN(parts, i);
            media.tasa_class += resultados.tasa_class;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------/" << endl;
		cout << "Media:" << " %_clas: " << media.tasa_class/tam << " %_red: " << media.tasa_red/tam
		<< " Agr: " << agregado(media.tasa_class/tam, media.tasa_red/tam)
		<< " T: " << media.tiempo/tam << endl << endl;

        media = {0.0};

        cout << "/-*****************************************************************-/" << endl;
		cout << "\t\t\t    Greedy-Relief    " << endl;
		cout << "/-*****************************************************************-/" << endl;

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarRelief(parts, i);
            media.tasa_class += resultados.tasa_class;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------/" << endl;
		cout << "Media:" << " %_clas: " << media.tasa_class/tam << " %_red: " << media.tasa_red/tam
		<< " Agr: " << agregado(media.tasa_class/tam, media.tasa_red/tam)
		<< " T: " << media.tiempo/tam << endl << endl;

        media = {0.0};

        cout << "/-*****************************************************************-/" << endl;
		cout << "\t\t\t   Búsqueda Local   " << endl;
		cout << "/-*****************************************************************-/" << endl;

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarBL(parts, i, seed);
            media.tasa_class += resultados.tasa_class;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------/" << endl;
		cout << "Media:" << " %_clas: " << media.tasa_class/tam << " %_red: " << media.tasa_red/tam
		<< " Agr: " << agregado(media.tasa_class/tam, media.tasa_red/tam)
		<< " T: " << media.tiempo/tam << endl << endl;

        for(int i = 0; i < parts.size(); i++){
            casos += parts[i].size();
        }

        cout << "Había " << casos << " casos divididos en " << categorias << " categorias." << endl;
    }

    else if(argc == 2){
        vector<FicheroARFF> breast_cancer, ecoli, parkinsons;
        vector<vector<FicheroARFF*>> partsBC, partsECOLI, partsPARK;
        double tiempo = 0.0;
        Resultados resultados;
        seed = stoi(argv[1]);
        string tablas = "./data/tablas_" + to_string(seed) + ".csv";
        Resultados mediaBC = {0.0}, mediaECOLI = {0.0}, mediaPARK = {0.0};

        cout << "Creando tablas...(El proceso puede tardar varios minutos)" << endl;

        ofstream myfile;
        myfile.open(tablas);
        myfile << " ,BREAST-CANCER,,,,ECOLI,,,,PARKINSONS,,,,\n";
        myfile << ",1-NN,,,,1-NN,,,,1-NN\n";
        myfile << " , %tasa_class,%tasa_red,Agr.,T(seg),%tasa_class,%tasa_red,Agr.,T(seg),%tasa_class,%tasa_red,Agr.,T(seg)\n";

        read_csv("./data/csv_result-breast-cancer_1.csv", breast_cancer);
        makePartitions(breast_cancer, partsBC);
        read_csv("./data/csv_result-ecoli_1.csv", breast_cancer);
        makePartitions(ecoli, partsECOLI);
        read_csv("./data/csv_result-parkinsons_1.csv", parkinsons);
        makePartitions(parkinsons, partsPARK);

        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarKNN(partsBC, i);
            myfile << "Particion " << i+1 << "," << resultados.tasa_class << "," << resultados.tasa_red << "," <<
            agregado(resultados.tasa_class, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_class += resultados.tasa_class;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarKNN(partsECOLI, i);
            myfile << "," << resultados.tasa_class << "," << resultados.tasa_red << "," <<
            agregado(resultados.tasa_class, resultados.tasa_red) << "," << resultados.tiempo;
            mediaECOLI.tasa_class += resultados.tasa_class;
            mediaECOLI.tasa_red += resultados.tasa_red;
            mediaECOLI.tiempo += resultados.tiempo;

            resultados = ejecutarKNN(partsPARK, i);
            myfile << "," << resultados.tasa_class << "," << resultados.tasa_red << "," <<
            agregado(resultados.tasa_class, resultados.tasa_red) << "," << resultados.tiempo;
            mediaPARK.tasa_class += resultados.tasa_class;
            mediaPARK.tasa_red += resultados.tasa_red;
            mediaPARK.tiempo += resultados.tiempo;
            
        }

        myfile << "Media:" << "," << mediaBC.tasa_class/tam << "," << mediaBC.tasa_red/tam
        << "," << agregado(mediaBC.tasa_class/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;

        myfile << "," << mediaECOLI.tasa_class/tam << "," << mediaECOLI.tasa_red/tam
        << "," << agregado(mediaECOLI.tasa_class/tam, mediaECOLI.tasa_red/tam)
        << "," << mediaECOLI.tiempo/tam;

        myfile << "," << mediaPARK.tasa_class/tam << "," << mediaPARK.tasa_red/tam
        << "," << agregado(mediaPARK.tasa_class/tam, mediaPARK.tasa_red/tam)
        << "," << mediaPARK.tiempo/tam << endl;

        mediaBC = mediaECOLI = mediaPARK = {0.0};

        myfile << ",Greedy-Relief,,,,Greedy-Relief,,,,Greedy-Relief\n";


        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarRelief(partsBC, i);
            myfile << "Particion " << i+1 << "," << resultados.tasa_class << "," << resultados.tasa_red << "," <<
            agregado(resultados.tasa_class, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_class += resultados.tasa_class;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarRelief(partsECOLI, i);
            myfile << "," << resultados.tasa_class << "," << resultados.tasa_red << "," <<
            agregado(resultados.tasa_class, resultados.tasa_red) << "," << resultados.tiempo;
            mediaECOLI.tasa_class += resultados.tasa_class;
            mediaECOLI.tasa_red += resultados.tasa_red;
            mediaECOLI.tiempo += resultados.tiempo;

            resultados = ejecutarRelief(partsPARK, i);
            myfile << "," << resultados.tasa_class << "," << resultados.tasa_red << "," <<
            agregado(resultados.tasa_class, resultados.tasa_red) << "," << resultados.tiempo;
            mediaPARK.tasa_class += resultados.tasa_class;
            mediaPARK.tasa_red += resultados.tasa_red;
            mediaPARK.tiempo += resultados.tiempo;
        }

        myfile << "Media:" << "," << mediaBC.tasa_class/tam << "," << mediaBC.tasa_red/tam
        << "," << agregado(mediaBC.tasa_class/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;

        myfile << "," << mediaECOLI.tasa_class/tam << "," << mediaECOLI.tasa_red/tam
        << "," << agregado(mediaECOLI.tasa_class/tam, mediaECOLI.tasa_red/tam)
        << "," << mediaECOLI.tiempo/tam;

        myfile << "," << mediaPARK.tasa_class/tam << "," << mediaPARK.tasa_red/tam
        << "," << agregado(mediaPARK.tasa_class/tam, mediaPARK.tasa_red/tam)
        << "," << mediaPARK.tiempo/tam << endl;

        mediaBC = mediaECOLI = mediaPARK = {0.0};

        myfile << ",BL,,,,BL,,,,BL\n";

        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarBL(partsBC, i, seed);
            myfile << "Particion " << i+1 << "," << resultados.tasa_class << "," << resultados.tasa_red << "," <<
            agregado(resultados.tasa_class, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_class += resultados.tasa_class;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarBL(partsECOLI, i, seed);
            myfile << "," << resultados.tasa_class << "," << resultados.tasa_red << "," <<
            agregado(resultados.tasa_class, resultados.tasa_red) << "," << resultados.tiempo;
            mediaECOLI.tasa_class += resultados.tasa_class;
            mediaECOLI.tasa_red += resultados.tasa_red;
            mediaECOLI.tiempo += resultados.tiempo;

            resultados = ejecutarBL(partsPARK, i, seed);
            myfile << "," << resultados.tasa_class << "," << resultados.tasa_red << "," <<
            agregado(resultados.tasa_class, resultados.tasa_red) << "," << resultados.tiempo;
            mediaPARK.tasa_class += resultados.tasa_class;
            mediaPARK.tasa_red += resultados.tasa_red;
            mediaPARK.tiempo += resultados.tiempo;
        }

        myfile << "Media:" << "," << mediaBC.tasa_class/tam << "," << mediaBC.tasa_red/tam
        << "," << agregado(mediaBC.tasa_class/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;

        myfile << "," << mediaECOLI.tasa_class/tam << "," << mediaECOLI.tasa_red/tam
        << "," << agregado(mediaECOLI.tasa_class/tam, mediaECOLI.tasa_red/tam)
        << "," << mediaECOLI.tiempo/tam;

        myfile << "," << mediaPARK.tasa_class/tam << "," << mediaPARK.tasa_red/tam
        << "," << agregado(mediaPARK.tasa_class/tam, mediaPARK.tasa_red/tam)
        << "," << mediaPARK.tiempo/tam << endl;

        myfile.close();
        cout << "Proceso terminado" << endl;

    }

    return 0;
}