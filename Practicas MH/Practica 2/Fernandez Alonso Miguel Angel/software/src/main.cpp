#include "Relief.h"
#include "BL.h"
#include "Geneticos.h"
#include "Memeticos.h"

int main(int argc, char *argv[]){
    int seed;
    double tam = 5.0;

    if(argc == 3){
        vector<FicheroCSV> v;
        vector<vector<FicheroCSV*>> parts;
        int casos = 0;
        int categorias = 0;
        Resultados resultados;
        Resultados media = {0.0};
        seed = stoi(argv[2]);

        read_csv(argv[1], v);
        categorias = makePartitions(v, parts);
        cout << "/-****************************************************************************************-/" << endl;
        cout << "\t\t\t         1-NN        " << endl;
        cout << "/-****************************************************************************************-/" << endl;

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarKNN(parts, i);
            media.tasa_clas += resultados.tasa_clas;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------------------------------" << endl;
        cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
        << " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
        << " T: " << media.tiempo/tam << endl << endl;


        media = {0.0};

        cout << "/-****************************************************************************************-/" << endl;
        cout << "\t\t\t         Greedy-Relief        " << endl;
        cout << "/-****************************************************************************************-/" << endl;

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarRelief(parts, i);
            media.tasa_clas += resultados.tasa_clas;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------------------------------" << endl;
        cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
        << " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
        << " T: " << media.tiempo/tam << endl << endl;

        media = {0.0};

        cout << "/-****************************************************************************************-/" << endl;
        cout << "\t\t\t         Búsqueda Local        " << endl;
        cout << "/-****************************************************************************************-/" << endl;

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarBL(parts, i, seed);
            media.tasa_clas += resultados.tasa_clas;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------------------------------" << endl;
        cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
        << " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
        << " T: " << media.tiempo/tam << endl << endl;


        media = {0.0};

        cout << "/-****************************************************************************************-/" << endl;
        cout << "\t\t\t         AGG_BLX        " << endl;
        cout << "/-****************************************************************************************-/" << endl;

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarAGG_BLX(parts, i, seed);
            media.tasa_clas += resultados.tasa_clas;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------------------------------" << endl;
        cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
        << " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
        << " T: " << media.tiempo/tam << endl << endl;

        media = {0.0};


        cout << "/-****************************************************************************************-/" << endl;
        cout << "\t\t\t         AGG_CA        " << endl;
        cout << "/-****************************************************************************************-/" << endl;

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarAGG_CA(parts, i, seed);
            media.tasa_clas += resultados.tasa_clas;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------------------------------" << endl;
        cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
        << " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
        << " T: " << media.tiempo/tam << endl << endl;

        media = {0.0};

        cout << "/-****************************************************************************************-/" << endl;
        cout << "\t\t\t         AGE_BLX        " << endl;
        cout << "/-****************************************************************************************-/" << endl;

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarAGE_BLX(parts, i, seed);
            media.tasa_clas += resultados.tasa_clas;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------------------------------" << endl;
        cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
        << " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
        << " T: " << media.tiempo/tam << endl << endl;


        media = {0.0};

        cout << "/-****************************************************************************************-/" << endl;
        cout << "\t\t\t         AGE_CA        " << endl;
        cout << "/-****************************************************************************************-/" << endl;

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarAGE_CA(parts, i, seed);
            media.tasa_clas += resultados.tasa_clas;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------------------------------" << endl;
        cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
        << " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
        << " T: " << media.tiempo/tam << endl << endl;


        media = {0.0};


        cout << "/-****************************************************************************************-/" << endl;
        cout << "\t\t\t         AM_BLX_10_1_0        " << endl;
        cout << "/-****************************************************************************************-/" << endl;

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarAM_BLX_10_1_0(parts, i, seed);
            media.tasa_clas += resultados.tasa_clas;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------------------------------" << endl;
        cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
        << " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
        << " T: " << media.tiempo/tam << endl << endl;


        media = {0.0};


        cout << "/-****************************************************************************************-/" << endl;
        cout << "\t\t\t         AM_BLX_10_0_1        " << endl;
        cout << "/-****************************************************************************************-/" << endl;

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarAM_BLX_10_0_1(parts, i, seed);
            media.tasa_clas += resultados.tasa_clas;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------------------------------" << endl;
        cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
        << " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
        << " T: " << media.tiempo/tam << endl << endl;


        media = {0.0};

        cout << "/-****************************************************************************************-/" << endl;
        cout << "\t\t\t         AM_BLX_10_0_1_mej        " << endl;
        cout << "/-****************************************************************************************-/" << endl;

        for(int i = 0; i < parts.size(); i++){
            resultados = ejecutarAM_BLX_10_0_1_mej(parts, i, seed);
            media.tasa_clas += resultados.tasa_clas;
            media.tasa_red += resultados.tasa_red;
            media.tiempo += resultados.tiempo;
        }

        cout << "/-------------------------------------------------------------------------------------------" << endl;
        cout << "Media:" << " %_clas: " << media.tasa_clas/tam << " %_red: " << media.tasa_red/tam
        << " Agr: " << agregado(media.tasa_clas/tam, media.tasa_red/tam)
        << " T: " << media.tiempo/tam << endl << endl;


        for(int i = 0; i < parts.size(); i++){
            casos += parts[i].size();
        } 

        cout << "Había " << casos << " casos divididos en " << categorias << " categorías." << endl;

    }

    else if(argc == 2){
        vector<FicheroCSV> breast_cancer, parkinsons, ecoli;
        vector<vector<FicheroCSV*>> partsBC, partsP, partsE;
        double tiempo = 0.0;
        Resultados resultados;
        seed = stoi(argv[1]);
        string tablas = "./data/tablas_" + to_string(seed) + ".csv";
        Resultados mediaP = {0.0}, mediaBC = {0.0}, mediaE = {0.0};

        cout << "Creando tablas....(Esto puede durar varios minutos)" << endl;

        ofstream myfile;
        myfile.open(tablas);
        myfile << " ,BREAST-CANCER,,,,ECOLI,,,,PARKINSONS,,,,\n";
        myfile << ",1-NN,,,,1-NN,,,,1-NN\n";
        myfile << " , %tasa_clas,%tasa_red,Agr.,T(seg),%tasa_clas,%tasa_red,Agr.,T(seg),%tasa_clas,%tasa_red,Agr.,T(seg)\n";

        //read_csv("./data/merged1.csv", breast_cancer);
        read_csv("./data/csv_result-breast-cancer_1.csv", breast_cancer);
        read_csv("./data/csv_result-breast-cancer_2.csv", breast_cancer);
        read_csv("./data/csv_result-breast-cancer_3.csv", breast_cancer);
        read_csv("./data/csv_result-breast-cancer_4.csv", breast_cancer);
        read_csv("./data/csv_result-breast-cancer_5.csv", breast_cancer);
        makePartitions(breast_cancer, partsBC);
        //read_csv("./data/merged2.csv", ecoli);
        read_csv("./datacsv_result-ecoli_1.csv", ecoli);
        read_csv("./datacsv_result-ecoli_2.csv", ecoli);
        read_csv("./datacsv_result-ecoli_3.csv", ecoli);
        read_csv("./datacsv_result-ecoli_4.csv", ecoli);
        read_csv("./datacsv_result-ecoli_5.csv", ecoli);
        makePartitions(ecoli, partsE);
        //read_csv("./data/merged2.csv", parkinsons);
        read_csv("./data/csv_result-parkinsons_1.csv", parkinsons);
        read_csv("./data/csv_result-parkinsons_2.csv", parkinsons);
        read_csv("./data/csv_result-parkinsons_3.csv", parkinsons);
        read_csv("./data/csv_result-parkinsons_4.csv", parkinsons);
        read_csv("./data/csv_result-parkinsons_5.csv", parkinsons);
        makePartitions(parkinsons, partsP);

        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarKNN(partsBC, i);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_clas += resultados.tasa_clas;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarKNN(partsE, i);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaE.tasa_clas += resultados.tasa_clas;
            mediaE.tasa_red += resultados.tasa_red;
            mediaE.tiempo += resultados.tiempo;

            resultados = ejecutarKNN(partsP, i);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaP.tasa_clas += resultados.tasa_clas;
            mediaP.tasa_red += resultados.tasa_red;
            mediaP.tiempo += resultados.tiempo;
        }

        myfile << "Media" << "," << mediaBC.tasa_clas/tam << "," << mediaBC.tasa_red/tam 
        << "," << agregado(mediaBC.tasa_clas/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;
        myfile << "Media" << "," << mediaE.tasa_clas/tam << "," << mediaE.tasa_red/tam 
        << "," << agregado(mediaE.tasa_clas/tam, mediaE.tasa_red/tam)
        << "," << mediaE.tiempo/tam;
        myfile << "Media" << "," << mediaP.tasa_clas/tam << "," << mediaP.tasa_red/tam 
        << "," << agregado(mediaP.tasa_clas/tam, mediaP.tasa_red/tam)
        << "," << mediaP.tiempo/tam;

        mediaBC = mediaE = mediaP = {0.0};

        myfile << ",Greedy-Relief,,,,Greedy-Relief,,,,Greedy-Relief\n";

        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarRelief(partsBC, i);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_clas += resultados.tasa_clas;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarRelief(partsE, i);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaE.tasa_clas += resultados.tasa_clas;
            mediaE.tasa_red += resultados.tasa_red;
            mediaE.tiempo += resultados.tiempo;

            resultados = ejecutarRelief(partsP, i);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaP.tasa_clas += resultados.tasa_clas;
            mediaP.tasa_red += resultados.tasa_red;
            mediaP.tiempo += resultados.tiempo;
        }

        myfile << "Media" << "," << mediaBC.tasa_clas/tam << "," << mediaBC.tasa_red/tam 
        << "," << agregado(mediaBC.tasa_clas/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;
        myfile << "Media" << "," << mediaE.tasa_clas/tam << "," << mediaE.tasa_red/tam 
        << "," << agregado(mediaE.tasa_clas/tam, mediaE.tasa_red/tam)
        << "," << mediaE.tiempo/tam;
        myfile << "Media" << "," << mediaP.tasa_clas/tam << "," << mediaP.tasa_red/tam 
        << "," << agregado(mediaP.tasa_clas/tam, mediaP.tasa_red/tam)
        << "," << mediaP.tiempo/tam;

        mediaBC = mediaE = mediaP = {0.0};

        myfile << ",BL,,,,BL,,,,BL\n";

        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarBL(partsBC, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_clas += resultados.tasa_clas;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarBL(partsE, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaE.tasa_clas += resultados.tasa_clas;
            mediaE.tasa_red += resultados.tasa_red;
            mediaE.tiempo += resultados.tiempo;

            resultados = ejecutarBL(partsP, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaP.tasa_clas += resultados.tasa_clas;
            mediaP.tasa_red += resultados.tasa_red;
            mediaP.tiempo += resultados.tiempo;
        }

        myfile << "Media" << "," << mediaBC.tasa_clas/tam << "," << mediaBC.tasa_red/tam 
        << "," << agregado(mediaBC.tasa_clas/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;
        myfile << "Media" << "," << mediaE.tasa_clas/tam << "," << mediaE.tasa_red/tam 
        << "," << agregado(mediaE.tasa_clas/tam, mediaE.tasa_red/tam)
        << "," << mediaE.tiempo/tam;
        myfile << "Media" << "," << mediaP.tasa_clas/tam << "," << mediaP.tasa_red/tam 
        << "," << agregado(mediaP.tasa_clas/tam, mediaP.tasa_red/tam)
        << "," << mediaP.tiempo/tam;

        mediaBC = mediaE = mediaP = {0.0};

        myfile << ",AGG_BLX,,,,AGG_BLX,,,,AGG_BLX\n";


        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarAGG_BLX(partsBC, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_clas += resultados.tasa_clas;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarAGG_BLX(partsE, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaE.tasa_clas += resultados.tasa_clas;
            mediaE.tasa_red += resultados.tasa_red;
            mediaE.tiempo += resultados.tiempo;

            resultados = ejecutarAGG_BLX(partsP, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaP.tasa_clas += resultados.tasa_clas;
            mediaP.tasa_red += resultados.tasa_red;
            mediaP.tiempo += resultados.tiempo;
        }

        myfile << "Media" << "," << mediaBC.tasa_clas/tam << "," << mediaBC.tasa_red/tam 
        << "," << agregado(mediaBC.tasa_clas/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;
        myfile << "Media" << "," << mediaE.tasa_clas/tam << "," << mediaE.tasa_red/tam 
        << "," << agregado(mediaE.tasa_clas/tam, mediaE.tasa_red/tam)
        << "," << mediaE.tiempo/tam;
        myfile << "Media" << "," << mediaP.tasa_clas/tam << "," << mediaP.tasa_red/tam 
        << "," << agregado(mediaP.tasa_clas/tam, mediaP.tasa_red/tam)
        << "," << mediaP.tiempo/tam;

        mediaBC = mediaE = mediaP = {0.0};

        myfile << ",AGG_CA,,,,AGG_CA,,,,AGG_CA\n";


        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarAGG_CA(partsBC, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_clas += resultados.tasa_clas;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarAGG_CA(partsE, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaE.tasa_clas += resultados.tasa_clas;
            mediaE.tasa_red += resultados.tasa_red;
            mediaE.tiempo += resultados.tiempo;

            resultados = ejecutarAGG_CA(partsP, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaP.tasa_clas += resultados.tasa_clas;
            mediaP.tasa_red += resultados.tasa_red;
            mediaP.tiempo += resultados.tiempo;
        }

        myfile << "Media" << "," << mediaBC.tasa_clas/tam << "," << mediaBC.tasa_red/tam 
        << "," << agregado(mediaBC.tasa_clas/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;
        myfile << "Media" << "," << mediaE.tasa_clas/tam << "," << mediaE.tasa_red/tam 
        << "," << agregado(mediaE.tasa_clas/tam, mediaE.tasa_red/tam)
        << "," << mediaE.tiempo/tam;
        myfile << "Media" << "," << mediaP.tasa_clas/tam << "," << mediaP.tasa_red/tam 
        << "," << agregado(mediaP.tasa_clas/tam, mediaP.tasa_red/tam)
        << "," << mediaP.tiempo/tam;

        mediaBC = mediaE = mediaP = {0.0};

        myfile << ",AGE_BLX,,,,AGE_BLX,,,,AGE_BLX\n";


        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarAGE_BLX(partsBC, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_clas += resultados.tasa_clas;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarAGE_BLX(partsE, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaE.tasa_clas += resultados.tasa_clas;
            mediaE.tasa_red += resultados.tasa_red;
            mediaE.tiempo += resultados.tiempo;

            resultados = ejecutarAGE_BLX(partsP, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaP.tasa_clas += resultados.tasa_clas;
            mediaP.tasa_red += resultados.tasa_red;
            mediaP.tiempo += resultados.tiempo;
        }

        myfile << "Media" << "," << mediaBC.tasa_clas/tam << "," << mediaBC.tasa_red/tam 
        << "," << agregado(mediaBC.tasa_clas/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;
        myfile << "Media" << "," << mediaE.tasa_clas/tam << "," << mediaE.tasa_red/tam 
        << "," << agregado(mediaE.tasa_clas/tam, mediaE.tasa_red/tam)
        << "," << mediaE.tiempo/tam;
        myfile << "Media" << "," << mediaP.tasa_clas/tam << "," << mediaP.tasa_red/tam 
        << "," << agregado(mediaP.tasa_clas/tam, mediaP.tasa_red/tam)
        << "," << mediaP.tiempo/tam;

        mediaBC = mediaE = mediaP = {0.0};

        myfile << ",AGE_CA,,,,AGE_CA,,,,AGE_CA\n";

        
        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarAGE_CA(partsBC, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_clas += resultados.tasa_clas;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarAGE_CA(partsE, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaE.tasa_clas += resultados.tasa_clas;
            mediaE.tasa_red += resultados.tasa_red;
            mediaE.tiempo += resultados.tiempo;

            resultados = ejecutarAGE_CA(partsP, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaP.tasa_clas += resultados.tasa_clas;
            mediaP.tasa_red += resultados.tasa_red;
            mediaP.tiempo += resultados.tiempo;
        }

        myfile << "Media" << "," << mediaBC.tasa_clas/tam << "," << mediaBC.tasa_red/tam 
        << "," << agregado(mediaBC.tasa_clas/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;
        myfile << "Media" << "," << mediaE.tasa_clas/tam << "," << mediaE.tasa_red/tam 
        << "," << agregado(mediaE.tasa_clas/tam, mediaE.tasa_red/tam)
        << "," << mediaE.tiempo/tam;
        myfile << "Media" << "," << mediaP.tasa_clas/tam << "," << mediaP.tasa_red/tam 
        << "," << agregado(mediaP.tasa_clas/tam, mediaP.tasa_red/tam)
        << "," << mediaP.tiempo/tam;

        mediaBC = mediaE = mediaP = {0.0};

        myfile << ",AM_BLX(10,1.0),,,,AM_BLX(10,1.0),,,,AM_BLX(10,1.0)\n";


        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarAM_BLX_10_1_0(partsBC, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_clas += resultados.tasa_clas;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarAM_BLX_10_1_0(partsE, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaE.tasa_clas += resultados.tasa_clas;
            mediaE.tasa_red += resultados.tasa_red;
            mediaE.tiempo += resultados.tiempo;

            resultados = ejecutarAM_BLX_10_1_0(partsP, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaP.tasa_clas += resultados.tasa_clas;
            mediaP.tasa_red += resultados.tasa_red;
            mediaP.tiempo += resultados.tiempo;
        }

        myfile << "Media" << "," << mediaBC.tasa_clas/tam << "," << mediaBC.tasa_red/tam 
        << "," << agregado(mediaBC.tasa_clas/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;
        myfile << "Media" << "," << mediaE.tasa_clas/tam << "," << mediaE.tasa_red/tam 
        << "," << agregado(mediaE.tasa_clas/tam, mediaE.tasa_red/tam)
        << "," << mediaE.tiempo/tam;
        myfile << "Media" << "," << mediaP.tasa_clas/tam << "," << mediaP.tasa_red/tam 
        << "," << agregado(mediaP.tasa_clas/tam, mediaP.tasa_red/tam)
        << "," << mediaP.tiempo/tam;

        mediaBC = mediaE = mediaP = {0.0};

        myfile << ",AM_BLX(10,0.1),,,,AM_BLX(10,0.1),,,,AM_BLX(10,0.1)\n";


        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarAM_BLX_10_0_1(partsBC, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_clas += resultados.tasa_clas;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarAM_BLX_10_0_1(partsE, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaE.tasa_clas += resultados.tasa_clas;
            mediaE.tasa_red += resultados.tasa_red;
            mediaE.tiempo += resultados.tiempo;

            resultados = ejecutarAM_BLX_10_0_1(partsP, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaP.tasa_clas += resultados.tasa_clas;
            mediaP.tasa_red += resultados.tasa_red;
            mediaP.tiempo += resultados.tiempo;
        }

        myfile << "Media" << "," << mediaBC.tasa_clas/tam << "," << mediaBC.tasa_red/tam 
        << "," << agregado(mediaBC.tasa_clas/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;
        myfile << "Media" << "," << mediaE.tasa_clas/tam << "," << mediaE.tasa_red/tam 
        << "," << agregado(mediaE.tasa_clas/tam, mediaE.tasa_red/tam)
        << "," << mediaE.tiempo/tam;
        myfile << "Media" << "," << mediaP.tasa_clas/tam << "," << mediaP.tasa_red/tam 
        << "," << agregado(mediaP.tasa_clas/tam, mediaP.tasa_red/tam)
        << "," << mediaP.tiempo/tam;

        mediaBC = mediaE = mediaP = {0.0};

        myfile << ",AM_BLX(10,0.1)_MEJ,,,,AM_BLX(10,0.1)_MEJ,,,,AM_BLX(10,0.1)_MEJ\n";


        for(int i = 0; i < partsBC.size(); i++){
            resultados = ejecutarAM_BLX_10_0_1_mej(partsBC, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaBC.tasa_clas += resultados.tasa_clas;
            mediaBC.tasa_red += resultados.tasa_red;
            mediaBC.tiempo += resultados.tiempo;

            resultados = ejecutarAM_BLX_10_0_1_mej(partsE, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaE.tasa_clas += resultados.tasa_clas;
            mediaE.tasa_red += resultados.tasa_red;
            mediaE.tiempo += resultados.tiempo;

            resultados = ejecutarAM_BLX_10_0_1_mej(partsP, i, seed);
            myfile << "Partición " << i+1 << "," << resultados.tasa_clas << "," << resultados.tasa_red << "," << 
            agregado(resultados.tasa_clas, resultados.tasa_red) << "," << resultados.tiempo;
            mediaP.tasa_clas += resultados.tasa_clas;
            mediaP.tasa_red += resultados.tasa_red;
            mediaP.tiempo += resultados.tiempo;
        }

        myfile << "Media" << "," << mediaBC.tasa_clas/tam << "," << mediaBC.tasa_red/tam 
        << "," << agregado(mediaBC.tasa_clas/tam, mediaBC.tasa_red/tam)
        << "," << mediaBC.tiempo/tam;
        myfile << "Media" << "," << mediaE.tasa_clas/tam << "," << mediaE.tasa_red/tam 
        << "," << agregado(mediaE.tasa_clas/tam, mediaE.tasa_red/tam)
        << "," << mediaE.tiempo/tam;
        myfile << "Media" << "," << mediaP.tasa_clas/tam << "," << mediaP.tasa_red/tam 
        << "," << agregado(mediaP.tasa_clas/tam, mediaP.tasa_red/tam)
        << "," << mediaP.tiempo/tam;

        myfile.close();
        cout << "Proceso terminado." << endl;


    }

    return 0;
}