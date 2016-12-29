//
// Created by Jaroslav Hrách on 26.12.16.
//

#include <iostream>
#include "CGenerace.h"

bool compareChromozoms(CChromozom * a, CChromozom * b) {
    return a->getFitness() > b->getFitness();
}

CGenerace::CGenerace(int delkaChromozomu, int velikostPopulace, CVec veci[], int kapacitaBatohu) {
    this->delkaChromozomu = delkaChromozomu;
    this->velikostPopulace = velikostPopulace;
    this->kapacitaBatohu = kapacitaBatohu;
    this->veci = veci;
    for (int i=0;i<velikostPopulace;++i) {
        CChromozom * tmp = new CChromozom(delkaChromozomu);
        tmp->nahodnyChromozom();
        tmp->fitness(veci, kapacitaBatohu);
        this->pridatChromozom(tmp);
    }
    sort (listChromozomu.begin(), listChromozomu.end(), compareChromozoms);
}
CGenerace::~CGenerace() {
    listChromozomu.clear();
}

void CGenerace::pridatChromozom(CChromozom *chromozom) {
    listChromozomu.push_back(chromozom);
}

void CGenerace::evoluce(double pravdepodobnostKrizeni, double pravdepodobnostMutace) {
    selekce();
    krizeni(pravdepodobnostKrizeni);
    mutace(pravdepodobnostMutace);
}

void CGenerace::selekce() {
    vector<CChromozom *> tmpList;
    int sumFitness = 0;
    double pravdepodobnost = 0;
    double nahodneCislo = 0;
    for( vector<CChromozom *>::const_iterator chromozom = listChromozomu.begin(); chromozom != listChromozomu.end(); ++chromozom) {
        sumFitness += (*chromozom)->getFitness() ;
    }

    for (int i = 0; i < velikostPopulace; ++i) {
        nahodneCislo = ((double) rand() / (RAND_MAX));
        for (vector<CChromozom *>::iterator chromozom = listChromozomu.begin(); chromozom != listChromozomu.end(); ++chromozom) {
            pravdepodobnost += (double) (*chromozom)->getFitness() / (double) sumFitness;
            if (nahodneCislo <= pravdepodobnost) {
                CChromozom * tmpChromozom = new CChromozom(delkaChromozomu);
                tmpChromozom->kopie( (*chromozom) );
                tmpChromozom->fitness(veci,kapacitaBatohu);
                tmpList.push_back( tmpChromozom );
                break;
            }
        }
        pravdepodobnost = 0;
    }

    listChromozomu.clear();
    listChromozomu = tmpList;
    sort (listChromozomu.begin(), listChromozomu.end(), compareChromozoms);
}

void CGenerace::krizeni(double pravdepodobnostKrizeni) {
    vector<CChromozom *> tmpList = listChromozomu;
    int pocetKrizeni = (int) (velikostPopulace * pravdepodobnostKrizeni);

    for (int i = 0; i < pocetKrizeni; ++i) {
        int index1 = (int) (rand() % listChromozomu.size());
        int index2 = (int) (rand() % listChromozomu.size());
        int bod = rand() % delkaChromozomu;

        while( index1 == index2 ) {
            index2 = (int) (rand() % listChromozomu.size());
        }
        while ( bod == 0) {
            bod = rand() % delkaChromozomu;
        }

        CChromozom * krizeni1 = new CChromozom(delkaChromozomu);
        CChromozom * krizeni2 = new CChromozom(delkaChromozomu);

        for (int i = 0; i <= bod; ++i) {
            krizeni1->setGen(i,listChromozomu[index1]->getGen(i));
            krizeni2->setGen(i,listChromozomu[index2]->getGen(i));
        }
        for (int i = bod; i < delkaChromozomu; ++i) {
            krizeni1->setGen(i,listChromozomu[index2]->getGen(i));
            krizeni2->setGen(i,listChromozomu[index1]->getGen(i));
        }
        krizeni1->fitness(veci, kapacitaBatohu);
        krizeni2->fitness(veci, kapacitaBatohu);
        tmpList.push_back(krizeni1);
        tmpList.push_back(krizeni2);
    }

    sort (tmpList.begin(), tmpList.end(), compareChromozoms);
    listChromozomu.clear();
    for (int i = 0; i < velikostPopulace; ++i) {
        listChromozomu.push_back(tmpList[i]);
    }
}

void CGenerace::mutace(double pravdepodobnostMutace) {
    for( vector<CChromozom *>::const_iterator chromozom = listChromozomu.begin(); chromozom != listChromozomu.end(); ++chromozom) {
        double nahodneCislo = ((double) rand() / (RAND_MAX));
        int bod = rand() % delkaChromozomu;
        if ( nahodneCislo < pravdepodobnostMutace ) {
            (*chromozom)->setGen(bod, !(*chromozom)->getGen(bod) );
            (*chromozom)->fitness(veci, kapacitaBatohu);
        }
    }
    sort (listChromozomu.begin(), listChromozomu.end(), compareChromozoms);
}

void CGenerace::vypsatGeneraci() {
    int i = 0;
    for( vector<CChromozom *>::const_iterator chromozom = listChromozomu.begin(); chromozom != listChromozomu.end(); ++chromozom) {
        cout << i << ". ";
        (*chromozom)->vypsatGeny();
        cout << '\n';
        ++i;
    }
}

void CGenerace::vypsatNejlepsiReseni() {
    listChromozomu.front()->vypsatGeny();
}

int CGenerace::nejlepsiCena() {
    return listChromozomu.front()->getFitness();
}
