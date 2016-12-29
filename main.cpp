#include <iostream>
#include <fstream>
#include <sstream>
#include "CVec.h"
#include "CGenerace.h"

#define SOUBOR "knap_40"
#define POCET_INSTANCI 50

using namespace std;

typedef struct {
    int id;
    int n;
    int spravneReseni;
    int vypocitaneReseni;
    float relativniChyba;
} INSTANCE;

int main() {
    ifstream inputFile;
    string fileInst;
    string fileSol;
    string line;
    CVec * veci;

    int id;
    int pocetVeci;
    int kapacitaBatohu;

    int velikostPopulace = 100;
    int pocetGeneraci = 100;
    double pravdepodobnostKrizeni = 0.6;
    double pravdepodobnostMutace = 0.3;

    double timeSum = 0;
    int j = 0;

    INSTANCE instance[POCET_INSTANCI];
    fileInst = (string)"inst/" + SOUBOR + ".inst.dat";
    fileSol = (string)"sol/" + SOUBOR + ".sol.dat";

    inputFile.open( fileInst.c_str() );


    while ( getline(inputFile, line) )
    {
        if ( inputFile.eof() && line.empty() ) break;
        istringstream ss(line);
        ss >> id >> pocetVeci >> kapacitaBatohu;
        veci = new CVec[pocetVeci];

        for(int i=0; i<pocetVeci; i++) {
            ss >> veci[i].vaha >> veci[i].cena;
            veci[i].poradi = i;
        }

        clock_t timeStart = clock();

        CGenerace * generace = new CGenerace(pocetVeci, velikostPopulace, veci, kapacitaBatohu);
        for (int i = 0; i < pocetGeneraci; ++i) {
            generace->evoluce(pravdepodobnostKrizeni, pravdepodobnostMutace);
        }

        cout << id << " " << kapacitaBatohu << " " << generace->nejlepsiCena() << "  ";
        generace->vypsatNejlepsiReseni();

        double duration = ( clock() - timeStart ) / (double) CLOCKS_PER_SEC;
        timeSum += duration;
        instance[j].vypocitaneReseni = generace->nejlepsiCena();
        j++;

        cout << fixed << "  " << duration << endl;
        delete generace;
        delete veci;
    }

    cout << "Průměrný čas jedné instance: " << timeSum / j << endl;

    inputFile.close();


    inputFile.open( fileSol.c_str() );
    j = 0;
    string test;
    while ( getline(inputFile, line) )
    {
        if ( inputFile.eof() && line.empty() ) break;
        istringstream ss(line);
        ss >> instance[j].id >> instance[j].n >> instance[j].spravneReseni;
        j++;
    }

    float avgChyba = 0.0;
    float maxChyba = 0.0;
    for (int i = 0; i< POCET_INSTANCI; i++) {
        if ( instance[i].spravneReseni != instance[i].vypocitaneReseni ) {
            //cout << instance[i].id << "  " << instance[i].spravneReseni << " " << instance[i].vypocitaneReseni << "\t rozdil: " << instance[i].spravneReseni - instance[i].vypocitaneReseni << endl;
        }
        instance[i].relativniChyba = (float)(instance[i].spravneReseni - instance[i].vypocitaneReseni) / (float)instance[i].spravneReseni;
        if( maxChyba < instance[i].relativniChyba ) {
            maxChyba = instance[i].relativniChyba;
        }
        avgChyba += instance[i].relativniChyba;
    }
    avgChyba = (avgChyba / POCET_INSTANCI) * 100 ;
    maxChyba = maxChyba * 100;
    cout << endl;
    cout << avgChyba << endl;
    cout << maxChyba << endl;


    return 0;
}